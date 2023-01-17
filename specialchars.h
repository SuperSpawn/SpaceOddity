#pragma once
#include "entity.h"

entity* specials;

bool generateSpecials()
{
	entity* k;
	int *skilz, *atts;
	
	skilz = new int[pspace::SKILL_NUM];
	if (skilz == NULL)
		return true;
	atts = new int[pspace::ATTR_NUM];
	if (atts == NULL)
	{
		delete[] skilz;
		return true;
	}
	
}



