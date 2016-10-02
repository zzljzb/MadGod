#include "HeroManager.h"

USING_NS_CC;
static HeroManager* m_Data = nullptr;
HeroManager* HeroManager::getInstance()
{
	if (!m_Data)
	{
		m_Data = new HeroManager();
		m_Data->init();
	}
	return m_Data;
}


bool HeroManager::init()
{
	//this->scheduleUpdate();
	return true;
}

void HeroManager::update(float d)
{
	for (auto Reds : Vec_HeroRed) {
		for (auto Blues : Vec_HeroBlue) {
			if (Reds->roadID == Blues->roadID) {
				if (Reds->getPosition().x + Reds->AttackRange >= Blues->getPosition().x) {
					
					//在攻击范围内
					Man_AI(Reds, Blues);
					break;
				}
				else
				{
					//不在攻击范围内,继续前进
					if (Reds->mStateEunm != HeroEnety::StateEunm::Attack) { Reds->GoForward(); }
				}
			}
		}
	}






}

void HeroManager::add(HeroEnety * hero)
{
	if (hero->mRaceEunm == HeroEnety::RaceEunm::Red)Vec_HeroRed.pushBack(hero);
	if (hero->mRaceEunm == HeroEnety::RaceEunm::Blue)Vec_HeroBlue.pushBack(hero);
}

void HeroManager::del(HeroEnety * hero, bool removeHero)
{
	if (hero->mRaceEunm == HeroEnety::RaceEunm::Red) { Vec_HeroRed.erase(Vec_HeroRed.find(hero)); }
	if (hero->mRaceEunm == HeroEnety::RaceEunm::Blue) { Vec_HeroBlue.erase(Vec_HeroBlue.find(hero)); }
    if (removeHero) {
        hero->removeFromParentAndCleanup(true);
    }
}

void HeroManager::Man_AI(HeroEnety * hero_A, HeroEnety * hero_B)
{
	hero_A->GoAttack(hero_B);
}


