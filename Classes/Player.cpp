//
//  Player.cpp
//  MyGame
//
//  Created by mixi on 16/1/30.
//
//

#include "Player.h"
#include "JsonUtils.hpp"
#include "HeroEnety.h"
#include "SwordsMan.h"
#include "Missionary.hpp"
#include "Farmer.hpp"
#include "ArrowMan.h"
#include "Utils.hpp"


using namespace std;
static float MinNum = pow(10, -3);
Player::Player()
:isAnabasisNumZero(false)
,_fractionHumanResource(-1)
,_fractionMP(-1)
,_fractionHP(-1)
{
}

Player::~Player()
{
}

bool Player::init()
{
    addListen();
    return true;
}

Player* create(HeroEnety::RaceEunm camp)
{
    Player* player = Player::create();
    if (player) {
        player->setCamp(camp);
        return player;
    }else{
        return nullptr;
    }
}

void Player::addRes(HeroEnety* res)
{
    _resVec.pushBack(res);
}

void Player::delRes(HeroEnety* res)
{
    _resVec.erase(_resVec.find(res));
}

void Player::anabasis(HeroEnety* res)
{
    _outsideResVec.pushBack(res);
}

Vector<HeroEnety*> Player::getEnemyTroops(int roadId)
{
    sortOutsideRes();
//    if (roadId > 0 && roadId <= _outsideSworldManMap.size()) {
//        return _outsideSworldManMap.at(roadId);
//    }else{
//        Vector<HeroEnety*>
//    }
    return _outsideResVec;
}

void Player::sortOutsideRes()
{
    
}

// 产兵
HeroEnety* Player::addSworldsMan(HeroEnety::HeroEunm heroEnum, int roadid)
{
    HeroEnety* heroEnety;// = HeroEnety::create(heroEnum , _camp, roadid);
    switch (heroEnum) {
        case HeroEnety::HeroEunm::ArrowMan:
            heroEnety = ArrowMan::create(heroEnum , _camp, roadid);
            break;
        case HeroEnety::HeroEunm::SwordsMan:
            heroEnety = SwordsMan::create(heroEnum , _camp, roadid);
            break;
        case HeroEnety::HeroEunm::Missionary:
            heroEnety = Missionary::create(heroEnum , _camp, roadid);
            break;
        case HeroEnety::HeroEunm::Farmer:
            heroEnety = Farmer::create(heroEnum , _camp, roadid);
            break;
        default:
            break;
    }
    if (heroEnety) {
        if (changeHumanResourceValue(-heroEnety->ManPowerToProduce)) {
            addRes(heroEnety);
            return heroEnety;
        }
    }
    return nullptr;
}

void Player::removeSworldMan(HeroEnety* hero)
{
    delRes(hero);
}

void Player::update(float d)
{
    if (floor(_fractionMP) >= _fractionMaxMP) {
        // win
        Director::getInstance()->getScheduler()->unscheduleAll();
        log("game win");
    } else if(floor(_fractionHP) < MinNum){
        // lose
        Director::getInstance()->getScheduler()->unscheduleAll();
        log("game lose");
    }
    updateOutsideSworldMan();
    if (isAnabasisNumZero != _outsideResVec.size() == 0) {
        isAnabasisNumZero = _outsideResVec.size() == 0;
        char* buf = new char[10];
        int value = isAnabasisNumZero and 1 or 0;
        sprintf(buf, "%d,%d", _camp, value);
        EventCustom event("event_all_solider_die");
        event.setUserData(buf);
        _eventDispatcher->dispatchEvent(&event);
    }
}

void Player::setCamp(HeroEnety::RaceEunm camp)
{
    _camp = camp;
    initData();
}

HeroEnety::RaceEunm Player::getCamp()
{
    return _camp;
}

void Player::updateOutsideSworldMan()
{
    for(auto men : _outsideResVec){
        if(men->NormalHP < MinNum){
            removeSworldMan(men);
        }
    }
}

void Player::addHumanResource(float dt)
{
    changeHumanResourceValue(_fractionHumanResourceIncreasPerSecond);
}

bool Player::changeHumanResourceValue(float value)
{
    float newValue = _fractionHumanResource + value;
    if (newValue > 0) {
        setHumanResourceValue(newValue);
        return true;
    }else{
        log("no enougth human");
        return false;
    }
}
void Player::setHumanResourceValue(float newValue)
{
    if(abs(floor(newValue) - floor(_fractionHumanResource)) > MinNum){
        char* buf = new char[10];
        sprintf(buf, "%d,%d", _camp, int(floor(newValue)));
        EventCustom event("event_update_population");
        event.setUserData(buf);
        _eventDispatcher->dispatchEvent(&event);
    }
    _fractionHumanResource = newValue;
}

// 祭祀数值修改
bool Player::changeFractionValue(float value)
{
    float newValue = _fractionMP + value;
    if (newValue > _fractionMaxMP) {
        newValue = _fractionMaxMP;
    }
    if (newValue >= 0) {
        setFractionValue(newValue);
        return true;
    } else{
        log("not enougth FractionValue");
        return false;
    }
}
void Player::setFractionValue(float newValue)
{
    if(abs(floor(newValue) - floor(_fractionMP)) > MinNum){
        char* buf = new char[10];
        sprintf(buf, "%d,%d", _camp, int(floor(newValue)));
        EventCustom event("event_update_sacrifice_value");
        event.setUserData(buf);
        _eventDispatcher->dispatchEvent(&event);
    }
    _fractionMP = newValue;
    if (_fractionMP >= _fractionMaxMP) {
        update(0);
    }
}

bool Player::changeHPValue(float value)
{
    float newValue = _fractionHP + value;
    if (newValue > _fractionMaxHP) {
        newValue = _fractionMaxHP;
    }
    if (newValue > 0) {
        setHPValue(newValue);
        return true;
    } else{
        log("not enougth FractionValue");
        return false;
    }
}
void Player::setHPValue(float newValue)
{
    if(abs(floor(newValue) - floor(_fractionHP)) > MinNum){
        char* buf = new char[10];
        sprintf(buf, "%d,%d", _camp, int(floor(newValue)));
        EventCustom event("event_update_hp_value");
        event.setUserData(buf);
        _eventDispatcher->dispatchEvent(&event);
    }
    _fractionHP = newValue;
}


void Player::initData()
{
    auto vmap = JsonUtils::valueVectorFromJsonFile("Fractions.json");
//    log("camp value %d", _camp);
    for (auto item : vmap)
    {
        auto  date = item.asValueMap();
        int id = date.at("FractionID").asInt() - 1;
//        log("camp value %d %d", _camp, id);
        if (_camp == id) {
            _fractionMaxHP = date.at("FractionMaxHP").asInt();//人物最高血量
            _fractionMaxMP = date.at("FractionMaxMP").asInt();//祭司数值最高数值
            _fractionHumanResourceIncreasPerSecond = date.at("FractionHumanResourceIncreasPerSecond").asFloat();//人力每秒增长值
            setHumanResourceValue(date.at("FractionInitHumanResource").asInt());//人力基础数值
            setHPValue(date.at("FractionInitHP").asInt());//人物血量
            setFractionValue(date.at("FractionInitMP").asInt());//祭司血量
        }
    }
    
    this->scheduleUpdate();
    this->schedule(CC_SCHEDULE_SELECTOR(Player::addHumanResource), 1);
//    (<#SEL_SCHEDULE selector#>, <#float interval#>, <#unsigned int repeat#>, <#float delay#>)

}

bool Player::addFractionValueFromHero(HeroEnety::HeroEunm heroEnum)
{
    HeroEnety* hero = nullptr;
    switch (heroEnum) {
        case HeroEnety::HeroEunm::ArrowMan:
            hero = ArrowMan::create(heroEnum, HeroEnety::RaceEunm::Red, 1);
            break;
            
        case HeroEnety::HeroEunm::Missionary:
            hero = Missionary::create(heroEnum, HeroEnety::RaceEunm::Red, 1);
            break;
            
        case HeroEnety::HeroEunm::SwordsMan:
            hero = SwordsMan::create(heroEnum, HeroEnety::RaceEunm::Red, 1);
            break;
            
        default:
            break;
    }
    if (hero) {
        //del suc
        if (changeHumanResourceValue(-hero->ManPowerToProduce)){
            // add
            return changeFractionValue(hero->DirectSacrificeValue);
        }
    }
    return false;
}

void Player::addListen()
{
    Director::getInstance()->getEventDispatcher()->addCustomEventListener("event_arrive_base", [this](cocos2d::EventCustom* event){
        ValueMap* data = (ValueMap*)event->getUserData();
        
        int raceEnum = data->at("RaceEunm").asInt();
        if (raceEnum == _camp) {
            int fractionOffset = data->at("fractionOffset").asInt();
            int humanResOffset = data->at("humanResOffset").asInt();
            int HPOffset = data->at("HPOffset").asInt();
            this->changePlayerParamsFromManWhlieAttainBase(fractionOffset, humanResOffset, HPOffset);
        }
    });
    /*
    Director::getInstance()->getEventDispatcher()->addCustomEventListener(
                                                                          "event_update_hp_value",
                                                                          [this](cocos2d::EventCustom* event){
                                                                              CCLOG("event_update_hp_value");
                                                                              string data((char *)event->getUserData());
                                                                              CCLOG("event_update_hp_value %s", data.c_str());
                                                                              vector<std::string> vect;
                                                                              Utils::split(data, ",", vect);
                                                                              int enumValue= atoi(vect[1].c_str());
                                                                              this->addFractionValueFromHero((HeroEnety::HeroEunm)enumValue);
                                                                          });
     */

}

void Player::changePlayerParamsFromManWhlieAttainBase(int fractionOffset, int humanResOffset, int HPOffset)
{

    changeFractionValue(fractionOffset);
    changeHPValue(HPOffset);
    changeHumanResourceValue(humanResOffset);

}
