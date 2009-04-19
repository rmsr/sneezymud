//////////////////////////////////////////////////////////////////////////
//
// SneezyMUD - All rights reserved, SneezyMUD Coding Team
//
// $Log: disc_aegis.h,v $
// Revision 5.2  2002/05/16 00:26:15  peel
// added relive spell
//
// Revision 5.1.1.1  1999/10/16 04:32:20  batopr
// new branch
//
// Revision 5.1  1999/10/16 04:31:17  batopr
// new branch
//
// Revision 1.1  1999/09/12 17:24:04  sneezy
// Initial revision
//
//
//////////////////////////////////////////////////////////////////////////


#ifndef __DISC_AEGIS_H
#define __DISC_AEGIS_H

// This is the AEGIS discipline.

#include "discipline.h"
#include "skills.h"

class CDAegis : public CDiscipline
{
public:
    CSkill skSanctuary;
    CSkill skCureParalyze;
    CSkill skSecondWind;
    CSkill skRelive;

    CDAegis()
      : CDiscipline(),
        skSanctuary(), skCureParalyze(),
        skSecondWind(), skRelive() {
    }
    CDAegis(const CDAegis &a)
      : CDiscipline(a),
        skSanctuary(a.skSanctuary), skCureParalyze(a.skCureParalyze),
        skSecondWind(a.skSecondWind), skRelive(a.skRelive) {
    }
    CDAegis & operator=(const CDAegis &a) {
      if (this == &a) return *this;
      CDiscipline::operator=(a),
      skSanctuary = a.skSanctuary;
      skCureParalyze = a.skCureParalyze;
      skSecondWind = a.skSecondWind;
      skRelive = a.skRelive;
      return *this;
    }
    virtual ~CDAegis() {}
    virtual CDAegis * cloneMe() { return new CDAegis(*this); }
private:
};

    void armor(TBeing *, TBeing *);
    void armor(TBeing *, TBeing *, TMagicItem * obj, spellNumT);
    int armor(TBeing *, TBeing *, int, sh_int, spellNumT);
 
    void sanctuary(TBeing *, TBeing *);
    void sanctuary(TBeing *, TBeing *, TMagicItem * obj);
    int sanctuary(TBeing *, TBeing *, int, sh_int);
 
    void bless(TBeing *, TObj *);
    void bless(TBeing *, TObj *, TMagicItem *, spellNumT);
    int bless(TBeing *, TObj *, int, sh_int, spellNumT);
 
    void bless(TBeing *, TBeing *);
    void bless(TBeing *, TBeing *, TMagicItem * obj, spellNumT);
    int bless(TBeing *, TBeing *, int, sh_int, spellNumT);
 
    void cureBlindness(TBeing *, TBeing *);
    void cureBlindness(TBeing *, TBeing *, TMagicItem *);
    int cureBlindness(TBeing *, TBeing *, int, sh_int);
 
    void curePoison(TBeing *, TBeing *);
    void curePoison(TBeing *, TBeing *, TMagicItem *, spellNumT);
    int curePoison(TBeing *, TBeing *, int, sh_int, spellNumT);
 
    void refresh(TBeing *, TBeing *);
    void refresh(TBeing *, TBeing *, TMagicItem *, spellNumT);
    int refresh(TBeing *, TBeing *, int, sh_int, spellNumT);
 
    void secondWind(TBeing *, TBeing *);
    void secondWind(TBeing *, TBeing *, TMagicItem *);
    int secondWind(TBeing *, TBeing *, int, sh_int);
 
    void cureParalysis(TBeing *, TBeing *);
    void cureParalysis(TBeing *, TBeing *, TMagicItem *);
    int cureParalysis(TBeing *, TBeing *, int, sh_int);
 
    void cureDisease(TBeing *, TBeing *);
    int  cureDisease(TBeing *, TBeing *, int, sh_int, spellNumT);
    void cureDisease(TBeing *, TBeing *, TMagicItem *, spellNumT);

    void relive(TBeing *, TBeing *);
#endif