//
//  DataManager.hpp
//  ggj-jzb
//
//  Created by jzb on 16/1/30.
//
//

#ifndef DataManager_hpp
#define DataManager_hpp

#include "cocos2d.h"
#include "GlobalDefine.h"

class DataManager
{
public:
    static DataManager* getInstance();
    
    MINE_STATE getMineState(int mineIndex);
    void setMineState(int mineIndex, MINE_STATE state);
    float getLimitPosRight(){ return _limitRangeRight; };
    float getLimitPosLeft(){ return _limitRangeLeft; };
    
private:
    bool init();
    
private:
    std::vector<MINE_STATE> _mineState = {kMineStateIdle, kMineStateIdle, kMineStateIdle};
	float _limitRangeLeft, _limitRangeRight;
};

#endif /* DataManager_hpp */
