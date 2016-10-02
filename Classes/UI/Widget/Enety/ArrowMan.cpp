#include "ArrowMan.h"
#include "HeroManager.h"

ArrowMan * ArrowMan::create(HeroEunm _HeroEunm, RaceEunm _RaceEunm, int _roadid)
{
	ArrowMan*m_Data = new ArrowMan();
	if (m_Data->init(_HeroEunm, _RaceEunm, _roadid))
	{
		m_Data->autorelease();
		return m_Data;
	}
	CC_SAFE_DELETE(m_Data);
	return nullptr;

}

bool ArrowMan::init(HeroEunm _HeroEunm, RaceEunm _RaceEunm, int _roadid)
{
	mRaceEunm = _RaceEunm;
	mHeroEunm = _HeroEunm;
	mStateEunm = Stand;
	roadID = _roadid;
	HeroManager::getInstance()->add(this);
	mSprite = Sprite::create("fireball_soldier.png");
	this->initAction("HeroB.plist", "HeroB.png");
	if (mRaceEunm == Blue) { mSprite->setFlipX(true); }
	this->addChild(mSprite);
	this->scheduleUpdate();
	loadjson(2);
	return true;
}

void ArrowMan::update(float d) {
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
	if (mRaceEunm == Red) { Heros = HeroManager::getInstance()->Vec_HeroBlue; }
	if (mRaceEunm == Blue) { Heros = HeroManager::getInstance()->Vec_HeroRed; }

    int offsetSym = mRaceEunm == RaceEunm::Red ? 1 : -1;
	for (auto Hero : Heros) {
		if (roadID == Hero->roadID) {
            float offset = (Hero->getPosition().x - getPosition().x) * offsetSym;
			if (offset <= AttackRange) {
                if(mStateEunm==StateEunm::Attack){break;}
                Hero->NormalHit(this->NormalAttackPower);
				this->GoAttack(Hero);
				break;
			}
		}
	}
    if (this->mStateEunm != HeroEnety::StateEunm::Attack) { this->GoForward(); }
//    if (not hasAttack and mStateEunm == Stand) {
//        mStateEunm = Forward;
//    }
}

