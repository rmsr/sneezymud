#include "handler.h"
#include "being.h"
#include "client.h"
#include "low.h"
#include "charfile.h"
#include "extern.h"
#include "mail.h"
#include "database.h"
#include "shop.h"
#include "monster.h"
#include "shopowned.h"
#include "rent.h"
#include "obj_trap.h"
#include "obj_open_container.h"
#include "spec_mobs.h"

// may not exceed NAME_SIZE (15) chars
static const char * const SNEEZY_ADMIN = "SneezyMUD Administration";

int mail_ok(TBeing *ch)
{
  if (no_mail) {
    ch->sendTo("Sorry, the mail system is having technical difficulties.\n\r");
    return FALSE;
  }
  return TRUE;
}

bool TObj::canBeMailed() const
{
  return !isObjStat(ITEM_ATTACHED) && !isObjStat(ITEM_NORENT) &&
          !isObjStat(ITEM_BURNING) && !isObjStat(ITEM_PROTOTYPE) &&
          !isObjStat(ITEM_NOPURGE) && !isObjStat(ITEM_NEWBIE) &&
          !isObjStat(ITEM_NODROP) && !isMonogrammed() && stuff.empty() &&
          !dynamic_cast<const TTrap*>(this) &&
          (!dynamic_cast<const TOpenContainer*>(this) ||
          !dynamic_cast<const TOpenContainer*>(this)->isContainerFlag(CONT_TRAPPED));
}

bool has_mail(const sstring recipient)
{
  TDatabase db(DB_SNEEZY);

  db.query("select count(*) as count from mail where port=%i and lower(mailto)=lower('%s')", gamePort, recipient.c_str());

  if(db.fetchRow() && convertTo<int>(db["count"]) != 0)
    return TRUE;

  return FALSE;
}

void store_mail(const char *to, const char *from, const char *message_pointer, int talens, int rent_id)
{
  TDatabase db(DB_SNEEZY);
  time_t mail_time;
  char *tmstr;

  mail_time=time(0);
  tmstr = asctime(localtime(&mail_time));
  *(tmstr + strlen(tmstr) - 1) = '\0';


  if(!strcmp(to, "faction")){
    TDatabase fm(DB_SNEEZY);
    fm.query("select name from factionmembers where faction=(select faction from factionmembers where name='%s')", from);
    
    while(fm.fetchRow()){
      db.query("insert into mail (port, mailfrom, mailto, timesent, content, talens, rent_id) values (%i, '%s', '%s', '%s', '%s', 0, 0)", gamePort, from, fm["name"].c_str(), tmstr, message_pointer);
    }
  } else {
    db.query("insert into mail (port, mailfrom, mailto, timesent, content, talens, rent_id) values (%i, '%s', '%s', '%s', '%s', %i, %i)", gamePort, from, to, tmstr, message_pointer, talens, rent_id);
  }
}                               /* store mail */

sstring read_delete(const sstring recipient, const char *recipient_formatted, sstring &from, int & talens, int & rent_id)
{
  TDatabase db(DB_SNEEZY);
  sstring buf;

  db.query("select mailfrom, timesent, content, mailid, talens, rent_id from mail where port=%i and lower(mailto)=lower('%s')", gamePort, recipient.c_str());
  if(!db.fetchRow())
    return "error!";

  from=db["mailfrom"];
  talens=convertTo<int>(db["talens"]);
  rent_id=convertTo<int>(db["rent_id"]);

  buf=format("The letter has a date stamped in the corner: %s\n\r\n\r%s,\n\r%s\n\rSigned, %s\n\r\n\r") %
    db["timesent"] % recipient_formatted % db["content"] % db["mailfrom"];

  db.query("delete from mail where mailid=%s", db["mailid"].c_str());
  
  return sstring(buf);
}

void postmasterValue(TBeing *ch, TBeing *postmaster, const char *arg)
{
  sstring args = arg, item, talen;
  int shop_nr = find_shop_nr(postmaster->number);
  float profit_buy = shop_index[shop_nr].getProfitBuy(NULL, ch);

  if (!mail_ok(ch))
    return;

  args = one_argument(args, item);
  args = one_argument(args, talen);

  if (is_abbrev(item, sstring("talens")) || is_abbrev(talen, sstring("talens")))
  {
    postmaster->doTell(fname(ch->name), format("When sending talens, I charge an additional %d talens for handling fees.") % int((float)STAMP_PRICE * profit_buy * 2));
    return;
  }

  if(item == "faction")
  {
    postmaster->doTell(fname(ch->name), format("Bulk faction mail from me will cost about %d talens.") % int((float)FACTION_STAMP_PRICE * profit_buy));
    return;
  }

  if (item.length() > 0)
  {
    TThing *thing = get_thing_on_list_vis(ch, item.c_str(), ch->stuff.front());
    TObj *obj = thing ? dynamic_cast<TObj*>(thing) : NULL;
    if (obj == NULL)
    {
      postmaster->doTell(fname(ch->name), "I don't see that item on you.");
      return;
    }
    if (!obj->canBeMailed())
    {
      postmaster->doTell(fname(ch->name), "Sorry, I can't ship that.");
      return;
    }
    postmaster->doTell(fname(ch->name), format("Shipping %s will cost you %d talens.") % obj->getName() %
      int((float)STAMP_PRICE * profit_buy * (obj->getWeight() + 3)));
    return;
  }

  postmaster->doTell(fname(ch->name), format("My price for regular postage is %d talens.") % int((float)STAMP_PRICE * profit_buy));
}


int postmaster(TBeing *ch, cmdTypeT cmd, const char *arg, TMonster *myself, TObj *)
{
  if (!ch->desc)
    return FALSE;               /* so mobs don't get caught here */

  switch (cmd) {
    case CMD_WHISPER:
      return shopWhisper(ch, myself, find_shop_nr(myself->number), arg);    
    case CMD_MAIL: 
      ch->postmasterSendMail(arg, myself);
      return TRUE;
    case CMD_CHECK: 
      ch->postmasterCheckMail(myself);
      return TRUE;
    case CMD_RECEIVE:
      ch->postmasterReceiveMail(myself);
      return TRUE;
    case CMD_VALUE:
      postmasterValue(ch, myself, arg);
      return TRUE;
    default:
      return FALSE;
  }
}

void TBeing::postmasterSendMail(const char *arg, TMonster *me)
{
  sstring args = arg, item, recipient, talen;
  charFile st;
  bool sendFaction;
  int i, imm = FALSE, amt, shop_nr=find_shop_nr(me->number);
  float profit_buy = 0;

// added this check - bat
  if (!mail_ok(this))
    return;

  if (!*arg) {
    me->doTell(getName(), "You need to specify an addressee!");
    return;
  }
  
  args = one_argument(args, recipient);
  args = one_argument(args, item);
  args = one_argument(args, talen);

  if (parse_name_sstring(recipient, recipient)) {
    sendTo("Illegal name, please try another.\n\r");
    return;
  }
  recipient = recipient.lower();
  sendFaction = recipient == "faction";

  if (recipient == "faction" && !load_char(recipient, &st)) {
    sendTo("No such player to mail to!\n\r");
    return;
  }
  imm = isImmortal();

  for (i = 0;!imm && i < 8; i++)
    if (st.level[i] > MAX_MORT)
      imm = TRUE;

  // let anybody mail to immortals
  if (GetMaxLevel() < MIN_MAIL_LEVEL && !imm) {
    me->doTell(getName(), format("Sorry, you have to be level %d to send mail!") % MIN_MAIL_LEVEL);
    return;
  }

  profit_buy = shop_index[shop_nr].getProfitBuy(NULL, this);

  if(sendFaction){
    if(getFaction() == FACT_NONE){
      me->doTell(fname(name), "You aren't in a faction!");
      return;
    }

    amt = (int)((float)FACTION_STAMP_PRICE * profit_buy);

    if(getMoney() < amt && !imm){
      me->doTell(fname(name), format("Bulk mailing costs %d talens.") % amt);
      me->doTell(fname(name), "...which I see you can't afford.");
      return;
    }
  // sending talens
  } else if (is_abbrev(talen, sstring("talens"))) {

    amt = (int)((float)STAMP_PRICE * profit_buy * 2);
    int talen_amt = convertTo<int>(item);

    if (talen_amt < 0) {
      me->doTell(fname(name), "What?! That's not a monetary amount.");
      return;
    }
    if (talen_amt + amt > getMoney()) {
      me->doTell(fname(name), format("Mailing %d talens plus a stamp costs a total of %d talens.") % talen_amt % (talen_amt + amt));
      me->doTell(fname(name), "...which I see you can't afford.");
      return;
    }
    desc->amount = max(0, talen_amt);

  // sending item
  } else if (item.length() > 0) {

    TThing *thing = searchLinkedListVis(this, item.c_str(), stuff, NULL, TYPEOBJ);
    TObj *obj = thing ? dynamic_cast<TObj*>(thing) : NULL;
    if (obj == NULL) {
      me->doTell(fname(name), "I don't see that item on you.");
      return;
    }

    amt = (int)((float)STAMP_PRICE * profit_buy * (obj->getWeight() + 3));
    if (amt > getMoney() && !imm) {
      me->doTell(fname(name), format("Mailing this item plus a stamp costs a total of %d talens.") % amt);
      me->doTell(fname(name), "...which I see you can't afford.");
      return;
    }

    // check for item flags that will stop the deal
    if (!obj->canBeMailed()) {
      me->doTell(fname(name), "You can't mail that item!");
      return;
    }

    desc->obj = obj;

  } else {
    amt = (int)((float)STAMP_PRICE * profit_buy);

    if (getMoney() < amt && !imm) {
      me->doTell(fname(name), format("A stamp costs %d talens.") % amt);
      me->doTell(fname(name), "...which I see you can't afford.");
      return;
    }
  }

  act("$n starts to write some mail.", TRUE, this, 0, 0, TO_ROOM);
  if (!imm) {
    me->doTell(fname(name), format("I'll take %d talens for the stamp.") % amt);
    TShopOwned tso(shop_nr, me, this);
    tso.doBuyTransaction(amt, format("mailing %s") % recipient, TX_BUYING_SERVICE);
  } else if (isImmortal()) {
    me->doTell(fname(name), "Since you're high and mighty, I'll waive the fee.");
  } else {
    me->doTell(fname(name), "Since you're mailing an immortal, I'll waive the fee.");
  }

  if (!desc->m_bIsClient) {
    me->doTell(fname(name), "Write your message, use ~ when done, or ` to cancel.");
    addPlayerAction(PLR_MAILING);
    desc->connected = CON_WRITING;
    strncpy(desc->name, recipient.c_str(), cElements(desc->name));

    desc->str = new const char *('\0');
    desc->max_str = MAX_MAIL_SIZE;
  } else
    desc->clientf(format("%d|%s") % CLIENT_MAIL % recipient);
}


void TBeing::postmasterCheckMail(TMonster *me)
{
  char recipient[100], *tmp;

  _parse_name(getName(), recipient);

// added this check - bat
  if (!mail_ok(this))
    return;

  for (tmp = recipient; *tmp; tmp++)
    if (isupper(*tmp))
      *tmp = tolower(*tmp);

  if (has_mail(recipient))
    me->doTell(getName(), "You have mail waiting.");
  else
    me->doTell(getName(), "Sorry, you don't have any mail waiting.");

}

void TBeing::postmasterReceiveMail(TMonster *me)
{
  sstring recipient;
  TObj *note, *envelope;
  sstring msg;
  sstring from;

  if (parse_name_sstring(sstring(getName()), recipient))
    return;

  // added this check - bat
  if (!mail_ok(this))
    return;

  recipient = recipient.lower();

  if (!has_mail(recipient)) {
    me->doTell(fname(name), "Sorry, you don't have any mail waiting.");
    return;
  }
  while (has_mail(recipient)) {
    int talens = 0;
    int rent_id = 0;
    int env_vnum = 124;

    // builder port uses stripped down database which was causing problems
    // hence this setup instead.
    int robj = real_object(GENERIC_NOTE);
    if (robj < 0 || robj >= (signed int) obj_index.size()) {
      vlogf(LOG_BUG, format("postmasterReceiveMail(): No object (%d) in database!") %  
            GENERIC_NOTE);
      return;
    }

    if (!(note = read_object(robj, REAL))) {
      vlogf(LOG_BUG, "Couldn't make a note for mail!");
      return;
    }

    note->swapToStrung();
    delete [] note->name;
    note->name = mud_str_dup("letter mail");
    delete [] note->shortDescr;
    note->shortDescr = mud_str_dup("<o>a handwritten <W>letter<1>"); 
    delete [] note->getDescr();
    note->setDescr(mud_str_dup("A wrinkled <W>letter<1> lies here."));
    delete [] note->action_description;
    msg = read_delete(recipient, getName(), from, talens, rent_id);
    note->action_description = mud_str_dup(msg.c_str());
    if (!note->action_description)
      note->action_description = mud_str_dup("Mail system buggy, please report!!  Error #8.\n\r");

    if (talens >= 1000 || rent_id > 0)
      env_vnum = 6600; // crate

    int env_robj = real_object(env_vnum);
    if (env_robj < 0 || env_robj >= (signed int) obj_index.size() ||
      !(envelope = read_object(env_robj, REAL))) {
      vlogf(LOG_BUG, "Couldn't load envelope object!");
      return;
    }
    
    envelope->addObjStat(ITEM_NEWBIE);
    envelope->addObjStat(ITEM_NORENT);

    *envelope += *note;

    if (talens > 0)
    {
      vlogf(LOG_OBJ, format("Mail: %s receiving %i talens from %s") %
          getName() % talens % from);
      *envelope += *create_money(talens);
    }

    if (rent_id > 0)
    {
      TObj *obj = NULL;
      int slot = -1;
      ItemLoadDB il("mail", GH_MAIL_SHOP);
      TDatabase db(DB_SNEEZY);

      obj = il.raw_read_item(rent_id, slot);
      db.query("delete from rent where rent_id=%i", rent_id);
      db.query("delete from rent_obj_aff where rent_id=%i", rent_id);
      db.query("delete from rent_strung where rent_id=%i", rent_id);

      if (obj)
      {
        vlogf(LOG_OBJ, format("Mail: retrieved object %s from rent_id:%i from mail for %s from %s") %
          obj->getName() % rent_id % getName() % from);
        *envelope += *obj;
      }
      else
      {
        vlogf(LOG_BUG, format("Mail: error retrieving rent_id:%i from mail for %s from %s") %
          rent_id % getName() % from);
      }
    }

    *this += *envelope;

    act(format("$n gives you $p from %s.") % from, FALSE, me, envelope, this, TO_VICT);
    act("$N gives $n $p.", FALSE, this, envelope, me, TO_ROOM);
  }
}

void autoMail(TBeing *ch, const char *targ, const char *msg)
{
  // from field limited to 15 chars by mail structure

  if (ch)
    store_mail(ch->getName(), SNEEZY_ADMIN, msg, 0, 0);
  else if (targ)
    store_mail(targ, SNEEZY_ADMIN, msg, 0, 0);
  else
    vlogf(LOG_BUG, "Error in autoMail");

  return;
}

