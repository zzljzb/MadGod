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


	int SoldierTypeID;					//����ID
	std::string SoliderTypeName;		//��������
	int AttackType;						//���ֹ�������,0ΪԶ������������1Ϊ��ս��ͨ�������÷��ӵ���2ΪԶ����ͨ������Ҫ���ӵ�
	int NormalDirection;
	int CapturedDirection;				//���״̬����Ĭ��ǰ������0Ϊ�ж���Ӫ����1Ϊ��Ӫ���ط���
	float NormalMoveSpeed;				//������ͨ״̬�ƶ��ٶ�
	float CapturedMoveSpeed;			//���ֱ���²״̬�ƶ��ٶ�
	int DoFarmHumanResource;			//���ֿɷ��������,0Ϊ���ɣ�1Ϊ����
	int NormalHP;						//����HP
	int LoyaltyHP;						//��������ֵHP
	float AttackRange;					//�������
	float AttackTime;					//����ÿ�ι�����ʱ��ÿ���������һ�ι�����ֵԽС����Խ��
	int NormalAttackPower;				//������ͨ������
	int ArmorAgainstNormalAttack;		//���ֵֿ���ͨ��������ֵ
	int ArmorAgainsLoyaltyAttack;		//��������ֵ������
	int LoyaltyAttackPower;				//��������ֵ������
	int ManPowerToProduce;				//����������������
	float ProduceButtonCoolDownTIme;	//�������찴ť��ȴʱ��
	int DirectSacrificeValue;			//����ֱ���׼���ü���ֵ
	int StopWhenBeingCaptured;			//�����⵽��������ʱ�Ƿ�ͣ�¹������ƶ���0Ϊ���ս����1Ϊ����ֹͣ
	int SacrificeValueWhenCaptured;		//���ֱ���²��ɹ��׼���ֵ
	int HumanPowerWhenCaptured;			//���ֱ���²��ɹ�������ֵ
	int HitPointWhenCaptured;			//�����Է�²״̬�����غ����Ӽ�̳Ѫ��
	int SacrificeValueWhenNormal;		//��������״̬�����غ����ӵļ���ֵ
	int HumanPowerWhenNormal;			//��������״̬�����غ����ӵ�����ֵ
	int HitPointWhenNormal;				//����������״̬�����غ����Ӽ�̳Ѫ��
	float AltarCoolDownTimeWhenSacrificed;	//�����׼�ʱ��̳��ȴʱ��
	int DeathCreateSoldierType;		//�������������ɱ��ֵ�SoldierType��0Ϊ������
	int JoinCombat;						//�����Ƿ����ս����0Ϊ������ս�������ᱻѡ������Ŀ��Ҳ���ṥ�����ˣ���1Ϊ����ս��
	float LifeTime;						//����Ĭ�ϴ��ʱ�䣬0Ϊ���ô���ʱ������0��Ϊ�Զ����ʱ��
    
    int LoyaltyMaxHP;
    float _limitPosLeft;
    float _limitPosRight;
};

#endif 
