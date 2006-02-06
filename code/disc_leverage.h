//////////////////////////////////////////////////////////////////////////
//
// SneezyMUD - All rights reserved, SneezyMUD Coding Team
//
//////////////////////////////////////////////////////////////////////////


#ifndef __DISC_LEVERAGE_H
#define __DISC_LEVERAGE_H 

class CDLeverage : public CDiscipline
{
public:
    CSkill skShoulderThrow;
    CSkill skHurl;
    CSkill skChainAttack;
    CSkill skDefenestrate;

    CDLeverage()
      : CDiscipline(),
      skShoulderThrow(),
      skHurl(),
      skChainAttack(),
      skDefenestrate(){
    }
    CDLeverage(const CDLeverage &a)
      : CDiscipline(a),
      skShoulderThrow(a.skShoulderThrow),
      skHurl(a.skHurl),
      skChainAttack(a.skChainAttack),
      skDefenestrate(a.skDefenestrate){
    }
    CDLeverage & operator=(const CDLeverage &a) {
      if (this == &a) return *this;
      CDiscipline::operator=(a);
      skShoulderThrow = a.skShoulderThrow;
      skHurl = a.skHurl;
      skChainAttack = a.skChainAttack;
      skDefenestrate = a.skDefenestrate;
      return *this;
    }
    virtual ~CDLeverage() {}
    virtual CDLeverage * cloneMe() { return new CDLeverage(*this); }

private:
};

  int shoulderThrow(TBeing *, TBeing *);
  int hurl(TBeing *, TBeing *, char *);
  int defenestrate(TBeing *, TBeing *, char *);

#endif








