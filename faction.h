#pragma once
#include "swindow.h"



struct faction
{
	string name;
	entity* leader;
	

};

namespace pspace
{
	enum p_factions
	{
		NO_FACTION = 0
		, THE_SYNDICATE				//SPACE FASCISTS
		, PILGOR_FACTION			//GOAT TERRORISTS
		, THE_SPACE_UNION			//OPPOSITION TO THE SYNDICATE
		, SPACE_PIRATES				//RRRRRR
		, SPACE_DOGS				//INTELLEGENT DOGS
		, SPACE_CATS				//CATS
		, THE_SPAWN_EMPIRE			//EHHHHHH
		, THE_MERCHANTS_GUILD		//SSETH
		, NUMBER_OF_FACTIONS
	};
}




