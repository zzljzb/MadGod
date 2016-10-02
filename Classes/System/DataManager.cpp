//
//  DataManager.cpp
//  ggj-jzb
//
//  Created by jzb on 16/1/30.
//
//

#include "DataManager.hpp"

static DataManager* s_DataManager = nullptr;

DataManager* DataManager::getInstance()
{
    if (s_DataManager == nullptr)
    {
        s_DataManager = new DataManager();
        s_DataManager->init();
    }
    
    return s_DataManager;
}

bool DataManager::init()
{
    _limitRangeLeft = 100;
    cocos2d::Size size = cocos2d::Director::getInstance()->getWinSize();
    _limitRangeRight = size.width - _limitRangeLeft;
    return true;
}

MINE_STATE DataManager::getMineState(int mineIndex)
{
    CCAssert(mineIndex >= 0 && mineIndex < 3, "invalid mineIndex");
    return _mineState[mineIndex];
}

void DataManager::setMineState(int mineIndex, MINE_STATE state)
{
    CCAssert(mineIndex >= 0 && mineIndex < 3, "invalid mineIndex");
    _mineState[mineIndex] = state;
}