#pragma once
#ifndef __SwordsMan_H__
#define __SwordsMan_H__
#include "cocos2d.h"
#include "HeroEnety.h"

USING_NS_CC;
class SwordsMan : public HeroEnety
{
public:
	static SwordsMan* create(HeroEunm _HeroEunm, RaceEunm _RaceEunm, int _roadid);


private:

	bool init(HeroEunm _HeroEunm, RaceEunm _RaceEunm, int _roadid);
	void update(float d);


};
#endif

