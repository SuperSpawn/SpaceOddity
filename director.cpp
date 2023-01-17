#include "director.h"

director::director(uint32_t _min, uint32_t _max)
{
	max = _max;
	min = _min;
	uint32_t size_of_block = max - min + 1, i, j;
	size_of_block /= director_event::NUMBER_OF_DIR_EVENTS;
	j = 0;
	for (i = min; i < max; i += size_of_block)
	{
		odds[j].first = i;
		odds[j++].second = std::min(i + size_of_block, max);
	}

	calls_for_sec = 5;
	ticks_for_call = 0;
	executed_events = 0;

	current_quest = quests.end();
}

uint32_t director::generate_event()
{
	uint32_t generated_num = big_alternate_rndInt128(min, max), iEvent = 1;
	std::array< std::pair<uint32_t, uint32_t>, director_event::NUMBER_OF_DIR_EVENTS>::iterator runner;
	for (runner = odds.begin(); runner != odds.end(); ++runner)
	{
		if ((generated_num >= runner->first) && (generated_num < runner->second))
		{
			return iEvent;
		}
		++iEvent;
	}

	return director_event::DIR_NULL;
}

uint32_t director::generate_quest(uint32_t level)
{
	int generate_num = big_alternate_rndInt128(0, pspace::quest_types::NUMBER_OF_QUEST_CATS);
	uint32_t difi = big_alternate_rndInt128(0, level);

	if (generate_num == pspace::quest_types::DELIVER_ITEM)
	{
		pspace::deliver_item deliver_ptr(difi);
		
		if (deliver_ptr.bFailed)
		{
			return 0;
		}
		if (quests.empty())
		{
			quests.push_back(deliver_ptr);
			current_quest = quests.begin();
		}
		else
		{
			quests.push_back(deliver_ptr);
		}
		
	}
	


	return 1;
}

uint32_t director::per_frame()
{
	if (ticks_for_call == 0)
	{
		ticks_for_call = CLOCKS_PER_SEC * calls_for_sec;
		return generate_event();
	}
	--ticks_for_call;
	return director_event::NUMBER_OF_DIR_EVENTS;
}

director::~director()
{
	quests.clear();
}

pspace::deliver_item::deliver_item(uint32_t dificulty)
{
	target_chunk.x = big_alternate_rndInt128(0, dificulty);
	target_chunk.x -= dificulty;
	target_chunk.y = big_alternate_rndInt128(0, dificulty);
	target_chunk.y -= dificulty;

	minute_time = dificulty + 3;
	second_time = 5.0f;


	reached_chunk = false;
	bFailed = false;
	bFreeze = false;
	_planet = -1;
	
	target_place.x = big_alternate_rndInt128(0, SCREEN_WIDTH / SIZE_OF_BLOCK) * SIZE_OF_BLOCK;
	target_place.y = big_alternate_rndInt128(0, SCREEN_HEIGHT / SIZE_OF_BLOCK) * SIZE_OF_BLOCK;

	desired_item = big_alternate_rndInt128(0, merchant_cats.size());
	desired_item = merchant_cats.at(desired_item).at(big_alternate_rndInt128(0, merchant_cats.at(desired_item).size()));
	amount = 1 + big_alternate_rndInt128(0, dificulty);
	payout = 3000 + amount * types[desired_item].price * dificulty;


}

int pspace::deliver_item::check_requirement()
{
	return 0;
}

int pspace::deliver_item::upon_start()
{
	return 0;
}

int pspace::deliver_item::upon_fail()
{
	return director_event::DELIVER_QUEST_FAIL;
}

int pspace::deliver_item::upon_complete()
{
	return director_event::INCREASE_PLAYER_LEVEL;
}

pspace::deliver_item::~deliver_item()
{
}

void pspace::quest::upon_going_right()
{
	target_chunk.x--;
	if ((target_chunk.x == 0) && (target_chunk.y == 0))
		reached_chunk = true;
	else
		reached_chunk = false;
}
void pspace::quest::upon_going_left()
{
	target_chunk.x++;
	if ((target_chunk.x == 0) && (target_chunk.y == 0))
		reached_chunk = true;
	else
		reached_chunk = false;
}
void pspace::quest::upon_going_up()
{
	target_chunk.y++;
	if ((target_chunk.x == 0) && (target_chunk.y == 0))
		reached_chunk = true;
	else
		reached_chunk = false;
}
void pspace::quest::upon_going_down()
{
	target_chunk.y--;
	if ((target_chunk.x == 0) && (target_chunk.y == 0))
		reached_chunk = true;
	else
		reached_chunk = false;
}

pspace::quest::~quest()
{
}

