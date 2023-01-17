#pragma once
#include <iostream>
#include <ostream>
#include <string>
#include <array>
#include "lehmer.h"
#include <stdarg.h>
#include <unordered_map>
#include <cstdint>
#include <stdint.h>

//typedef std::_Big_uint128 myuint128;

//using std::_Big_multiply;

//#include <vector>

#define SIZE_OF_BLOCK 32
#define SCREEN_WIDTH 920
#define SCREEN_HEIGHT 750

#define MUSIC_ASSETS_FOLDER_PATH "game_assets\\music\\David Bowie\\"
#define MUSIC_FILE_FORMAT ".wav"
#define SPRITE_ASSETS_FOLDER_PATH "game_assets\\assets\\"

using std::cout;
using std::endl;
using std::string;

extern unsigned long long int num_ships;
using std::unordered_map;
using std::to_string;
typedef unsigned char byte;//8 bit unsigned integer
typedef unsigned long long int decimal;//64 bit unsigned integer
typedef long long int ibig;
typedef void something;

using std::array;

/*
function pointer casting
//void* a = &func
//assuming func is of type void* func(void* arg)
//(void* (*)(void*))a is the casting

*/

class swindow;


template<typename a, typename b>
struct dual
{
	a first; b second;
};

struct windowStuff
{
	void* thing;
	swindow* parent;
};

struct parameter
{
	something* thing;
	string nametype;
	decimal id;
};



typedef struct
{
	int argnum;
	void** args;
} darg;

typedef enum
{
	DRAW = 0
	, REGULAR
} dfunctypes;

struct cfunc
{
	int type;
	int color;
	int argnum;
	void* (*func)(int, ...);
};
struct dfunc
{
	int type;
	int color;
	int argnum;
	void** args;
	void* (*func)(int, void**);

	void* activate()
	{
		return func(argnum, args);//call func
	}

	~dfunc()
	{
		int j;
		
		if (color == -1)
			return;

		for (j = 0; j < color; ++j)
			args[j] = NULL;
		while (j < argnum)
		{
			delete args[j++];
		}

		if (argnum == 1)
			delete args;
		else
			delete[] args;
	}


};

extern const dfunc nillfunc;

struct polyFunc
{
	virtual void activate()
	{
		return;
	}
	virtual ~polyFunc()
	{

	}
};



namespace pspace
{
	
	enum defaultstat
	{
		SKILL_NUM = 21
		, ATTR_NUM = 10
		, BASE_SKILL
		, BASE_ATTR
		
	};

	//increased by use
	typedef enum
	{
		GUNS = 0		//1. combat with guns
		, HACKING		//2. self explanitory 
		, REPAIR		//3. repair equipment to increase durability and value of object
		, BARTER		//4. increase value of trade goods and lower price of bought goods
		, INTIMIDATION	//5. intimidate people
		, PERSUATION	//6. persuade people
		, STREETWISE	//7. connect with common folk
		, NOBLESPEAK	//8. connect with the rich nobility
		, MELEE			//9. melee weapons
		, COOKING		//10. special skill
		, PICKPOCKET	//11. stealing from pockets
		, LOCKPICK		//12. pick locks to unlock stuff
		, SNEAK			//13. sneak 
		, ACROBAT		//14. jumping
		, ATHLETIC		//15. running
		, SURVIVAL		//16. toughness in harsh conditions
		, MEDIC			//17. first aid medic helps with light wounds
		, SURGERY		//18. complex diseases and operattions
		, ALCHEMY		//19. used to make stuff
		, LOOTING		//20. loot from bodies and identify parts
		, ELECTRONICS	//21. tinkering with electronics
		, NUMBER_OF_SKILLS
	}
	pskill;

	
	//increased at level up
	typedef enum
	{
		STRENGTH = 0	//1.
		, WILLPOWER		//2.
		, AGILITY		//3.
		, INTELLIGENCE	//4.
		, DEXTIRITY		//5.
		, CHARISMA		//6.
		, ENDURANCE		//7.
		, PERCEPTION	//8.
		, LUCK			//9.
		, CONFIDENCE	//10.
	}
	pattribute;

	

	typedef enum
	{
		CAREFUL = 0
		, BALANCED
		, AGGRESSIVE
	}	wayoflife;

	typedef enum
	{
		SUPPORT = 0
		, COMBAT
		, STEALTH
		
	}	focus;

	

	class personality
	{
		//focuses
		//movement
		//skill usage
		int aggression;
		int projection;
		int rationality;
		int confidence;
		

		



	public:




	};


	
	struct dcp
	{
		cord2<uint32_t> pos;
		uint32_t width, height, id;
		polyFunc* function;

		~dcp()
		{
			delete function;
		}
	};

	
	struct fscaled 
	{							
		float frac;
		decimal scale;
	};


	struct dscaled
	{
		double frac;
		long long int scale;//base 10 for now
	};

	//template<decimal base>
	struct dunit
	{
		decimal units;
		double offset;

		double consumptionModifier, gainModifier;
		
		dunit& operator+=(double value)
		{
			double val = value * gainModifier;
			offset += val;
			decimal whole = offset;
			offset -= whole;
			units += whole;
			return *this;
		}
		dunit& operator-=(float value)
		{
			double val = value * consumptionModifier;
			if (offset < val)
			{
				if (units != 0)
				{
					--units;
					offset += 1.0;
					offset -= val;
					return *this;
				}
				
				offset = 0.0;
				return *this;
			}

			offset -= val;
			return *this;
		}
		dunit& operator-=(double value)
		{
			double val = consumptionModifier * value;
			if (offset < val)
			{
				if (units != 0)
				{
					--units;
					offset += 1.0;
					offset -= val;
					return *this;
				}
				
				offset = 0.0;
				return *this;
			}

			offset -= value;
			return *this;
		}

	};
}



enum director_event
{
	DIR_NULL = 0
	, SPAWN_WHALE_PACK
	, START_SPACE_BATTLE
	, ACCIDENT_MONEY_TRANFER
	, GIFT_FROM_SOMEONE
	, MONEY_ROBBED
	, SPAWN_BLACK_HOLE
	, SPAWN_ASTROID
	, NUMBER_OF_DIR_EVENTS
	, EPACK_COLLIDE
	, ASTROID_COLLIDE
	, BLACK_HOLE_COLLIDE
	, SYNDICATE_PATROL_COLLIDE
	, WARZONE_COLLIDE
	, DELIVER_QUEST_FAIL
	, INCREASE_PLAYER_LEVEL
};


enum nStates
{
	WHALE_IDLE1 = 0
	, WHALE_IDLE2
	, WHALE_MOVE1
	, WHALE_MOVE2
	, WHALE_MOVE3
	, WHALE_MOVE4
	, WHALE_MOVE5
	, WHALE_MOVE6
	, WHALE_MOVE7
	, WHALE_ROTATION1
	, WHALE_ROTATION2
	, WHALE_ROTATION3
	, WHALE_ATTACK1
	, WHALE_ATTACK2
	, WHALE_ATTACK3
	, WHALE_ATTACK4

	, PARTIAL_WHALE_IDLE1
	, PARTIAL_WHALE_IDLE2
	, PARTIAL_WHALE_MOVE1
	, PARTIAL_WHALE_MOVE2
	, PARTIAL_WHALE_MOVE3
	, PARTIAL_WHALE_MOVE4
	, PARTIAL_WHALE_MOVE5
	, PARTIAL_WHALE_MOVE6
	, PARTIAL_WHALE_MOVE7
	, NSTATES_NUMBER
};
