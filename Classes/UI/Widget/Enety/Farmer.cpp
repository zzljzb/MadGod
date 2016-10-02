//
//  Farmer.cpp
//  ggj-jzb
//
//  Created by jzb on 16/1/31.
//
//

#include "Farmer.hpp"
#include "HeroManager.h"

Farmer* Farmer::create(HeroEunm _HeroEunm, RaceEunm _RaceEunm, int _roadid)
{
    Farmer* m_Data = new Farmer();
    if (m_Data->init(_HeroEunm, _RaceEunm, _roadid))
    {
        m_Data->autorelease();
        return m_Data;
    }
    CC_SAFE_DELETE(m_Data);
    return nullptr;
    
}

bool Farmer::init(HeroEunm _HeroEunm, RaceEunm _RaceEunm, int _roadid)
{
    mRaceEunm = _RaceEunm;
    mHeroEunm = _HeroEunm;
    mStateEunm = Stand;
    roadID = _roadid;
    HeroManager::getInstance()->add(this);
    mSprite = Sprite::create("farmer.png");
    mSprite->setScale(0.5 );
    this->initAction("HeroD.plist", "HeroD.png");
    if (mRaceEunm == Blue) { mSprite->setFlipX(true); }
    this->addChild(mSprite);
    this->scheduleUpdate();
    loadjson(4);
    return true;
}

void Farmer::update(float d) {
    if(judgeIfAttainBase())
    {
        return;
    }
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    Vec2 myPosition = this->getPosition();
    if (mStateEunm == StateEunm::Forward) {
        if (mRaceEunm == RaceEunm::Red)
        {
            Vec2 targetPos = Vec2(myPosition.x + NormalMoveSpeed, myPosition.y);
            if (targetPos.x < origin.x + visibleSize.width * 0.2 && _listener)
            {
                _listener->onReachLeft();
            }
            else if (targetPos.x > origin.x + visibleSize.width * 0.8 && _listener)
            {
                _listener->onReachRight();
            }
            else
            {
                
            }
            this->setPosition(targetPos);
        }
        if (mRaceEunm == RaceEunm::Blue)
        {
            Vec2 targetPos = Vec2(myPosition.x - NormalMoveSpeed, myPosition.y);
            if (targetPos.x < origin.x + visibleSize.width * 0.2 && _listener)
            {
                _listener->onReachLeft();
            }
            else if (targetPos.x > origin.x + visibleSize.width * 0.8 && _listener)
            {
                _listener->onReachRight();
            }
            else
            {
                
            }
            this->setPosition(targetPos);
        }
    }
    if (mStateEunm == StateEunm::Back)
    {
        if (mRaceEunm == RaceEunm::Red)
        {
            Vec2 targetPos = Vec2(myPosition.x - NormalMoveSpeed, myPosition.y);
            if (targetPos.x < origin.x + visibleSize.width * 0.2 && _listener)
            {
                _listener->onReachLeft();
            }
            else if (targetPos.x > origin.x + visibleSize.width * 0.8 && _listener)
            {
                _listener->onReachRight();
            }
            else
            {
                
            }
            this->setPosition(targetPos);
        }
        if (mRaceEunm == RaceEunm::Blue)
        {
            Vec2 targetPos = Vec2(myPosition.x + NormalMoveSpeed, myPosition.y);
            if (targetPos.x < origin.x + visibleSize.width * 0.2 && _listener)
            {
                _listener->onReachLeft();
            }
            else if (targetPos.x > origin.x + visibleSize.width * 0.8 && _listener)
            {
                _listener->onReachRight();
            }
            else
            {
                
            }
            this->setPosition(targetPos);
        }
    }
    
    Vector<HeroEnety*>Heros;
    if (mRaceEunm == Red) { Heros = HeroManager::getInstance()->Vec_HeroBlue; }
    if (mRaceEunm == Blue) { Heros = HeroManager::getInstance()->Vec_HeroRed; }
    
    for (auto Hero : Heros) {
        if (roadID == Hero->roadID) {
            if (getPosition().x + AttackRange >= Hero->getPosition().x) {
                //this->GoAttack(Hero);
                break;
            }
        }
    }
    if (this->mStateEunm != HeroEnety::StateEunm::Attack) { this->GoForward(); }
}

void Farmer::addListener(FarmerListener* listener)
{
    CCAssert(listener != nullptr, "listener should not be nil");
    _listener = listener;
}

void Farmer::removeListener()
{
    _listener = nullptr;
}