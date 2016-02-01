//
//  Player.hpp
//  MyGame
//
//  Created by mixi on 16/1/30.
//
//

#ifndef Player_hpp
#define Player_hpp

#include <stdio.h>
#include "cocos2d.h"
#include "HeroEnety.h"

USING_NS_CC;
// 玩家的资源： 士兵 祭司
class Player: public Node
{
public:
    void addRes(HeroEnety* res);
    void delRes(HeroEnety* res);
    void anabasis(HeroEnety* res);
    
    HeroEnety* addSworldsMan(HeroEnety::HeroEunm heroEnum, int roadid);
    void removeSworldMan(HeroEnety* hero);
    
    bool addFractionValueFromHero(HeroEnety::HeroEunm heroEnum);
    
    // 根据兵的状态修改数值
//    bool changePlayerParamsFromManWhlieTouchHome(HeroEnety* men);
    void changePlayerParamsFromManWhlieAttainBase(int fractionOffset, int HPOffset, int humanResOffset);

    
    Vector<HeroEnety*> getEnemyTroops(int roadId);
//    Map<int, Vector<HeroEnety*>> _outsideSworldManMap; // 后面优化时候使用
    void update(float d); // 判断兵的数据 以及胜利条件的判断
    void updateOutsideSworldMan();
    
    Player* create(HeroEnety::RaceEunm camp);
    
    void addListen();
    
    CC_SYNTHESIZE(HeroEnety*, _enemyPlayer, EnemyPlayer);
    CC_PROPERTY(HeroEnety::RaceEunm, _camp, Camp);
    
    
    CREATE_FUNC(Player);

private:
    
    Player();
    ~Player();
    bool init();
    void sortOutsideRes();
    void initData();
    // 人力数值的修改
    void addHumanResource(float dt);
    bool changeHumanResourceValue(float num);
    void setHumanResourceValue(float newValue);
    
    // 祭祀数值修改
    bool changeFractionValue(float num);
    void setFractionValue(float newValue);
    
    // 人物血量修改
    bool changeHPValue(float num);
    void setHPValue(float newValue);

    
    Vector<HeroEnety*> _outsideResVec;//外出部分的资源存储  用来外部做处理
    Vector<HeroEnety*> _resVec;
    
    // 初始数据
    float _fractionHumanResource;//人力基础数值
    float _fractionHumanResourceIncreasPerSecond;//人力每秒增长值
    float _fractionHP;//人物血量
    float _fractionMP;//祭祀数值
    float _fractionMaxHP;//人物最高血量
    float _fractionMaxMP;//祭司数值最高数值
    
    bool isAnabasisNumZero;
};

#endif /* Player_hpp */
