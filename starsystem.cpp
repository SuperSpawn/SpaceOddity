#include "starsystem.h"

solarsystem::solarsystem(const byte& planetNum, const bool& destroyPlanets)
{
	byte i, j;

	number_planet = planetNum;
	destroyPlanetsToo = false;
	_system = new sPlanet * [planetNum];
	if (_system == NULL)
		throw - 1;//no memory left :(
	for (i = 0; i < planetNum; ++i)
	{
		_system[i] = new sPlanet();
		if (_system[i] == NULL)
		{
			for (j = 0; j <= i; ++j)
				delete _system[i];
			delete _system;
			throw - 1;
		}
	}
}

void pspace::warzone::rePosition()
{
	cord.x = sSlot.x + big_alternate_rndInt128(0, SIZE_OF_BLOCK);
	cord.y = sSlot.y + big_alternate_rndInt128(0, SIZE_OF_BLOCK);
}

pspace::disease::disease()
{
	name = "";
	detected = false;
	bActive = false;
	level_to_cure = level_to_detect = t_minutes = t_second = 0;
}
pspace::disease::disease(uint32_t dificulty, decimal id)
{
	name = "";
	detected = false;
	nLehmer128 = id;
	nLehmer128 <<= 64;
	nLehmer128 += id;
	uint32_t number_of_name_factors = big_alternate_rndInt128(5, 17);
	uint32_t i;
	for (i = 0; i < number_of_name_factors; ++i)
	{
		name += g_drug_name_factors[big_alternate_rndInt128(0, G_DRUG_NAME_FACTORS_SIZE)];
	}
	name.shrink_to_fit();
	level_to_cure = dificulty + big_alternate_rndInt128(0, dificulty >> 1);
	level_to_detect = big_alternate_rndInt128(0, dificulty >> 1);
	t_minutes = big_alternate_rndInt128(3, 60);
	t_second = big_alternate_rndInt128(1, 60);
}




