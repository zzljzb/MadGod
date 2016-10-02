//
//  Missionary.hpp
//  ggj-jzb
//
//  Created by jzb on 16/1/30.
//
//

#ifndef Missionary_hpp
#define Missionary_hpp

#include "cocos2d.h"
#include "HeroEnety.h"

USING_NS_CC;

class Missionary : public HeroEnety
{
public:
    static Missionary* create(HeroEunm _HeroEunm, RaceEunm _RaceEunm, int _roadid);
    
private:
    bool init(HeroEunm _HeroEunm, RaceEunm _RaceEunm, int _roadid);
    void update(float d);
    
private:
    bool _isStanding = false;
};

#endif /* Missionary_hpp */
