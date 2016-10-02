//
//  Farmer.hpp
//  ggj-jzb
//
//  Created by jzb on 16/1/31.
//
//

#ifndef Farmer_hpp
#define Farmer_hpp
#include "cocos2d.h"
#include "HeroEnety.h"

USING_NS_CC;

class FarmerListener
{
public:
    virtual void onReachLeft() = 0;
    virtual void onReachRight() = 0;
};

class Farmer : public HeroEnety
{
public:
    static Farmer* create(HeroEunm _HeroEunm, RaceEunm _RaceEunm, int _roadid);
    
public:
    void addListener(FarmerListener* listener);
    void removeListener();
    
private:
    bool init(HeroEunm _HeroEunm, RaceEunm _RaceEunm, int _roadid);
    void update(float d);
    
private:
    Farmer* _farmer = nullptr;
    FarmerListener* _listener = nullptr;
};

#endif /* Farmer_hpp */
