#include "HeroEnety.h"
#include "HeroManager.h"
#include "JsonUtils.hpp"
#include "DataManager.hpp"
USING_NS_CC;



HeroEnety*HeroEnety::create(HeroEunm _HeroEunm, RaceEunm _RaceEunm, int _roadid)
{
	HeroEnety*m_Data = new HeroEnety();
	if (m_Data->init(_HeroEunm, _RaceEunm, _roadid))
	{
		m_Data->autorelease();
		return m_Data;
	}
	CC_SAFE_DELETE(m_Data);
	return nullptr;

}


bool HeroEnety::init(HeroEunm _HeroEunm, RaceEunm _RaceEunm, int _roadid)
{
	mRaceEunm = _RaceEunm;
	mHeroEunm = _HeroEunm;
	mStateEunm = Stand;
	roadID = _roadid;
    mMentalEnum = Normal;
	std::string plistname ;
	std::string pngname ;
	std::string filename;
	switch (_HeroEunm)
	{
	case HeroEnety::ArrowMan:
		plistname = "";
		pngname = "";
		filename = "";
		break;
	case HeroEnety::SwordsMan:
		plistname = "HeroA.plist";
		pngname = "HeroA.png";
		filename = "walk_00.png";
		break;
	case HeroEnety::Missionary:
		plistname = "";
		pngname = "";
		break;
	default:
		break;
	}



	HeroManager::getInstance()->add(this);



	loadjson(1);
	mSprite = Sprite::create(filename);
	if (mRaceEunm == Blue) { mSprite->setFlipX(true); }
	this->addChild(mSprite);
	this->initAction(plistname, pngname);

	auto label = Label::create(String::createWithFormat("%d", NormalHP)->getCString() , "msyh.ttf",40);
	label->setPosition(Vec2(this->getPosition().x, this->getPosition().y+100));
	label->setColor(Color3B::WHITE);
	this->addChild(label);


	//this->scheduleUpdate();
	return true;
}

void HeroEnety::GoForward(){
	if (mStateEunm == StateEunm::Forward) { return; }
	mSprite->stopAllActions();
	mStateEunm = StateEunm::Forward;
	mSprite->runAction(Action_Forward);
}

void HeroEnety::GoBack(){
	if (mStateEunm == StateEunm::Back) { return; }
	mStateEunm = StateEunm::Back;
	mSprite->runAction(Action_Back);
}

void HeroEnety::GoDead(){
	if(mStateEunm == StateEunm::Dead) { return; }
	mStateEunm = StateEunm::Dead;
	HeroManager::getInstance()->del(this);
    
    if (SoldierTypeID == 3)
    {
        ValueMap data;
        data.insert(std::make_pair("raid", Value(roadID)));
        bool isLeft = false;
        if (mRaceEunm == RaceEunm::Red)
        {
            isLeft = true;
        }
        data.insert(std::make_pair("isLeft", Value(isLeft)));
        
        std::string eventName = "missionary_dead";
        EventCustom event = EventCustom(eventName);
        event.setUserData((void *)(&data));
        Director::getInstance()->getEventDispatcher()->dispatchEvent(&event);
    }
    
	return;
	auto callback = CallFuncN::create( CC_CALLBACK_0(HeroEnety::deadcallback,this));
	auto dt = DelayTime::create(1);
	auto fo = FadeOut::create(1);
	//auto d = Sequence::create((Animate*)Action_Dead, dt, callback, nullptr);
	auto d = Sequence::create(fo, dt, callback,nullptr);
	this->runAction(d);
}

void HeroEnety::GoAttack(HeroEnety * hero_Blue){
	if (mStateEunm == StateEunm::Attack){ return; }
	mSprite->stopAllActions();
	mStateEunm = StateEunm::Attack;

	this->scheduleOnce(schedule_selector(HeroEnety::AttackTimeCD), AttackTime);
	mSprite->runAction(Action_Attack);
}

void HeroEnety::GoStand(){
	mStateEunm = StateEunm::Stand;
	//mSprite->runAction(Action_Stand);
	mSprite->stopAllActions();
}

void HeroEnety::NormalHit(int _hit){
	int mhit = _hit - ArmorAgainstNormalAttack;
	
	auto hitback = CallFunc::create(CC_CALLBACK_0(HeroEnety::NormalHitCallback,this, mhit));
	auto sq = Sequence::create(DelayTime::create(AttackTime) , hitback, nullptr);
	this->runAction(sq);
	//mSprite->runAction(Action_Hit);
}
void HeroEnety::NormalHitCallback( int data)
{
	NormalHP = NormalHP - data;
	//auto label_hp = Label::create(String::createWithFormat(),"",20);
	label_hp->setString(String::createWithFormat("%d", NormalHP)->getCString());


	if (NormalHP <= 0) {

		GoDead();
	}
}

void HeroEnety::LoyaltyHit(int _hit) {
	int mhit = _hit - ArmorAgainsLoyaltyAttack;
	LoyaltyHP = LoyaltyHP - mhit;
    
    LoyaltyHitCallback(mhit);
}

void HeroEnety::LoyaltyHitCallback(int data)
{
    if (LoyaltyHP <= 0) {
        changeMental(MentalEnum::Captured);
    }
}

void HeroEnety::AttackTimeCD(float d)
{
	mStateEunm = StateEunm::Stand;
}

void HeroEnety::deadcallback()
{
	
}

void HeroEnety::loadjson(int _SoldierTypeID)
{
	_limitPosRight = DataManager::getInstance()->getLimitPosRight();
    _limitPosLeft = DataManager::getInstance()->getLimitPosLeft();
	auto vmap=JsonUtils::valueVectorFromJsonFile("Soldiers.json");
	
	for (auto item : vmap)
	{
		auto  date = item.asValueMap();
		int id=date.at("SoldierTypeID").asInt();
		if (_SoldierTypeID == id) {
			SoldierTypeID= date.at("SoldierTypeID").asInt();					//兵种ID
			SoliderTypeName = date.at("SoliderTypeName").asString();		//兵种名称
			AttackType= date.at("AttackType").asInt();						//兵种攻击类型,0为远程信仰攻击，1为近战普通攻击不用放子弹，2为远程普通攻击需要放子弹
			NormalDirection= date.at("NormalDirection").asInt();
			CapturedDirection= date.at("CapturedDirection").asInt();				//皈依状态兵种默认前进方向，0为敌对阵营方向，1为阵营基地方向
			NormalMoveSpeed = date.at("NormalMoveSpeed").asFloat();				//兵种普通状态移动速度
			CapturedMoveSpeed= date.at("CapturedMoveSpeed").asFloat();			//兵种被俘虏状态移动速度
			DoFarmHumanResource = date.at("DoFarmHumanResource").asInt();			//兵种可否采人力矿,0为不可，1为可以
			NormalHP = date.at("NormalHP").asInt();							//兵种HP
			LoyaltyHP = date.at("LoyaltyHP").asInt();							//兵种信仰值HP
			AttackRange = date.at("AttackRange").asFloat();					//兵种射程
			AttackTime = date.at("AttackTime").asFloat();					//兵种每次攻击需时，每多少秒进行一次攻击，值越小攻击越快
			NormalAttackPower = date.at("NormalAttackPower").asInt();					//兵种普通攻击力
			ArmorAgainstNormalAttack = date.at("ArmorAgainstNormalAttack").asInt();			//兵种抵抗普通攻击护甲值
			ArmorAgainsLoyaltyAttack = date.at("ArmorAgainsLoyaltyAttack").asInt();		//兵种信仰值防御力
			LoyaltyAttackPower = date.at("LoyaltyAttackPower").asInt();			//兵种信仰值攻击力
			ManPowerToProduce = date.at("ManPowerToProduce").asInt();					//兵种制造消耗人力
			ProduceButtonCoolDownTIme = date.at("ProduceButtonCoolDownTIme").asFloat();	//兵种制造按钮冷却时间
			DirectSacrificeValue = date.at("DirectSacrificeValue").asInt();			//兵种直接献祭获得祭祀值
			StopWhenBeingCaptured = date.at("StopWhenBeingCaptured").asInt();			//兵种遭到信仰攻击时是否停下攻击与移动，0为坚持战斗，1为立即停止
			SacrificeValueWhenCaptured = date.at("SacrificeValueWhenCaptured").asInt();		//兵种被俘虏后可贡献祭祀值
			HumanPowerWhenCaptured = date.at("HumanPowerWhenCaptured").asInt();			//兵种被俘虏后可贡献人力值
			HitPointWhenCaptured = date.at("HitPointWhenCaptured").asInt();				//兵种以俘虏状态到基地后增加祭坛血量
			SacrificeValueWhenNormal = date.at("SacrificeValueWhenNormal").asInt();			//兵种正常状态到基地后增加的祭祀值
			HumanPowerWhenNormal = date.at("HumanPowerWhenNormal").asInt();				//兵种正常状态到基地后增加的人力值
			HitPointWhenNormal = date.at("HitPointWhenNormal").asInt();				//兵种以正常状态到基地后增加祭坛血量
			AltarCoolDownTimeWhenSacrificed = date.at("AltarCoolDownTimeWhenSacrificed").asFloat();			//兵种献祭时祭坛冷却时间
			DeathCreateSoldierType = date.at("DeathCreateSoldierType").asInt();		//兵种死亡后生成兵种的SoldierType，0为不生成
			JoinCombat = date.at("JoinCombat").asInt();								//兵种是否参与战斗，0为不参与战斗（不会被选作攻击目标也不会攻击敌人），1为参与战斗
			LifeTime = date.at("LifeTime").asFloat();						//兵种默认存活时间，0为永久存活不限时，大于0则为自动存活时长
            
            
            LoyaltyMaxHP = LoyaltyHP;
		}
	}

	label_hp = Label::create(String::createWithFormat("%d", NormalHP)->getCString(), "msyh.ttf", 32);
	label_hp->setPosition(Vec2(this->getPosition().x, this->getPosition().y + 80));
	label_hp->setColor(Color3B::BLACK);
	this->addChild(label_hp);

	//NormalMoveSpeed = 1;
	//AttackRange = 60;
	//AttackTime = 0.72f;
	//ArmorAgainstNormalAttack = 2;
	//NormalAttackPower = 5;
	//NormalHP = 20;


}
//
//void HeroEnety::update(float d){
//
//
//}


void HeroEnety::initAction(std::string plistname, std::string pngname)
{

	auto cache = SpriteFrameCache::getInstance();
	SpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile(plistname, pngname);


	Vector<cocos2d::SpriteFrame *> Action_Forward_arr;
	Vector<cocos2d::SpriteFrame *> Action_Back_arr;
	Vector<cocos2d::SpriteFrame *> Action_Dead_arr;
	Vector<cocos2d::SpriteFrame *> Action_Attack_arr;

	Vector<cocos2d::SpriteFrame *> Action_Stand_arr;
	Vector<cocos2d::SpriteFrame *> Action_Hit_arr;
	char str[100] = { 0 };
    
    if (plistname == (std::string)"HeroB.plist") {
        
        for (int i = 0; i <= 11; i++)
        {
            sprintf(str, "huoqiu_walk_%02d.png", i);
            Action_Forward_arr.pushBack(cache->SpriteFrameCache::getInstance()->getSpriteFrameByName(str));
            
        }
        
        for (int i = 0; i <= 11; i++)
        {
            sprintf(str, "huoqiu_attack_%02d.png", i);
            Action_Attack_arr.pushBack(cache->SpriteFrameCache::getInstance()->getSpriteFrameByName(str));
        }
    }
    
    
    
    
    
    if (plistname == (std::string)"HeroA.plist") {
        
        for (int i = 0; i <= 11; i++)
        {
            sprintf(str, "walk_%02d.png", i);
            Action_Forward_arr.pushBack(cache->SpriteFrameCache::getInstance()->getSpriteFrameByName(str));
            
        }
        
        for (int i = 0; i <= 24; i++)
        {
            sprintf(str, "shibing_attack_%02d.png", i);
            Action_Attack_arr.pushBack(cache->SpriteFrameCache::getInstance()->getSpriteFrameByName(str));
        }
    }
    
    if (plistname == (std::string)"HeroD.plist") {
        
        for (int i = 0; i <= 11; i++)
        {
            sprintf(str, "walk_%02d_frame.png", i);
            Action_Forward_arr.pushBack(cache->SpriteFrameCache::getInstance()->getSpriteFrameByName(str));
            
        }
        
    }
    
    
    if (plistname == (std::string)"HeroC.plist") {
        
        for (int i = 0; i <= 4; i++)
        {
            sprintf(str, "walk_%02d_C.png", i);
            Action_Forward_arr.pushBack(cache->SpriteFrameCache::getInstance()->getSpriteFrameByName(str));
            
        }
        for (int i = 0; i <= 11; i++)
        {
            sprintf(str, "attack_%02d_C.png", i);
            Action_Attack_arr.pushBack(cache->SpriteFrameCache::getInstance()->getSpriteFrameByName(str));
        }
        
    }
	

	Action_Forward = RepeatForever::create(Animate::create(Animation::createWithSpriteFrames(Action_Forward_arr, 0.1f)));
	//Action_Back = RepeatForever::create(Animate::create(Animation::createWithSpriteFrames(Action_Back_arr, 0.1f)));
	//Action_Dead = Animate::create(Animation::createWithSpriteFrames(Action_Dead_arr, 0.1f));
	Action_Attack = Animate::create(Animation::createWithSpriteFrames(Action_Attack_arr, 0.03f));
	//Action_Stand = RepeatForever::create(Animate::create(Animation::createWithSpriteFrames(Action_Stand_arr, 0.1f)));
	//Action_Hit = Animate::create(Animation::createWithSpriteFrames(Action_Hit_arr, 0.1f));

	Action_Forward->retain();
	//Action_Back->retain();
	//Action_Dead->retain();
	Action_Attack->retain();
	//Action_Stand->retain();
	//Action_Hit->retain();

}

void HeroEnety::changeMental(MentalEnum mental)
{
    if (mMentalEnum != mental) {
        //被俘虏
        if (mental == MentalEnum::Captured) {
            HeroManager::getInstance()->del(this, false);
            // change race
            mRaceEunm = mRaceEunm == RaceEunm::Blue ? RaceEunm::Red:RaceEunm::Blue;
            HeroManager::getInstance()->add(this);
            // change
            LoyaltyHP = LoyaltyMaxHP;
            
        }
        mMentalEnum = mental;
    }
}

bool HeroEnety::judgeIfAttainBase()
{
    float posX = getPositionX();
    if (posX >= _limitPosLeft && posX <= _limitPosRight) {
        return false;
    }
    attainBase(posX < _limitPosLeft ? RaceEunm::Red :RaceEunm::Blue);
    GoDead();
    return true;
}
void HeroEnety::attainBase(RaceEunm race)
{
    ValueMap data;
    float fractionOffset, humanResOffset, HPOffset;
    switch (mMentalEnum) {
        case MentalEnum::Normal:
            fractionOffset = SacrificeValueWhenNormal;
            humanResOffset = HumanPowerWhenNormal;
            HPOffset = HitPointWhenNormal;
            break;
        case MentalEnum::Captured:
            fractionOffset = SacrificeValueWhenCaptured;
            humanResOffset = HumanPowerWhenCaptured;
            HPOffset = HitPointWhenCaptured;
            break;
        default:
            break;
    }
    data.insert(std::make_pair("fractionOffset", Value(fractionOffset)));
    data.insert(std::make_pair("humanResOffset", Value(humanResOffset)));
    data.insert(std::make_pair("HPOffset", Value(HPOffset)));
    data.insert(std::make_pair("RaceEunm", Value(race)));
    
    std::string eventName = "event_arrive_base";
    EventCustom event = EventCustom(eventName);
    event.setUserData((void *)(&data));
    Director::getInstance()->getEventDispatcher()->dispatchEvent(&event);
}

