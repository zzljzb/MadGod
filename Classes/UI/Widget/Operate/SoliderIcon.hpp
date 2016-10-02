//
//  SoliderIcon.hpp
//  ggj-jzb
//
//  Created by jzb on 16/1/29.
//
//

#ifndef SoliderIcon_hpp
#define SoliderIcon_hpp

#include "cocos2d.h"
#include "ui/UIRelativeBox.h"
#include "ui/UIImageView.h"
#include "GlobalDefine.h"

class SoliderIconListener
{
public:
    virtual void onSoliderSelectedBegin(ARMS arms, const cocos2d::Vec2& pos) = 0;
    virtual void onSoliderSelectedEnd(ARMS arms, const cocos2d::Vec2& pos) = 0;
};

class SoliderIcon : public cocos2d::ui::RelativeBox
{
public:
    static SoliderIcon* create(const cocos2d::ValueMap& data);
    
    void addListener(SoliderIconListener* listener);
    void removeListener();
    
protected:
    SoliderIcon();
    virtual ~SoliderIcon();
    
private:
    bool init(const cocos2d::ValueMap& data);
    
private:
    std::string _iconFilePath = "";
    int _soliderNum = 0;
    ARMS _arms = kArmsPrivateSoldier;
    
    SoliderIconListener* _listener = nullptr;
    
private:
    cocos2d::ui::ImageView* _iconImg = nullptr;
};

#endif /* SoliderIcon_hpp */
