
#ifndef __DISC_SHAMAN_SPIDER_H
#define __DISC_SHAMAN_SPIDER_H

#include "discipline.h"
#include "skills.h"

class CDShamanSpider : public CDiscipline
{
public:
    CSkill skSticksToSnakes;
    CSkill skControlUndead;
    CSkill skHypnosis;
    CSkill skRaze;
    CSkill skRootControl;
    CSkill skLivingVines;
    CSkill skTransfix;
    CSkill skClarity;

    CDShamanSpider()
      : CDiscipline(),
      skSticksToSnakes(),
      skControlUndead(),
      skHypnosis(),
      skRaze(),
      skRootControl(),
      skLivingVines(),
      skTransfix(),
      skClarity() { 
    }
    CDShamanSpider(const CDShamanSpider &a)
      : CDiscipline(a),
      skSticksToSnakes(a.skSticksToSnakes),
      skControlUndead(a.skControlUndead),
      skHypnosis(a.skHypnosis),
      skRaze(a.skRaze),
      skRootControl(a.skRootControl),
      skLivingVines(a.skLivingVines),
      skTransfix(a.skTransfix),
      skClarity(a.skClarity) {
    }
    CDShamanSpider & operator=(const CDShamanSpider &a) {
      if (this == &a) return *this;
      CDiscipline::operator=(a);
      skSticksToSnakes = a.skSticksToSnakes;
      skControlUndead = a.skControlUndead;
      skHypnosis = a.skHypnosis;
      skRaze = a.skRaze;
      skRootControl = a.skRootControl;
      skLivingVines = a.skLivingVines;
      skTransfix = a.skTransfix;
      skClarity = a.skClarity;
      return *this;
    }
    virtual ~CDShamanSpider() {}
    virtual CDShamanSpider * cloneMe() { return new CDShamanSpider(*this); }
private:
};

    int transfix(TBeing *, TBeing *);
    int transfix(TBeing *, TBeing *, int, sh_int);
 
    void livingVines(TBeing *, TBeing *);
    void livingVines(TBeing *, TBeing *, TMagicItem *);
    int livingVines(TBeing *, TBeing *, int, sh_int);
    
    int rootControl(TBeing *, TBeing *, int, int, sh_int);
    int rootControl(TBeing *, TBeing *, TMagicItem *);
    int rootControl(TBeing *, TBeing *);

    int controlUndead(TBeing *, TBeing *);
    int castControlUndead(TBeing *, TBeing *);
    void controlUndead(TBeing *, TBeing *, TMagicItem *);
    int controlUndead(TBeing *, TBeing *, int, sh_int);

    int sticksToSnakes(TBeing *, TBeing *);
    void sticksToSnakes(TBeing *, TBeing *, TMagicItem *);
    int castSticksToSnakes(TBeing *, TBeing *);
    int sticksToSnakes(TBeing *, TBeing *, int, sh_int);

    int clarity(TBeing *, TBeing *);
    int castClarity(TBeing *, TBeing *);
    void clarity(TBeing *, TBeing *, TMagicItem *);
    int clarity(TBeing *, TBeing *, int, sh_int);

    int hypnosis(TBeing *, TBeing *);
    int castHypnosis(TBeing *, TBeing *);
    void hypnosis(TBeing *, TBeing *, TMagicItem *);
    int hypnosis(TBeing *, TBeing *, int, sh_int);

    int raze(TBeing *, TBeing *);
    int castRaze(TBeing *, TBeing *);
    int raze(TBeing *, TBeing *, int, sh_int, int);
    int raze(TBeing *, TBeing *, TMagicItem *);

#endif

