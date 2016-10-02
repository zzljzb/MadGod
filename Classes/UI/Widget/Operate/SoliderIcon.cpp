//
//  SoliderIcon.cpp
//  ggj-jzb
//
//  Created by jzb on 16/1/29.
//
//

#include "SoliderIcon.hpp"
#include "Utils.hpp"

USING_NS_CC;
using namespace std;
using namespace ui;

SoliderIcon::SoliderIcon()
{
    
}

SoliderIcon::~SoliderIcon()
{
    
}

SoliderIcon* SoliderIcon::create(const ValueMap& data)
{
    SoliderIcon *pRet = new(std::nothrow) SoliderIcon();
    if (pRet && pRet->init(data))
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

bool SoliderIcon::init(const ValueMap& data)
{
    if (!RelativeBox::init())
    {
        return false;
    }
    
    auto size = Size(72, 72);
    this->setContentSize(size);
    
    Utils::stdStringFromMap(data, "filePath", _iconFilePath);
    CCAssert(_iconFilePath != "", "invalid icon file path");
    _iconImg = ImageView::create(_iconFilePath);
    _arms = (ARMS)Utils::integerFromMap(data, "arms");
    auto layoutParameter = RelativeLayoutParameter::create();
    layoutParameter->setAlign(RelativeLayoutParameter::RelativeAlign::CENTER_IN_PARENT);
    layoutParameter->setMargin(Margin::ZERO);
    _iconImg->setLayoutParameter(layoutParameter);
    this->addChild(_iconImg);
    
    this->setTouchEnabled(true);
    this->setSwallowTouches(false);
    this->addTouchEventListener([this](Ref*, Widget::TouchEventType type)
                                {
                                    if (type == Widget::TouchEventType::BEGAN)
                                    {
                                        if (_listener)
                                        {
                                            _listener->onSoliderSelectedBegin(_arms, this->getPosition());
                                        }
                                    }
                                    else if (type == Widget::TouchEventType::ENDED)
                                    {
                                        if (_listener)
                                        {
                                            _listener->onSoliderSelectedEnd(_arms, this->getPosition());
                                        }
                                    }
                                    else
                                    {
                                        //do nothing
                                    }
                                });
    
    
    return true;
}

void SoliderIcon::addListener(SoliderIconListener* listener)
{
    CCAssert(listener != nullptr, "invalid listener");
    _listener = listener;
}

void SoliderIcon::removeListener()
{
    _listener = nullptr;
}



