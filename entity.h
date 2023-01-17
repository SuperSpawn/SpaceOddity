#pragma once
//#include "pathfind.h"
#include "filestuff.h"

#define NAME_PREFIX_NUM 23
#define NAME_SUFFIX_NUM 23
#define NAME_STEM_NUM 20

#define COMPANION_NAME_FACTOR_ARR_SIZE 36

extern decimal number_of_chars;//number of total characters loaded
extern decimal num_special_chars;//number of total special characters loaded


//going to save special characters
//special characters file


namespace pspace
{
	enum entity_age_types
	{
		ENTITY_CHILD = 0	//7 - 12
		, ENTITY_TEEN		//12 - 18
		, ENTITY_YOUNG_ADULT	//18 - 30
		, ENTITY_ADULT		//30 - 45
		, ENTITY_ELDERLY	//45 - 70
		, ENTITY_REALLY_OLD		//100+
		, NUMBER_OF_AGE_TYPES
	};

	enum entity_species_types
	{
		HUMAN = 0
		, SPACE_DOG
		, SPACE_CAT
		, KILLER_WHALE
		, PILGOR
		, GNOME
		, ARGONIAN
		, SPICER
		, KILLER_ROBOT
		, SENTIENT_AI
		, NUMBER_OF_SPECIES_TYPES
	};

	enum entity_class_ship_companions
	{
		UNARMED_BRUTE = 0			//BRUTE TACTICS
		, MARTIAL_ART			//MARTIAL ART TACTICS
		, MELEE_FIGHTER			//MELEE WEAPONS
		, SNIPER_FIGHTER		//PERCISION NOT SPEED
		, PISTOL_FIGHTER		//SPEED NOT PERCISION	- PISTOL ONLY
		, RIFLE_FIGHTER			//SPEED NOT PERCISION	- RIFLE ONLY
		, MECHANIC				//FIX MECHANICAL STUFF
		, FIELD_MEDIC			//HEALS WOUNDS AND SOME ILLNESSES - NOT SERIOUS ONES
		, SURGEON				//DOES OPERATIONS - CANNOT DETECT DISEASES (UNTIL TOO LATE)
		, DOCTOR				//DETECTS FOR DISEASES - GIVES PERSCREPTION
		, LOGISTICS_MANAGER		//HELPS WITH BUYING SUPPLIES FOR THE CREW
		, JANITOR				//CLEANS SPACESHIP AND PREVENTS DISEASE
		, TECHNICIAN			//FIXES TECH STUFF
		, CHEF					//COOKS FOR THE CREW AND SAVES SCRAPS FOR FUTURE USE
		, NUMBER_OF_COMPANION_TYPES
	};
	
	enum entity_class_types
	{
		TRADER = 0
		, CITIZEN
		, FARMER, CLOTHES_MAKER, CARPENTER, SCHOLAR
		, MERCENARY, RAIDER, NOMAD
		, SOLDIER, OFFICER, GENERAL
		, STORE_OWNER
		, BEUROCRAT, ARISTOCRAT
		, KING
		, NUMBER_OF_CLASS_TYPES
	};

	const string ent_name_factors[] =
	{
		"xi", "a", "xin", "ta", "tao", "tal", "at", "an", "ak", "ba", "r", "e", "ee", "d"
		, "jim", "him", "meh", "sun", "abd", "l", "ke", "che", "we", "wi", "wa", "wo", "zo", "za", "zi"
		, "kek", "gen", "obi", "k", "ken", "kino", "wal"
	};

	class companion
	{
	public:
		string name;
		float age;
		int species, class_type;
		uint32_t level;

		companion(decimal id1, decimal id2, decimal _level)
		{
			name = "";
			nLehmer128 = id1;
			nLehmer128 <<= 64;
			nLehmer128 += id2;

			int size, i;
			size = 3 + big_alternate_rndInt128(0, 12);
			for (i = 0; i < size; ++i)
				name += ent_name_factors[big_alternate_rndInt128(0, COMPANION_NAME_FACTOR_ARR_SIZE)];
			species = big_alternate_rndInt128(0, pspace::entity_species_types::NUMBER_OF_SPECIES_TYPES);
			class_type = big_alternate_rndInt128(0, pspace::entity_class_ship_companions::NUMBER_OF_COMPANION_TYPES);
			age = 7.0f + big_alternate_rndInt128(0, 200);
			level = big_alternate_rndInt128(0, _level);
		}

	};
}

extern string companion_class_types[pspace::entity_class_ship_companions::NUMBER_OF_COMPANION_TYPES];
extern string species_types[pspace::entity_species_types::NUMBER_OF_SPECIES_TYPES];

class entity : public object
{
public:
	string _name;
	//useless for now tbh
	float _age;
	int _species;
	int class_type;
	
	

	entity(const string& name, int age_range);

	


	//set stuff

	~entity();
};


const string nameprefix[] =
{
	"", "bel", "nar", "xan", "bell", "natr", "ev", "an", "ell", "el", "al", "lil"
	, "al ", "ab", "jib", "lo ", "lo", "poly", "xi", "za", "zoo", "ze", "xsd"
};
const string namesuffix[] =
{
	"", "us", "ix", "ox", "ith", "ath", "um", "ator", "or", "axia", "imus",
	"ais", "itur", "orex", "o", "y", "at", "am", "ex", "ax", "ok", "ak", "von"
};
const string namestems[] =
{
	"adur", "aes", "anim", "apoll", "imac", "educ", "equis", "extr", "guius",
	"han", "equi", "amora", "hum", "iace", "ille", "inept", "iuv", "obe",
	"ocul", "orbis"
};


string generate_name();