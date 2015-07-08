from django.db import models

# Create your models here.
# This is an auto-generated Django model module.
# You'll have to do the following manually to clean this up:
#   * Rearrange models' order
#   * Make sure each model has one field with primary_key=True
# Feel free to rename the models, but don't rename db_table values or field names.
#
# Also note: You'll have to insert the output of 'django-admin.py sqlcustom [app_label]'
# into your database.

from django.db import models


class Account(models.Model):
    account_id = models.BigIntegerField(primary_key=True)
    email = models.CharField(max_length=80, blank=True)
    passwd = models.CharField(max_length=13, blank=True)
    name = models.CharField(max_length=80, blank=True) # TODO indexed
    birth = models.IntegerField(blank=True, null=True)
    term = models.IntegerField(blank=True, null=True)
    time_adjust = models.IntegerField(blank=True, null=True)
    flags = models.IntegerField(blank=True, null=True)
    last_logon = models.IntegerField(blank=True, null=True)

    class Meta:
        db_table = 'account'


class Blockedlist(models.Model):
    # TODO no primary key
    player_id = models.IntegerField(blank=True, null=True)
    blocked = models.CharField(max_length=33, blank=True)

    class Meta:
        db_table = 'blockedlist'


class BoardMessage(models.Model):
    # TODO no primary key
    board_vnum = models.IntegerField() # TODO indexed with date_removed
    post_num = models.IntegerField(blank=True, null=True)
    date_posted = models.DateTimeField()
    date_removed = models.DateTimeField(blank=True, null=True)
    subject = models.CharField(max_length=80, blank=True)
    author = models.CharField(max_length=80, blank=True)
    post = models.TextField(blank=True)

    class Meta:
        db_table = 'board_message'


class Brickquest(models.Model):
    # TODO no primary key
    numbricks = models.IntegerField(blank=True, null=True)
    name = models.CharField(max_length=30)

    class Meta:
        db_table = 'brickquest'


class Cgisession(models.Model):
    # TODO no primary key
    session_id = models.CharField(max_length=32, blank=True)
    account_id = models.IntegerField(blank=True, null=True)
    duration = models.IntegerField(blank=True, null=True)
    timeset = models.IntegerField(blank=True, null=True)
    name = models.CharField(max_length=32, blank=True)

    class Meta:
        db_table = 'cgisession'


class Commodprices(models.Model):
    # TODO no primary key
    logtime = models.DateTimeField()
    shop_nr = models.IntegerField(blank=True, null=True)
    material = models.IntegerField(blank=True, null=True)
    price = models.FloatField(blank=True, null=True)

    class Meta:
        db_table = 'commodprices'


class Corpaccess(models.Model):
    # TODO no primary key
    corp_id = models.IntegerField()
    access = models.IntegerField()
    player_id = models.IntegerField(blank=True, null=True)
    name = models.CharField(max_length=80, blank=True)

    class Meta:
        db_table = 'corpaccess'


class Corplog(models.Model):
    # TODO no primary key
    corp_id = models.IntegerField(blank=True, null=True)
    name = models.CharField(max_length=80, blank=True)
    action = models.CharField(max_length=80, blank=True)
    talens = models.IntegerField(blank=True, null=True)
    corptalens = models.IntegerField(blank=True, null=True)
    logtime = models.DateTimeField()

    class Meta:
        db_table = 'corplog'


class Corporation(models.Model):
    # TODO no primary key
    corp_id = models.BigIntegerField(primary_key=True)
    name = models.CharField(max_length=80)
    bank = models.IntegerField(blank=True, null=True)

    class Meta:
        db_table = 'corporation'


class DrugUse(models.Model):
    # TODO no primary key
    drug_id = models.IntegerField(blank=True, null=True)
    player_id = models.IntegerField(blank=True, null=True) # TODO indexed
    first_use_sec = models.IntegerField(blank=True, null=True)
    first_use_min = models.IntegerField(blank=True, null=True)
    first_use_hour = models.IntegerField(blank=True, null=True)
    first_use_day = models.IntegerField(blank=True, null=True)
    first_use_mon = models.IntegerField(blank=True, null=True)
    first_use_year = models.IntegerField(blank=True, null=True)
    last_use_sec = models.IntegerField(blank=True, null=True)
    last_use_min = models.IntegerField(blank=True, null=True)
    last_use_hour = models.IntegerField(blank=True, null=True)
    last_use_day = models.IntegerField(blank=True, null=True)
    last_use_mon = models.IntegerField(blank=True, null=True)
    last_use_year = models.IntegerField(blank=True, null=True)
    total_consumed = models.IntegerField(blank=True, null=True)
    current_consumed = models.IntegerField(blank=True, null=True)

    class Meta:
        db_table = 'drug_use'


class Factionmembers(models.Model):
    # TODO no primary key
    name = models.CharField(max_length=80)
    faction = models.CharField(max_length=8, blank=True)
    level = models.IntegerField(blank=True, null=True)

    class Meta:
        db_table = 'factionmembers'


class Factoryblueprint(models.Model):
    # TODO no primary key
    vnum = models.IntegerField(blank=True, null=True)
    supplytype = models.IntegerField(blank=True, null=True)
    supplyamt = models.IntegerField(blank=True, null=True)

    class Meta:
        db_table = 'factoryblueprint'


class Factoryproducing(models.Model):
    # TODO no primary key
    shop_nr = models.IntegerField(blank=True, null=True)
    vnum = models.IntegerField(blank=True, null=True)

    class Meta:
        db_table = 'factoryproducing'


class Factorysupplies(models.Model):
    # TODO no primary key
    shop_nr = models.IntegerField(blank=True, null=True)
    supplytype = models.IntegerField(blank=True, null=True)
    supplyname = models.CharField(max_length=16, blank=True)
    supplyamt = models.IntegerField(blank=True, null=True)

    class Meta:
        db_table = 'factorysupplies'


class Fishkeeper(models.Model):
    # TODO no primary key
    name = models.CharField(max_length=80) # TODO indexed
    weight = models.FloatField(blank=True, null=True)

    class Meta:
        db_table = 'fishkeeper'


class Fishlargest(models.Model):
    # TODO no primary key
    name = models.CharField(max_length=80, blank=True)
    vnum = models.IntegerField(blank=True, null=True) # TODO indexed
    weight = models.FloatField(blank=True, null=True)

    class Meta:
        db_table = 'fishlargest'


class Gamblers(models.Model):
    # TODO no primary key
    player_id = models.IntegerField()
    money = models.IntegerField(blank=True, null=True)

    class Meta:
        db_table = 'gamblers'


class Globaltoggles(models.Model):
    # TODO no primary key
    tog_id = models.IntegerField()
    toggle = models.IntegerField(blank=True, null=True)
    testcode = models.IntegerField(blank=True, null=True)
    name = models.CharField(max_length=80, blank=True)
    descr = models.CharField(max_length=256, blank=True)

    class Meta:
        db_table = 'globaltoggles'


class ImmortalExchangeCoin(models.Model):
    # TODO no primary key
    k_coin = models.IntegerField() # TODO indexed
    created_by = models.IntegerField(blank=True, null=True)
    created_for = models.IntegerField(blank=True, null=True)
    redeemed_by = models.IntegerField(blank=True, null=True)
    redeemed_for = models.IntegerField(blank=True, null=True)
    date_created = models.DateTimeField(blank=True, null=True)
    date_redeemed = models.DateTimeField(blank=True, null=True)
    utility_flag = models.IntegerField(blank=True, null=True)

    class Meta:
        db_table = 'immortal_exchange_coin'


class Itemtypes(models.Model):
    # TODO no primary key
    type = models.IntegerField(blank=True, null=True)
    name = models.CharField(max_length=32, blank=True)

    class Meta:
        db_table = 'itemtypes'


class Lowtasks(models.Model):
    # implicit primary key
    priority = models.IntegerField(blank=True, null=True)
    assigned_to = models.CharField(max_length=80, blank=True)
    task = models.TextField(blank=True)
    status = models.CharField(max_length=80, blank=True)

    class Meta:
        db_table = 'lowtasks'


class Mail(models.Model):
    mailid = models.BigIntegerField(primary_key=True)
    port = models.IntegerField(blank=True, null=True)
    mailfrom = models.CharField(max_length=80, blank=True)
    mailto = models.CharField(max_length=80, blank=True)
    timesent = models.CharField(max_length=32, blank=True)
    content = models.CharField(max_length=4000, blank=True)
    talens = models.IntegerField(blank=True, null=True)
    rent_id = models.IntegerField(blank=True, null=True)

    class Meta:
        db_table = 'mail'


class Material(models.Model):
    # TODO no primary key
    num = models.IntegerField(blank=True, null=True)
    name = models.CharField(max_length=32, blank=True)

    class Meta:
        db_table = 'material'


class Mob(models.Model):
    vnum = models.IntegerField(primary_key=True)
    name = models.CharField(max_length=127)
    short_desc = models.CharField(max_length=127)
    long_desc = models.CharField(max_length=255)
    description = models.TextField()
    actions = models.IntegerField()
    affects = models.IntegerField()
    faction = models.IntegerField()
    fact_perc = models.IntegerField()
    letter = models.CharField(max_length=1)
    attacks = models.FloatField()
    class_field = models.IntegerField(db_column='class')  # Field renamed because it was a Python reserved word.
    level = models.IntegerField()
    tohit = models.IntegerField()
    ac = models.FloatField()
    hpbonus = models.FloatField()
    damage_level = models.FloatField()
    damage_precision = models.IntegerField()
    gold = models.IntegerField()
    race = models.IntegerField()
    weight = models.IntegerField()
    height = models.IntegerField()
    str = models.IntegerField()
    bra = models.IntegerField()
    con = models.IntegerField()
    dex = models.IntegerField()
    agi = models.IntegerField()
    intel = models.IntegerField()
    wis = models.IntegerField()
    foc = models.IntegerField()
    per = models.IntegerField()
    cha = models.IntegerField()
    kar = models.IntegerField()
    spe = models.IntegerField()
    pos = models.IntegerField()
    def_position = models.IntegerField()
    sex = models.IntegerField()
    spec_proc = models.IntegerField()
    skin = models.IntegerField()
    vision = models.IntegerField()
    can_be_seen = models.IntegerField()
    max_exist = models.IntegerField()
    local_sound = models.CharField(max_length=255, blank=True)
    adjacent_sound = models.CharField(max_length=255, blank=True)

    class Meta:
        db_table = 'mob'


class MobExtra(models.Model):
    # TODO no primary key
    vnum = models.IntegerField() # TODO unique index with keyword
    keyword = models.CharField(max_length=32)
    description = models.CharField(max_length=255, blank=True)

    class Meta:
        db_table = 'mob_extra'


class MobImm(models.Model):
    # TODO no primary key
    vnum = models.IntegerField() # TODO unique index with type
    type = models.IntegerField()
    amt = models.IntegerField(blank=True, null=True)

    class Meta:
        db_table = 'mob_imm'


class Mobresponses(models.Model):
    # TODO no primary key
    vnum = models.IntegerField() # TODO indexed
    response = models.TextField()

    class Meta:
        db_table = 'mobresponses'


class Obj(models.Model):
    vnum = models.IntegerField(primary_key=True)
    name = models.CharField(max_length=127)
    short_desc = models.CharField(max_length=127)
    long_desc = models.CharField(max_length=255)
    action_desc = models.CharField(max_length=255)
    type = models.IntegerField()
    action_flag = models.IntegerField()
    wear_flag = models.IntegerField()
    val0 = models.IntegerField()
    val1 = models.IntegerField()
    val2 = models.IntegerField()
    val3 = models.IntegerField()
    weight = models.FloatField()
    price = models.IntegerField()
    can_be_seen = models.IntegerField()
    spec_proc = models.IntegerField()
    max_exist = models.IntegerField()
    max_struct = models.IntegerField()
    cur_struct = models.IntegerField()
    decay = models.IntegerField()
    volume = models.IntegerField()
    material = models.IntegerField()

    class Meta:
        db_table = 'obj'


class ObjLoadMinLevel(models.Model):
    # TODO no primary key
    obj_vnum = models.IntegerField(blank=True, null=True)
    mob_vnum = models.IntegerField(blank=True, null=True)
    mob_level = models.IntegerField(blank=True, null=True)

    class Meta:
        db_table = 'obj_load_min_level'


class Objaffect(models.Model):
    # TODO no primary key
    vnum = models.IntegerField()
    type = models.IntegerField()
    mod1 = models.IntegerField()
    mod2 = models.IntegerField()

    class Meta:
        db_table = 'objaffect'


class Objextra(models.Model):
    # TODO no primary key
    vnum = models.IntegerField()
    name = models.CharField(max_length=127)
    description = models.TextField()

    class Meta:
        db_table = 'objextra'


class Objlog(models.Model):
    # TODO no primary key
    vnum = models.IntegerField()
    loadtime = models.DateTimeField()
    objcount = models.IntegerField()

    class Meta:
        db_table = 'objlog'


class Permadeath(models.Model):
    # TODO no primary key
    name = models.CharField(max_length=80)
    level = models.IntegerField(blank=True, null=True)
    died = models.IntegerField(blank=True, null=True)
    killer = models.CharField(max_length=80, blank=True)

    class Meta:
        db_table = 'permadeath'


class Pet(models.Model):
    # TODO no primary key
    player_id = models.IntegerField(blank=True, null=True)
    vnum = models.IntegerField(blank=True, null=True)
    exp = models.FloatField(blank=True, null=True)
    name = models.CharField(max_length=32, blank=True)
    level = models.IntegerField(blank=True, null=True)

    class Meta:
        db_table = 'pet'


class Pings(models.Model):
    # TODO no primary key
    host = models.TextField(blank=True)
    pingtime = models.FloatField(blank=True, null=True)

    class Meta:
        db_table = 'pings'


class Player(models.Model):
    # implicit primary key
    name = models.CharField(unique=True, max_length=80, blank=True) # TODO indexed with account_id
    talens = models.IntegerField(blank=True, null=True)
    title = models.CharField(max_length=80, blank=True)
    account_id = models.IntegerField(blank=True, null=True)
    guild_id = models.IntegerField(blank=True, null=True)
    guildrank = models.IntegerField(blank=True, null=True)
    load_room = models.IntegerField(blank=True, null=True)
    last_logon = models.IntegerField(blank=True, null=True)
    nutrition = models.IntegerField(blank=True, null=True)

    class Meta:
        db_table = 'player'


class Playerprompt(models.Model):
    # TODO no primary key
    player_id = models.IntegerField(blank=True, null=True) # TODO indexed
    p_type = models.IntegerField(blank=True, null=True)
    hp = models.CharField(max_length=20, blank=True)
    mana = models.CharField(max_length=20, blank=True)
    move = models.CharField(max_length=20, blank=True)
    money = models.CharField(max_length=20, blank=True)
    exp = models.CharField(max_length=20, blank=True)
    room = models.CharField(max_length=20, blank=True)
    opp = models.CharField(max_length=20, blank=True)
    tank = models.CharField(max_length=20, blank=True)
    piety = models.CharField(max_length=20, blank=True)
    lifeforce = models.CharField(max_length=20, blank=True)
    time = models.CharField(max_length=20, blank=True)

    class Meta:
        db_table = 'playerprompt'


class Poll(models.Model):
    # TODO no primary key
    poll_id = models.IntegerField()
    descr = models.CharField(max_length=127, blank=True)
    status = models.CharField(max_length=8, blank=True)

    class Meta:
        db_table = 'poll'


class PollOption(models.Model):
    # TODO no primary key
    option_id = models.IntegerField()
    poll_id = models.IntegerField()
    descr = models.CharField(max_length=127, blank=True)

    class Meta:
        db_table = 'poll_option'


class PollVote(models.Model):
    # TODO no primary key
    account = models.CharField(max_length=80)
    poll_id = models.IntegerField()
    option_id = models.IntegerField()

    class Meta:
        db_table = 'poll_vote'


class Property(models.Model):
    # implicit primary key
    name = models.CharField(max_length=80, blank=True)
    owner = models.IntegerField(blank=True, null=True)
    key_vnum = models.IntegerField(blank=True, null=True)
    entrance = models.IntegerField(blank=True, null=True)

    class Meta:
        db_table = 'property'


class Querytimes(models.Model):
    # TODO no primary key
    query = models.CharField(max_length=512, blank=True)
    secs = models.FloatField(blank=True, null=True)
    date_logged = models.DateTimeField()

    class Meta:
        db_table = 'querytimes'


class QuestLimbs(models.Model):
    # TODO no primary key
    player = models.CharField(max_length=80)
    team = models.CharField(max_length=30, blank=True)
    mob_vnum = models.IntegerField()
    slot_num = models.IntegerField()
    slot_name = models.CharField(max_length=127, blank=True)
    date_submitted = models.DateTimeField()

    class Meta:
        db_table = 'quest_limbs'


class QuestLimbsTeam(models.Model):
    # TODO no primary key
    team = models.CharField(max_length=30, blank=True)
    player = models.CharField(max_length=80)

    class Meta:
        db_table = 'quest_limbs_team'


class Rent(models.Model):
    rent_id = models.IntegerField(primary_key=True)
    owner_type = models.CharField(max_length=6, blank=True)
    owner = models.IntegerField()
    slot = models.IntegerField()
    vnum = models.IntegerField()
    container = models.IntegerField()
    val0 = models.IntegerField()
    val1 = models.IntegerField()
    val2 = models.IntegerField()
    val3 = models.IntegerField()
    extra_flags = models.IntegerField()
    weight = models.FloatField(blank=True, null=True)
    bitvector = models.IntegerField()
    decay = models.IntegerField()
    cur_struct = models.IntegerField()
    max_struct = models.IntegerField()
    material = models.IntegerField()
    volume = models.IntegerField()
    price = models.IntegerField()
    depreciation = models.IntegerField()

    class Meta:
        db_table = 'rent'


class RentObjAff(models.Model):
    # TODO no primary key
    rent_id = models.IntegerField() # TODO indexed
    type = models.IntegerField()
    level = models.IntegerField()
    duration = models.IntegerField()
    renew = models.IntegerField()
    modifier = models.IntegerField()
    location = models.IntegerField()
    modifier2 = models.IntegerField()
    bitvector = models.IntegerField()

    class Meta:
        db_table = 'rent_obj_aff'


class RentStrung(models.Model):
    # TODO no primary key
    rent_id = models.IntegerField() # TODO indexed
    name = models.CharField(max_length=127)
    short_desc = models.CharField(max_length=127)
    long_desc = models.CharField(max_length=255)
    action_desc = models.CharField(max_length=255)

    class Meta:
        db_table = 'rent_strung'


class Room(models.Model):
    vnum = models.IntegerField(primary_key=True)
    x = models.IntegerField()
    y = models.IntegerField()
    z = models.IntegerField()
    name = models.CharField(max_length=127)
    description = models.TextField()
    zone = models.IntegerField()
    room_flag = models.IntegerField()
    sector = models.IntegerField()
    teletime = models.IntegerField()
    teletarg = models.IntegerField()
    telelook = models.IntegerField()
    river_speed = models.IntegerField()
    river_dir = models.IntegerField()
    capacity = models.IntegerField()
    height = models.IntegerField()
    spec = models.IntegerField()

    class Meta:
        db_table = 'room'


class Roomexit(models.Model):
    # TODO no primary key
    vnum = models.IntegerField() # TODO indexed
    direction = models.IntegerField()
    name = models.CharField(max_length=127)
    description = models.TextField()
    type = models.IntegerField()
    condition_flag = models.IntegerField()
    lock_difficulty = models.IntegerField()
    weight = models.IntegerField()
    key_num = models.IntegerField()
    destination = models.IntegerField()

    class Meta:
        db_table = 'roomexit'


class Roomextra(models.Model):
    # TODO no primary key
    vnum = models.IntegerField() # TODO indexed
    name = models.TextField()
    description = models.TextField()

    class Meta:
        db_table = 'roomextra'


class ShipDestinations(models.Model):
    # TODO no primary key
    vnum = models.IntegerField(blank=True, null=True) # TODO indexed
    name = models.CharField(max_length=32, blank=True)
    room = models.IntegerField(blank=True, null=True)

    class Meta:
        db_table = 'ship_destinations'


class ShipMaster(models.Model):
    # TODO no primary key
    captain_vnum = models.IntegerField() # TODO indexed
    account_id = models.IntegerField(blank=True, null=True)
    player_id = models.IntegerField(blank=True, null=True)

    class Meta:
        db_table = 'ship_master'


class Shop(models.Model):
    shop_nr = models.IntegerField(primary_key=True)
    profit_buy = models.FloatField()
    profit_sell = models.FloatField()
    no_such_item1 = models.CharField(max_length=127)
    no_such_item2 = models.CharField(max_length=127)
    do_not_buy = models.CharField(max_length=127)
    missing_cash1 = models.CharField(max_length=127)
    missing_cash2 = models.CharField(max_length=127)
    message_buy = models.CharField(max_length=127)
    message_sell = models.CharField(max_length=127)
    temper1 = models.IntegerField()
    temper2 = models.IntegerField()
    keeper = models.IntegerField()
    flags = models.IntegerField()
    in_room = models.IntegerField()
    open1 = models.IntegerField()
    close1 = models.IntegerField()
    open2 = models.IntegerField()
    close2 = models.IntegerField()
    expense_ratio = models.FloatField(blank=True, null=True)

    class Meta:
        db_table = 'shop'


class Shopgoldtmp(models.Model):
    # TODO no primary key
    shop_nr = models.IntegerField(blank=True, null=True)
    gold = models.IntegerField(blank=True, null=True)

    class Meta:
        db_table = 'shopgoldtmp'


class Shoplog(models.Model):
    # TODO no primary key
    shop_nr = models.IntegerField(blank=True, null=True) # TODO indexed
    name = models.CharField(max_length=80, blank=True) # TODO indexed
    action = models.CharField(max_length=32, blank=True)
    item = models.CharField(max_length=80, blank=True)
    talens = models.IntegerField(blank=True, null=True)
    shoptalens = models.IntegerField(blank=True, null=True)
    shopvalue = models.IntegerField(blank=True, null=True)
    logtime = models.DateTimeField()
    itemcount = models.IntegerField(blank=True, null=True)

    class Meta:
        db_table = 'shoplog'


class Shoplogaccountchart(models.Model):
    # TODO no primary key
    post_ref = models.IntegerField(blank=True, null=True)
    name = models.TextField(blank=True)

    class Meta:
        db_table = 'shoplogaccountchart'


class Shoplogarchive(models.Model):
    # TODO no primary key
    shop_nr = models.IntegerField(blank=True, null=True)
    name = models.CharField(max_length=80, blank=True)
    action = models.CharField(max_length=32, blank=True)
    item = models.CharField(max_length=80, blank=True)
    talens = models.IntegerField(blank=True, null=True)
    shoptalens = models.IntegerField(blank=True, null=True)
    shopvalue = models.IntegerField(blank=True, null=True)
    logtime = models.DateTimeField()
    itemcount = models.IntegerField(blank=True, null=True)

    class Meta:
        db_table = 'shoplogarchive'


class Shoplogcogs(models.Model):
    # TODO no primary key
    shop_nr = models.IntegerField(blank=True, null=True)
    obj_name = models.CharField(max_length=128, blank=True)
    count = models.IntegerField(blank=True, null=True)
    total_cost = models.IntegerField(blank=True, null=True)

    class Meta:
        db_table = 'shoplogcogs'


class Shoplogjournal(models.Model):
    # TODO no primary key
    shop_nr = models.IntegerField(blank=True, null=True) # TODO indexed with sneezy_year
    journal_id = models.IntegerField() # TODO indexed
    customer_name = models.TextField(blank=True)
    obj_name = models.TextField(blank=True)
    logtime = models.DateTimeField()
    post_ref = models.IntegerField(blank=True, null=True)
    debit = models.IntegerField(blank=True, null=True)
    credit = models.IntegerField(blank=True, null=True)
    sneezy_year = models.IntegerField(blank=True, null=True)

    class Meta:
        db_table = 'shoplogjournal'


class Shoplogjournalarchive(models.Model):
    # TODO no primary key
    shop_nr = models.IntegerField(blank=True, null=True) # TODO indexed with sneezy_year
    journal_id = models.IntegerField()
    customer_name = models.TextField(blank=True)
    obj_name = models.TextField(blank=True)
    logtime = models.DateTimeField()
    post_ref = models.IntegerField(blank=True, null=True)
    debit = models.IntegerField(blank=True, null=True)
    credit = models.IntegerField(blank=True, null=True)
    sneezy_year = models.IntegerField(blank=True, null=True)

    class Meta:
        db_table = 'shoplogjournalarchive'


class Shopmaterial(models.Model):
    # TODO no primary key
    shop_nr = models.IntegerField()
    mat_type = models.IntegerField()

    class Meta:
        db_table = 'shopmaterial'


class Shopowned(models.Model):
    shop_nr = models.IntegerField(primary_key=True)
    profit_buy = models.FloatField()
    profit_sell = models.FloatField()
    max_num = models.IntegerField(blank=True, null=True)
    corp_id = models.IntegerField(blank=True, null=True)
    dividend = models.FloatField(blank=True, null=True)
    reserve_max = models.IntegerField(blank=True, null=True)
    reserve_min = models.IntegerField(blank=True, null=True)
    no_such_item1 = models.CharField(max_length=127, blank=True)
    no_such_item2 = models.CharField(max_length=127, blank=True)
    do_not_buy = models.CharField(max_length=127, blank=True)
    missing_cash1 = models.CharField(max_length=127, blank=True)
    missing_cash2 = models.CharField(max_length=127, blank=True)
    message_buy = models.CharField(max_length=127, blank=True)
    message_sell = models.CharField(max_length=127, blank=True)
    tax_nr = models.IntegerField(blank=True, null=True)
    gold = models.IntegerField(blank=True, null=True)

    class Meta:
        db_table = 'shopowned'


class Shopownedaccess(models.Model):
    # TODO no primary key
    shop_nr = models.IntegerField()
    name = models.CharField(max_length=80)
    access = models.IntegerField()

    class Meta:
        db_table = 'shopownedaccess'


class Shopownedauction(models.Model):
    # TODO no primary key
    shop_nr = models.IntegerField(blank=True, null=True)
    ticket = models.IntegerField(blank=True, null=True)
    bidder = models.IntegerField(blank=True, null=True)
    buyout = models.IntegerField(blank=True, null=True)
    days = models.IntegerField(blank=True, null=True)
    current_bid = models.IntegerField(blank=True, null=True)
    max_bid = models.IntegerField(blank=True, null=True)
    seller = models.IntegerField(blank=True, null=True)

    class Meta:
        db_table = 'shopownedauction'


class Shopownedbank(models.Model):
    # TODO no primary key
    shop_nr = models.IntegerField(blank=True, null=True)
    player_id = models.IntegerField(blank=True, null=True)
    talens = models.IntegerField(blank=True, null=True)
    earned_interest = models.FloatField(blank=True, null=True)

    class Meta:
        db_table = 'shopownedbank'


class Shopownedcentralbank(models.Model):
    # TODO no primary key
    bank = models.IntegerField(blank=True, null=True)
    centralbank = models.IntegerField(blank=True, null=True)

    class Meta:
        db_table = 'shopownedcentralbank'


class Shopownedcorpbank(models.Model):
    # TODO no primary key
    shop_nr = models.IntegerField(blank=True, null=True)
    corp_id = models.IntegerField(blank=True, null=True)
    talens = models.IntegerField(blank=True, null=True)
    earned_interest = models.FloatField(blank=True, null=True)

    class Meta:
        db_table = 'shopownedcorpbank'


class Shopownedloanrate(models.Model):
    # TODO no primary key
    shop_nr = models.IntegerField(blank=True, null=True)
    x = models.IntegerField(blank=True, null=True)
    y = models.IntegerField(blank=True, null=True)
    term = models.IntegerField(blank=True, null=True)

    class Meta:
        db_table = 'shopownedloanrate'


class Shopownedloans(models.Model):
    # TODO no primary key
    shop_nr = models.IntegerField(blank=True, null=True)
    player_id = models.IntegerField(blank=True, null=True)
    amt = models.IntegerField(blank=True, null=True)
    granted_time = models.IntegerField(blank=True, null=True)
    term = models.IntegerField(blank=True, null=True)
    rate = models.FloatField(blank=True, null=True)
    default_charge = models.FloatField(blank=True, null=True)

    class Meta:
        db_table = 'shopownedloans'


class Shopownedmatch(models.Model):
    # TODO no primary key
    shop_nr = models.IntegerField(blank=True, null=True)
    match_str = models.CharField(max_length=128, blank=True)
    profit_buy = models.FloatField(blank=True, null=True)
    profit_sell = models.FloatField(blank=True, null=True)
    max_num = models.IntegerField(blank=True, null=True)

    class Meta:
        db_table = 'shopownedmatch'


class Shopownednpcloan(models.Model):
    # TODO no primary key
    loan_id = models.IntegerField(blank=True, null=True)
    amt = models.IntegerField(blank=True, null=True)
    rate = models.FloatField(blank=True, null=True)
    risk = models.FloatField(blank=True, null=True)
    owner = models.IntegerField(blank=True, null=True)

    class Meta:
        db_table = 'shopownednpcloan'


class Shopownedplayer(models.Model):
    # TODO no primary key
    shop_nr = models.IntegerField(blank=True, null=True)
    player = models.CharField(max_length=128, blank=True)
    profit_buy = models.FloatField(blank=True, null=True)
    profit_sell = models.FloatField(blank=True, null=True)
    max_num = models.IntegerField(blank=True, null=True)

    class Meta:
        db_table = 'shopownedplayer'


class Shopownedratios(models.Model):
    # TODO no primary key
    shop_nr = models.IntegerField()
    obj_nr = models.IntegerField()
    profit_buy = models.FloatField(blank=True, null=True)
    profit_sell = models.FloatField(blank=True, null=True)
    max_num = models.IntegerField(blank=True, null=True)

    class Meta:
        db_table = 'shopownedratios'


class Shopownedrepair(models.Model):
    # TODO no primary key
    shop_nr = models.IntegerField(blank=True, null=True)
    speed = models.FloatField(blank=True, null=True)
    quality = models.FloatField(blank=True, null=True)

    class Meta:
        db_table = 'shopownedrepair'


class Shopproducing(models.Model):
    # TODO no primary key
    shop_nr = models.IntegerField()
    producing = models.IntegerField()

    class Meta:
        db_table = 'shopproducing'


class Shoptype(models.Model):
    # TODO no primary key
    shop_nr = models.IntegerField()
    type = models.IntegerField()

    class Meta:
        db_table = 'shoptype'


class Tellhistory(models.Model):
    # TODO no primary key
    tellfrom = models.CharField(max_length=80, blank=True) # TODO indexed with telltime
    tellto = models.CharField(max_length=80, blank=True) # TODO indexed with telltime
    tell = models.CharField(max_length=1024, blank=True)
    telltime = models.DateTimeField()

    class Meta:
        db_table = 'tellhistory'


class Trophy(models.Model):
    # TODO no primary key
    player_id = models.IntegerField() # TODO indexed with mobvnum
    mobvnum = models.IntegerField()
    count = models.FloatField()
    totalcount = models.FloatField()

    class Meta:
        db_table = 'trophy'


class Trophymob(models.Model):
    # TODO no primary key
    mobvnum = models.IntegerField()

    class Meta:
        db_table = 'trophymob'


class Trophyplayer(models.Model):
    # TODO no primary key
    player_id = models.IntegerField() # TODO indexed
    count = models.IntegerField(blank=True, null=True)
    totalcount = models.FloatField(blank=True, null=True)

    class Meta:
        db_table = 'trophyplayer'


class Usagelogs(models.Model):
    # TODO no primary key
    time = models.IntegerField(blank=True, null=True) # TODO indexed with port
    players = models.IntegerField(blank=True, null=True)
    port = models.IntegerField(blank=True, null=True)

    class Meta:
        db_table = 'usagelogs'


class Usagelogsarchive(models.Model):
    # TODO no primary key
    time = models.IntegerField(blank=True, null=True)
    players = models.IntegerField(blank=True, null=True)
    port = models.IntegerField(blank=True, null=True)

    class Meta:
        db_table = 'usagelogsarchive'


class Wholist(models.Model):
    # TODO no primary key
    name = models.CharField(max_length=80, blank=True)
    title = models.CharField(max_length=256, blank=True)
    port = models.IntegerField(blank=True, null=True)
    invis = models.IntegerField(blank=True, null=True)

    class Meta:
        db_table = 'wholist'


class Wizpower(models.Model):
    # TODO no primary key
    player_id = models.IntegerField(blank=True, null=True) # TODO indexed
    wizpower = models.IntegerField(blank=True, null=True)

    class Meta:
        db_table = 'wizpower'


class Zone(models.Model):
    zone_nr = models.IntegerField(primary_key=True)
    zone_name = models.CharField(max_length=255)
    zone_enabled = models.IntegerField(blank=True, null=True)
    bottom = models.IntegerField(blank=True, null=True)
    top = models.IntegerField(blank=True, null=True)
    reset_mode = models.IntegerField(blank=True, null=True)
    lifespan = models.IntegerField(blank=True, null=True)
    age = models.IntegerField(blank=True, null=True)
    util_flag = models.IntegerField(blank=True, null=True)

    class Meta:
        db_table = 'zone'
