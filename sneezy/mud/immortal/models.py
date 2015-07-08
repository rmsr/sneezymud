from django.db import models

from sneezy.mud.fields import FixedCharField

class Mob(models.Model):
    vnum = models.IntegerField(primary_key=True)
    owner = models.CharField(max_length=80, blank=True)
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
    mob_class = models.IntegerField(db_column='class')
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
    vnum = models.ForeignKey(Mob, db_column='vnum', default=0)
    owner = models.CharField(max_length=80, null=True, blank=True)
    keyword = FixedCharField(max_length=32)
    description = FixedCharField(max_length=255, null=True, blank=True)

    class Meta:
        unique_together = (('vnum', 'keyword'))
        db_table = 'mob_extra'


class MobImm(models.Model):
    vnum = models.ForeignKey(Mob, db_column='vnum', default=0)
    owner = models.CharField(max_length=80, blank=True)
    type = models.IntegerField()
    amt = models.IntegerField(blank=True, null=True)

    class Meta:
        unique_together = (('vnum', 'type'))
        db_table = 'mob_imm'


class Mobresponses(models.Model):
    vnum = models.ForeignKey(Mob, db_index=True)
    owner = models.CharField(max_length=80, blank=True)
    response = models.TextField()

    class Meta:
        db_table = 'mobresponses'


class Obj(models.Model):
    vnum = models.IntegerField(primary_key=True)
    owner = models.CharField(max_length=80, blank=True)
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


class Objaffect(models.Model):
    vnum = models.ForeignKey(Obj)
    owner = models.CharField(max_length=80, blank=True)
    type = models.IntegerField()
    mod1 = models.IntegerField()
    mod2 = models.IntegerField()

    class Meta:
        db_table = 'objaffect'


class Objextra(models.Model):
    vnum = models.ForeignKey(Obj)
    owner = models.CharField(max_length=80, blank=True)
    name = models.CharField(max_length=127)
    description = models.TextField()

    class Meta:
        db_table = 'objextra'


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
    owner = models.CharField(max_length=32, blank=True)
    block = models.IntegerField(blank=True, null=True)

    class Meta:
        db_table = 'room'


class Roomexit(models.Model):
    vnum = models.ForeignKey(Room, db_index=True)
    direction = models.IntegerField()
    name = models.CharField(max_length=127)
    description = models.TextField()
    type = models.IntegerField()
    condition_flag = models.IntegerField()
    lock_difficulty = models.IntegerField()
    weight = models.IntegerField()
    key_num = models.IntegerField()
    destination = models.IntegerField()
    owner = models.CharField(max_length=32, blank=True)
    block = models.IntegerField(blank=True, null=True)

    class Meta:
        db_table = 'roomexit'


class Roomextra(models.Model):
    vnum = models.ForeignKey(Room, db_index=True)
    name = models.TextField()
    description = models.TextField()
    owner = models.CharField(max_length=32, blank=True)
    block = models.IntegerField(blank=True, null=True)

    class Meta:
        db_table = 'roomextra'
