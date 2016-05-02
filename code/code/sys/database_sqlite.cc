#ifdef DB_SQLITE
#include "database.h"

#include "enum.h"
#include "extern.h"
#include "sstring.h"
#include "timing.h"

#include <boost/algorithm/string/replace.hpp>
#include <sqlite3.h>

#include <iostream>
#include <map>
#include <stdarg.h>

std::vector <std::string> db_hosts(DB_MAX);
std::vector <std::string> db_names(DB_MAX);
std::vector <std::string> db_users(DB_MAX);
std::vector <std::string> db_passwords(DB_MAX);

const char * db_connect[DB_MAX] = {
  "sneezy",
  "immortal",
};


namespace {
  class debug {
    public:
      debug() { buf << ">>> DB: "; std::cout << ">>> DB: "; }
      template<typename T>
      debug& operator<<(T t) {
        buf << t;
        std::cout << t;
        return *this;
      };
      std::string str() { return buf.str(); }
      ~debug() { std::cout << std::endl; }
    protected:
      std::ostringstream buf;
  };

  struct error : public debug {
      ~error() {
        std::cout << std::endl;
        void closeAllDbs();
        closeAllDbs();
        throw std::runtime_error(buf.str());
      }
  };

  std::string getDbName(dbTypeT type)
  {
    assert(type >= 0);
    assert(type < DB_MAX);
    if (db_names[type] != "")
      return db_names[type] + ".db";
    return std::string(db_connect[type]) + ".db";
  }

  // One per sqlite .db file, owns the .db and wraps the calls to SQLite
  // long-lived, survives many queries, therefore shouldn't save transient state. State goes into pimpl.
  // owns the SQLite3 db object
  class TDBConnection
  {
    public:
      TDBConnection(dbTypeT tdb)
        : db(nullptr)
        , name(getDbName(tdb))
      {
        debug() << "sqlite3_open " << name;
        if (sqlite3_open(name.c_str(), &db))
          error() << "Cannot open DB " << name << ": " << sqlite3_errmsg(db);
      }

      // must run after all queries are closed
      ~TDBConnection() {
        assert(db);
        debug() << "sqlite3_close " << name << ": " << sqlite3_close(db);
      }

      long lastInsertId() {
        return sqlite3_last_insert_rowid(db);
      }

      void getColumnNames(sqlite3_stmt* stmt, std::vector<std::string>& columnNames) {
        for (int i = 0; i < sqlite3_column_count(stmt); ++i)
          columnNames.push_back(sqlite3_column_name(stmt, i));
      }

      const char* lastError() {
        assert(db);
        return sqlite3_errmsg(db);
      }

      int rowCount() {
        assert(db);
        return sqlite3_changes(db);
      }

      int step(sqlite3_stmt* stmt) {
        assert(db);
        assert(stmt);
        int ret = sqlite3_step(stmt);
        debug() << "... step " << ret << "=" << sqlite3_errmsg(db);
        switch (ret) {
          case SQLITE_DONE:
          case SQLITE_ROW:
            return ret;
          default:
            error() << "Step failed with " << ret << ": " << sqlite3_errmsg(db);
            return ret;
        }
      }

      sqlite3_stmt* prepare(const char* query) {
        assert(db);
        assert(query);
        sqlite3_stmt* stmt;
        // We can optimize away these prepares by memoizing in a map --
        // however, some queries are created dynamically by concatenating
        // stuff. These can be excluded from memoization by passing a sstring
        // in, not const char*. The remaining then would be indexable by
        // pointer value.
        debug() << "sqlite3_prepare_v2 " << query;
        if (sqlite3_prepare_v2(db, query, -1, &stmt, nullptr) || stmt == nullptr)
          error() << "prepare failed: " << sqlite3_errmsg(db);
        return stmt;
      }

      void getVals(sqlite3_stmt* stmt, std::vector<std::string>& out) {
        assert(out.empty());
        assert(db);
        assert(stmt);
        int cols = sqlite3_column_count(stmt);
        for (int i = 0; i < cols; ++i) {
          const unsigned char* text = sqlite3_column_text(stmt, i); // yay unsigned char
          std::string ts = text ? reinterpret_cast<const char*>(text) : "";
          boost::replace_all(ts, "\\n", "\n"); // Which other chars are there?
          boost::replace_all(ts, "\\r", ""); // Which other chars are there?
          out.push_back(ts);
        }
      }

      void bindArgs(sqlite3_stmt* stmt, std::vector<StringOrIntOrDouble> const& args) {
        assert(db);
        int argpos = 1; // yes, sqlite counts args from 1
        long ival;
        double dval;
        for (auto& i : args) {
          switch (i.getType()) {
            case StringOrIntOrDouble::STRING:
              debug() << i.getStr();
              sqlite3_bind_text(stmt, argpos, i.getStr(), -1, nullptr);
              break;
            case StringOrIntOrDouble::INT:
              ival = i.getInt();
              debug() << ival;
              sqlite3_bind_int64(stmt, argpos, ival);
              break;
            case StringOrIntOrDouble::DOUBLE:
              dval = i.getDouble();
              debug() << dval;
              sqlite3_bind_double(stmt, argpos, dval);
              break;
            default:
              error() << "corrupted arg type in db query";
          }
          ++argpos;
        }
        assert(argpos == args.size() + 1);
      }

    private:
      sqlite3* db;
      const std::string name; // for logging only
  };

  // to avoid opening and closing the DBs on every query
  std::map<dbTypeT, TDBConnection> open_dbs;

  TDBConnection& createOrOpen(dbTypeT type)
  {
    {
      debug() << "create or open " << type << "=" << getDbName(type);
    }
    auto it = open_dbs.find(type);
    if (it == open_dbs.end())
    {
      debug() << "didn't find DB in map, creating";
      auto ret = open_dbs.emplace(
          std::piecewise_construct,
          std::forward_as_tuple(type),
          std::forward_as_tuple(type));
      return ret.first->second;
    }
    return it->second;
  }

  void closeAllDbs()
  {
    debug() << "emergency shutdown, closing all DBs";
    open_dbs.clear();
  }
}

// Doesn't own the .db file
// Holds the results of the query
class TDatabasePimpl
{
  public:
    TDatabasePimpl(TDBConnection& db)
      : db(db)
      , prev_step_ret(-1) // not a valid SQLITE return code
      , stmt(nullptr)
      , rowCount(0)
    {}

    ~TDatabasePimpl() {
      if (stmt) {
        debug() << "sqlite3_finalize";
        sqlite3_finalize(stmt);
      }
    }

    void reset() {
      res.clear();
      columnNames.clear();
      prev_step_ret = -1;
      if (stmt) {
        debug() << "sqlite3_finalize";
        sqlite3_finalize(stmt);
      }
      rowCount = 0;
    }

    TDBConnection& db;
    std::vector<std::string> res;
    std::vector<std::string> columnNames;
    int prev_step_ret;
    sqlite3_stmt* stmt; // temporarily initialized while the DB is being queried. At other times, nullptr.
    int rowCount;
};

TDatabase::TDatabase(dbTypeT tdb)
  : pimpl(new TDatabasePimpl(createOrOpen(tdb)))
{}

TDatabase::~TDatabase()
{
  delete pimpl;
}

long TDatabase::lastInsertId() {
  return pimpl->db.lastInsertId();
}

bool TDatabase::fetchRow() {
  { debug() << "fetchRow"; }
  switch (pimpl->prev_step_ret) {
    case SQLITE_DONE: {
      debug() << "... done";
      pimpl->res.clear();
      return false;
    }
    case SQLITE_ROW: {
      debug() << "... more";
      pimpl->res.clear();
      pimpl->db.getVals(pimpl->stmt, pimpl->res);
      pimpl->prev_step_ret = pimpl->db.step(pimpl->stmt);
      return true;
    }
    default:
      error() << "Step failed with " << pimpl->prev_step_ret << ": " << pimpl->db.lastError();
      return false;
  }
}

const sstring TDatabase::operator[] (unsigned int i) const {
  if (i >= pimpl->res.size())
    error() << "Out-of-range access " << i;
  return pimpl->res[i];
}

const sstring TDatabase::operator[] (const sstring &s) const {
  // on last step, res is cleared, because some code depends on [] returning empty result on end
  assert(pimpl->res.empty() || pimpl->columnNames.size() == pimpl->res.size());
  if (pimpl->res.empty())
    return "";
  auto it = std::find(pimpl->columnNames.begin(), pimpl->columnNames.end(), s.lower());
  if (it == pimpl->columnNames.end())
    error() << "Accessed invalid column name " << s.lower();
  debug() << "col " << s.lower() << " idx " << it - pimpl->columnNames.begin() << " val " << pimpl->res[it - pimpl->columnNames.begin()];
  return pimpl->res[it - pimpl->columnNames.begin()];
}

bool TDatabase::queryInner(const char *query, std::vector<StringOrIntOrDouble> args) {
  TTiming t;
  t.start();

  // clear the results from any previous query()
  pimpl->reset();

  std::string q = query;
  // TODO: some queries are '%s' and some are '%%%s%%'. Are there any others?
  boost::replace_all(q, "'%s'", "?");  // TODO: there are some places where encode gets called manually and then the result is stuck into %s -- do they encode twice?
  boost::replace_all(q, "%s", "?");  // TODO: there are some places where encode gets called manually and then the result is stuck into %s -- do they encode twice?
  boost::replace_all(q, "%r", "TODO remove raw queries");
  boost::replace_all(q, "%i", "?");
  boost::replace_all(q, "%f", "?");
  boost::replace_all(q, "%%", "%");
  { debug() << "DB query: \n" << query << "\n" << q; }
  pimpl->stmt = pimpl->db.prepare(q.c_str());

  pimpl->db.bindArgs(pimpl->stmt, args);

  // execute first step ASAP to protect inserts/updates against bugs later on
  pimpl->prev_step_ret = pimpl->db.step(pimpl->stmt);
  pimpl->rowCount = pimpl->db.rowCount();
  if (pimpl->prev_step_ret == SQLITE_ROW)
    pimpl->db.getVals(pimpl->stmt, pimpl->res);

  pimpl->db.getColumnNames(pimpl->stmt, pimpl->columnNames);
  assert(pimpl->prev_step_ret == SQLITE_DONE || pimpl->columnNames.size() == pimpl->res.size());

  t.end();
  if(t.getElapsed() > 1.0){
    vlogf(LOG_DB, format("Query took %f seconds.") % t.getElapsed());
    vlogf(LOG_DB, format("%s") % query);
  }

  /*
  // this saves the queries (without args) and the execution time
  // it slows things down pretty significantly though
  if(toggleInfo.isLoaded() && toggleInfo[TOG_DBTIMING]->toggle){
    query=qsave;
    buf="";

    // escape ' and %
    while(*query){
      if(*query == '\'' || *query == '%'){
        buf += "\\";
      }
      buf += *query++;
    }

    buf = format("insert into querytimes (query, secs) values ('%s', %f)") % 
      buf % t.getElapsed();

    mysql_query(pimpl->db, buf.c_str());
  }
  */
  return true;
}

bool TDatabase::isResults(){
  return pimpl->res.size() > 0;
}

long TDatabase::rowCount(){
  // return # of affected or retrieved rows
  // -1 if query returned an error

  // this gets set in TDatabase::query
  // because the db pointer will have changed state if query timing is on
  return pimpl->rowCount;
}
#endif
