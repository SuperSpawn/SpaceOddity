#include "entity.h"

decimal number_of_chars = 0;

const dfunc nillfunc = { 0,0,0,NULL, NULL };


entity::entity(const string& name, int age_range)
{
	_name = name;
	

}


entity::~entity()
{
	
}

string generate_name()
{
	string nname;
	decimal rrand;
	rrand = big_alternate_rndInt128(0, NAME_PREFIX_NUM);
	nname = nameprefix[rrand];
	rrand = big_alternate_rndInt128(0, NAME_STEM_NUM);
	nname += namestems[rrand];
	rrand = big_alternate_rndInt128(0, NAME_SUFFIX_NUM);
	nname += namesuffix[rrand];
	nname.shrink_to_fit();
	return nname;
}


string companion_class_types[pspace::entity_class_ship_companions::NUMBER_OF_COMPANION_TYPES] =
{
	"Unarmed brute", "Martial art", "Melee fighter", "Sniper fighter", "Pistol fighter"
	, "Rifle fighter", "Mechanic", "Field medic", "Surgeon", "Doctor", "Logistics manager"
	, "Janitor", "Technician", "Chef"
};

string species_types[pspace::entity_species_types::NUMBER_OF_SPECIES_TYPES] =
{
	"Human", "Space dog", "Space cat", "Killer whale", "Pilgor", "Gnome", "Argonian", "Spicer"
	, "Killer robot", "Sentient AI"
};