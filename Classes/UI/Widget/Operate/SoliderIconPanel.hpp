//
//  SoliderIconPanel.hpp
//  ggj-jzb
//
//  Created by jzb on 16/1/29.
//
//

#ifndef SoliderIconPanel_hpp
#define SoliderIconPanel_hpp

#include "cocos2d.h"
#include "SoliderIcon.hpp"
#include "ui/UIVBox.h"

class SoliderIconPanelListener
{
public:
    virtual void onSoliderSelectedBegin(ARMS arms, const cocos2d::Vec2& pos) = 0;
    virtual void onSoliderSelectedEnd(ARMS arms, const cocos2d::Vec2& pos) = 0;
};

class SoliderIconPanel : public cocos2d::ui::RelativeBox, public SoliderIconListener
{
public:
    CREATE_FUNC(SoliderIconPanel);
    
    virtual void onSoliderSelectedBegin(ARMS arms, const cocos2d::Vec2& pos) override;
    virtual void onSoliderSelectedEnd(ARMS arms, const cocos2d::Vec2& pos) override;
    
    void addListener(SoliderIconPanelListener* listener);
    void removeListener();
    
protected:
    SoliderIconPanel();
    virtual ~SoliderIconPanel();
    
private:
    bool init() override;
    
private:
    cocos2d::Vector<SoliderIcon*> _icons;
    SoliderIconPanelListener* _listener = nullptr;
};

#endif /* SoliderIconPanel_hpp */
