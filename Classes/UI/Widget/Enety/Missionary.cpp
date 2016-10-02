//
//  Missionary.cpp
//  ggj-jzb
//
//  Created by jzb on 16/1/30.
//
//

#include "Missionary.hpp"
#include "HeroManager.h"
#include "DataManager.hpp"

USING_NS_CC;
using namespace std;

Missionary* Missionary::create(HeroEunm _HeroEunm, RaceEunm _RaceEunm, int _roadid)
{
    Missionary* m_Data = new Missionary();
    if (m_Data->init(_HeroEunm, _RaceEunm, _roadid))
    {
        m_Data->autorelease();
        return m_Data;
    }
    CC_SAFE_DELETE(m_Data);
    return nullptr;
    
}

bool Missionary::init(HeroEunm _HeroEunm, RaceEunm _RaceEunm, int _roadid)
{
    mRaceEunm = _RaceEunm;
    mHeroEunm = _HeroEunm;
    mStateEunm = Stand;
    roadID = _roadid;
    HeroManager::getInstance()->add(this);
    mSprite = Sprite::create("missionary.png");
    mSprite->setScale(0.3);
    this->initAction("HeroC.plist", "HeroC.png");
    if (mRaceEunm == Blue)
    {
        mSprite->setFlippedX(true);
    }
    this->addChild(mSprite);
    this->scheduleUpdate();
    loadjson(3);
    
    return true;
}

void Missionary::update(float d)
{
    if(judgeIfAttainBase())
    {
        return;
    }
    
    if (_isStanding)
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
            if (abs(targetPos.x - (origin.x + visibleSize.width * 0.4)) < 75
                && abs(targetPos.y - (origin.y + visibleSize.height * 0.8)) < 75)
            {
                MINE_STATE state = DataManager::getInstance()->getMineState(0);
                switch (state)
                {
                    case kMineStateIdle:
                        _isStanding = true;
                        if (mRaceEunm == Red)
                        {
                            Director::getInstance()->getEventDispatcher()->dispatchCustomEvent("left_occupied_mine_0");
                        }
                        else
                        {
                            Director::getInstance()->getEventDispatcher()->dispatchCustomEvent("right_occupied_mine_0");
                        }
                        
                        break;
                        
                    case kMineStateOccupiedRight:
                        if (mRaceEunm == Red)
                        {
                            _isStanding = true;
                            Director::getInstance()->getEventDispatcher()->dispatchCustomEvent("mine_config_0");
                        }
                        break;
                        
                    case kMineStateOccupiedLeft:
                        if (mRaceEunm == Blue)
                        {
                            _isStanding = true;
                            Director::getInstance()->getEventDispatcher()->dispatchCustomEvent("mine_config_0");
                        }
                        
                    default:
                        break;
                }
            }
            else if(abs(targetPos.x - (origin.x + visibleSize.width * 0.5)) < 75
                    && abs(targetPos.y - (origin.y + visibleSize.height * 0.55)) < 75)
            {
                MINE_STATE state = DataManager::getInstance()->getMineState(1);
                switch (state)
                {
                    case kMineStateIdle:
                        _isStanding = true;
                        if (mRaceEunm == Red)
                        {
                            Director::getInstance()->getEventDispatcher()->dispatchCustomEvent("left_occupied_mine_1");
                        }
                        else
                        {
                            Director::getInstance()->getEventDispatcher()->dispatchCustomEvent("right_occupied_mine_1");
                        }
                        
                        break;
                        
                    case kMineStateOccupiedRight:
                        if (mRaceEunm == Red)
                        {
                            _isStanding = true;
                            Director::getInstance()->getEventDispatcher()->dispatchCustomEvent("mine_config_1");
                        }
                        break;
                        
                    case kMineStateOccupiedLeft:
                        if (mRaceEunm == Blue)
                        {
                            _isStanding = true;
                            Director::getInstance()->getEventDispatcher()->dispatchCustomEvent("mine_config_1");
                        }
                        
                    default:
                        break;
                }
            }
            else if(abs(targetPos.x - (origin.x + visibleSize.width * 0.6)) < 75
                    && abs(targetPos.y - (origin.y + visibleSize.height * 0.2)) < 75)
            {
                MINE_STATE state = DataManager::getInstance()->getMineState(2);
                switch (state)
                {
                    case kMineStateIdle:
                        _isStanding = true;
                        if (mRaceEunm == Red)
                        {
                            Director::getInstance()->getEventDispatcher()->dispatchCustomEvent("left_occupied_mine_2");
                        }
                        else
                        {
                            Director::getInstance()->getEventDispatcher()->dispatchCustomEvent("right_occupied_mine_2");
                        }
                        
                        break;
                        
                    case kMineStateOccupiedRight:
                        if (mRaceEunm == Red)
                        {
                            _isStanding = true;
                            Director::getInstance()->getEventDispatcher()->dispatchCustomEvent("mine_config_2");
                        }
                        break;
                        
                    case kMineStateOccupiedLeft:
                        if (mRaceEunm == Blue)
                        {
                            _isStanding = true;
                            Director::getInstance()->getEventDispatcher()->dispatchCustomEvent("mine_config_2");
                        }
                        
                    default:
                        break;
                }
            }
            else
            {
                
            }
            if (!_isStanding)
            {
                this->setPosition(myPosition.x + NormalMoveSpeed, myPosition.y);
            }
        }
        if (mRaceEunm == RaceEunm::Blue)
        {
            Vec2 targetPos = Vec2(myPosition.x - NormalMoveSpeed, myPosition.y);
            if (abs(targetPos.x - (origin.x + visibleSize.width * 0.4)) < 75
                && abs(targetPos.y - (origin.y + visibleSize.height * 0.8)) < 75)
            {
                MINE_STATE state = DataManager::getInstance()->getMineState(0);
                switch (state)
                {
                    case kMineStateIdle:
                        _isStanding = true;
                        if (mRaceEunm == Red)
                        {
                            Director::getInstance()->getEventDispatcher()->dispatchCustomEvent("left_occupied_mine_0");
                        }
                        else
                        {
                            Director::getInstance()->getEventDispatcher()->dispatchCustomEvent("right_occupied_mine_0");
                        }
                        
                        break;
                        
                    case kMineStateOccupiedLeft:
                        if (mRaceEunm == Blue)
                        {
                            _isStanding = true;
                            Director::getInstance()->getEventDispatcher()->dispatchCustomEvent("mine_config_0");
                        }
                        break;
                        
                    case kMineStateOccupiedRight:
                        if (mRaceEunm == Red)
                        {
                            _isStanding = true;
                            Director::getInstance()->getEventDispatcher()->dispatchCustomEvent("mine_config_0");
                        }
                        
                    default:
                        break;
                }
            }
            else if(abs(targetPos.x - (origin.x + visibleSize.width * 0.5)) < 75
                    && abs(targetPos.y - (origin.y + visibleSize.height * 0.55)) < 75)
            {
                MINE_STATE state = DataManager::getInstance()->getMineState(1);
                switch (state)
                {
                    case kMineStateIdle:
                        _isStanding = true;
                        if (mRaceEunm == Red)
                        {
                            Director::getInstance()->getEventDispatcher()->dispatchCustomEvent("left_occupied_mine_1");
                        }
                        else
                        {
                            Director::getInstance()->getEventDispatcher()->dispatchCustomEvent("right_occupied_mine_1");
                        }
                        
                        break;
                        
                    case kMineStateOccupiedRight:
                        if (mRaceEunm == Red)
                        {
                            _isStanding = true;
                            Director::getInstance()->getEventDispatcher()->dispatchCustomEvent("mine_config_1");
                        }
                        break;
                        
                    case kMineStateOccupiedLeft:
                        if (mRaceEunm == Blue)
                        {
                            _isStanding = true;
                            Director::getInstance()->getEventDispatcher()->dispatchCustomEvent("mine_config_1");
                        }
                        
                    default:
                        break;
                }
            }
            else if(abs(targetPos.x - (origin.x + visibleSize.width * 0.6)) < 75
                    && abs(targetPos.y - (origin.y + visibleSize.height * 0.2)) < 75)
            {
                MINE_STATE state = DataManager::getInstance()->getMineState(2);
                switch (state)
                {
                    case kMineStateIdle:
                        _isStanding = true;
                        if (mRaceEunm == Red)
                        {
                            Director::getInstance()->getEventDispatcher()->dispatchCustomEvent("left_occupied_mine_2");
                        }
                        else
                        {
                            Director::getInstance()->getEventDispatcher()->dispatchCustomEvent("right_occupied_mine_2");
                        }
                        
                        break;
                        
                    case kMineStateOccupiedRight:
                        if (mRaceEunm == Red)
                        {
                            _isStanding = true;
                            Director::getInstance()->getEventDispatcher()->dispatchCustomEvent("mine_config_2");
                        }
                        break;
                        
                    case kMineStateOccupiedLeft:
                        if (mRaceEunm == Blue)
                        {
                            _isStanding = true;
                            Director::getInstance()->getEventDispatcher()->dispatchCustomEvent("mine_config_2");
                        }
                        
                    default:
                        break;
                }
            }
            else
            {
                
            }
            
            if (!_isStanding)
            {
                this->setPosition(myPosition.x - NormalMoveSpeed, myPosition.y);
            }
        }
    }
    if (mStateEunm == StateEunm::Back) {
        if (mRaceEunm == RaceEunm::Red) { this->setPosition(myPosition.x - NormalMoveSpeed, myPosition.y); }
        if (mRaceEunm == RaceEunm::Blue) { this->setPosition(myPosition.x + NormalMoveSpeed, myPosition.y); }
    }
    
    Vector<HeroEnety*> Heros;
    Vector<HeroEnety*> selfHeros;
    auto hm=HeroManager::getInstance();
    if (mRaceEunm == Red)
    {
        Heros = HeroManager::getInstance()->Vec_HeroBlue;
        selfHeros = HeroManager::getInstance()->Vec_HeroRed;
    }
    if (mRaceEunm == Blue)
    {
        Heros = HeroManager::getInstance()->Vec_HeroRed;
        selfHeros = HeroManager::getInstance()->Vec_HeroBlue;
    }
    
    for (auto Hero : Heros) {
        if (roadID == Hero->roadID) {
            int i ;
            if (mRaceEunm == Blue) { i = -1; }
            else { i = 1; }
            if (mStateEunm == StateEunm::Dead) { break; }
            
            if ((getPosition().x +AttackRange*i)*i >= Hero->getPosition().x*i ) {
                if (mStateEunm == StateEunm::Attack ) { break; }
                Hero->LoyaltyHit(this->LoyaltyAttackPower);
                
                this->GoAttack(Hero);
                
                break;
            }
        }
    }

    for (auto Hero : selfHeros) {
        if (roadID == Hero->roadID && Hero != this) {
            int i ;
            if (mRaceEunm == Blue) { i = -1; }
            else { i = 1; }
            if (mStateEunm == StateEunm::Dead) { break; }
            
            if ((getPosition().x +AttackRange*i)*i >= Hero->getPosition().x*i ) {
                if (mStateEunm == StateEunm::Attack ) { break; }
                Hero->LoyaltyHit(-1 * this->LoyaltyAttackPower);
                
                this->GoAttack(Hero);
                
                break;
            }
        }
    }
    if (this->mStateEunm != HeroEnety::StateEunm::Attack) { this->GoForward(); }
}