#ifndef _PK_h
#define _PK_h
#include<iostream>
#include<string>
#include<time.h>
class Weapon {
public:
	virtual int get_m_baseDamage() = 0;//基础伤害
	virtual int get_SuckBlood() = 0;//吸血
	virtual bool get_Hold() = 0;//眩晕
	virtual bool get_Crit() = 0;//暴击
	
	virtual int Crit()=0;
	virtual int Suck()=0;

	bool isTrigger(int rate);


private:

public:
	std::string m_WeaponName;
	int m_BaseDamage;
};
/*
神剑特点：
各方面数字较均衡
*/
class GodSword :public Weapon
{
public:
	GodSword();
	virtual int get_m_baseDamage();//基础伤害
	virtual int get_SuckBlood();//吸血
	virtual bool get_Hold();//眩晕
	virtual bool get_Crit();//暴击
	virtual int Crit();
	virtual int Suck();
private:
	int SuckRate = 20;
	int HoldRate = 35;
	int CritRate = 5;
};
/*
长剑特点：
眩晕能力和暴击能力高，不能吸血
基础伤害低
*/
class Knife :public Weapon
{
public:
	Knife();
	virtual int get_m_baseDamage();//基础伤害
	virtual int get_SuckBlood();//吸血
	virtual bool get_Hold();//眩晕
	virtual bool get_Crit();//暴击
	virtual int Crit();
	virtual int Suck();
private:
	int SuckRate = 0;
	int HoldRate = 25;
	int CritRate = 70;
};
/*
法杖特点：
高吸血高眩晕，但是无暴击
基础伤害高
*/
class MagicStick :public Weapon
{
public:
	MagicStick();
	virtual int get_m_baseDamage();//基础伤害
	virtual int get_SuckBlood();//吸血
	virtual bool get_Hold();//眩晕
	virtual bool get_Crit();//暴击
	virtual int Crit();
	virtual int Suck();
private:
	int SuckRate = 60;
	int HoldRate = 30;
	int CritRate = 0;
};

class Monster;
class Hero {
public:
	Hero();
	void EquipWeapon(Weapon* weapon);
	void Attack(Monster* monster);
	void out();

	std::string m_Name;
	int m_Atk;
	int m_Def;
	int m_Hp;
	Weapon* weapon;
	bool is_energy;
};

class Monster {
public:
	Monster();
	void Attack(Hero* hero);
	int get_m_Def();
	std::string get_m_Name();
	int get_m_Hp();
	void set_m_Hp(int a);
private:
	std::string m_Name;
	int m_Atk;
	int m_Def;
	int m_Hp;
public:
	bool m_Hold;

};
#endif
