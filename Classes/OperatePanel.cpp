//
//  OperatePanel.cpp
//  ggj-jzb
//
//  Created by jzb on 16/1/30.
//
//

#include "OperatePanel.hpp"

USING_NS_CC;
using namespace ui;
using namespace std;

OperatePanel::OperatePanel()
{
    
}

OperatePanel::~OperatePanel()
{
    
}

OperatePanel* OperatePanel::create(OPERATE_PANEL_TYPE type)
{
    OperatePanel *pRet = new(std::nothrow) OperatePanel();
    if (pRet && pRet->init(type))
    {
        pRet->autorelease();
        return pRet;
    }
    else
    {
        delete pRet;
        pRet = nullptr;
        return nullptr;
    }
}

bool OperatePanel::init(OPERATE_PANEL_TYPE type)
{
    if (!RelativeBox::init())
    {
        return false;
    }
    
    _type = type;
    this->setContentSize(Size(200, 640));
    
    this->initPopulationPanel();
    this->initSoliderPanel();
    this->initAltar();
    //this->initSkillButton();
    
    return true;
}

void OperatePanel::initPopulationPanel()
{
    RelativeBox* populationBox = RelativeBox::create(Size(200, 100));
    auto boxLayoutParameter = RelativeLayoutParameter::create();
    if (_type == kOperatePanelLeft)
    {
        boxLayoutParameter->setAlign(RelativeLayoutParameter::RelativeAlign::PARENT_TOP_LEFT);
        boxLayoutParameter->setMargin(Margin(100, 0, 0, 0));
    }
    else
    {
        boxLayoutParameter->setAlign(RelativeLayoutParameter::RelativeAlign::PARENT_TOP_RIGHT);
        boxLayoutParameter->setMargin(Margin(0, 0, 100, 0));
    }
    populationBox->setLayoutParameter(boxLayoutParameter);
    this->addChild(populationBox);
    
    _populationText = Text::create("人口: 0", "", 24);
    auto layoutParameter = RelativeLayoutParameter::create();
    layoutParameter->setAlign(RelativeLayoutParameter::RelativeAlign::PARENT_LEFT_CENTER_VERTICAL);
    layoutParameter->setMargin(Margin::ZERO);
    _populationText->setLayoutParameter(layoutParameter);
    populationBox->addChild(_populationText);
    
    _hpText = Text::create("血量: 0", "", 24);
    auto layoutParameter1 = RelativeLayoutParameter::create();
    layoutParameter1->setAlign(RelativeLayoutParameter::RelativeAlign::PARENT_LEFT_CENTER_VERTICAL);
    layoutParameter1->setMargin(Margin(150, 0, 0, 0));
    _hpText->setLayoutParameter(layoutParameter1);
    populationBox->addChild(_hpText);
    
}

void OperatePanel::initSoliderPanel()
{
    _pSoliderIconPanel = SoliderIconPanel::create();
    auto layoutParameter = RelativeLayoutParameter::create();
    if (_type == kOperatePanelLeft)
    {
        layoutParameter->setAlign(RelativeLayoutParameter::RelativeAlign::PARENT_LEFT_BOTTOM);
        layoutParameter->setMargin(Margin(0, 0, 0, 20));
    }
    else
    {
        layoutParameter->setAlign(RelativeLayoutParameter::RelativeAlign::PARENT_RIGHT_BOTTOM);
        layoutParameter->setMargin(Margin(0, 0, 0, 20));
    }
    _pSoliderIconPanel->setLayoutParameter(layoutParameter);
    _pSoliderIconPanel->addListener(this);
    this->addChild(_pSoliderIconPanel, 1);
}

void OperatePanel::initAltar()
{
    string altarImgPath = "altar_left.png";
    if (_type == kOperatePanelRight)
    {
        altarImgPath = "altar_right.png";
    }
    _altarImg = ImageView::create(altarImgPath);
    auto layoutParameter = RelativeLayoutParameter::create();
    if (_type == kOperatePanelLeft)
    {
        layoutParameter->setAlign(RelativeLayoutParameter::RelativeAlign::PARENT_TOP_LEFT);
        layoutParameter->setMargin(Margin(0, 265, 0, 0));
    }
    else
    {
        layoutParameter->setAlign(RelativeLayoutParameter::RelativeAlign::PARENT_TOP_RIGHT);
        layoutParameter->setMargin(Margin(0, 265, 0, 0));
    }

    _altarImg->setLayoutParameter(layoutParameter);
    this->addChild(_altarImg);
}

void OperatePanel::initSkillButton()
{
    _leftSkillButton = Button::create("skill_button.png", "skill_button.png");
    _leftSkillButton->setTitleText("Skill 1");
    _leftSkillButton->setTitleFontSize(24);
    auto leftLayoutParameter = RelativeLayoutParameter::create();
    if (_type == kOperatePanelLeft)
    {
        leftLayoutParameter->setAlign(RelativeLayoutParameter::RelativeAlign::PARENT_TOP_LEFT);
        leftLayoutParameter->setMargin(Margin(100, 550, 0, 0));
    }
    else
    {
        leftLayoutParameter->setAlign(RelativeLayoutParameter::RelativeAlign::PARENT_TOP_RIGHT);
        leftLayoutParameter->setMargin(Margin(0, 550, 200, 0));
    }
    _leftSkillButton->setLayoutParameter(leftLayoutParameter);
    this->addChild(_leftSkillButton);
    _leftSkillButton->addTouchEventListener([this](Ref*, Widget::TouchEventType type)
                                            {
                                                if (type == Widget::TouchEventType::ENDED)
                                                {
                                                    if (this->_listener)
                                                    {
                                                        this->_listener->onSkill1ButtonDown(this->_type);
                                                    }
                                                }
                                            });

    _rightSkillButton = Button::create("skill_button.png", "skill_button.png");
    _rightSkillButton->setTitleText("Skill 2");
    _rightSkillButton->setTitleFontSize(24);
    auto rightLayoutParameter = RelativeLayoutParameter::create();
    if (_type == kOperatePanelLeft)
    {
        rightLayoutParameter->setAlign(RelativeLayoutParameter::RelativeAlign::PARENT_TOP_LEFT);
        rightLayoutParameter->setMargin(Margin(200, 550, 0, 0));
    }
    else
    {
        rightLayoutParameter->setAlign(RelativeLayoutParameter::RelativeAlign::PARENT_TOP_RIGHT);
        rightLayoutParameter->setMargin(Margin(0, 550, 100, 0));
    }
    _rightSkillButton->setLayoutParameter(rightLayoutParameter);
    this->addChild(_rightSkillButton);
    _rightSkillButton->addTouchEventListener([this](Ref*, Widget::TouchEventType type)
                                            {
                                                if (type == Widget::TouchEventType::ENDED)
                                                {
                                                    
                                                }
                                            });
}

void OperatePanel::addListener(OperatePanelListener* listner)
{
    CCAssert(listner != nullptr, "listener should not be nil");
    _listener = listner;
}

void OperatePanel::removeListener()
{
    _listener = nullptr;
}


void OperatePanel::onSoliderSelectedBegin(ARMS arms, const Vec2& pos)
{
    if (_listener)
    {
        _listener->onSoliderSelectedBegin(arms, pos);
    }
}

void OperatePanel::onSoliderSelectedEnd(ARMS arms, const Vec2& pos)
{
    if (_listener)
    {
        _listener->onSoliderSelectedEnd(arms, pos);
    }
}

void OperatePanel::setPopulation(int population)
{
    string lableStr = StringUtils::format("人口: %d", population);
    _populationText->setString(lableStr);
}

void OperatePanel::setLoaylty(int loaylty)
{
    float percent = loaylty / 100.0;
    if (percent > 1)
    {
        percent = 1;
    }
    float length = 500 * percent;
    if (length < _altarImg->getPositionY())
    {
        length = _altarImg->getPositionY() + 10;
    }
    MoveTo* moveBy = MoveTo::create(1.0, Vec2(_altarImg->getPositionX(), length));
    _altarImg->runAction(moveBy);
}

void OperatePanel::setHp(int hp)
{
    string lableStr = StringUtils::format("血量: %d", hp);
    _hpText->setString(lableStr);
}