#pragma once
#include "item_subcats.h"



class product_type
{
protected:
	decimal id;
	string name;
	decimal tier;
	decimal subtype;

public:
	
	product_type(const string& _name);

	virtual double getPrice(decimal amount = 1);
	virtual string getName()
	{
		return "HELLO";
	}

	virtual ~product_type();
};


enum planet_types
{
	DESERT_PLANET = 0
	, ICE_PLANET
	, WATER_PLANET
	, EARTH_LIKE_PLANET
	, ROCK_PLANET
	, TOXIC_PLANET
	, MINERAL_PLANET
	, NUMBER_OF_TYPES
};




enum e_items
{
	PNULL = 0
	, COMMON_METALS, PRESCIOUS_METALS, EXOTIC_METALS, RARE_METALS
	, COMMON_METAL_ORE, PRESCIOUS_METAL_ORE, EXOTIC_METAL_ORE, RARE_METAL_ORE
	, COMMON_MINERALS, PRESCIOUS_MINERALS, EXOTIC_MINERALS, RARE_MINERALS
	, COMMON_NARCOTICS, RARE_NARCOTICS, EXOTIC_NARCOTICS
	, INDUSTRIAL_ELECTRONICS, CONSUMER_ELECTRONICS, MILITARY_ELECTRONICS
	, COMPUTER_CHIPS, SUPER_COMPUTER_CHIPS, QUANTUM_COMPUTER_CHIPS
	, COMPUTER_PROCESSORS, QUANTUM_PROCESSORS
	, SMALL_BAL_ARMS, HEAVY_BAL_ARMS, SMALL_LAZER_ARMS, HEAVY_LAZER_ARMS
	, COMMON_SPICES, EXOTIC_SPICES
	, MEDICAL_EQUIPMENT, INDUSTRIAL_EQUIPMENT, MILITARY_EQUIPMENT
	, ORGANS
	, MEDICINE			//DRUGS	
	, COMPUTER_PARTS, SUPER_COMPUTER_PARTS, QUANTUM_COMPUTER_PARTS
	, COMPUTERS, SUPER_COMPUTERS
	, AI_CORES			//HIGHLY ILLEGAL
	, MECH_PARTS, SPACESHIP_MECH_PARTS
	, JUNK
	, UWU
	, FOOD, WATER, FUEL, OIL, SAND, QUARTZ, DIAMOND, GLASS, COMMON_POTTERY
	, EXOTIC_POTTERY, IRON, STEEL, GOLD, HISTORICAL_RELICS, RELIGIOUS_RELICS, PAPER, SUGAR
	, OLIVE_OIL, OLIVES, SUGAR_CANE, WOODEN_PLANKS, TREE_TRUNKS, TREE_SAPLING
	, ICE, HONEY, MILK, BUTTER, LIVESTOCK, COPPER, LAVA
	, PEN, PENCIL, BAG, C4, TNT, GUNPOWDER, SUPER_GUNPOWDER, SWEETS, CAKE, MALE_CLOTHES
	, FEMALE_CLOTHES, CHILD_CLOTHES, DIRT, TOXIC_WASTE, BROKEN_TV, BROKEN_RADIO, OLD_COUCH
	, SPACE_WHALE_EGGS, SPACE_WHALE_TEETH, SPACE_WHALE_SKULL, SPACE_WHALE_BONES
	, BATH_SALTS, ACID
	, ICE_CREAM, EMPTY_GLASS_BOTTLE, BROKEN_GLASS_BOTTLE, RIPPED_CLOTHES, EMPTY_CANS
	, PLASTIC_BOTTLES, PILLOWS, MATTRESS, ENERGY_DRINKS, STOMACH_ACID, EMERALDS
	, RUBYS, CIGARS, CIGARRETES, BATTERIES, NAPKINS, GLOVES, HAMMERS, WORK_GLASSES, GLASSES
	, SUNGLASSES, HAT, HELMET, POLICE_UNIFORM, MILITARY_UNIFORM, POLICE_ID
	, MILITARY_ID, UNDERWEAR, BLANKETS, REAL_FAKE_DOORS, WOODEN_DOORS, METAL_DOORS
	, HOUSES, TREES, GOAT_MILK
	, ONIONS, TOMATOES, POTATOS, CARROTS, BEANS, BREAD, CORN, FLOUR, ORANGES, ORANGE_JUICE
	, CUCUMBERS, PICKLES, PAPRIKA, THOUSAND_ISLANDS_SAUCE, MUSTARD, KETCHUP, GRAPES
	, LIVE_LOBSTER, FROZEN_LOBSTER, PUFFER_FISH, JAR_OF_JELLY, HOTDOGS, PIZZA
	, PINEAPPLE_PIZZA, SUSHI, MAYO, EGGS, RAW_MEAT, COOKED_MEAT
	, SHAMPOO
	, WRENCH, CROWBAR, GRENADES, EMP_GRENADES, NUCLEAR_WARHEADS
	, NUMBER_OF_ITEMS
};


struct item
{
	string name;
	decimal price;
	double weight;
	int id;
};


struct slot
{
	item type;
	decimal amount;
};
extern std::vector<std::vector<uint32_t>> merchant_cats;
extern item types[e_items::NUMBER_OF_ITEMS];

class merchant
{
public:
	string name;
	//array<float, e_items::NUMBER_OF_ITEMS> priceFactors;
	
	std::vector<slot> stock;
	std::array<int, e_items::NUMBER_OF_ITEMS> desire;

	merchant(decimal idx, decimal idy)
	{
		//std::vector<int>& stockRef = item_cats[merchantType];
		nLehmer128 = idx;
		nLehmer128 <<= 64;
		nLehmer128 += idy;

		std::array<int, e_items::NUMBER_OF_ITEMS>::iterator desire_itr;
		for (desire_itr = desire.begin(); desire_itr != desire.end(); ++desire_itr)
		{
			*desire_itr = big_alternate_rndInt128(0, 1000);
			*desire_itr -= 1000;
		}

		uint32_t type = big_alternate_rndInt128(0, merchant_cats.size());
		
		std::vector<uint32_t>::iterator item_itr;
		for (item_itr = merchant_cats.at(type).begin();
			item_itr != merchant_cats.at(type).end(); ++item_itr)
		{
			slot i;
			i.type = types[*item_itr];
			i.amount = big_alternate_rndInt128(0, 200);
			stock.push_back(i);
		}
		name = generate_name();
	}
	~merchant()
	{
		stock.clear();
	}
};



