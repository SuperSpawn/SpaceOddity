#include "merchant.h"

product_type::product_type(const string& _name)
{



}

double product_type::getPrice(decimal amount)
{
	return 0.0;
}

product_type::~product_type()
{
}

std::vector<std::vector<uint32_t>> merchant_cats =
{
	{e_items::FUEL, e_items::FUEL, e_items::FUEL}	//fuel seller
	,	{e_items::WATER, e_items::WATER}	//water seller
	,	{e_items::UWU}		//uwu seller
	,	{e_items::FOOD, e_items::FOOD}
	,	{e_items::FUEL, e_items::WATER, e_items::FOOD, e_items::BATTERIES, e_items::UWU, e_items::CIGARS
			, e_items::CIGARRETES, e_items::ICE_CREAM, e_items::SUNGLASSES, e_items::MILK
			, e_items::ENERGY_DRINKS}//gas station
	,	{e_items::BREAD, e_items::BUTTER}
	,	{e_items::BROKEN_TV, e_items::OLD_COUCH, e_items::BROKEN_RADIO, e_items::BROKEN_GLASS_BOTTLE
			, e_items::RIPPED_CLOTHES, e_items::JUNK, e_items::EMPTY_CANS, e_items::EMPTY_GLASS_BOTTLE}
	,	{e_items::SMALL_BAL_ARMS, e_items::SMALL_LAZER_ARMS, e_items::GRENADES, e_items::MECH_PARTS}
	,	{e_items::COMMON_SPICES, e_items::EXOTIC_SPICES, e_items::PAPRIKA, e_items::SUGAR}
	,	{e_items::HOUSES}
	,	{e_items::REAL_FAKE_DOORS, e_items::REAL_FAKE_DOORS, e_items::REAL_FAKE_DOORS
			, e_items::REAL_FAKE_DOORS, e_items::REAL_FAKE_DOORS}
	,	{e_items::ICE_CREAM, e_items::ICE_CREAM, e_items::ICE_CREAM}
	,	{e_items::CAKE, e_items::SWEETS, e_items::SUGAR}
	,	{e_items::METAL_DOORS, e_items::WOODEN_DOORS}
	,	{e_items::MECH_PARTS, e_items::WRENCH, e_items::CROWBAR, e_items::SPACESHIP_MECH_PARTS
			, e_items::HAMMERS, e_items::WORK_GLASSES, e_items::HELMET}
	,	{e_items::HAMMERS, e_items::WORK_GLASSES, e_items::HELMET, e_items::WRENCH, e_items::CROWBAR}
	,	{e_items::BLANKETS, e_items::MATTRESS, e_items::PILLOWS}
	,	{e_items::WATER, e_items::SHAMPOO, e_items::SHAMPOO, e_items::SHAMPOO, e_items::BATH_SALTS}
	,	{e_items::CIGARRETES, e_items::CIGARRETES, e_items::CIGARRETES,
			e_items::CIGARS, e_items::CIGARS}
	,	{e_items::BAG, e_items::PEN, e_items::PENCIL, e_items::PAPER}
	,	{e_items::BATTERIES, e_items::BATTERIES, e_items::BATTERIES}
	,	{e_items::BREAD, e_items::BUTTER, e_items::EGGS, e_items::HONEY}
	,	{e_items::CARROTS, e_items::BEANS, e_items::CUCUMBERS, e_items::TOMATOES, e_items::POTATOS
			, e_items::CORN, e_items::ONIONS}
	,	{e_items::PUFFER_FISH, e_items::FROZEN_LOBSTER, e_items::FROZEN_LOBSTER}
	,	{e_items::INDUSTRIAL_EQUIPMENT, e_items::INDUSTRIAL_ELECTRONICS, e_items::MECH_PARTS}
	,	{e_items::CONSUMER_ELECTRONICS, e_items::CONSUMER_ELECTRONICS, e_items::CONSUMER_ELECTRONICS,}
	,	{e_items::MALE_CLOTHES, e_items::FEMALE_CLOTHES, e_items::CHILD_CLOTHES, e_items::UNDERWEAR}
	,	{e_items::COMMON_POTTERY, e_items::COMMON_POTTERY, e_items::EXOTIC_POTTERY}
	,	{e_items::COPPER, e_items::IRON, e_items::STEEL, e_items::COMMON_METALS, e_items::PRESCIOUS_METALS
			, e_items::EXOTIC_METALS, e_items::RARE_METALS}
	,	{e_items::COMMON_METAL_ORE, e_items::PRESCIOUS_METAL_ORE, e_items::RARE_METAL_ORE
			, e_items::EXOTIC_METAL_ORE}
	,	{e_items::COMMON_NARCOTICS, e_items::EXOTIC_NARCOTICS, e_items::RARE_NARCOTICS, e_items::PAPRIKA}
	,	{e_items::COMPUTER_CHIPS, e_items::COMPUTER_PARTS, e_items::COMPUTER_PROCESSORS
			, e_items::COMPUTERS}
	,	{e_items::SUPER_COMPUTER_CHIPS, e_items::SUPER_COMPUTER_CHIPS, e_items::COMPUTER_PROCESSORS
			, e_items::SUPER_COMPUTERS}
	,	{e_items::EGGS, e_items::GOAT_MILK, e_items::MILK, e_items::FLOUR, e_items::SUGAR}
	,	{e_items::ICE, e_items::ICE, e_items::ICE}
	,	{e_items::QUARTZ, e_items::COMMON_MINERALS, e_items::EXOTIC_MINERALS, e_items::PRESCIOUS_MINERALS
			, e_items::RARE_MINERALS}
	,	{e_items::DIAMOND, e_items::EMERALDS, e_items::RUBYS}
	,	{e_items::HAT, e_items::HAT, e_items::HAT, e_items::HAT}
	,	{e_items::GOLD}
	,	{e_items::JAR_OF_JELLY, e_items::HONEY, e_items::GRAPES, e_items::BREAD}
	,	{e_items::SPACE_WHALE_BONES, e_items::SPACE_WHALE_SKULL, e_items::SPACE_WHALE_TEETH}
	,	{e_items::KETCHUP, e_items::MAYO, e_items::THOUSAND_ISLANDS_SAUCE, e_items::MUSTARD}
	,	{e_items::KETCHUP, e_items::MAYO, e_items::THOUSAND_ISLANDS_SAUCE, e_items::MUSTARD,
			e_items::HOTDOGS}
	,	{e_items::ACID, e_items::TOXIC_WASTE}
	,	{e_items::DIRT, e_items::TREE_SAPLING, e_items::TREES}
	,	{e_items::WOODEN_PLANKS, e_items::WOODEN_PLANKS, e_items::TREE_TRUNKS}
	,	{e_items::ENERGY_DRINKS, e_items::ENERGY_DRINKS}
	,	{e_items::RAW_MEAT, e_items::RAW_MEAT, e_items::RAW_MEAT}
	,	{e_items::GUNPOWDER, e_items::SMALL_BAL_ARMS, e_items::HEAVY_BAL_ARMS, e_items::GRENADES}
	,	{e_items::BATTERIES, e_items::SMALL_LAZER_ARMS, e_items::HEAVY_LAZER_ARMS}
	,	{e_items::SUSHI, e_items::CUCUMBERS, e_items::PUFFER_FISH}
	,	{e_items::BAG, e_items::PEN, e_items::PENCIL, e_items::PAPER}
	,	{e_items::COMMON_METAL_ORE, e_items::PRESCIOUS_METAL_ORE, e_items::RARE_METAL_ORE
				, e_items::EXOTIC_METAL_ORE}



};

item types[e_items::NUMBER_OF_ITEMS] =
{
		{"NULL", 0, 0.0, e_items::PNULL}					//1
	,	{"Common metals", 50, 10.0, e_items::COMMON_METALS}			//2
	,	{"Prescious metals", 500, 10.0, e_items::PRESCIOUS_METALS}		//3
	,	{"Exotic metals", 5000, 10.0, e_items::EXOTIC_METALS}		//4
	,	{"Rare metals", 10000, 10.0, e_items::RARE_METALS}		//5
	,	{"Common metal ores", 10, 10.0, e_items::COMMON_METAL_ORE}		//6
	,	{"Prescious metal ores", 100, 10.0, e_items::PRESCIOUS_METAL_ORE}		//7
	,	{"Exotic metal ores", 1000, 10.0, e_items::EXOTIC_METAL_ORE}			//8
	,	{"Rare metal ores", 100, 10.0, e_items::RARE_METAL_ORE}			//9
	,	{"Common minerals", 10, 1.0, e_items::COMMON_MINERALS}				//10
	,	{"Prescious minerals", 50, 0.1, e_items::PRESCIOUS_MINERALS}			//11
	,	{"Exotic minerals", 85, 0.1, e_items::EXOTIC_MINERALS}				//12
	,	{"Rare minerals", 175, 0.01, e_items::RARE_MINERALS}				//13
	,	{"Common narcotics", 250, 1.0, e_items::COMMON_NARCOTICS}			//14
	,	{"Rare narcotics", 1000, 1.0, e_items::RARE_NARCOTICS}				//15
	,	{"Exotic narcotics", 2500, 1.0, e_items::EXOTIC_NARCOTICS}			//16
	,	{"Industrial electronics", 70, 1.0, e_items::INDUSTRIAL_ELECTRONICS}		//17
	,	{"Consumer electronics", 30, 1.0, e_items::CONSUMER_ELECTRONICS}		//18
	,	{"Military electronics", 700, 1.0, e_items::MILITARY_ELECTRONICS}		//19
	,	{"Computer chips", 1, 0.001, e_items::COMPUTER_CHIPS}				//20
	,	{"Super computer chips", 1000, 0.002, e_items::SUPER_COMPUTER_CHIPS}		//21
	,	{"Quantum computer chips", 1000000, 0.5, e_items::QUANTUM_COMPUTER_CHIPS}	//22
	,	{"Computer processors", 300, 0.1, e_items::COMPUTER_PROCESSORS}		//23
	,	{"Quantum processors", 50000000, 10.0, e_items::QUANTUM_PROCESSORS}	//24
	,	{"Small ballistic arms", 300, 12.0, e_items::SMALL_BAL_ARMS}		//25
	,	{"Heavy ballistic arms", 30000, 5000.0, e_items::HEAVY_BAL_ARMS}		//26
	,	{"Small lazer arms", 1200, 15.0, e_items::SMALL_LAZER_ARMS}			//27
	,	{"Heavy lazer arms", 120000, 7500.0, e_items::HEAVY_LAZER_ARMS}		//28
	,	{"Common spices", 50, 1.0, e_items::COMMON_SPICES}				//29
	,	{"Exotic spices", 500, 1.0, e_items::EXOTIC_SPICES}				//30
	,	{"Medical equiptment", 1000, 50.0, e_items::MEDICAL_EQUIPMENT}		//31
	,	{"Industrial equiptment", 15000, 100.0, e_items::INDUSTRIAL_EQUIPMENT}	//32
	,	{"Military equiptment", 300000, 150.0, e_items::MILITARY_EQUIPMENT}		//33
	,	{"Organs", 2000, 30.0, e_items::ORGANS}					//34
	,	{"Medicine", 3000, 1.0, e_items::MEDICINE}					//35
	,	{"Computer parts", 300, 10.0, e_items::COMPUTER_PARTS}				//36
	,	{"Super computer parts", 30000, 10.0, e_items::SUPER_COMPUTER_PARTS}		//37
	,	{"Quantum computer parts", 3000000, 10.0, e_items::QUANTUM_COMPUTER_PARTS}	//38
	,	{"Computers", 1500, 50.0, e_items::COMPUTERS}					//39
	,	{"Super computers", 90000, 5000.0, e_items::SUPER_COMPUTERS}			//40
	,	{"AI cores", 999999999, 500.0, e_items::AI_CORES}				//41
	,	{"Mechanical parts", 1000, 20.0, e_items::MECH_PARTS}			//42
	,	{"Spaceship mechanical parts", 20000, 200.0, e_items::SPACESHIP_MECH_PARTS}	//43
	,	{"Junk", 10, 10.0, e_items::JUNK}
	,	{"Ultimate weight Unit", 50, -50.0, e_items::UWU}		//44
	,	{"Food", 20, 1.0, e_items::FOOD}						//45
	,	{"Water", 1, 1.0, e_items::WATER}						//46
	,	{"Fuel", 2, 1.0, e_items::FUEL}						//47
	,	{"Oil", 1, 4.0, e_items::OIL}		//48
	,	{"Sand", 1, 200.0, e_items::SAND}
	,	{"Quartz", 2, 40.0, e_items::QUARTZ}
	,	{"Diamond", 5000, 1.0, e_items::DIAMOND}
	,	{"Glass", 50, 50.0, e_items::GLASS}
	,	{"Common pottery", 5, 5.0, e_items::COMMON_POTTERY}
	,	{"Exotic pottery", 500, 5.0, e_items::EXOTIC_POTTERY}
	,	{"Iron", 50, 10.0, e_items::IRON}
	,	{"Steel", 500, 10.0, e_items::STEEL}
	,	{"Gold", 2000000, 1.0, e_items::GOLD}
	,	{"Historical relics", 1000000, 1.0, e_items::HISTORICAL_RELICS}
	,	{"Religious relics", 500000, 1.0, e_items::RELIGIOUS_RELICS}		//highly illegal
	,	{"Paper", 1, 200.0, e_items::PAPER}
	,	{"Sugar", 5000, 1.0, e_items::SUGAR}
	,	{"Olive oil", 200, 0.5, e_items::OLIVE_OIL}
	,	{"Olives", 5000, 0.01, e_items::OLIVES}
	,	{"Sugar cane", 5, 1.0, e_items::SUGAR_CANE}
	,	{"Wooden planks", 2, 1.0, e_items::WOODEN_PLANKS}
	,	{"Tree trunks", 5, 300.0, e_items::TREE_TRUNKS}
	,	{"Tree sapling", 900, 0.2, e_items::TREE_SAPLING}
	,	{"Ice", 1, 10.0, e_items::ICE}
	,	{"Honey", 2500, 0.5, e_items::HONEY}
	,	{"Milk", 3, 1.0, e_items::MILK}
	,	{"Butter", 1, 0.3, e_items::BUTTER}
	,	{"Livestock", 1000, 70.0, e_items::LIVESTOCK}
	,	{"Copper", 30, 10.0, e_items::COPPER}
	,	{"Lava", 15, 1.0, e_items::LAVA}
	,	{"Pen", 2, 0.1, e_items::PEN}
	,	{"Pencil", 1, 0.1, e_items::PENCIL}
	,	{"Bag", 5, 0.4, e_items::BAG}
	,	{"C4", 3000, 0.5, e_items::C4}
	,	{"TNT", 300, 0.5, e_items::TNT}
	,	{"Gunpowder", 10, 1.0, e_items::GUNPOWDER}
	,	{"Super gunpowder", 100, 1.0, e_items::SUPER_GUNPOWDER}
	,	{"Sweets", 15, 1.0, e_items::SWEETS}
	,	{"Cake", 20, 1.0, e_items::CAKE}
	,	{"Male clothes", 20, 0.5, e_items::MALE_CLOTHES}
	,	{"Female clothes", 200, 0.5, e_items::FEMALE_CLOTHES}
	,	{"Child clothes", 25, 0.5, e_items::CHILD_CLOTHES}
	,	{"Dirt", 1, 5.0, e_items::DIRT}
	,	{"Toxic waste", 5, 1.0, e_items::TOXIC_WASTE}
	,	{"Broken TV", 2, 20.0, e_items::BROKEN_TV}
	,	{"Broken radio", 1, 5.0, e_items::BROKEN_RADIO}
	,	{"Old couch", 100, 70.0, e_items::OLD_COUCH}
	,	{"Space whale eggs", 300, 50.0, e_items::SPACE_WHALE_EGGS}
	,	{"Space whale teeth", 5, 1.0, e_items::SPACE_WHALE_TEETH}
	,	{"Space whale skull", 500, 100.0, e_items::SPACE_WHALE_SKULL}
	,	{"Space whale bones", 100, 20.0, e_items::SPACE_WHALE_BONES}
	,	{"Bath salts", 5, 1.0, e_items::BATH_SALTS}
	,	{"Acid", 100, 1.0, e_items::ACID}
	,	{"Ice cream", 5, 1.0, e_items::ICE_CREAM}
	,	{"Empty glass bottle", 5, 10.0, e_items::EMPTY_GLASS_BOTTLE}
	,	{"Broken glass bottle", 1, 20.0, e_items::BROKEN_GLASS_BOTTLE}
	,	{"Ripped clothes", 1, 1.0, e_items::RIPPED_CLOTHES}
	,	{"Empty cans", 3, 1.0, e_items::EMPTY_CANS}
	,	{"Plastic bottles", 1, 1.0, e_items::PLASTIC_BOTTLES}
	,	{"Pillows", 4, 1.0, e_items::PILLOWS}
	,	{"Mattress", 1000, 30.0, e_items::MATTRESS}
	,	{"Energy drinks", 3, 1.0, e_items::ENERGY_DRINKS}
	,	{"Stomach acid", 25, 0.1, e_items::STOMACH_ACID}
	,	{"Emeralds", 100, 0.1, e_items::EMERALDS}
	,	{"Rubys", 30, 0.1, e_items::RUBYS}
	,	{"Cigars", 20, 0.2, e_items::CIGARS}
	,	{"Cigarettes", 10, 0.2, e_items::CIGARRETES}
	,	{"Batteries", 5, 0.1, e_items::BATTERIES}
	,	{"Napkins", 1, 0.5, e_items::NAPKINS}
	,	{"Gloves", 5, 0.6, e_items::GLOVES}
	,	{"Hammers", 10, 1.0, e_items::HAMMERS}
	,	{"Work glasses", 20, 0.2, e_items::WORK_GLASSES}
	,	{"Glasses", 300, 0.1, e_items::GLASSES}
	,	{"Sunglasses", 20, 0.1, e_items::SUNGLASSES}
	,	{"Hat", 3, 0.15, e_items::HAT}
	,	{"Helmet", 10, 0.7, e_items::HELMET}
	,	{"Police uniform", 500, 1.0, e_items::POLICE_UNIFORM}
	,	{"Military uniform", 750, 1.0, e_items::MILITARY_UNIFORM}
	,	{"Police ID", 20000, 0.2, e_items::POLICE_ID}
	,	{"Military ID", 50000, 0.2, e_items::MILITARY_ID}
	,	{"Underwear", 5, 0.5, e_items::UNDERWEAR}
	,	{"Blankets", 10, 1.0, e_items::BLANKETS}
	,	{"Real fake doors", 500, 50.0, e_items::REAL_FAKE_DOORS}
	,	{"Wooden doors", 300, 50.0, e_items::WOODEN_DOORS}
	,	{"Metal doors", 600, 100.0, e_items::METAL_DOORS}
	,	{"Houses", 600000, 80000.0, e_items::HOUSES}
	,	{"Trees", 1500, 10000.0, e_items::TREES}
	,	{"Goat milk", 4, 1.0, e_items::GOAT_MILK}
	,	{"Onions", 3, 2.0, e_items::ONIONS}
	,	{"Tomatoes", 3, 1.0, e_items::TOMATOES}
	,	{"Potatos", 5, 2.0, e_items::POTATOS}
	,	{"Carrots", 1, 2.0, e_items::CARROTS}
	,	{"Beans", 2, 1.0, e_items::BEANS}
	,	{"Bread", 5, 2.0, e_items::BREAD}
	,	{"Corn", 1, 2.2, e_items::CORN}
	,	{"Flour", 1, 2.0, e_items::FLOUR}
	,	{"Oranges", 4, 1.0, e_items::ORANGES}
	,	{"Orange juice", 5, 1.0, e_items::ORANGE_JUICE}
	,	{"Cucumbers", 2, 1.0, e_items::CUCUMBERS}
	,	{"Pickles", 15, 3.0, e_items::PICKLES}
	,	{"Paprika", 20, 1.5, e_items::PAPRIKA}
	,	{"Thousand islands sauce", 3, 1.0, e_items::THOUSAND_ISLANDS_SAUCE}
	,	{"Mustard", 1, 0.591, e_items::MUSTARD}
	,	{"Ketchup", 4, 1, e_items::KETCHUP}
	,	{"Grapes", 5, 2.0, e_items::GRAPES}
	,	{"Live lobster", 130, 3.0, e_items::LIVE_LOBSTER}
	,	{"Frozen lobster", 30, 3.0, e_items::FROZEN_LOBSTER}
	,	{"Puffer fish", 40, 10.0, e_items::PUFFER_FISH}
	,	{"Jar of jelly", 20, 1.0, e_items::JAR_OF_JELLY}
	,	{"Hotdogs", 2, 1.0, e_items::HOTDOGS}
	,	{"Pizza", 10, 1.0, e_items::PIZZA}
	,	{"Pineapple pizza", 11, 1.0, e_items::PINEAPPLE_PIZZA}
	,	{"Sushi", 20, 1.0, e_items::SUSHI}
	,	{"Mayo", 8, 1.0, e_items::MAYO}
	,	{"Eggs", 3, 1.0, e_items::EGGS}
	,	{"Raw meat", 5, 1.0, e_items::RAW_MEAT}
	,	{"Cooked meat", 10, 1.0, e_items::COOKED_MEAT}
	,	{"Shampoo", 10, 1.0, e_items::SHAMPOO}
	,	{"Wrench set", 110, 3.5, e_items::WRENCH}
	,	{"Crowbar", 30, 3.0, e_items::CROWBAR}
	,	{"Grenades", 300, 10.0, e_items::GRENADES}
	,	{"EMP grenades", 300000, 1.0, e_items::EMP_GRENADES}
	,	{"Nuclear warhead", 300000000, 500.0, e_items::NUCLEAR_WARHEADS}
};
