//
//  MainLayer.hpp
//  ggj-jzb
//
//  Created by jzb on 16/1/29.
//
//

#ifndef MainLayer_hpp
#define MainLayer_hpp

#include "cocos2d.h"
#include "OperatePanel.hpp"
#include "Player.h"
#include "GlobalDefine.h"
#include "Farmer.hpp"

class MainLayer : public cocos2d::Layer, public OperatePanelListener, public FarmerListener
{
public:
    CREATE_FUNC(MainLayer);
    static cocos2d::Scene* createScene();
    
public:
    virtual void onSkill1ButtonDown(OPERATE_PANEL_TYPE type) override;
    virtual void onSoliderSelectedBegin(ARMS arms, const cocos2d::Vec2& pos) override;
    virtual void onSoliderSelectedEnd(ARMS arms, const cocos2d::Vec2& pos) override;
    
    virtual void onReachLeft() override;
    virtual void onReachRight() override;
    
protected:
    MainLayer();
    virtual ~MainLayer();
    
private:
    bool init() override;
    void initMine();
    void initListeners();
    void initTouchesListener();
    
    void firstMineSendFarmerToLeft();
    void firstMineSendFarmerToRight();
    void secondMineSendFarmerToLefrt();
    void secondMineSendFarmerToRight();
    void thirdMineSendFarmerToLeft();
    void thirdMineSendFarmerToRight();
	inline int getRoadIndexFromPos(Vec2 pos);
    
private:
    cocos2d::Sprite* _leftSkill1Sprite = nullptr;
    cocos2d::Sprite* _leftSelectedSolider = nullptr;
    
    cocos2d::Sprite* _leftSkillSprite = nullptr;
    cocos2d::Sprite* _rightSkillSprite = nullptr;
    cocos2d::Sprite* _rightSelectedSolider = nullptr;
    
    Player* _playerBlue = nullptr;
    Player* _playerRed = nullptr;
    
    cocos2d::Vector<cocos2d::Sprite*> _mines;
    
    OperatePanel* _pLeftPanel = nullptr;
    OperatePanel* _pRightPanel = nullptr;
    
    ARMS _leftSelectedArm = kArmsFireballSoldier;
    ARMS _rightSelectedArm = kArmsFireballSoldier;
	float _limitPosLeft;
    float _limitPosRight;
};

#endif /* MainLayer_hpp */
