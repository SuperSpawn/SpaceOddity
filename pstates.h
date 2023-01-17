#pragma once
#include "faction.h"



//empty for now

struct uaction
{
	void (*action_v)();
	void (*action1)(void*);
	void (*action2)(void*, void*);
};


struct paction
{
	int mode;
	uaction func;
	void* first_p;
	void* second_p;
	void* third_p;
	void* fourth_p;


	void operator()(void* first = NULL, void* second = NULL)
	{
		if (func.action_v)
			func.action_v();
		if (func.action1)
			func.action1(first);
		if (func.action2)
			func.action2(first, second);

		return;
	}
	void* operator*()
	{
		switch (mode)
		{
		case 0:
			return func.action_v;
		case 1:
			return func.action1;
		case 2:
			return func.action2;
		default:
			return NULL;
		}
	}
};

struct SpriteState
{
	decimal sspriteID;
	double time, ctime;
	decimal nextState;

	decimal misc1;
	decimal misc2;

	paction func;
	byte flags;
	bool partial;
};

struct eState
{
	int state;
	double tmodifier;
};


struct ssprite
{
	decimal spriteID;
	cord2<olc::vi2d> state;
};

enum eStates
{
	IDLE = 0
	, ATTACK
	, RUSH
	, MOVE_UP
	, MOVE_DOWN
	, MOVE_RIGHT
	, MOVE_LEFT
	, DIE
	, LEFT_2_RIGHT
	, RIGHT_2_LEFT
};




enum sspriteNames
{
	SNULL = 0
	, WHALE1
	, WHALE2
	, WHALE3
	, WHALE4
	, WHALE5
	, WHALE6
	, WHALE7
	, WHALE8
	, WHALE9
	, WHALE10
	, WHALE_MOUTH1
	, WHALE_MOUTH2
	, EXPLOSION1
	, EXPLOSION2
	, EXPLOSION3
	, EXPLOSION4
	, EXPLOSION5
	, BLUE_WHALE1
	, BLUE_WHALE2
	, BLUE_WHALE3
	, BLUE_WHALE4
	, BLUE_WHALE5
	, BLUE_WHALE6
	, BLUE_WHALE7
	, BLUE_WHALE8
	, BLUE_WHALE9
	, BLUE_WHALE10
	, BLUE_WHALE_MOUTH1
	, BLUE_WHALE_MOUTH2

	, PARTIAL_WHALE1
	, PARTIAL_WHALE2
	, PARTIAL_WHALE3
	, PARTIAL_WHALE4
	, PARTIAL_WHALE5
	, PARTIAL_WHALE6
	, PARTIAL_WHALE7
	, PARTIAL_WHALE8
	, PARTIAL_WHALE9
	, PARTIAL_WHALE10
};


enum sprites
{
	NULL_SPRITE = 0
	, REGULAR_WHALE_SPRITE
	, SINE_WHALE_SPRITE
	, LINE_WHALE_SPRITE
	, CITY_SPRITE
};


extern SpriteState whaleState[nStates::NSTATES_NUMBER];



extern ssprite ssprites[];

void A_look(void* thee);
void A_speak(void* thee, void* world);
void A_scream(void* thee);
void A_wakeup(void* thee);








