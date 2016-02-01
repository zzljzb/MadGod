#include "SwordsMan.h"
#include "HeroManager.h"

SwordsMan * SwordsMan::create(HeroEunm _HeroEunm, RaceEunm _RaceEunm, int _roadid)
{
	SwordsMan*m_Data = new SwordsMan();
	if (m_Data->init(_HeroEunm, _RaceEunm, _roadid))
	{
		m_Data->autorelease();
		return m_Data;
	}
	CC_SAFE_DELETE(m_Data);
	return nullptr;

}

bool SwordsMan::init(HeroEunm _HeroEunm, RaceEunm _RaceEunm, int _roadid)
{
	mRaceEunm = _RaceEunm;
	mHeroEunm = _HeroEunm;
	mStateEunm = Stand;
	roadID = _roadid;
	HeroManager::getInstance()->add(this);
	mSprite = Sprite::create("walk_00.png");
	this->initAction("HeroA.plist", "HeroA.png");
	if (mRaceEunm == Blue) { mSprite->setFlipX(true); }
	this->addChild(mSprite);
	this->scheduleUpdate();
	loadjson(1);

	return true;
}

void SwordsMan::update(float d) {
    if(judgeIfAttainBase())
    {
        return;
    }
	Vec2 myPosition = this->getPosition();
	if (mStateEunm == StateEunm::Forward) {
		if (mRaceEunm == RaceEunm::Red) { this->setPosition(myPosition.x + NormalMoveSpeed, myPosition.y); }
		if (mRaceEunm == RaceEunm::Blue) { this->setPosition(myPosition.x - NormalMoveSpeed, myPosition.y); }
	}
	if (mStateEunm == StateEunm::Back) {
		if (mRaceEunm == RaceEunm::Red) { this->setPosition(myPosition.x - NormalMoveSpeed, myPosition.y); }
		if (mRaceEunm == RaceEunm::Blue) { this->setPosition(myPosition.x + NormalMoveSpeed, myPosition.y); }
	}

	Vector<HeroEnety*>Heros;
	auto hm=HeroManager::getInstance();
	if (mRaceEunm == Red) { Heros=HeroManager::getInstance()->Vec_HeroBlue; }
	if (mRaceEunm == Blue) { Heros = HeroManager::getInstance()->Vec_HeroRed; }

    
	for (auto Hero : Heros) {
		if (roadID == Hero->roadID) {
			int i ;
			if (mRaceEunm == Blue) { i = -1; }
			else { i = 1; }
			if (mStateEunm == StateEunm::Dead) { break; }

			if ((getPosition().x +AttackRange*i)*i >= Hero->getPosition().x*i ) {
				//ÔÚ¹¥»÷·¶Î§ÄÚ
				if (mStateEunm == StateEunm::Attack ) { break; }
				Hero->NormalHit(this->NormalAttackPower); 

				this->GoAttack(Hero);
				
				break;
			}
		}
	}
    if (this->mStateEunm != HeroEnety::StateEunm::Attack) { this->GoForward(); }
}

