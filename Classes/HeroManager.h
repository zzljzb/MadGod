#pragma once
#ifndef __HeroManager_H__
#define __HeroManager_H__

#include "cocos2d.h"
#include "HeroEnety.h"
USING_NS_CC;
class HeroManager : public Node
{
public:
	static HeroManager* getInstance();
	bool init();
	void update(float d);


	void add(HeroEnety * hero);
	void del(HeroEnety * hero, bool removeHero = true);



	Vector<HeroEnety*> Vec_HeroRed;
	Vector<HeroEnety*> Vec_HeroBlue;



	void Man_AI(HeroEnety * hero_A, HeroEnety * hero_B);
};
#endif

