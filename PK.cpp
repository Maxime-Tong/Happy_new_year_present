#include"PK.h"

bool Weapon::isTrigger(int rate) {
	int num = rand() % 100 + 1;
	if (num <= rate)return true;
	return false;
}

GodSword::GodSword() {
	this->m_BaseDamage =60;
	this->m_WeaponName = "无心";
}

int GodSword::get_m_baseDamage(){
	return m_BaseDamage;
}

int GodSword::get_SuckBlood() {
	if (isTrigger(SuckRate))
	{
		return m_BaseDamage; //吸血百分之25
	}
	return 0;
}

bool GodSword::get_Hold() {
	if (isTrigger(HoldRate)) { 
		return true; 
	}
	return false;
}

bool GodSword::get_Crit() {
	if (isTrigger(CritRate)) {
		return true;
	}
	return false;
}
int GodSword::Crit() { return CritRate; }
int GodSword::Suck() { return SuckRate; }

Knife::Knife() {
	this->m_BaseDamage = 50;
	this->m_WeaponName = "无名";
}
int Knife::get_m_baseDamage(){
	return m_BaseDamage;
}

int Knife::get_SuckBlood() {
	return 0;
}
bool Knife::get_Hold() {
	if (isTrigger(HoldRate)) {
    //std::cout << "发动眩晕，对方眩晕一回合！\n";
		return true;
	}
	return false;
}

bool Knife::get_Crit() {
	if (isTrigger(CritRate)) {
		//std::cout << "暴击！\n";
		return true;
	}
	return false;
}

int Knife::Crit() { return CritRate; }
int Knife::Suck() { return SuckRate; }

MagicStick::MagicStick() {
	this->m_BaseDamage = 80;
	this->m_WeaponName = "无君";
}
int MagicStick::get_m_baseDamage() {
	return m_BaseDamage;
}

int MagicStick::get_SuckBlood() {
	if (isTrigger(SuckRate))
	{
		return m_BaseDamage ; 
	}
	return 0;
}

bool MagicStick::get_Hold() {
	return isTrigger(HoldRate);
}

bool MagicStick::get_Crit() {
	return false;//无暴击
}

int MagicStick::Crit() { return CritRate; }
int MagicStick::Suck() { return SuckRate; }

Hero::Hero() {
	m_Hp = 450;
	m_Atk = 50;
	m_Def = 30;
	weapon = nullptr;
	is_energy = true;
}
void Hero::EquipWeapon(Weapon* weapon) {
	this->weapon = weapon;
}
void Hero::Attack(Monster* monster) {
	int ComsumeHp=this->m_Atk - monster->get_m_Def();
	ComsumeHp = ComsumeHp > 0 ? ComsumeHp : 1;
	if (weapon == nullptr) {//空手，虽然这种情况一般不会发生
		monster->set_m_Hp(monster->get_m_Hp()-ComsumeHp);
		return;
	}
	ComsumeHp += weapon->get_m_baseDamage();

	//暴击
	if (weapon->get_Crit()) {
		ComsumeHp += weapon->get_m_baseDamage()*2;
		std::cout << "英雄的武器：‘" << weapon->m_WeaponName << "’触发了暴击！\n";
	}


	//计算吸血伤害
	int tmp = m_Hp + weapon->get_SuckBlood();
	if (tmp != m_Hp) {
		std::cout << "英雄的武器：‘" << weapon->m_WeaponName << "’吸血效果！\n";
		if (tmp > 450)m_Hp = 450;
		else m_Hp = tmp;
	}
	//眩晕
	if (weapon->get_Hold()){
		std::cout << "英雄的武器：‘" << weapon->m_WeaponName << "’触发禁锢效果！迫使敌方停止攻击一回合！\n";
		monster->m_Hold = true;
	}
	if (ComsumeHp != 1) {
		monster->set_m_Hp(monster->get_m_Hp() - ComsumeHp);
		std::cout << "英雄" << m_Name << "攻击了敌人‘" << monster->get_m_Name() << "’并造成了"
			<< ComsumeHp << "的伤害值\n";
	}
	else {
		monster->set_m_Hp(monster->get_m_Hp() - ComsumeHp);
		std::cout << "英雄" << m_Name << "攻击了敌人‘" << monster->get_m_Name() << "’没有造成伤害值\n";
	}
}

void Hero::out() {
	std::cout << "英雄" << m_Name << ":\n" << " Hp:" << m_Hp << " 防御（Def）:" << m_Def << "\n";
	std::cout << "武器:\n基础攻击:" << weapon->get_m_baseDamage()<< " 暴击(Cruit)：" << weapon->Crit()<<" 吸血(Suck):"<<weapon->Suck()<<"\n\n";
}

Monster::Monster() {
	std::string m_Name = "幻兽——普兰奎尔";
	m_Atk = 225;
	m_Def = 75;
	m_Hp = 1000;
	m_Hold = false;
}

void Monster::Attack(Hero* hero)
{

	if (m_Hold) {
		std::cout << "幻兽普兰奎尔被禁锢\n";
		m_Hold = false;
		return;
	}

	int damage = m_Atk - hero->m_Def;
	damage = (damage > 0) ? damage : 1;
	if (damage != 1) {
		hero->m_Hp = hero->m_Hp - damage;
		std::cout << "‘" << this->get_m_Name() << "'攻击了英雄‘" << hero->m_Name << "’并造成了"
			<< damage<< "的伤害值\n";
	}
	else {	
		std::cout << "‘" << this->get_m_Name()<< "'攻击了英雄‘" << hero->m_Name << "’但没有造成伤害值\n";
	}

}

int Monster::get_m_Def()
{
	return m_Def;
}

std::string Monster::get_m_Name() {
	return  "幻兽——普兰奎尔";
}

int Monster::get_m_Hp() {
	return m_Hp;
}

void Monster::set_m_Hp(int a) {
	m_Hp = a;
}
