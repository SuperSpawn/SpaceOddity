#pragma once
#include "entity.h"


enum eBits
{
	bENEMY_MOVE = 0b00000001
	, bENEMY_THINK = 0b00000010
	, bENEMY_OBSERVE = 0b00000100
	, bENEMY_ATTACK = 0b00001000
	, bENEMY_DIE = 0b00010000
	, bENEMY_INTERACT = 0b00100000
};


enum o_strats
{
	WHALE_DASH_LEFT2RIGHT = 0
	, WHALE_DASH_RIGHT2LEFT
	
};

class enemy : public object
{
protected:
	//pspace::personality _per;
	//int state;
	float tmodifier;
	float reactThresh;
public:

	//enemy();
	bool bmove;

	//dfunc fthink, fobserve, fmove, fattack, fdie, finteract;
	
	virtual void* setmove(olc::vf2d ctarget) = 0;
	virtual void* move(olc::vf2d ctarget) = 0;
	virtual void changeStrat() = 0;
	virtual bool checkCollide(olc::vf2d upperLeft, olc::vf2d bottomRight)
	{
		return false;
	}
	virtual void perFrame(float fElapsedTime, decimal misc) {
		return;
	}
	virtual void setState(decimal state);
	virtual bool pcheckCollide(olc::Sprite* spr) { return false; }
	virtual decimal type() = 0;
	virtual void draw(olc::PixelGameEngine* game)
	{
		return;
	}

	//virtual unsigned int getIndex();

	//void act();
	virtual ~enemy();
};






class killer_whale : public enemy
{
	int i, j;//texture index
	
public:

	float reactionTime;

	killer_whale(float x, float y, object* _target);

	
	virtual void* setmove(olc::vf2d ctarget);
	virtual bool checkCollide(olc::vf2d upperLeft, olc::vf2d bottomRight);
	virtual void* move(olc::vf2d ctarget);
	virtual void changeStrat();
	virtual void perFrame(float fElapsedTime, decimal misc);
	//virtual unsigned int getIndex();
	virtual decimal type();
	virtual void draw(olc::PixelGameEngine* game);
	virtual bool pcheckCollide(olc::Sprite* spr);
	//virtual decimal updateState(float fElapsedTime);

	virtual ~killer_whale();
};

class giant_killer_whale : public enemy
{
public:
	giant_killer_whale(float x, float y, uint32_t _width, uint32_t _height);

	
	virtual void* setmove(olc::vf2d ctarget);
	virtual bool checkCollide(olc::vf2d upperLeft, olc::vf2d bottomRight);
	virtual void* move(olc::vf2d ctarget);
	virtual void changeStrat();
	virtual void perFrame(float fElapsedTime, decimal misc);
	//virtual unsigned int getIndex();
	virtual decimal type();
	virtual void draw(olc::PixelGameEngine* game);
	virtual bool pcheckCollide(olc::Sprite* spr);
	//virtual decimal updateState(float fElapsedTime);

	virtual ~giant_killer_whale();
};


class space_pirate_ship : public enemy
{
	f2 sides[3];	
	float _rotateThresh;
	float prevSlope;

public:
	
	space_pirate_ship(float x, float y);

	virtual void* think(int param, ...);
	virtual void* observe(int param, ...);
	virtual void* setmove(olc::vf2d ctarget);
	virtual void* move(olc::vf2d ctarget);
	virtual void* attack(int param, ...);
	virtual void* die(int param, ...);
	virtual void* interact(int param, ...);
	virtual void changeStrat();
	virtual void perFrame(float fElapsedTime, decimal misc);
	//virtual unsigned int getIndex();
	virtual decimal type();
	virtual void draw(olc::PixelGameEngine* game);
	virtual bool pcheckCollide(olc::Sprite* spr);
	//virtual decimal updateState(float fElapsedTime);

	virtual ~space_pirate_ship();
};


class pirate : public enemy
{
public:
	virtual void* think(int param, ...);
	virtual void* observe(int param, ...);
	virtual void* setmove(olc::vf2d target);
	virtual void* move(int param, ...);
	virtual void* attack(int param, ...);
	virtual void* die(int param, ...);
	virtual void* interact(int param, ...);
	virtual void changeStrat();
	//virtual bool pcheckCollide(olc::Sprite* spr);
	//virtual unsigned int getIndex();
	virtual ~pirate();
};

class pirate_ship : public enemy
{
public:
	virtual void* think(int param, ...);
	virtual void* observe(int param, ...);
	virtual void* setmove(olc::vf2d target);
	virtual void* move(int param, ...);
	virtual void* attack(int param, ...);
	virtual void* die(int param, ...);
	virtual void* interact(int param, ...);
	virtual void changeStrat();
	//virtual unsigned int getIndex();
	virtual ~pirate_ship();
};


class killer_robot : public enemy
{
public:

	virtual void* think(int param, ...);
	virtual void* observe(int param, ...);
	virtual void* move(int param, ...);
	virtual void* attack(int param, ...);
	virtual void* die(int param, ...);
	virtual void* interact(int param, ...);
	virtual void changeStrat();
	//virtual unsigned int getIndex();
	virtual ~killer_robot();
};

//they call them the diamond dogs...
class diamond_dog : public enemy
{
public:
	virtual void* think(int param, ...);
	virtual void* observe(int param, ...);
	virtual void* move(int param, ...);
	virtual void* attack(int param, ...);
	virtual void* die(int param, ...);
	virtual void* interact(int param, ...);
	virtual void changeStrat();
	//virtual unsigned int getIndex();
	virtual ~diamond_dog();
};

class space_fascist : public enemy
{
public:
	virtual void* think(int param, ...);
	virtual void* observe(int param, ...);
	virtual void* move(int param, ...);
	virtual void* attack(int param, ...);
	virtual void* die(int param, ...);
	virtual void* interact(int param, ...);
	virtual void changeStrat();
	//virtual unsigned int getIndex();
	virtual ~space_fascist();
};

class rizzy : public enemy
{
public:

	virtual void* think(int param, ...);
	virtual void* observe(int param, ...);
	virtual void* move(int param, ...);
	virtual void* attack(int param, ...);
	virtual void* die(int param, ...);
	virtual void* interact(int param, ...);
	virtual void changeStrat();
	//virtual unsigned int getIndex();
	virtual ~rizzy();
};

class predator : public enemy
{

public:
	virtual void* think(int param, ...);
	virtual void* observe(int param, ...);
	virtual void* move(int param, ...);
	virtual void* attack(int param, ...);
	virtual void* die(int param, ...);
	virtual void* interact(int param, ...);
	virtual void changeStrat();
	//virtual unsigned int getIndex();
	virtual ~predator();

};

class assassin : public enemy
{

public:
	virtual void* think(int param, ...);
	virtual void* observe(int param, ...);
	virtual void* move(int param, ...);
	virtual void* attack(int param, ...);
	virtual void* die(int param, ...);
	virtual void* interact(int param, ...);
	virtual void changeStrat();
	//virtual unsigned int getIndex();
	virtual ~assassin();
};















