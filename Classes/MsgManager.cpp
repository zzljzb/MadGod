//
//  MsgManager.cpp
//  MyGame
//
//  Created by mixi on 16/1/31.
//
//

#include "MsgManager.h"
static MsgManager* _msgInstance = nullptr;
static int LabelSize = 40;
static float DulTime = 1.0;
MsgManager::MsgManager()
:_msgIndex(0)
{
    _msgLabelVec.reverse();
}
MsgManager::~MsgManager()
{
}
bool MsgManager::init()
{
    return true;
}
MsgManager* MsgManager::getInstance()
{
    if (!_msgInstance) {
        _msgInstance = new MsgManager();
        _msgInstance->init();
    }
    return _msgInstance;
}
void MsgManager::popMsg(string str)
{
    if (_msgLabelVec.size() > 0) {
        moveAllLabel();
    }
    createLabel(str);
}

void MsgManager::createLabel(string str)
{
    Label * label = Label::createWithTTF(str, "fonts/Marker Felt.ttf", LabelSize);
    Director::getInstance()->getRunningScene()->addChild(label);
    _msgLabelVec.pushBack(label);
    Size winSize = Director::getInstance()->getWinSize();
    label->setPosition(winSize.width / 2, winSize.height / 2);
    int index = _msgIndex++;
    label->setTag(index);
    label->runAction(
                     Sequence::create(
                                      FadeIn::create(DulTime),
                                      FadeOut::create(DulTime),
                                      CallFuncN::create( CC_CALLBACK_1(MsgManager::removeLabelTag, this, index)),
                                      nullptr
                                      )
                     );
}
                                      
void MsgManager::removeLabelTag(Node* sender, int index)
{
    int num = -1;
    int labelIndex = -1;
    for (auto label : _msgLabelVec) {
        if (label->getTag() == index) {
            labelIndex = num + 1;
            label->removeFromParent();
            break;
        }
        num++;
    }
    if (labelIndex >= 0) {
        _msgLabelVec.erase(labelIndex);
    }
}

void MsgManager::moveAllLabel()
{
    for (auto label: _msgLabelVec) {
        label->runAction(MoveBy::create(DulTime, Vec2(0, LabelSize)));
    }
}
