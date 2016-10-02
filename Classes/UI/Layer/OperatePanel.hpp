//
//  OperatePanel.hpp
//  ggj-jzb
//
//  Created by jzb on 16/1/30.
//
//

#ifndef OperatePanel_hpp
#define OperatePanel_hpp

#include "cocos2d.h"
#include "ui/UIRelativeBox.h"
#include "SoliderIconPanel.hpp"
#include "ui/UIText.h"
#include "2d/CCProgressTimer.h"
#include "ui/UIButton.h"

typedef enum
{
    kOperatePanelLeft = 0,
    kOperatePanelRight
}OPERATE_PANEL_TYPE;

class OperatePanelListener
{
public:
    virtual void onSkill1ButtonDown(OPERATE_PANEL_TYPE type) = 0;
    virtual void onSoliderSelectedBegin(ARMS arms, const cocos2d::Vec2& pos) = 0;
    virtual void onSoliderSelectedEnd(ARMS arms, const cocos2d::Vec2& pos) = 0;
};

class OperatePanel : public cocos2d::ui::RelativeBox, public SoliderIconPanelListener
{
public:
    static OperatePanel* create(OPERATE_PANEL_TYPE type);
    
    virtual void onSoliderSelectedBegin(ARMS arms, const cocos2d::Vec2& pos) override;
    virtual void onSoliderSelectedEnd(ARMS arms, const cocos2d::Vec2& pos) override;
    
public:
    void addListener(OperatePanelListener* listner);
    void removeListener();
    
    void setPopulation(int population);
    void setLoaylty(int loaylty);
    void setHp(int hp);
    
protected:
    OperatePanel();
    virtual ~OperatePanel();
    
private:
    bool init(OPERATE_PANEL_TYPE type);
    void initSoliderPanel();
    void initPopulationPanel();
    void initAltar();
    void initSkillButton();
    
private:
    OPERATE_PANEL_TYPE _type = kOperatePanelLeft;
    SoliderIconPanel* _pSoliderIconPanel = nullptr;
    cocos2d::ui::Text* _populationText = nullptr;
    cocos2d::ui::Text* _hpText = nullptr;
    cocos2d::ui::Button* _leftSkillButton = nullptr;
    cocos2d::ui::Button* _rightSkillButton = nullptr;
    OperatePanelListener* _listener = nullptr;
    cocos2d::ui::ImageView* _altarImg = nullptr;
};

#endif /* OperatePanel_hpp */
