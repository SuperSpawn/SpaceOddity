#pragma once
#include "merchant.h"

#define QUIRK_NUM_LIMIT 3
#define CHUNK_ATTEMPS 10 





namespace pspace
{
	//quest stuff
	enum quest_types
	{
		DELIVER_ITEM = 0
		, NUMBER_OF_QUEST_CATS		
	};

	extern std::vector<uint32_t> deliver_item_types;


	class quest
	{
	public:
		uint32_t minute_time;
		float second_time;
		olc::vi2d target_chunk, target_place;
		bool reached_chunk;
		bool bFailed;
		bool bFreeze;

		virtual int check_requirement() = 0;
		virtual int upon_start() = 0;
		virtual int upon_fail() = 0;
		virtual int upon_complete() = 0;

		virtual void upon_going_right();
		virtual void upon_going_left();
		virtual void upon_going_up();
		virtual void upon_going_down();

		virtual ~quest();
	};
	class deliver_item : public quest
	{
	public:
		uint32_t desired_item, amount;
		int _planet;
		byte planet_pos;
		decimal payout;

		deliver_item(uint32_t dificulty);

		virtual int check_requirement();
		virtual int upon_start();
		virtual int upon_fail();
		virtual int upon_complete();
		virtual ~deliver_item();
	};
	//end of quest stuff

	//scene stuff
	

	//end of scene stuff
}



class director
{
public:	
	
	std::list<pspace::deliver_item> quests;
	std::list<pspace::deliver_item>::iterator current_quest;

	uint32_t executed_events, ticks_for_call, min, max;
	uint32_t calls_for_sec;

	std::array<std::pair<uint32_t,uint32_t>, director_event::NUMBER_OF_DIR_EVENTS> odds;

	director(uint32_t _min, uint32_t _max);
	
	uint32_t generate_event();
	uint32_t generate_quest(uint32_t level);
	
	uint32_t per_frame();

	virtual ~director();

};


