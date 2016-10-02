//
//  SoliderIconPanel.cpp
//  ggj-jzb
//
//  Created by jzb on 16/1/29.
//
//

#include "SoliderIconPanel.hpp"
#include "SoliderIcon.hpp"

USING_NS_CC;
using namespace std;
using namespace ui;

static string filePath[3] = {"buy_private_solider.png", "buy_fireball_solider.png", "buy_missionary.png"};
static ARMS armsType[3] = {kArmsPrivateSoldier, kArmsFireballSoldier, kArmsMissionary};
SoliderIconPanel::SoliderIconPanel()
{
    
}

SoliderIconPanel::~SoliderIconPanel()
{
    
}

bool SoliderIconPanel::init()
{
    if (!RelativeBox::init())
    {
        return false;
    }
    
    this->setContentSize(Size(91, 326));
    
    for (int i = 0; i < 3; i++)
    {
        ValueMap data;
        data.insert(pair<string, Value>("filePath", Value(filePath[i])));
        data.insert(pair<string, Value>("arms", Value((int)armsType[i])));
        SoliderIcon* soliderIcon = SoliderIcon::create(data);
        Size soliderIconSize = soliderIcon->getContentSize();
        auto layoutParameter = RelativeLayoutParameter::create();
        layoutParameter->setAlign(RelativeLayoutParameter::RelativeAlign::PARENT_TOP_CENTER_HORIZONTAL);
        layoutParameter->setMargin(Margin(0, i * (102 + 10), 0, 0));
        soliderIcon->setLayoutParameter(layoutParameter);
        soliderIcon->addListener(this);
        _icons.pushBack(soliderIcon);
        this->addChild(soliderIcon);
    }
    
    return true;
}

void SoliderIconPanel::onSoliderSelectedBegin(ARMS arms, const Vec2& pos)
{
    this->setOpacity(90);
    if (_listener)
    {
        Vec2 worldPos = this->convertToWorldSpace(pos);
        _listener->onSoliderSelectedBegin(arms, worldPos);
    }
}

void SoliderIconPanel::onSoliderSelectedEnd(ARMS arms, const Vec2& pos)
{
    this->setOpacity(255);
    if (_listener)
    {
        Vec2 worldPos = this->convertToWorldSpace(pos);
        _listener->onSoliderSelectedEnd(arms, worldPos);
    }
}

void SoliderIconPanel::addListener(SoliderIconPanelListener* listener)
{
    CCAssert(listener != nullptr, "invalid listener");
    _listener = listener;
}

void SoliderIconPanel::removeListener()
{
    _listener = nullptr;
}
