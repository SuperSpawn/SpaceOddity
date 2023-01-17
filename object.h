#pragma once
#include "defs.h"
//#include "olcPixelGameEngine.h"
#include "olcPGEX_Graphics2D.h"
//#include "olcPGEX_Sound.h"

//class olc::GFX2D;


#define OTYPE_NUM 41
#define MUTUAL_DEFENCE_THRESH 100
#define INSTANT_ATTACK_THRESH -200
#define SAME_TYPE_OFFSET 25


enum o_types
{
	PLAYER = 0
	, HUMAN
	, ALIEN_NOMAD
	, ALIEN_DWELLLER
	, ALIEN_MERC
	, DOG
	, SPAWN						//servant of king spawn
	, KING_SPAWN				//local spawn leader
	, EMPEROR_SPAWN				//emperor of all spawns
	, GENGHIS_SPAWN				//the single greatest spawn
	, KILLER_WHALE
	, KILLER_WHALE_PACT
	, GIANT_KILLER_WHALE
	, SPACE_PIRATE
	, SPACE_PIRATE_SHIP
	, SPACE_PIRATE_CAPTAIN
	, CONFEDERATE_CITIZEN
	, CONFEDERATE_SOLDIER
	, CONFEDERATE_LEADER
	, ROBOT
	, ARCEDIAN
	, KOMOE
	, SPICER
	, SPICER_PACT
	, SPICER_CARAVAN
	, SPICER_SPACE_SHIP
	, SPICER_SOLDIER
	, SPICER_TRADER
	, SPICER_KING
	, SYNDICATE_SOLDIER
	, SYNDICATE_OFFICER
	, SYNDICATE_SPACESHIP
	, SYNDICATE_MEDIUM_SHIP
	, SYNDICATE_LARGE_SHIP
	, SYNDICATE_MOTHER_SHIP
	, UNION_CITIZEN
	, UNION_SOLDIER
	, UNION_WORKER
	, UNION_OFFICER
	, UNION_GENERAL
	, RIZZY						//evill
};


class object
{
public:
	float _lookAngle, _movementAngle;
	float _terminalSpeed;//max speed
	float cosval, sinval;//save processing time
	float totalSpeed;

	float vpov = 0.0f, hpov = 0.0f;
	uint32_t width = 0, height = 0;


	friend void A_look(void* thee);
	
	decimal sprite_id;
	decimal id;
	pspace::fscaled _mass;
	
	olc::GFX2D::Transform2D trans;
	//olc::GFX2D strans;

	object* target;
	object* previousTarget;

	unsigned int beat;

	olc::vf2d cord;
	//float x, y;
	float localScale;
	float speedModifier;
	float r;

	float speedFactor[3];//0. horizontal speed 1.vertical speed 2.acceleration
	
	bool moving;
	
	double broadcastRange;
	double stateTime;

	decimal state1 = 0, state2 = 0, misc1 = 0, misc2 = 0, sound = 0;
	decimal flags = 0;

	int crisis;

	void* first_p;
	void* second_p;

	//void rotate(const float& rotateby, const float& rx = 0, const float& ry = 0);

	friend class spaceoddity;

	virtual void translatex(const float& translate = 0);
	virtual void translatey(const float& translate = 0);
	virtual void translate(const float& sx = 0, const float& sy = 0);
	virtual void translate(const f2& sh);

	virtual bool checkCollide(olc::vi2d upperLeft, olc::vi2d bottomRight)
	{
		//bool a = (cord.x > upperLeft.x);
		//bool b = (cord.x < bottomRight.x);

		return (cord.x > (upperLeft.x - r)) && (cord.x < (bottomRight.x + r))
			&& (cord.y > (upperLeft.y - r)) && (cord.y < (bottomRight.x + r));
	}

	virtual void raccelerate(const int& index, const float& shift = 0.0f);

	virtual const float& getDir();
	virtual void adjustDir(const float& angle);//change direction of ship
	virtual void setDir(const float& angle);

	virtual void rotateAround(f2 point, float force);

	virtual void flush(const float& pointx, const float& pointy)
	{
		cord.x -= pointx;
		cord.y -= pointy;
	}
	virtual decimal updateState(float fElapsedTime);
	virtual void setState(decimal state);
	virtual decimal type() = 0;
	
	virtual ibig examineOther(object* other);
	virtual void changeStrat()
	{
		return;
	}
	virtual void perFrame(float fElapsedTime, decimal misc)
	{
		return;
	}
	virtual void draw(void* game)
	{
		return;
	}
	virtual bool pcheckCollide(olc::Sprite* spr) { return false; }
	virtual ~object()
	{

	}
	
};



extern ibig topinions[OTYPE_NUM][OTYPE_NUM];





