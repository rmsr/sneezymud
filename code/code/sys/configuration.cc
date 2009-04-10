#include <iostream>
#include <fstream>

#include "stdsneezy.h"
#include "configuration.h"
#include "database.h"

#include <boost/program_options.hpp>
namespace po = boost::program_options;

const int PROD_GAMEPORT = 7900;
const int PROD_XMLPORT = 7901;
const int BETA_GAMEPORT = 5678;
const int ALPHA_GAMEPORT = 6969;
const int BUILDER_GAMEPORT = 8900;
      int GAMMA_GAMEPORT = 6961; // Maror - quick boot! (skips zones) -Updated to allow otf swapping -Lapsos
const int ITEM_DAMAGE_RATE = 1;
const int RENT_CREDIT_VAL = 75;
const bool RENT_SELL_TO_PAWN = false;
const bool RENT_RESTRICT_INNS_BY_LEVEL = false;
const int WEAPON_DAM_MIN_HARDNESS = 20;
const int WEAPON_DAM_MAX_HARDNESS = 150;
const int WEAPON_DAM_MAX_SHARP = 150;
const bool NUKE_REPAIR_ITEMS=true;
const bool CHECK_MULTIPLAY=true;
const bool FORCE_MULTIPLAY_COMPLIANCE=true;
const bool REPO_MOBS=true;
const bool SUPER_REPO_MOBS=false;
const bool NO_DAMAGED_ITEMS_SHOP=false;
const bool PENALIZE_FOR_AUTO_RENTING=true;
const bool SPEEF_MAKE_BODY=false;


void sendHelp(po::options_description desc){
  cout << "Usage: sneezy [options] [port]" << endl;
  cout << desc;  
}

bool doConfiguration(int argc, char *argv[])
{
  string configFile="sneezy.cfg";

  // command line only options
  po::options_description cmdline("Command line only");
  cmdline.add_options()
    ("help", "produce help message")
    ("config,c", po::value<string>(&configFile)->default_value("sneezy.cfg"),
     "configuration file to use")
    ;

  // command line OR in config file
  po::options_description config("Configuration");
  config.add_options()
    ("lib,l", po::value<string>(&dir)->default_value(DFLT_DIR), 
     "data directory to run in")
    ("nospecials,s", po::value<bool>(&noSpecials)->zero_tokens(),
     "suppress assignment of special routines")
    ("trimmed,t", po::value<bool>(&bTrimmed)->zero_tokens(),
     "load as trimmed port")
    ("port,p", po::value<int>(&gamePort)->default_value(PROD_GAMEPORT),
     "game port")
    ;

  // database options
  po::options_description databases("Databases");
  databases.add_options()
    ("sneezy_db", po::value<string>(&db_hosts[DB_SNEEZY]),
     "host for sneezy database")
    ("sneezybeta_db", po::value<string>(&db_hosts[DB_SNEEZYBETA]),
     "host for sneezybeta database (unused)")
    ("immortal_db", po::value<string>(&db_hosts[DB_IMMORTAL]),
     "host for immortal database")
    ("sneezyglobal_db", po::value<string>(&db_hosts[DB_SNEEZYGLOBAL]),
     "host for sneezyglobal database")
    ("sneezyprod_db", po::value<string>(&db_hosts[DB_SNEEZYPROD]),
     "host for sneezyprod database (unused)")
    ("sneezybuilder_db", po::value<string>(&db_hosts[DB_SNEEZYBUILDER]),
     "host for sneezybuilder database (unused)")
    ("wiki_mortal_db", po::value<string>(&db_hosts[DB_WIKI_MORTAL]),
     "host for mortal wiki database")
    ("wiki_builder_db", po::value<string>(&db_hosts[DB_WIKI_BUILDER]),
     "host for builder wiki database")
    ("wiki_admin_db", po::value<string>(&db_hosts[DB_WIKI_ADMIN]),
     "host for admin wiki database")
    ("forums_admin_db", po::value<string>(&db_hosts[DB_FORUMS_ADMIN]),
     "host for admin forums database")
    ;

  po::options_description cmdline_options;
  cmdline_options.add(cmdline).add(config).add(databases);

  po::options_description config_options;
  config_options.add(config).add(databases);

  po::options_description visible("Allowed options");
  visible.add(cmdline).add(config).add(databases);


  // first positional argument is port number
  po::positional_options_description p;
  p.add("port", -1);
  
  po::variables_map vm;


  try {
    if(argc){
      po::store(po::command_line_parser(argc, argv).
		options(cmdline_options).positional(p).run(), vm);
    }
    po::notify(vm);
    ifstream ifs(configFile.c_str());

    po::store(parse_config_file(ifs, config_options), vm);
    po::notify(vm);
  } catch(po::unknown_option){
    sendHelp(visible);
    return false;    
  }

  if(vm.count("help")){
    sendHelp(visible);
    return false;
  }
  return true;
}
