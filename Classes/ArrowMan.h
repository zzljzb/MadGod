#pragma once
#ifndef __ArrowMan_H__
#define __ArrowMan_H__
#include "cocos2d.h"
#include "HeroEnety.h"

USING_NS_CC;
class ArrowMan : public HeroEnety
{
public:
	static ArrowMan* create(HeroEunm _HeroEunm, RaceEunm _RaceEunm, int _roadid);


private:

	bool init(HeroEunm _HeroEunm, RaceEunm _RaceEunm, int _roadid);
	void update(float d);


};
#endif