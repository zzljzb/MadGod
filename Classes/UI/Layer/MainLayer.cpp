//
//  MainLayer.cpp
//  ggj-jzb
//
//  Created by jzb on 16/1/29.
//
//

#include "MainLayer.hpp"
#include "ui/UIScale9Sprite.h"
#include "HeroManager.h"
#include "SwordsMan.h"
#include "Player.h"
#include "DataManager.hpp"
#include "Utils.hpp"
#include "MsgManager.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;
using namespace std;
using namespace ui;

static string mineFilePath[3] = {"mine_left.png", "mine_mid.png", "mine_right.png"};
static float minePos[3][2] = {{0.4, 0.8}, {0.5, 0.55}, {0.6, 0.2}};
static float RoadPosY[] = {0, 98, 190, 287, 385, 481, 577};
static int RoadNum = 5;
static int RoadOffset = RoadPosY[1] - RoadPosY[0];
MainLayer::MainLayer()
{
    
}

MainLayer::~MainLayer()
{
    
}

Scene* MainLayer::createScene()
{
    auto scene = Scene::create();
    auto layer = MainLayer::create();
    scene->addChild(layer);
    return scene;
}

bool MainLayer::init()
{
    if (!Layer::init())
    {
        return false;
    }
	_limitPosRight = DataManager::getInstance()->getLimitPosRight();
    _limitPosLeft = DataManager::getInstance()->getLimitPosLeft();
    
    initListeners();
    
    CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic("BGM.ogg", true);
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    this->addChild(HeroManager::getInstance());
    
    auto bg = Scale9Sprite::create("bg.jpg");
    bg->setContentSize(Size(visibleSize));
    bg->setCapInsets(Rect(0, 0, 0, 0));
    bg->setPosition(Vec2(origin.x + visibleSize.width * 0.5, origin.y + visibleSize.height * 0.5));
    this->addChild(bg);
    
    _pLeftPanel = OperatePanel::create(kOperatePanelLeft);
    _pLeftPanel->setPosition(Vec2(origin.x, origin.y));
    _pLeftPanel->addListener(this);
    this->addChild(_pLeftPanel);

    _pRightPanel  = OperatePanel::create(kOperatePanelRight);
    _pRightPanel->setPosition(Vec2(origin.x + visibleSize.width - _pRightPanel->getContentSize().width, origin.y));
    _pRightPanel->addListener(this);
    this->addChild(_pRightPanel);
    
    _playerRed = Player::create();
    _playerRed->setCamp(HeroEnety::RaceEunm::Red);
    this->addChild(_playerRed);
    
    _playerBlue = Player::create();
    _playerBlue->setCamp(HeroEnety::RaceEunm::Blue);
    this->addChild(_playerBlue);
    
    this->initTouchesListener();
    this->initMine();
    
    this->schedule([this](float){
        this->firstMineSendFarmerToLeft();
    }, 3.0, -1, 0, "firstMineSendFarmerToLeft");
    this->schedule([this](float){
        this->firstMineSendFarmerToRight();
    }, 3.0, -1, 0, "firstMineSendFarmerToRight");
    this->schedule([this](float){
        this->secondMineSendFarmerToLefrt();
    }, 3.0, -1, 0, "secondMineSendFarmerToLefrt");
    this->schedule([this](float){
        this->secondMineSendFarmerToRight();
    }, 3.0, -1, 0, "secondMineSendFarmerToRight");
    this->schedule([this](float){
        this->thirdMineSendFarmerToLeft();
    }, 3.0, -1, 0, "thirdMineSendFarmerToLeft");
    this->schedule([this](float){
        this->thirdMineSendFarmerToRight();
    }, 3.0, -1, 0, "thirdMineSendFarmerToRight");
    
    return true;
}

void MainLayer::onSkill1ButtonDown(OPERATE_PANEL_TYPE type)
{
    if (type == kOperatePanelLeft)
    {
        if (this->_leftSkillSprite == nullptr)
        {
            _leftSkillSprite = Sprite::create("sd3.png");
            _leftSkillSprite->setName("left_skill_sprite");
            _leftSkillSprite->setPosition(Vec2(400, 20));
            this->addChild(_leftSkillSprite);
        }
    }
    else
    {
        if (this->_rightSkillSprite == nullptr)
        {
            _rightSkillSprite = Sprite::create("sd3.png");
            _rightSkillSprite->setName("right_skill_sprite");
            _rightSkillSprite->setFlippedX(true);
            this->addChild(_rightSkillSprite);
        }
    }
}

void MainLayer::onSoliderSelectedBegin(ARMS arms, const Vec2& pos)
{
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    string selectedImgPath = "";
    switch (arms)
    {
        case kArmsFireballSoldier:
            selectedImgPath = "fireball_soldier.png";
            break;
            
        case kArmsMissionary:
            selectedImgPath = "missionary.png";
            break;
            
        case kArmsPrivateSoldier:
            selectedImgPath = "private_soldier.png";
            
        default:
            break;
    }
    
    if (pos.x > origin.x + visibleSize.width * 0.5)
    {
        if (this->_rightSelectedSolider == nullptr)
        {
            _rightSelectedSolider = Sprite::create(selectedImgPath);
            _rightSelectedSolider->setFlippedX(true);
            _rightSelectedSolider->setName("right_selected_solider");
            _rightSelectedSolider->setPosition(pos);
            _rightSelectedSolider->setAnchorPoint(Vec2(0, 0));
            this->addChild(_rightSelectedSolider);
            this->_rightSelectedArm = arms;
        }
    }
    else
    {
        if (this->_leftSelectedSolider == nullptr)
        {
            _leftSelectedSolider = Sprite::create(selectedImgPath);
            _leftSelectedSolider->setName("left_selected_solider");
            _leftSelectedSolider->setPosition(pos);
            _leftSelectedSolider->setAnchorPoint(Vec2(0, 0));
            this->addChild(_leftSelectedSolider);
            this->_leftSelectedArm = arms;
        }
    }
}

void MainLayer::onSoliderSelectedEnd(ARMS arms, const Vec2& pos)
{

}

void MainLayer::initMine()
{
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    for (int i = 0; i < 3; i++)
    {
        Sprite* mineSprite = Sprite::create(mineFilePath[i]);
        mineSprite->setPosition(Vec2(origin.x + visibleSize.width * minePos[i][0], origin.y + visibleSize.height * minePos[i][1]));
        _mines.pushBack(mineSprite);
        this->addChild(mineSprite);
    }
}

void MainLayer::initListeners()
{
    Director::getInstance()->getEventDispatcher()->addCustomEventListener("event_update_population", [this](cocos2d::EventCustom* event)
    {
        string data((char *)event->getUserData());
        vector<std::string> vect;
        Utils::split(data, ",", vect);
        int population = atoi(vect[1].c_str());
        if (vect[0] == "0")
        {
            this->_pLeftPanel->setPopulation(population);
        }
        else
        {
            this->_pRightPanel->setPopulation(population);
        }
    });
    
    Director::getInstance()->getEventDispatcher()->addCustomEventListener("event_update_sacrifice_value", [this](cocos2d::EventCustom* event)
    {
        string data((char *)event->getUserData());
        vector<std::string> vect;
        Utils::split(data, ",", vect);
        int loyalty = atoi(vect[1].c_str());
        if (vect[0] == "0")
        {
            this->_pLeftPanel->setLoaylty(loyalty);
        }
        else
        {
            this->_pRightPanel->setLoaylty(loyalty);
        }
    });
    
    Director::getInstance()->getEventDispatcher()->addCustomEventListener("event_update_hp_value", [this](cocos2d::EventCustom* event)
    {
        string data((char *)event->getUserData());
        vector<std::string> vect;
        Utils::split(data, ",", vect);
        int hp = atoi(vect[1].c_str());
        if (vect[0] == "0")
        {
            this->_pLeftPanel->setHp(hp);
        }
        else
        {
            this->_pRightPanel->setHp(hp);
        }
    });
    
    Director::getInstance()->getEventDispatcher()->addCustomEventListener("event_all_solider_die", [this](cocos2d::EventCustom* event)
    {
        string data((char *)event->getUserData());
    });
    
    Director::getInstance()->getEventDispatcher()->addCustomEventListener("event_mine_state_change", [this](cocos2d::EventCustom* event)
    {
    });
    
    Director::getInstance()->getEventDispatcher()->addCustomEventListener("left_occupied_mine_0", [this](cocos2d::EventCustom* event)
    {
        DataManager::getInstance()->setMineState(0, kMineStateOccupiedLeft);
        this->_mines.at(0)->setOpacity(90);
    });
    
    Director::getInstance()->getEventDispatcher()->addCustomEventListener("right_occupied_mine_0", [this](cocos2d::EventCustom* event)
    {
        DataManager::getInstance()->setMineState(0, kMineStateOccupiedRight);
        this->_mines.at(0)->setOpacity(90);
    });
    
    Director::getInstance()->getEventDispatcher()->addCustomEventListener("mine_config_0", [this](cocos2d::EventCustom* event)
    {
        DataManager::getInstance()->setMineState(0, kMineStateConfit);
        this->_mines.at(0)->setOpacity(255);
    });
    
    Director::getInstance()->getEventDispatcher()->addCustomEventListener("left_occupied_mine_1", [this](cocos2d::EventCustom* event)
    {
        DataManager::getInstance()->setMineState(1, kMineStateOccupiedLeft);
        this->_mines.at(1)->setOpacity(90);
    });
    
    Director::getInstance()->getEventDispatcher()->addCustomEventListener("right_occupied_mine_1", [this](cocos2d::EventCustom* event)
    {
        DataManager::getInstance()->setMineState(1, kMineStateOccupiedRight);
        this->_mines.at(1)->setOpacity(90);
    });
    
    Director::getInstance()->getEventDispatcher()->addCustomEventListener("mine_config_1", [this](cocos2d::EventCustom* event)
    {
        DataManager::getInstance()->setMineState(1, kMineStateConfit);
        this->_mines.at(1)->setOpacity(255);
    });
    
    Director::getInstance()->getEventDispatcher()->addCustomEventListener("left_occupied_mine_2", [this](cocos2d::EventCustom* event)
    {
        DataManager::getInstance()->setMineState(2, kMineStateOccupiedLeft);
        this->_mines.at(2)->setOpacity(255);
    });
    
    Director::getInstance()->getEventDispatcher()->addCustomEventListener("right_occupied_mine_2", [this](cocos2d::EventCustom* event)
    {
        DataManager::getInstance()->setMineState(2, kMineStateOccupiedRight);
        this->_mines.at(2)->setOpacity(255);
    });
    
    Director::getInstance()->getEventDispatcher()->addCustomEventListener("mine_config_2", [this](cocos2d::EventCustom* event)
    {
        DataManager::getInstance()->setMineState(2, kMineStateConfit);
        this->_mines.at(2)->setOpacity(255);
    });
    
    Director::getInstance()->getEventDispatcher()->addCustomEventListener("missionary_dead", [this](cocos2d::EventCustom* event)
    {
        ValueMap* data = (ValueMap*)event->getUserData();
        if (data)
        {
            int radid = data->at("raid").asInt();
            bool isLeft = data->at("isLeft").asBool();
            if (radid == 5)
            {
                if (isLeft)
                {
                    if (DataManager::getInstance()->getMineState(0) == kMineStateConfit)
                    {
                        DataManager::getInstance()->setMineState(0, kMineStateOccupiedRight);
                    }
                    else
                    {
                        DataManager::getInstance()->setMineState(0, kMineStateIdle);
                    }
                }
                else
                {
                    if (DataManager::getInstance()->getMineState(0) == kMineStateConfit)
                    {
                        DataManager::getInstance()->setMineState(0, kMineStateOccupiedLeft);
                    }
                    else
                    {
                        DataManager::getInstance()->setMineState(0, kMineStateIdle);
                    }
                }
                
            }
            
            if (radid == 3)
            {
                if (isLeft)
                {
                    if (DataManager::getInstance()->getMineState(1) == kMineStateConfit)
                    {
                        DataManager::getInstance()->setMineState(1, kMineStateOccupiedRight);
                    }
                    else
                    {
                        DataManager::getInstance()->setMineState(1, kMineStateIdle);
                    }
                }
                else
                {
                    if (DataManager::getInstance()->getMineState(1) == kMineStateConfit)
                    {
                        DataManager::getInstance()->setMineState(1, kMineStateOccupiedLeft);
                    }
                    else
                    {
                        DataManager::getInstance()->setMineState(1, kMineStateIdle);
                    }
                }
            }
            
            if (radid == 1)
            {
                if (isLeft)
                {
                    if (DataManager::getInstance()->getMineState(2) == kMineStateConfit)
                    {
                        DataManager::getInstance()->setMineState(2, kMineStateOccupiedRight);
                    }
                    else
                    {
                        DataManager::getInstance()->setMineState(2, kMineStateIdle);
                    }
                }
                else
                {
                    if (DataManager::getInstance()->getMineState(2) == kMineStateConfit)
                    {
                        DataManager::getInstance()->setMineState(2, kMineStateOccupiedLeft);
                    }
                    else
                    {
                        DataManager::getInstance()->setMineState(2, kMineStateIdle);
                    }
                    
                }
            }
            
        }
    });
}

void MainLayer::initTouchesListener()
{
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    auto touchAllInOnce = EventListenerTouchAllAtOnce::create();
    touchAllInOnce->onTouchesBegan = [this](const std::vector<Touch*>& touches, Event *event)
    {
        for (auto touch : touches)
        {
            if (this->_leftSkillSprite)
            {
                if (this->_leftSkillSprite->getBoundingBox().containsPoint(touch->getLocation()))
                {
                    this->_leftSkillSprite->setTag(touch->getID());
                }
            }
            if (this->_rightSkillSprite)
            {
                if (this->_rightSkillSprite->getBoundingBox().containsPoint(touch->getLocation()))
                {
                    this->_rightSkillSprite->setTag(touch->getID());
                }
            }
            if (this->_leftSelectedSolider)
            {
                if (this->_leftSelectedSolider->getBoundingBox().containsPoint(touch->getLocation()))
                {
                    this->_leftSelectedSolider->setTag(touch->getID());
                }
            }
            if (this->_rightSelectedSolider)
            {
                if (this->_rightSelectedSolider->getBoundingBox().containsPoint(touch->getLocation()))
                {
                    this->_rightSelectedSolider->setTag(touch->getID());
                }
            }
        }
    };
    touchAllInOnce->onTouchesMoved = [this](const std::vector<Touch*>& touches, Event *event)
    {
        for (auto touch : touches)
        {
            int touchId = touch->getID();
            auto child = this->getChildByTag(touchId);
            if (child)
            {
                child->setPosition(touch->getLocation());
            }
        }
    };
    touchAllInOnce->onTouchesEnded = [this, origin, visibleSize](const std::vector<Touch*>& touches, Event *event)
    {
        for (auto touch : touches)
        {
            int touchId = touch->getID();
            auto child = this->getChildByTag(touchId);
            if (child)
            {
                Vec2 pos = child->getPosition();
                pos.y += RoadOffset / 2;
                string name = child->getName();
                if (name == "left_selected_solider")
                {
                    if (pos.x < 100 && pos.y > 320)
                    {
                        HeroEnety::HeroEunm type;
                        switch (this->_leftSelectedArm) {
                            case kArmsFireballSoldier:
                                type = HeroEnety::HeroEunm::ArrowMan;
                                break;
                                
                            case kArmsMissionary:
                                type = HeroEnety::HeroEunm::Missionary;
                                break;
                                
                            case kArmsPrivateSoldier:
                                type = HeroEnety::HeroEunm::ArrowMan;
                                break;
                                
                            default:
                                break;
                        }
                        
                        _playerRed->addFractionValueFromHero(type);
                    }
                    else
                    {
                        int roadIndex = getRoadIndexFromPos(pos);

                        ProgressTimer* cdTimer = ProgressTimer::create(this->_leftSelectedSolider);
                        cdTimer->setPosition(Vec2(_limitPosLeft + 100, RoadPosY[roadIndex] + RoadOffset / 2));
                        this->addChild(cdTimer);
                        cdTimer->setPercentage(0);
                        ProgressTo* progressTo = ProgressTo::create(2, 100);
                        CallFunc * funcall= CallFunc::create([this, roadIndex](){
                            if(roadIndex > 0 && roadIndex <= RoadNum){
                                HeroEnety* hero = nullptr;
                                switch (this->_leftSelectedArm)
                                {
                                    case kArmsPrivateSoldier:
                                        hero = _playerRed->addSworldsMan(HeroEnety::HeroEunm::SwordsMan,  roadIndex);
                                        break;
                                        
                                    case kArmsFireballSoldier:
                                        hero = _playerRed->addSworldsMan(HeroEnety::HeroEunm::ArrowMan, roadIndex);
                                        break;
                                        
                                    case kArmsMissionary:
                                        hero = _playerRed->addSworldsMan(HeroEnety::HeroEunm::Missionary, roadIndex);
                                        break;
                                        
                                    default:
                                        break;
                                }
                                
                                if (hero) {
                                    hero->setPosition(Vec2(_limitPosLeft + 100, RoadPosY[roadIndex] + RoadOffset / 2));
                                    this->addChild(hero);
                                } else{
                                    MsgManager::getInstance()->popMsg("no enough");
                                }
                            }
                        });
                        Sequence* action = Sequence::create(progressTo, funcall, Hide::create(), nullptr);
                        cdTimer->runAction(action);
                    }
                    
                    this->removeChild(this->_leftSelectedSolider);
                    this->_leftSelectedSolider = nullptr;
                    

                }
                else if (name == "right_selected_solider")
                {
                    if (pos.x > 750 && pos.y > 320)
                    {
                        HeroEnety::HeroEunm type;
                        switch (this->_rightSelectedArm) {
                            case kArmsFireballSoldier:
                                type = HeroEnety::HeroEunm::ArrowMan;
                                break;
                                
                            case kArmsMissionary:
                                type = HeroEnety::HeroEunm::Missionary;
                                break;
                                
                            case kArmsPrivateSoldier:
                                type = HeroEnety::HeroEunm::ArrowMan;
                                break;
                                
                            default:
                                break;
                        }
                        _playerBlue->addFractionValueFromHero(type);
                    }
                    else
                    {
                        int roadIndex = getRoadIndexFromPos(pos);

   
                        ProgressTimer* cdTimer = ProgressTimer::create(this->_rightSelectedSolider);
                        cdTimer->setPosition(Vec2(_limitPosRight - 100, RoadPosY[roadIndex] + RoadOffset / 2));
                        this->addChild(cdTimer);
                        cdTimer->setPercentage(0);
                        ProgressTo* progressTo = ProgressTo::create(2, 100);
                        CallFunc * funcall= CallFunc::create([this, roadIndex](){
                            if(roadIndex > 0 && roadIndex <= RoadNum){
                                HeroEnety* hero = nullptr;
                                switch (this->_rightSelectedArm)
                                {
                                    case kArmsPrivateSoldier:
                                        hero = _playerBlue->addSworldsMan(HeroEnety::HeroEunm::SwordsMan, roadIndex);
                                        break;
                                        
                                    case kArmsFireballSoldier:
                                        hero = _playerBlue->addSworldsMan(HeroEnety::HeroEunm::ArrowMan, roadIndex);
                                        break;
                                        
                                    case kArmsMissionary:
                                        hero = _playerBlue->addSworldsMan(HeroEnety::HeroEunm::Missionary, roadIndex);
                                        break;
                                        
                                    default:
                                        break;
                                }
                                
                                //SwordsMan* swordsMan = _playerBlue->addSworldsMan(HeroEnety::HeroEunm::SwordsMan,  roadIndex);
                                if(hero){
                                    hero->setPosition(Vec2(_limitPosRight - 100, RoadPosY[roadIndex] + RoadOffset / 2));
                                    this->addChild(hero);
                                } else{
                                    MsgManager::getInstance()->popMsg("no enough");
                                }
                            }
                        });
                        Sequence* action = Sequence::create(progressTo, funcall, Hide::create(), nullptr);
                        cdTimer->runAction(action);
                    }

                    this->removeChild(this->_rightSelectedSolider);
                    this->_rightSelectedSolider = nullptr;
                }
                else if (name == "left_skill_sprite")
                {
                    if (pos.x > 200 && pos.x < origin.x + visibleSize.width - 200)
                    {
                        this->_rightSkillSprite->setPosition(Vec2(origin.x + visibleSize.width * 0.5, pos.y));
                        FadeIn* fadeIn = FadeIn::create(1.0);
                        FadeOut* fadeOut = FadeOut::create(1.0);
                        CallFunc * funcall= CallFunc::create([this](){
                            this->removeChild(this->_rightSelectedSolider);
                            this->_rightSelectedSolider = nullptr;
                        });
                        Sequence* action = Sequence::create(fadeIn, fadeOut, funcall, NULL);
                        this->_rightSkillSprite->runAction(action);
                    }
                    
                }
                else if (name == "right_skill_sprite")
                {
                    if (pos.x > 200 && pos.x < origin.x + visibleSize.width - 200)
                    {
                        this->_rightSkillSprite->setPosition(Vec2(origin.x + visibleSize.width * 0.5, pos.y));
                        FadeIn* fadeIn = FadeIn::create(1.0);
                        FadeOut* fadeOut = FadeOut::create(1.0);
                        CallFunc * funcall= CallFunc::create([this](){
                            this->removeChild(this->_rightSelectedSolider);
                            this->_rightSelectedSolider = nullptr;
                        });
                        Sequence* action = Sequence::create(fadeIn, fadeOut, funcall, NULL);
                        this->_rightSkillSprite->runAction(action);
                    }
                    
                    auto vechero=HeroManager::getInstance()->Vec_HeroRed;
                    for(auto hero:vechero){
                        int roadindex=hero->roadID;
                        if (roadindex==getRoadIndexFromPos(pos)){
                            hero->NormalHit(10);
                        }
                    
                    
                    }
                    
                    
                    
                }
                else
                {
                    
                }                
            }
        }
    };
    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(touchAllInOnce, this);
}

void MainLayer::firstMineSendFarmerToLeft()
{
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    if (DataManager::getInstance()->getMineState(0) == kMineStateOccupiedLeft)
    {
        Farmer* farmer = Farmer::create(HeroEnety::HeroEunm::Farmer, HeroEnety::RaceEunm::Blue, 4);
        farmer->setPosition(Vec2(origin.x + visibleSize.width * 0.4, origin.y + visibleSize.height * 0.8));
        farmer->GoForward();
        farmer->addListener(this);
        this->addChild(farmer);
    }
}

void MainLayer::firstMineSendFarmerToRight()
{
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    if (DataManager::getInstance()->getMineState(0) == kMineStateOccupiedRight)
    {
        Farmer* farmer = Farmer::create(HeroEnety::HeroEunm::Farmer, HeroEnety::RaceEunm::Red, 4);
        farmer->addListener(this);
        farmer->setPosition(Vec2(origin.x + visibleSize.width * 0.4, origin.y + visibleSize.height * 0.8));
        farmer->GoForward();
        this->addChild(farmer);
    }
}

void MainLayer::secondMineSendFarmerToLefrt()
{
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    if (DataManager::getInstance()->getMineState(1) == kMineStateOccupiedLeft)
    {
        Farmer* farmer = Farmer::create(HeroEnety::HeroEunm::Farmer, HeroEnety::RaceEunm::Blue, 4);
        farmer->addListener(this);
        farmer->setPosition(Vec2(origin.x + visibleSize.width * 0.5, origin.y + visibleSize.height * 0.55));
        farmer->GoForward();
        this->addChild(farmer);
    }
}

void MainLayer::secondMineSendFarmerToRight()
{
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    if (DataManager::getInstance()->getMineState(1) == kMineStateOccupiedRight)
    {
        Farmer* farmer = Farmer::create(HeroEnety::HeroEunm::Farmer, HeroEnety::RaceEunm::Red, 4);
        farmer->addListener(this);
        farmer->setPosition(Vec2(origin.x + visibleSize.width * 0.5, origin.y + visibleSize.height * 0.55));
        farmer->GoForward();
        this->addChild(farmer);
    }
}

void MainLayer::thirdMineSendFarmerToLeft()
{
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    if (DataManager::getInstance()->getMineState(2) == kMineStateOccupiedLeft)
    {
        Farmer* farmer = Farmer::create(HeroEnety::HeroEunm::Farmer, HeroEnety::RaceEunm::Blue, 4);
        farmer->addListener(this);
        farmer->setPosition(Vec2(origin.x + visibleSize.width * 0.6, origin.y + visibleSize.height * 0.2));
        farmer->GoForward();
        this->addChild(farmer);
    }
}

void MainLayer::thirdMineSendFarmerToRight()
{
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    if (DataManager::getInstance()->getMineState(2) == kMineStateOccupiedRight)
    {
        Farmer* farmer = Farmer::create(HeroEnety::HeroEunm::Farmer, HeroEnety::RaceEunm::Red, 4);
        farmer->addListener(this);
        farmer->setPosition(Vec2(origin.x + visibleSize.width * 0.6, origin.y + visibleSize.height * 0.2));
        farmer->GoForward();
        this->addChild(farmer);
    }
}

void MainLayer::onReachLeft()
{
    //do nothing
}

void MainLayer::onReachRight()
{
    //do nothing
}

int MainLayer::getRoadIndexFromPos(Vec2 pos)
{
    int index = 0;
    if (pos.y >= RoadPosY[1] && pos.y <= RoadPosY[RoadNum + 1]) {
        index = (pos.y - RoadPosY[1])/RoadOffset + 1;
    }
    return index;
}

