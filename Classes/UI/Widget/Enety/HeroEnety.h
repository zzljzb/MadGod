#ifndef __HeroEnety_H__
#define __HeroEnety_H__

#include "cocos2d.h"
USING_NS_CC;
class HeroEnety : public Node
{
public:

	enum HeroEunm { ArrowMan, SwordsMan, Missionary, Farmer } mHeroEunm;
	enum RaceEunm { Red, Blue } mRaceEunm;
	enum StateEunm { Forward, Back, Attack, Stand, Dead } mStateEunm;
    enum MentalEnum {Normal, Captured} mMentalEnum;
	int roadID;
	static HeroEnety* create(HeroEunm _HeroEunm, RaceEunm _RaceEunm,int _roadid);

	void GoForward();
	void GoBack();
	void GoDead();
	void GoAttack(HeroEnety * hero_Blue);
	void GoStand();
	void NormalHit(int _hit);
	void NormalHitCallback( int data);

	void LoyaltyHit(int _hit);
    void LoyaltyHitCallback( int data);
    
	void AttackTimeCD(float d);
    
    void changeMental(MentalEnum mental);
    void attainBase(RaceEunm race);
	
protected:
	bool init(HeroEunm _HeroEunm, RaceEunm _RaceEunm, int _roadid);
	void initAction(std::string plistname, std::string pngname);
	//void update(float d);

	Label* label_hp;
	
	
	Sprite * mSprite;

	void deadcallback();

	Action * Action_Forward, *Action_Back, *Action_Dead, *Action_Attack, *Action_Stand, *Action_Hit;

public:
	void loadjson(int _SoldierTypeID);
    bool judgeIfAttainBase();


	int SoldierTypeID;					//兵种ID
	std::string SoliderTypeName;		//兵种名称
	int AttackType;						//兵种攻击类型,0为远程信仰攻击，1为近战普通攻击不用放子弹，2为远程普通攻击需要放子弹
	int NormalDirection;
	int CapturedDirection;				//皈依状态兵种默认前进方向，0为敌对阵营方向，1为阵营基地方向
	float NormalMoveSpeed;				//兵种普通状态移动速度
	float CapturedMoveSpeed;			//兵种被俘虏状态移动速度
	int DoFarmHumanResource;			//兵种可否采人力矿,0为不可，1为可以
	int NormalHP;						//兵种HP
	int LoyaltyHP;						//兵种信仰值HP
	float AttackRange;					//兵种射程
	float AttackTime;					//兵种每次攻击需时，每多少秒进行一次攻击，值越小攻击越快
	int NormalAttackPower;				//兵种普通攻击力
	int ArmorAgainstNormalAttack;		//兵种抵抗普通攻击护甲值
	int ArmorAgainsLoyaltyAttack;		//兵种信仰值防御力
	int LoyaltyAttackPower;				//兵种信仰值攻击力
	int ManPowerToProduce;				//兵种制造消耗人力
	float ProduceButtonCoolDownTIme;	//兵种制造按钮冷却时间
	int DirectSacrificeValue;			//兵种直接献祭获得祭祀值
	int StopWhenBeingCaptured;			//兵种遭到信仰攻击时是否停下攻击与移动，0为坚持战斗，1为立即停止
	int SacrificeValueWhenCaptured;		//兵种被俘虏后可贡献祭祀值
	int HumanPowerWhenCaptured;			//兵种被俘虏后可贡献人力值
	int HitPointWhenCaptured;			//兵种以俘虏状态到基地后增加祭坛血量
	int SacrificeValueWhenNormal;		//兵种正常状态到基地后增加的祭祀值
	int HumanPowerWhenNormal;			//兵种正常状态到基地后增加的人力值
	int HitPointWhenNormal;				//兵种以正常状态到基地后增加祭坛血量
	float AltarCoolDownTimeWhenSacrificed;	//兵种献祭时祭坛冷却时间
	int DeathCreateSoldierType;		//兵种死亡后生成兵种的SoldierType，0为不生成
	int JoinCombat;						//兵种是否参与战斗，0为不参与战斗（不会被选作攻击目标也不会攻击敌人），1为参与战斗
	float LifeTime;						//兵种默认存活时间，0为永久存活不限时，大于0则为自动存活时长
    
    int LoyaltyMaxHP;
    float _limitPosLeft;
    float _limitPosRight;
};

#endif 
