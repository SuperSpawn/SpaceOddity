#pragma once
//#include "olcPixelGameEngine.h"
//#include "pstates.h"
//#include "tradesystem.h"
//#include "director.h"
#define NUMBER_OF_STARS_BACKGROUND 1000
#define DTICK_RATE 2
#define GENERATE_CHUNCK_DIST 5

#define SUBMODE_SLEEP_TIME 10
#define STARTING_PLAYER_MONEY 50000
#define START_FUEL_AMOUNT 30000
#define STATIC_CONSUMPTION_RATE 1
#define STATIC_CONSUMPTION_START 10
#define UPDATE_CONSUMPTION_THRESH 2
#define MOVE_CONSUMPTION_MULTIPLIER 1
#define STATIC_FOOD_CONSUMPTION_RATE 1
#define STATIC_WATER_CONSUMPTION_RATE 1

#define SYSTEM_MOUSE_DEAD_RANGE 50;
#define NUMBER_OF_SHIP_ARMS 3

#define SPLIT_HEIGHT_SUBMOD_FACTOR 8
#define X_OFFSET_SUBMOD_BOX 0

#define __cpp_concepts
#define OLC_PGEX_SOUND
#define OLC_PGEX_GRAPHICS2D
//#define OLC_PGEX_GFX2D
#define OLC_PGEX_POPUPMENU
#define OLC_PGEX_TRANSFORMEDVIEW
#define OLC_PGEX_RAYCASTWORLD

#include "olcPGEX_Graphics2D.h"
#include "olcPGEX_Sound.h"
//#include "starsystem.h"
#include "olcPGEX_PopUpMenu.h"
#include "olcPGEX_TransformedView.h"
#include "olcPGEX_RayCastWorld.h"
#include "director.h"
#include <thread>

long mem = 0;

std::list<void*> helpinghand;

spaceoddity* globalGame;//I'm so sorry

class cSpaceStation
{
public:
	bool stationExists;
	uint32_t occupation;
	std::list<slot> sImport, sExport;

	cSpaceStation(uint32_t x, uint32_t y, int bGenerateFull = 0)
	{
		




	}
};


namespace pspace
{
	typedef enum
	{
		MAIN_MENU = 0
		, PAUSE
		, SPACE_OVERLOOK		//Main game in space
		, SPACESHIP_INSIDE		//inside spaceship
		, STAR_SYSTEM_OVERLOOK	//inside a star system
		, PLANET_OVERLOOK		//over planet
		, CINEMATIC
		, EDITOR
		, STORE_INTERFACE
		, COMBAT_MODE
		, GAME_OVER
		, CITY_INSIDE
	} gamestates;

	enum substates
	{
		SUBTYPE_NULL = 0
		, MUSIC, DISPLAY_QUEST, DISPLAY_ITEM, DISPLAY_MONEY, DISPLAY_DISEASE
		, NUMBER_OF_SUBSTATES
		, DISPLAY_JOBS
	};

	struct t_time
	{
		double offset;
		uint32_t unit;
	};
}

class raycastv : public olc::rcw::Engine
{
	olc::vi2d mdim;
	int pic = 0;
	int* arr;

public:
	float pspeed = 6.0f;

	friend class spaceoddity;

	void setMap(const string& nmap)
	{
		return;
	}

	raycastv(const int screen_w, const int screen_h, const float fov)
		: olc::rcw::Engine(screen_w, screen_h, fov)
	{
		int i;
		mdim.x = 64;
		mdim.y = 17;
		arr = new int[mdim.x * mdim.y];
		if (arr == nullptr)
			return;
		for (i = 0; i < mdim.x * mdim.y; ++i)
			arr[i] = 0;


		//nn.Load("C:\\Users\\aafaq\\Desktop\\spaceoddityassets\\spaceoddity pictures\\karma2.png");
	}

	~raycastv()
	{
		delete[] arr;
	}

	// ABSTRACT - User must return a suitable olc::Pixel depending on world location information provided
	virtual olc::Pixel SelectSceneryPixel(const int tile_x, const int tile_y, const olc::rcw::Engine::CellSide side, const float sample_x, const float sample_y, const float distance);
	// ABSTRACT - User must return a boolean indicating if the tile is solid or not
	virtual bool IsLocationSolid(const float tile_x, const float tile_y);
	// ABSTRACT - User must return sizes of requested objects in Unit Cell Size
	virtual float GetObjectWidth(const uint32_t id)
	{
		return 1.0f;
	}
	virtual float GetObjectHeight(const uint32_t id)
	{
		return 1.0f;
	}

	// ABSTRACT - User must return suitable olc::Pixel for object sprite sample location
	virtual olc::Pixel SelectObjectPixel(const uint32_t id, const float sample_x, const float sample_y, const float distance, const float angle)
	{
		olc::Pixel p = olc::MAGENTA;
		return p;
	}

	// OPTIONAL - User can handle collsiion response with scenery should they choose to
	//virtual void HandleObjectVsScenery(std::shared_ptr<olc::rcw::Object> object, const int tile_x, const int tile_y, const olc::rcw::Engine::CellSide side, const float offset_x, const float offset_y);

	// OPTIONAL - User can handle collsiion response with objects should they choose to
	//virtual void HandleObjectVsObject(std::shared_ptr<olc::rcw::Object> object1, std::shared_ptr<olc::rcw::Object> object2);



};
class supermenu : public olc::popup::Menu
{
	int index;


public:



};

std::vector<string> renderables_address =
{
	"NULL", "whale.png", "whale2.png", "whale3.png", "city.png"
};


class test_file_stuff : public olc::PixelGameEngine
{
	olc::Renderable city;
	olc::Pixel color;

public:
	bool OnUserCreate() override
	{
		//spr = new olc::Sprite("game_assets\\spaceoddity pictures\\stone.png");
		city.Load("game_assets\\assets\\city.png");
		olc::vi2d runner;
		for (runner.x = 0; runner.x < city.Sprite()->width; runner.x++)
		{
			for (runner.y = 0; runner.y < city.Sprite()->height; runner.y++)
			{
				if (city.Sprite()->GetPixel(runner) == olc::WHITE)
					city.Sprite()->SetPixel(runner, olc::BLANK);
			}
		}
		

		color = olc::DARK_BLUE;

		return true;
	}

	bool OnUserUpdate(float fElapsedTime) override
	{
		Clear(color);
		SetPixelMode(olc::Pixel::ALPHA);
		DrawSprite(0, 0, city.Sprite());
		SetPixelMode(olc::Pixel::NORMAL);

		if (GetKey(olc::Key::ESCAPE).bPressed)
			return false;

		return true;
	}
	
};

class start_cinematic
{

public:
	olc::vf2d size;
	olc::Renderable spr;
	olc::vf2d cor[4];
	float speed;
	bool pause;
	float time;

	bool OnUserCreate(int screen_width, int screen_height)
	{
		size = { 915.0f, 0.0f };
		spr.Load("game_assets\\assets\\text1.png");
		cout << olc::SOUND::LoadAudioSample("game_assets\\music\\starwars.wav");
		olc::SOUND::PlaySample(1);
		pause = false;
		//olc::SOUND::PlaySample(i);
		cor[0].y = 0.0f;
		cor[0].x = (screen_width / 4);
		cor[1].y = screen_height;
		cor[1].x = 0.0f;
		cor[2].y = screen_height;
		cor[2].x = screen_width;
		cor[3].y = 0.0f;
		cor[3].x = (screen_width / 2) + (screen_width / 4);

		speed = 7.0f;
		time = 90.0f;

		return true;
	}

};

class wind
{
public:

	bool bKill;
	bool bHide;
	int** blocks;
	uint32_t blockSize;
	olc::vi2d size;
	olc::vi2d orig;
	olc::vi2d scaled;
	
	olc::Sprite* spr;
	
	std::vector<dfunc> util;
	

	//tag the window to be killed
	dfunc& killUtil()
	{
		dfunc ret;
		ret.args = (void**)&(*this);
		ret.color = -1;
		ret.argnum = 1;
		ret.func = [](int k, void** args)
		{
			wind* thee = (wind*)args;
			if (thee)
				thee->bKill = true;
			return (void*)nullptr;
		};
		return ret;
	}

	//also used for draw functions
	static dfunc& constUtil(void* var)	
	{
		dfunc ret;
		ret.argnum = 1;
		ret.args = (void**)var;
		ret.color = -1;
		ret.func = NULL;
		return ret;
	}
	
		
	static dfunc& dynamicUtil(uint32_t _size, uint32_t _color = 0)
	{
		dfunc ret;
		ret.argnum = _size;
		ret.color = _color;
		ret.func = NULL;
		ret.args = new void* [_size];
		if (ret.args == NULL)
		{
			ret.color = -1;
		}
		return ret;
	}
	void click(const olc::vi2d& mouse)
	{
		olc::vi2d k = mouse - orig;
		if ((k.x < 0) || (k.y < 0))
			return;
		if ((k.x > size.x) || (k.y > size.y))
			return;
		int val;
		val = blocks[k.y][k.x];
		if (val == -1)
			return;
		util.at(val).activate();
		return;
	}

	friend class makeWind;

	wind(olc::vi2d _size, uint32_t bsize)
	{
		blockSize = bsize;
		size = _size;
		scaled.x = _size.x / bsize;
		scaled.y = _size.y / bsize;
		orig = { 0,0 };
		bKill = false;
		bHide = false;
		spr = new olc::Sprite(_size.x, _size.y);
		blocks = NULL;
		if (spr == NULL)
		{
			bKill = true;
		}


		
		//util.push_back(killUtil());
	}

	

	~wind()
	{
		uint32_t i;
		util.clear();
		for (i = 0; i < scaled.y; ++i)
			delete[] blocks[i];
		delete[] blocks;
		delete spr;
	}
};

class makeWind : public olc::PixelGameEngine
{

	void fill(uint32_t x, uint32_t y)
	{
		arr[y][x] = mode;
		if (arr[y][x + 1] != mode)
			fill(x + 1, y);
		if (arr[y][x - 1] != mode)
			fill(x - 1, y);
		if (arr[y + 1][x] != mode)
			fill(x, y + 1);
		if (arr[y + 1][x + 1] != mode)
			fill(x + 1, y + 1);
		if (arr[y + 1][x - 1] != mode)
			fill(x - 1, y + 1);
		if (arr[y - 1][x] != mode)
			fill(x, y - 1);
		if (arr[y - 1][x + 1] != mode)
			fill(x + 1, y - 1);
		if (arr[y - 1][x - 1] != mode)
			fill(x - 1, y - 1);
	}

public:
	
	int mode;
	int blockSize;
	olc::vi2d actual;

	int** arr;

	olc::vi2d mouse;
	olc::vi2d scaled;
	olc::vi2d bmouse;
	olc::Renderable spr;
	olc::vf2d cor[4];

	makeWind(string add, uint32_t bsize, uint32_t scale = 1)
	{
		blockSize = bsize;
		mode = 0;
		spr.Load(add);
		actual = { spr.Sprite()->width, spr.Sprite()->height};
		arr = NULL;
		if (Construct(actual.x, actual.y,
			scale, scale, false, false, false))
			Start();
	}

	bool setSprite(string address)
	{
		spr.Load(address);
		actual = { spr.Sprite()->width, spr.Sprite()->height};
		return true;
	}

	makeWind(int _bSize, olc::vi2d _act)
	{
		mode = 0;
		blockSize = _bSize;
		actual = _act;
		arr = NULL;
	}

	~makeWind()
	{
		uint32_t i;
		for (i = 0; i < scaled.y; ++i)
			delete[] arr[i];
		delete[] arr;
	}

	wind& saveAs(olc::vi2d _size)
	{
		int i;
		wind ret(_size, blockSize);
		ret.blocks = new int* [scaled.y];
		if (ret.blocks == NULL)
		{
			ret.bKill = true;
			return ret;
		}
		for (i = 0; i < scaled.y; ++i)
		{
			int j;
			ret.blocks[i] = new int[scaled.x];
			if (ret.blocks[i] == NULL)
			{
				for (j = 0; j < i; ++j)
					delete[] ret.blocks[j];
				delete[] ret.blocks;
				ret.bKill = true;
				return ret;
			}
			for (j = 0; j < scaled.x; ++j)
				ret.blocks[i][j] = arr[i][j];
		}
		
		return ret;
	}

	bool OnUserCreate() override
	{
		
		int i, j;
		scaled = { ScreenWidth() / blockSize,ScreenHeight() / blockSize };
		arr = new int*[scaled.y];
		if (arr == NULL)
			return false;
		for (i = 0; i < scaled.y; ++i)
		{
			arr[i] = new int[scaled.x];
			if (arr[i] == NULL)
			{
				for (j = 0; j < i; ++j)
					delete[] arr[j];
				delete[] arr;
				return false;
			}
			for (j = 0; j < scaled.x; ++j)
				arr[i][j] = -1;
		}

		cor[0].x = 0.0f;
		cor[0].y = 0.0f;
		cor[1].x = 0.0f;
		cor[1].y = ScreenHeight();
		cor[2].x = ScreenWidth();
		cor[2].y = ScreenHeight();
		cor[3].x = ScreenWidth();
		cor[3].y = 0.0f;



		return true;
	}
	bool OnUserUpdate(float fElapsedTime) override
	{
		int i, j;

		
		Clear(olc::WHITE);
		DrawSprite({ 0,0 }, spr.Sprite());
		

		
		mouse = GetMousePos();
		bmouse = { mouse.x / blockSize, mouse.y / blockSize };

		if (GetKey(olc::ESCAPE).bPressed)
			return false;
		if (GetKey(olc::UP).bPressed)
			++mode;
		if (GetKey(olc::DOWN).bPressed)
			--mode;
		if (GetMouse(0).bHeld)
		{
			arr[bmouse.y][bmouse.x] = mode;
		}
		if (GetMouse(1).bHeld)
		{
			arr[bmouse.y][bmouse.x] = -1;
		}

		if (GetMouse(0).bPressed && GetKey(olc::SHIFT).bHeld)
		{
			fill(bmouse.x, bmouse.y);
		}



		for (j = 0; j < scaled.y; ++j)
		{
			for (i = 0; i < scaled.x; ++i)
			{
				if (arr[j][i] == mode)
					FillRect({ i * blockSize, j * blockSize }, { blockSize, blockSize }, olc::YELLOW);
				
			}
		}

		return true;
	}

};


class spaceoddity : public olc::PixelGameEngine
{
	bool UpdateMainMenu(float fElapsedTime);
	bool UpdateSpace(float fElapsedTime);
	bool UpdateStarSystem(float fElapsedTime);
	bool UpdatePlanet(float fElapsedTime);
	bool UpdateCinematic(float fElapsedTime);
	bool UpdateEditor(float fElapsedTime);
	bool UpdateSpaceship(float fElapsedTime);
	bool UpdateStoreInterface(float fElapsedTime);
	bool UpdateCombat(float fElapsedTime);
	bool UpdateGameOver(float fElapsedTime);
	bool UpdateCityInside(float fElapsedTime);
	
	bool UpdateCityWelcome(float fElapsedTime);
	bool UpdateCityInventory(float fElapsedTime);
	bool UpdateCityBarter(float fElapsedTime);
	bool UpdateCityPeople(float fElapsedTime);
	bool UpdateCityQuest(float fElapsedTime);

	void drawPlayer(float fElapsedTime, int tick)
	{
		/*
	FillTriangle(
		(player->_sides[0].x * _scale) - (vGalaxyOffset.x * SIZE_OF_BLOCK * _scale),
		(player->_sides[0].y * _scale) - (vGalaxyOffset.y * SIZE_OF_BLOCK * _scale),
		(player->_sides[1].x * _scale) - (vGalaxyOffset.x * SIZE_OF_BLOCK * _scale),
		(player->_sides[1].y * _scale) - (vGalaxyOffset.y * SIZE_OF_BLOCK * _scale),
		(player->_sides[2].x * _scale) - (vGalaxyOffset.x * SIZE_OF_BLOCK * _scale),
		(player->_sides[2].y * _scale) - (vGalaxyOffset.y * SIZE_OF_BLOCK * _scale), olc::GREEN);
	*/
	//DrawSprite(player->x, player->y, sprites.front());
	/*
	olc::vi2d corner[3];

	corner[0] = camera.WorldToScreen({ player->x + player->_sides[0].x, player->y + player->_sides[0].y });
	corner[1] = camera.WorldToScreen({ player->x + player->_sides[1].x, player->y + player->_sides[1].y });
	corner[2] = camera.WorldToScreen({ player->x + player->_sides[2].x, player->y + player->_sides[2].y });

	FillTriangle(corner[0], corner[1], corner[2], olc::GREEN);
	*/

	//SetPixelMode(olc::Pixel::Mode::ALPHA);
	//
	//olc::vi2d pos;
	//decimal k = player->updateState(fElapsedTime);
	//cord2< olc::vi2d> in = ssprites[k].state;
	//k = ssprites[k].spriteID;
	//pos = camera.WorldToScreen({ player->cord.x, player->cord.y });
	//DrawPartialSprite(pos, sprites.at(k), in.x, in.y, 1);
	//
	//SetPixelMode(olc::Pixel::Mode::NORMAL);

		//camera.FillCircle(camera.ScreenToWorld({ ScreenWidth() >> 1, ScreenHeight() >> 1 }), 10.0f, olc::GREEN);
		//olc::vf2d co = camera.ScreenToWorld({ ScreenWidth() >> 1, ScreenHeight() >> 1 });
		FillTriangle(
			player->cord.x + player->_sides[0].x, player->cord.y + player->_sides[0].y,
			player->cord.x + player->_sides[1].x, player->cord.y + player->_sides[1].y,
			player->cord.x + player->_sides[2].x, player->cord.y + player->_sides[2].y, olc::GREEN);
	}

	void generateSystem();
	bool generateNewGame();

	olc::popup::Manager manage;
	olc::popup::Menu mainMenu;

	raycastv* inter;

	bool space_grid;
	decimal player_level;
public:
	int gamestate;
	olc::vi2d vStarSelected;

	cStarSystem* current_lookedStar;

	bool pause = false;
	bool _move = true;
	unsigned int beat;

	int enemy_type;

	olc::TransformedView camera;

	olc::vf2d prev;

	spaceship* player;
	director _dir;

	

	bool bHolding_window;
	std::list<swindow*> windowList;
	std::vector<pspace::projectile> proj_list;

	
	std::list<pspace::space_object*> space_objects;
	std::list<pspace::space_object*>::iterator objects_itr;
	std::list<enemy*> enemy_list;


	array<f2, NUMBER_OF_STARS_BACKGROUND> _star;//array of stars
	float starScroll;

	int picture;
	int music;

	float _scale;
	float orbit_offset;

	
	//moves stars
	void shiftStars(float sx, float sy);
	
	std::vector<olc::Renderable*> renderables;

	olc::vf2d outside_cord;

	decimal balance;
	olc::vi2d _mouse;
	olc::vi2d selected_slot;

	int planetType;
	int slot_number;

	string amount;
	int amount_slot, iamount_slot;
	std::array<slot, e_items::NUMBER_OF_ITEMS> inventory;
	std::array<slot, e_items::NUMBER_OF_ITEMS>::iterator istart_slot, icurr_slot, inv_itm;
	std::vector<merchant>::iterator currentMerch;
	std::vector<slot>::iterator curr_slot, start_slot;
	//end of store interface stuff

	//star system stuff
	int selectedPlanet;
	//end of star system stuff

	//submode stuff
	struct substate_stuff
	{
		int music_index = 0, currently_playing_track_id = -1;
		std::vector<string> music_address;
		bool bStopped = false;
		std::array<pspace::disease, pspace::special_diseases::NUMBER_OF_DISEASES>::iterator ills_itr;
		
		int jobs_seed;

		substate_stuff()
		{
			jobs_seed = 0;
			music_address.push_back("...");
			music_address.push_back("Daddy Cool");
			music_address.push_back("David Bowie dancing in the street");
			music_address.push_back("David Bowie heroes");
			music_address.push_back("David Bowie lets dance");
			music_address.push_back("David Bowie life on mars");
			music_address.push_back("David Bowie spaceoddity");
			music_address.push_back("David Bowie starman");
			music_address.push_back("David Bowie Rebel Rebel");
		}

		inline const string& getmusic_add(int index)
		{
			return music_address.at(index);
		}
		inline void music_inc()
		{
			++music_index;
			music_index %= music_address.size();
		}
		inline void music_dec()
		{
			--music_index;
			if (music_index == -1)
				music_index = music_address.size() - 1;
		}

		void load_music()
		{
			if (music_index == 0)
				return;
			if (currently_playing_track_id == music_index)
			{
				if (bStopped)
				{
					olc::SOUND::PlaySample(music_index);
					bStopped = false;
				}
				else
				{
					olc::SOUND::StopSample(music_index);
					bStopped = true;
				}
				return;
			}
			if (currently_playing_track_id != -1)
			{
				olc::SOUND::StopSample(currently_playing_track_id);
				//have to delete manually to prevent leak
				delete[] olc::vecAudioSamples.back().fSample;	
				olc::vecAudioSamples.pop_back();
			}
			currently_playing_track_id =
				olc::SOUND::LoadAudioSample(MUSIC_ASSETS_FOLDER_PATH 
					+ music_address.at(music_index) + ".wav");
			olc::SOUND::PlaySample(currently_playing_track_id);
		}

		const string& get_current_track_name()
		{
			return music_address.at(music_index);
		}
	};

	int submode;
	double substate_time;
	substate_stuff submode_struct;
	//std::vector<olc::SOUND::AudioSample> vecAudioSamples;

	//end of submode stuff

	bool loadSprites();
	bool unloadSprites();
	bool loadSounds();

	double star_syst_local_offset;

	void updateScreen(float fElapsedTime);

	void execute_event(decimal id);

	timedevice timer;

	//money
	superint offshore_balance;
	//end of money

	start_cinematic cinematicStart;

	//combat mode stuff
	olc::vf2d combat_cord;
	//end of combat stuff

	//backup stuff
	float backup_lookAngle;
	float backup_movementAngle;
	//end of backup stuff

	//fuel
	decimal spaceFuel;
	int static_fuel_consumption;
	double static_consumptionOff;
	double move_consumption;
	bool engine_dead;
	//end of fuel

	//food
	decimal foodSupply;
	int static_food_consumption;
	double static_food_consumptionOff;
	//end of food

	//water
	decimal waterSupply;
	int static_water_consumption;
	double static_water_consumptionOff;
	//end of water

	//diease
	std::array<pspace::disease, pspace::special_diseases::NUMBER_OF_DISEASES> ills_list;
	//end of disease

	//game over
	
	//end of game over

	//planet overlook stuff
	struct planet_overlook_stuff
	{
		byte seed;
		bool re_generate_plain, re_generate_city;
		std::vector<pspace::city> cities;
		std::vector<merchant> vendors;
		uint32_t current_merch, current_city_mode;
		
		std::list<pspace::companion> peeps;
		std::list<pspace::companion>::iterator current_peep;

		sPlanet* currentPlanet;
		pspace::city* currentCity;
		decimal seed_data;
		olc::vf2d pCurrent_pos;
		int spaceship_dir;
		olc::vi2d points[3];
		olc::vf2d ship_speed;

		double current_cargo_weight, max_cargo_weight;

		planet_overlook_stuff()
		{
			seed = 0;
			re_generate_plain = false;
			re_generate_city = false;
			currentPlanet = nullptr;
			currentCity = nullptr;
			seed_data = 0;
			pCurrent_pos = { SCREEN_WIDTH / 2.0f, SIZE_OF_BLOCK * 2.0f };
			spaceship_dir = 1;
			points[0] = { -5, -5 };
			points[1] = { -5, 5 };
			points[2] = { 10, 0 };
			ship_speed = { 0.0f, 0.0f };
			current_merch = 0; current_city_mode = 0;
			max_cargo_weight = 1000.0;
			current_cargo_weight = 0.0;
		}
	};
	
	planet_overlook_stuff planet_over;
	//end of planet overlook stuff

	//weapon ammo
	//end of weapon ammo

//public:

	decimal minute_time;
	float second_time;

	void freeMem();


	spaceoddity();
	~spaceoddity();


	enum sound_files
	{
		STAR_WARS_INTRO = 0
		, SPACE_MUSIC1
		, SPACE_MUSIC2
		, SPACE_MUSIC3
		, SPACE_BROADCAST1
		, SPACE_BROADCAST2
		, SPACE_BROADCAST3
		, SPACE_BROADCAST4
		, SPACE_BROADCAST5
		, SPACE_BROADCAST6
		, SPACE_BROADCAST7
		, SPACE_BROADCAST8
		, SPACE_BROADCAST9
		, SPACE_BROADCAST10
		, SPACE_BROADCAST11
		, SPACE_BROADCAST12
		, SPACE_BROADCAST13
		, SPACE_BROADCAST14
		, SPACE_BROADCAST15
		, SPACE_BROADCAST16
		, SPACE_BROADCAST17
		, SPACE_BROADCAST18
		, SYNDICATE_ZONE
		, WHALES_DETECTED1
		, WHALES_DETECTED2
		, SIGNAL_DETECTED
		, LASER_SOUND1
		, LASER_SOUND2
		, LASER_BURST1
		, CUSTOM_LOADED_SOUND1
		, NUMBER_OF_SOUND_FILES
	};

	void re_evaluate_inv()
	{
		auto inv_itr = inventory.begin();
		for (; inv_itr != inventory.end(); ++inv_itr)
		{
			if (inv_itr->amount != 0)
			{
				istart_slot = icurr_slot = inv_itr;
				return;
			}
		}
		return;
	}
	void use_current_item(uint32_t amount)
	{
		switch (inv_itm->type.id)
		{
		case e_items::WATER:
			waterSupply += amount;
			ills_list.at(pspace::special_diseases::DISEASE_THIRST).bActive = false;
			break;
		case e_items::FOOD:
			foodSupply += amount;
			ills_list.at(pspace::special_diseases::DISEASE_STARVE).bActive = false;
			break;
		case e_items::FUEL:
			spaceFuel += amount;
			engine_dead = false;
			break;
		default:
			return;
		}

		inv_itm->amount -= amount;
	}

	void update_music_substate(float fElapsedTime)
	{
		substate_time -= fElapsedTime;
		if (substate_time <= 0.0)
		{
			substate_time = 0.0;
			submode = pspace::substates::SUBTYPE_NULL;
			return;
		}

		if (GetKey(olc::Key::RIGHT).bPressed)
		{
			substate_time = SUBMODE_SLEEP_TIME;
			submode_struct.music_inc();
		}
		if (GetKey(olc::Key::LEFT).bPressed)
		{
			substate_time = SUBMODE_SLEEP_TIME;
			submode_struct.music_dec();
		}

		if (GetKey(olc::Key::SPACE).bPressed)
		{
			substate_time = SUBMODE_SLEEP_TIME;
			submode_struct.load_music();
		}
	}
	void update_disaease_substate(float fElapsedTime)
	{
		substate_time -= fElapsedTime;
		if (substate_time <= 0.0)
		{
			substate_time = 0.0;
			submode = pspace::substates::SUBTYPE_NULL;
			return;
		}
	}
	void update_display_quest_substate(float fElapsedTime)
	{
		substate_time -= fElapsedTime;
		if (substate_time <= 0.0)
		{
			substate_time = 0.0;
			submode = pspace::substates::SUBTYPE_NULL;
			return;
		}

		if (_dir.quests.empty() == false)
		{
			if (GetKey(olc::Key::RIGHT).bPressed)
			{
				substate_time = SUBMODE_SLEEP_TIME;
				if(_dir.current_quest != _dir.quests.end())
					++_dir.current_quest;
			}
			else if (GetKey(olc::Key::LEFT).bPressed)
			{
				substate_time = SUBMODE_SLEEP_TIME;
				if (_dir.current_quest != _dir.quests.begin())
					--_dir.current_quest;
			}
		}


	}
	void update_display_item_substate(float fElapsedTime)
	{
		
		substate_time -= fElapsedTime;
		if (substate_time <= 0.0)
		{
			substate_time = 0.0;
			submode = pspace::substates::SUBTYPE_NULL;
			return;
		}
		if (GetKey(olc::Key::RIGHT).bPressed)
		{
			substate_time = SUBMODE_SLEEP_TIME;
			while (inv_itm != inventory.end())
			{
				if (inv_itm->amount != 0)
					break;
				++inv_itm;
			}
		}
		else if (GetKey(olc::Key::LEFT).bPressed)
		{
			substate_time = SUBMODE_SLEEP_TIME;
			while (inv_itm != inventory.begin())
			{
				if (inv_itm->amount != 0)
					break;
				--inv_itm;
			}
		}

		if (GetKey(olc::Key::SPACE).bPressed)
		{
			substate_time = SUBMODE_SLEEP_TIME;
			if (GetKey(olc::Key::TAB).bHeld)				//use 1000
			{
				if (inv_itm->amount < 1000)
					return;
				use_current_item(1000);
			}
			else if (GetKey(olc::Key::SHIFT).bHeld)			//use 100
			{
				if (inv_itm->amount < 100)
					return;
				use_current_item(100);
			}
			else if (GetKey(olc::Key::CTRL).bHeld)		//use 10
			{
				if (inv_itm->amount < 10)
					return;
				use_current_item(10);
			}
			else			//use 1
			{
				if (inv_itm->amount == 0)
					return;
				use_current_item(1);
			}

		}
	}
	void update_display_money_substate(float fElapsedTime)
	{
		substate_time -= fElapsedTime;
		if (substate_time <= 0.0)
		{
			substate_time = 0.0;
			submode = pspace::substates::SUBTYPE_NULL;
			return;
		}

		if (GetKey(olc::Key::UP).bPressed)
		{
			if (balance > 50000)
			{
				balance -= 50000;
				offshore_balance.inc();
			}
		}
		if (GetKey(olc::Key::DOWN).bPressed)
		{
			if (offshore_balance.bZero == false)
			{
				balance += 50000;
				offshore_balance.dec();
			}
		}

	}
	void update_display_jobs_substate(float fElapsedTime)
	{
		if (GetKey(olc::Key::RIGHT).bPressed)
		{
			cout << "Next quest" << endl;
			_dir.quests.pop_back();
			submode_struct.jobs_seed++;
			nLehmer64 = submode_struct.jobs_seed;
			nLehmer128 = submode_struct.jobs_seed;	nLehmer128 <<= 64; nLehmer128 += submode_struct.jobs_seed;
			nLehmer128 += Lehmer64();
			_dir.generate_quest(player_level);
		}
		else if (GetKey(olc::Key::LEFT).bPressed)
		{
			cout << "Prev quest" << endl;
			_dir.quests.pop_back();
			submode_struct.jobs_seed--;
			nLehmer64 = submode_struct.jobs_seed;
			nLehmer128 = submode_struct.jobs_seed;	nLehmer128 <<= 64; nLehmer128 += submode_struct.jobs_seed;
			nLehmer128 += Lehmer64();
			_dir.generate_quest(player_level);
		}

		if (GetKey(olc::Key::SPACE).bPressed)
		{
			submode = pspace::substates::SUBTYPE_NULL;
			_dir.quests.back().bFreeze = false;
		}
	}

	void render_music_substate(float fElapsedTime)
	{
		uint32_t box_height = SCREEN_HEIGHT / SPLIT_HEIGHT_SUBMOD_FACTOR;
		uint32_t tile_width = SCREEN_WIDTH / SPLIT_HEIGHT_SUBMOD_FACTOR;
		box_height = SCREEN_HEIGHT - box_height;
		FillRect(X_OFFSET_SUBMOD_BOX, box_height, SCREEN_WIDTH - X_OFFSET_SUBMOD_BOX, box_height, olc::BLACK);
		DrawRect(X_OFFSET_SUBMOD_BOX, box_height, SCREEN_WIDTH - X_OFFSET_SUBMOD_BOX, box_height);
		DrawString(X_OFFSET_SUBMOD_BOX, box_height, "<", olc::WHITE, SPLIT_HEIGHT_SUBMOD_FACTOR);
		DrawString(X_OFFSET_SUBMOD_BOX + tile_width, box_height, submode_struct.get_current_track_name(), olc::WHITE, 2);
		DrawString(SCREEN_WIDTH - X_OFFSET_SUBMOD_BOX - tile_width, box_height, ">", olc::WHITE, SPLIT_HEIGHT_SUBMOD_FACTOR);
	}
	void render_disease_substate(float fElapsedTime)
	{

	}
	void render_display_quest_substate(float fElapsedTime)
	{
		if (_dir.quests.empty() || _dir.current_quest == _dir.quests.end())
			return;
		string sContent = "";
		sContent += "Objective: Deliver " + to_string(_dir.current_quest->amount) + " "
			+ types[_dir.current_quest->desired_item].name + "\n";
		sContent += "X - " + to_string(_dir.current_quest->target_chunk.x) + "\n";
		sContent += "Y - " + to_string(_dir.current_quest->target_chunk.y) + "\n";
		sContent += "Remaining time: " +
			to_string(_dir.current_quest->minute_time) + ":" + to_string(_dir.current_quest->second_time);

		uint32_t box_height = SCREEN_HEIGHT / SPLIT_HEIGHT_SUBMOD_FACTOR;
		uint32_t tile_width = SCREEN_WIDTH / SPLIT_HEIGHT_SUBMOD_FACTOR;
		box_height = SCREEN_HEIGHT - box_height;
		FillRect(X_OFFSET_SUBMOD_BOX, box_height, SCREEN_WIDTH - X_OFFSET_SUBMOD_BOX, box_height, olc::BLACK);
		DrawRect(X_OFFSET_SUBMOD_BOX, box_height, SCREEN_WIDTH - X_OFFSET_SUBMOD_BOX, box_height);
		DrawString(X_OFFSET_SUBMOD_BOX, box_height, "<", olc::WHITE, SPLIT_HEIGHT_SUBMOD_FACTOR);
		DrawString(X_OFFSET_SUBMOD_BOX + tile_width, box_height, sContent, olc::WHITE, 2);
		DrawString(SCREEN_WIDTH - X_OFFSET_SUBMOD_BOX - tile_width, box_height, ">", olc::WHITE, SPLIT_HEIGHT_SUBMOD_FACTOR);
	}
	void render_display_item_substate(float fElapsedTime)
	{
		if (inv_itm == inventory.end())
			return;
		uint32_t box_height = SCREEN_HEIGHT / SPLIT_HEIGHT_SUBMOD_FACTOR;
		uint32_t tile_width = SCREEN_WIDTH / SPLIT_HEIGHT_SUBMOD_FACTOR;
		box_height = SCREEN_HEIGHT - box_height;
		FillRect(X_OFFSET_SUBMOD_BOX, box_height, SCREEN_WIDTH - X_OFFSET_SUBMOD_BOX, box_height, olc::BLACK);
		DrawRect(X_OFFSET_SUBMOD_BOX, box_height, SCREEN_WIDTH - X_OFFSET_SUBMOD_BOX, box_height);
		DrawString(X_OFFSET_SUBMOD_BOX, box_height, "<", olc::WHITE, SPLIT_HEIGHT_SUBMOD_FACTOR);
		DrawString(X_OFFSET_SUBMOD_BOX + tile_width, box_height, inv_itm->type.name + "\n" + to_string(inv_itm->amount), olc::WHITE, 2);
		DrawString(SCREEN_WIDTH - X_OFFSET_SUBMOD_BOX - tile_width, box_height, ">", olc::WHITE, SPLIT_HEIGHT_SUBMOD_FACTOR);
	}
	void render_display_money_substate(float fElapsedTime)
	{
		uint32_t box_height = SCREEN_HEIGHT / SPLIT_HEIGHT_SUBMOD_FACTOR;
		uint32_t tile_width = SCREEN_WIDTH / SPLIT_HEIGHT_SUBMOD_FACTOR;
		string sOutput = "";
		sOutput += "Pocket balance: " + to_string(balance) + 
			"\nPress Up to deposit 50k into offshore balance\nPress Down to withdraw 50k from offshore balance";


		box_height = SCREEN_HEIGHT - box_height;
		FillRect(X_OFFSET_SUBMOD_BOX, box_height, SCREEN_WIDTH - X_OFFSET_SUBMOD_BOX, box_height, olc::BLACK);
		DrawRect(X_OFFSET_SUBMOD_BOX, box_height, SCREEN_WIDTH - X_OFFSET_SUBMOD_BOX, box_height);
		DrawString(X_OFFSET_SUBMOD_BOX, box_height, "<", olc::WHITE, SPLIT_HEIGHT_SUBMOD_FACTOR);
		DrawString(X_OFFSET_SUBMOD_BOX + tile_width, box_height, sOutput, olc::WHITE, 2);
		DrawString(SCREEN_WIDTH - X_OFFSET_SUBMOD_BOX - tile_width, box_height, ">", olc::WHITE, SPLIT_HEIGHT_SUBMOD_FACTOR);
	}
	void render_display_jobs_substate(float fElapsedTime)
	{
		pspace::deliver_item& quest_ref = _dir.quests.back();
		uint32_t box_height = SCREEN_HEIGHT / SPLIT_HEIGHT_SUBMOD_FACTOR;
		uint32_t tile_width = SCREEN_WIDTH / SPLIT_HEIGHT_SUBMOD_FACTOR;
		string sOutput = "";
		sOutput += "Deliver " + to_string(quest_ref.amount) + " " + types[quest_ref.desired_item].name + "\n";
		sOutput += "Payout: " + to_string(quest_ref.payout) + "\n";
		sOutput += "X - " + to_string(quest_ref.target_chunk.x) + " Y - " + to_string(quest_ref.target_chunk.y);
		sOutput += "\nTime: " + to_string(quest_ref.minute_time) + ":" + to_string(quest_ref.second_time);

		box_height = SCREEN_HEIGHT - box_height;
		FillRect(X_OFFSET_SUBMOD_BOX, box_height, SCREEN_WIDTH - X_OFFSET_SUBMOD_BOX, box_height, olc::BLACK);
		DrawRect(X_OFFSET_SUBMOD_BOX, box_height, SCREEN_WIDTH - X_OFFSET_SUBMOD_BOX, box_height);
		DrawString(X_OFFSET_SUBMOD_BOX, box_height, "<", olc::WHITE, SPLIT_HEIGHT_SUBMOD_FACTOR);
		DrawString(X_OFFSET_SUBMOD_BOX + tile_width, box_height, sOutput, olc::WHITE, 2);
		DrawString(SCREEN_WIDTH - X_OFFSET_SUBMOD_BOX - tile_width, box_height, ">", olc::WHITE, SPLIT_HEIGHT_SUBMOD_FACTOR);

	}

	bool check_delivery()
	{
		decimal minval = _dir.current_quest->amount;

		minval = std::min(minval, inventory.at(_dir.current_quest->desired_item).amount);
		if (minval >= _dir.current_quest->amount)
		{
			inventory.at(_dir.current_quest->desired_item).amount -= minval;
			balance += _dir.current_quest->payout;
			execute_event(_dir.current_quest->upon_complete());
			_dir.current_quest = _dir.quests.erase(_dir.current_quest);
			return true;
		}

		return false;
	}

	bool OnUserCreate() override
	{
		
		player_level = 3;

		waterSupply = 300;
		static_water_consumption = 1;
		static_water_consumptionOff = STATIC_WATER_CONSUMPTION_RATE;

		foodSupply = 300;
		static_food_consumption = 1;
		static_consumptionOff = STATIC_FOOD_CONSUMPTION_RATE;

		beat = 0;
		orbit_offset = 0.0f;

		engine_dead = false;

		spaceFuel = START_FUEL_AMOUNT;
		static_fuel_consumption = STATIC_CONSUMPTION_START;
		static_consumptionOff = STATIC_CONSUMPTION_RATE;
		move_consumption = 0.0;
		//init scene
		
		space_grid = false;

		bHolding_window = false;

		minute_time = 0;
		float second_time;

		inter = new raycastv(ScreenWidth(), ScreenHeight(), (3.14159f / 10.0f));
		if (inter == NULL)
		{
			cout << "failed to load engine" << endl;
			freeMem();
			return false;
		}

		int i;
		//start of store interface stuff
		_mouse = { 0,0 };
		selected_slot = { -1, 0 };
		amount.resize(3);
		amount.assign("000");
		slot_number = 5;
		amount_slot = 0;
		iamount_slot = 0;
		nLehmer128 = 0;
		std::array<slot, e_items::NUMBER_OF_ITEMS>::iterator k;
		i = 0;
		for (k = inventory.begin(); k != inventory.end(); ++k)
		{
			k->amount = 0;
			k->type = types[i++];
		}
		//end of store interface stuff
		inv_itm = inventory.begin();

		std::shared_ptr < olc::rcw::Object> pcam = std::make_shared<olc::rcw::Object>();
		current_lookedStar = nullptr;

		pcam->pos = { 2.0f, 2.0f };
		pcam->bVisible = false;
		inter->mapObjects.insert_or_assign(0, pcam);

		//end scene

		//CreateLayer();

		
		cout << "Init disease array" << endl;

		

		ills_list.at(pspace::special_diseases::DISEASE_STARVE).name = "Malnutrition";
		ills_list.at(pspace::special_diseases::DISEASE_STARVE).detected = true;
		ills_list.at(pspace::special_diseases::DISEASE_STARVE).level_to_cure = 999;
		ills_list.at(pspace::special_diseases::DISEASE_STARVE).level_to_detect = 0;
		ills_list.at(pspace::special_diseases::DISEASE_STARVE).t_minutes = 5;
		ills_list.at(pspace::special_diseases::DISEASE_STARVE).t_second = 0.0;
		ills_list.at(pspace::special_diseases::DISEASE_STARVE).bActive = false;
		
		ills_list.at(pspace::special_diseases::DISEASE_THIRST).name = "Thirst";
		ills_list.at(pspace::special_diseases::DISEASE_THIRST).detected = true;
		ills_list.at(pspace::special_diseases::DISEASE_THIRST).level_to_cure = 9999;
		ills_list.at(pspace::special_diseases::DISEASE_THIRST).level_to_detect = 0;
		ills_list.at(pspace::special_diseases::DISEASE_THIRST).t_minutes = 2;
		ills_list.at(pspace::special_diseases::DISEASE_THIRST).t_second = 0.0;
		ills_list.at(pspace::special_diseases::DISEASE_THIRST).bActive = false;

		cout << "Finished init disease array" << endl;

		
		//olc::Sprite* whole = sprites.at(0);
		//for (i = 0; i < 10; ++i)
		//{
		//	spri = whole->Duplicate(ssprites[i].state.x, ssprites[i].state.y);
		//	if (spri == NULL)
		//	{
		//		freeMem();
		//		return false;
		//	}
		//	
		//	sprites.push_back(spri);
		//}

		//sprites.push_front(whale);

		//dec = new olc::Decal(whole);
		//if (dec == NULL)
		//{
		//	freeMem();
		//	return false;
		//}

		selectedPlanet = 0;

		player = NULL;
		
		player = new spaceship("The Space Machine", ScreenWidth() >> 1
			, ScreenHeight() >> 1, 3, 10);//temporary
		if (player == NULL)
		{
			cout << "Failed to create player" << endl;
			freeMem();
			return false;
		}

		//actors.push_back(player);
		//collidables.push_back(player);

		orbit_offset = 0.0f;
		picture = -1;
		music = 0;

		/*
		spr = new olc::Sprite("C:\\Users\\aafaq\\Desktop\\spaceoddityassets\\spaceoddity pictures\\RetroMenu.png");
		if (spr == NULL)
		{
			cout << "Failed to create sprite thing" << endl;
			freeMem();
			return false;
		}
		*/

		

		_move = true;

		if (player != NULL)
		{
			player->_sides[0].x = -5;
			player->_sides[0].y = 5;
			player->_sides[1].x = player->_sides[0].x + 10;
			player->_sides[1].y = player->_sides[0].y;
			player->_sides[2].x = player->_sides[0].x + 5;
			player->_sides[2].y = player->_sides[0].y - 15;
		}
		starScroll = 8.0f;//speed of scrolling stars


		//bStarSelected = false;//TODO: Get rid of this 
		vStarSelected = { 0,0 };

		_scale = 1.0f;//initial scale

		//load background music
		//background = olc::SOUND::LoadAudioSample("C:\\Users\\aafaq\\Desktop\\spaceoddity assets\\spaceoddity music\\MuawiyaMusic.wav");
		//olc::SOUND::PlaySample(background, true);

		//set submode
		submode = 0;
		offshore_balance = 0;
		balance = STARTING_PLAYER_MONEY;
		
		gamestate = pspace::gamestates::CINEMATIC;
		combat_cord = { 0.0f, 0.0f };
		

		backup_lookAngle = backup_movementAngle = NAN;

		// Called once at the start, so create things here
		cout << "Creating window..." << endl;

		
		


		

		//signal to the destructor not no attempt to delete the arg, becuse it's not ours
		


		cout << "window created successfully" << endl;

		cout << "Creating table" << endl;

		cout << "Created table" << endl;
		cout << "Loading sprites" << endl;

		if (loadSprites())
			return false;
		cout << "Loaded sprites" << endl;

		cout << "Loading sounds" << endl;
		if (loadSounds())
		{
			//freeMem();
			return false;
		}

		//cinematicStart.OnUserCreate(ScreenWidth(), ScreenHeight());
		//olc::SOUND::PlaySample(1, true);

		cout << "Loaded sprites" << endl;
		prev = { -1,-1 };

		cout << "Initiating stars..." << endl;
		for (auto& s : _star)
		{
			s.x = rndInt(0, ScreenWidth());
			s.y = rndInt(0, ScreenHeight());
		}
		cout << "Initiated stars" << endl;

		cout << "loading cinimatic" << endl;
		if (cinematicStart.OnUserCreate(SCREEN_WIDTH, SCREEN_HEIGHT) == false)
			return false;
		cout << "Finished loading cinematic" << endl;
		cout << "done" << endl;
		return true;
	}
	bool OnUserUpdate(float fElapsedTime) override
	{
		
		if (submode == pspace::substates::DISPLAY_JOBS)
		{
			if (GetKey(olc::Key::TAB).bPressed)
				submode = pspace::substates::SUBTYPE_NULL;
			goto SKIP_SUBSTATE_SWITCH;
		}
		if (GetKey(olc::Key::PGUP).bPressed && GetKey(olc::SHIFT).bHeld)
		{
			substate_time = SUBMODE_SLEEP_TIME;
			if (submode != 0)
				--submode;
		}
		else if (GetKey(olc::Key::PGDN).bPressed && GetKey(olc::SHIFT).bHeld)
		{
			substate_time = SUBMODE_SLEEP_TIME;
			if (submode != pspace::substates::NUMBER_OF_SUBSTATES)
				++submode;
		}
		if (GetKey(olc::Key::M).bPressed)
		{
			submode = pspace::substates::MUSIC;
			substate_time = SUBMODE_SLEEP_TIME;
		}
		else if (GetKey(olc::Key::I).bPressed)
		{
			submode = pspace::substates::DISPLAY_ITEM;
			substate_time = SUBMODE_SLEEP_TIME;
		}
		else if (GetKey(olc::Key::Q).bPressed)
		{
			submode = pspace::substates::DISPLAY_QUEST;
			substate_time = SUBMODE_SLEEP_TIME;
		}
		else if (GetKey(olc::Key::O).bPressed)
		{
			submode = pspace::substates::DISPLAY_MONEY;
			substate_time = SUBMODE_SLEEP_TIME;
		}
		else if (GetKey(olc::Key::U).bPressed)
		{
			submode_struct.ills_itr = ills_list.begin();
			submode = pspace::substates::DISPLAY_DISEASE;
			substate_time = SUBMODE_SLEEP_TIME;
		}
		else if (GetKey(olc::Key::TAB).bPressed)
		{
			substate_time = SUBMODE_SLEEP_TIME;
			submode = pspace::substates::DISPLAY_JOBS;
			_dir.generate_quest(player_level);
			_dir.quests.back().bFreeze = true;
		}

SKIP_SUBSTATE_SWITCH:
		if (submode != pspace::substates::SUBTYPE_NULL)
		{
			switch (submode)
			{
			case pspace::substates::MUSIC:
				update_music_substate(fElapsedTime);
				break;
			case pspace::substates::DISPLAY_QUEST:
				update_display_quest_substate(fElapsedTime);
				break;
			case pspace::substates::DISPLAY_ITEM:
				update_display_item_substate(fElapsedTime);
				break;
			case pspace::substates::DISPLAY_MONEY:
				update_display_money_substate(fElapsedTime);
				break;
			case pspace::substates::DISPLAY_JOBS:
				update_display_jobs_substate(fElapsedTime);
				break;
			default:
				break;
			}
			goto SKIP_SUBSTATE_CHECK;
		}

	SKIP_SUBSTATE_CHECK:
		bool state_ret;

		second_time += fElapsedTime;
		if (second_time >= 60.0f)
		{
			++minute_time;
			second_time -= 60.0f;
		}
		switch (gamestate)
		{
		case pspace::gamestates::SPACE_OVERLOOK:
			state_ret = UpdateSpace(fElapsedTime);
			break;
		case pspace::gamestates::MAIN_MENU:
			state_ret = UpdateMainMenu(fElapsedTime);
			break;
		case pspace::gamestates::PAUSE:
			state_ret = true;
			break;
		case pspace::gamestates::STAR_SYSTEM_OVERLOOK:
			state_ret = UpdateStarSystem(fElapsedTime);
			break;
		case pspace::gamestates::PLANET_OVERLOOK:
			state_ret = UpdatePlanet(fElapsedTime);
			break;
		case pspace::gamestates::CINEMATIC:
			state_ret = UpdateCinematic(fElapsedTime);
			break;
		case pspace::gamestates::SPACESHIP_INSIDE:
			state_ret = UpdateSpaceship(fElapsedTime);
			break;
		case pspace::gamestates::STORE_INTERFACE:
			state_ret = UpdateStoreInterface(fElapsedTime);
			break;
		case pspace::gamestates::GAME_OVER:
			return UpdateGameOver(fElapsedTime);
		case pspace::gamestates::CITY_INSIDE:
			state_ret =  UpdateCityInside(fElapsedTime);
			break;
		case pspace::gamestates::COMBAT_MODE:
			state_ret = UpdateCombat(fElapsedTime);
			break;
		default:
			state_ret = false;
		}
		switch (submode)
		{
		case pspace::substates::MUSIC:
			render_music_substate(fElapsedTime);
			break;
		case pspace::substates::DISPLAY_DISEASE:
			render_disease_substate(fElapsedTime);
			break;
		case pspace::substates::DISPLAY_QUEST:
			render_display_quest_substate(fElapsedTime);
			break;
		case pspace::substates::DISPLAY_ITEM:
			render_display_item_substate(fElapsedTime);
			break;
		case pspace::substates::DISPLAY_MONEY:
			render_display_money_substate(fElapsedTime);
			break;
		case pspace::substates::DISPLAY_JOBS:
			render_display_jobs_substate(fElapsedTime);
			break;
		default:
			break;
		}

		std::list<pspace::deliver_item>::iterator quest_itr;
		for (quest_itr = _dir.quests.begin(); quest_itr != _dir.quests.end(); ++quest_itr)
		{
			if (quest_itr->bFreeze)
				continue;
			quest_itr->second_time -= fElapsedTime;
			if (quest_itr->second_time <= 0.0f)
			{
				if (quest_itr->minute_time == 0)
				{
					execute_event(quest_itr->upon_fail());
				}
				else
				{
					quest_itr->minute_time--;
					quest_itr->second_time = 60.0f;
				}
			}

		}

		

		return state_ret;
	}
};

void flip(olc::Sprite* spr, olc::vi2d og, olc::vi2d size);
void myDrawPSprite(olc::Sprite* sprite, olc::GFX2D::Transform2D& transform, bool flip);

void test(int argnum, ...)
{
	va_list args;
	va_start(args, argnum);


	int param, i;
	for (i = 0; i < argnum; ++i)
	{
		param = va_arg(args, int);
		cout << param << endl;
	}

	va_end(args);

	return;
}

void print_super(const superint& number)
{
	std::vector<int64_t>::const_iterator k;
	for (k = number.list.begin(); k != number.list.end(); ++k)
	{
		cout << *k << " ";
	}
	cout << endl;
}

int main(int argc, char* argv[])
{

	olc::PGEX* texten = new olc::TransformedView();
	if (texten == NULL) return 1;
	olc::PGEX* sexten = new olc::SOUND();
	if (sexten == NULL) {
		delete texten;
		return 1;
	}
	
	//spaceoddity demo;
	//demo.pgex_Register(exten);

	globalGame = new spaceoddity();
	if (globalGame == NULL)
		return 1;
	globalGame->pgex_Register(sexten);
	globalGame->pgex_Register(texten);
	if (globalGame->Construct(SCREEN_WIDTH, SCREEN_HEIGHT, 2, 2, false, false,  false))
		globalGame->Start();
	else
	{
		olc::SOUND::DestroyAudio();
		delete sexten;
		delete texten;
		globalGame->freeMem();
		delete globalGame;
		return 1;
	}
		
	olc::SOUND::DestroyAudio();
	delete sexten;
	delete texten;
	globalGame->freeMem();
	delete globalGame;
	cout << endl << "Hope you had fun" << endl;

	return 0;
}

void actifunc(const dfunc& fun)
{
	fun.func(fun.argnum, fun.args);
}
void spaceoddity::freeMem(){
	unsigned int i;

	if(player != NULL) delete player;
	player = NULL;
	if (current_lookedStar != NULL) delete current_lookedStar;
	current_lookedStar = NULL;

	
	while (!olc::vecAudioSamples.empty())
	{
		float* data = olc::vecAudioSamples.back().fSample;
		delete[] data;
		olc::vecAudioSamples.pop_back();
	}

	std::list<pspace::space_object*>::iterator space_objects_runner;
	for (space_objects_runner = space_objects.begin(); space_objects_runner != space_objects.end(); ++space_objects_runner)
	{
		delete* space_objects_runner;
	}
	std::list<enemy*>::iterator enemy_itr;
	for (enemy_itr = enemy_list.begin(); enemy_itr != enemy_list.end(); ++enemy_itr)
	{
		delete* enemy_itr;
	}
	enemy_list.clear();
	space_objects.clear();

	while (!windowList.empty())
	{
		delete windowList.front();
		windowList.pop_front();
	}
	
	std::vector<olc::Renderable*>::iterator render_itr;
	for (render_itr = renderables.begin(); render_itr != renderables.end(); ++render_itr)
		delete (*render_itr);
	renderables.clear();
	
	//delete spr;
	if(inter != NULL)
		delete inter;
	inter = NULL;
	manage.Close();	
}

spaceoddity::spaceoddity(): _dir(0, 1001)
{
	sAppName = "Space";
	
}
void spaceoddity::shiftStars(float sx, float sy)
{

	for (auto& s : _star)
	{
		s.x += sx;
		s.y += sy;

		if (s.y > ScreenHeight())
		{
			s.x = rndInt128(0, ScreenWidth());
			s.y = 0;
		}
		else if (s.y < 0)
		{
			s.x = rndInt128(0, ScreenWidth());
			s.y = ScreenHeight();
		}
		if (s.x > ScreenWidth())
		{
			s.x = 0;
			s.y = rndInt128(0, ScreenHeight());
		}
		else if (s.x < 0)
		{
			s.x = ScreenWidth();
			s.y = rndInt128(0, ScreenHeight());
		}
	}

	return;
}

spaceoddity::~spaceoddity()
{
	//freeMem();	//DO NOT CALL!!!!!!!!!
}

bool spaceoddity::loadSprites()
{
	olc::vi2d itr;
	olc::Sprite* spr;
	for (auto& k : renderables_address)
	{
		olc::Renderable* ren = new olc::Renderable();
		if (ren == nullptr)
			return true;
		ren->Load(SPRITE_ASSETS_FOLDER_PATH + k);
		renderables.push_back(ren);
	}
	spr = renderables.at(sprites::CITY_SPRITE)->Sprite();
	for (itr.x = 0; itr.x < spr->width; itr.x++)
	{
		for (itr.y = 0; itr.y < spr->height; itr.y++)
		{
			if (spr->GetPixel(itr) == olc::WHITE)
				spr->SetPixel(itr, olc::BLANK);
		}
	}
	renderables.at(sprites::CITY_SPRITE)->Decal()->Update();

	//pics.push_back(k);
	return false;
}
bool spaceoddity::unloadSprites()
{
	
	return true;
}
bool spaceoddity::loadSounds()
{
	return olc::SOUND::InitialiseAudio() == false;
}

bool spaceoddity::UpdateMainMenu(float fElapsedTime)
{
	// Draw Menu at position (30, 30), using "patch sprite"
	Clear(olc::BLACK);
	//manage.Draw(spr, { 50,50 });
	
	// Send key events to menu	
	if (GetKey(olc::Key::UP).bPressed)    manage.OnUp();
	if (GetKey(olc::Key::DOWN).bPressed)  manage.OnDown();
	if (GetKey(olc::Key::LEFT).bPressed)  manage.OnLeft();
	if (GetKey(olc::Key::RIGHT).bPressed) manage.OnRight();
	if (GetKey(olc::Key::Z).bPressed)     manage.OnBack();
	if (GetKey(olc::Key::C).bPressed) gamestate = pspace::gamestates::SPACE_OVERLOOK;

	// "Confirm/Action" Key does something, if it returns non-null
	// then a menu item has been selected. The specific item will
	// be returned
	olc::popup::Menu* command = nullptr;
	if (GetKey(olc::Key::SPACE).bPressed) command = manage.OnConfirm();

	if (command != nullptr)
	{	
		picture = command->GetID();
		// Optionally close menu?
		//manage.Close();
		manage.OnBack();
	}

	
	return true;
}
bool spaceoddity::UpdateSpace(float fElapsedTime){
	// called once per frame
	int nSectorsX = ScreenWidth() / (_scale * SIZE_OF_BLOCK);
	int nSectorsY = ScreenHeight() / (_scale * SIZE_OF_BLOCK);
	olc::vf2d s;
	olc::vi2d player_box, player_target_box;
	int mx, my;
	//save it so it doesnt change and ruin everything
	mx = GetMouseX();
	my = GetMouseY();

	//SetDrawTarget(1);	//actors layer
	if (GetKey(olc::P).bPressed) pause = !pause;
	if (GetKey(olc::ESCAPE).bPressed)
	{
		//open main menu

		return false;//exit game
	}

	


	//olc::Pixel test111 = GetDrawTarget()->GetPixel({ mx,my });
	//if (test111 == olc::DARK_BLUE)
	//	return false;
	
	//if (GetKey(olc::LEFT).bPressed) if (picture > -1) --picture;
	//if (GetKey(olc::RIGHT).bPressed) if (picpath[picture + 1] != "END") ++picture;
	
	orbit_offset += 10.0f * fElapsedTime;
	if (orbit_offset >= 360.0f)
		orbit_offset -= 360.0f;
	execute_event(_dir.per_frame());

	//static fuel consumption
	if (spaceFuel != 0)
	{
		static_consumptionOff -= fElapsedTime;
		if (static_consumptionOff <= 0.0)
		{
			if (spaceFuel >= static_fuel_consumption)
				spaceFuel -= static_fuel_consumption;
			else
				spaceFuel = 0;
			static_consumptionOff = STATIC_CONSUMPTION_RATE;
		}
	}
	if (foodSupply != 0)
	{
		static_food_consumptionOff -= fElapsedTime;
		if (static_food_consumptionOff <= 0.0)
		{
			if (foodSupply >= static_food_consumption)
			{
				foodSupply -= static_food_consumption;
				static_water_consumptionOff = STATIC_FOOD_CONSUMPTION_RATE;
			}
			if(foodSupply < static_food_consumption)
			{
				foodSupply = 0;
				
				ills_list.at(pspace::special_diseases::DISEASE_STARVE).bActive = true;
				ills_list.at(pspace::special_diseases::DISEASE_STARVE).t_minutes = 5;
				ills_list.at(pspace::special_diseases::DISEASE_STARVE).t_second = 0.0;
			}
			static_food_consumptionOff = STATIC_FOOD_CONSUMPTION_RATE;
		}
	}
	if (waterSupply != 0)
	{
		static_water_consumptionOff -= fElapsedTime;
		if (static_water_consumptionOff <= 0.0)
		{
			if (waterSupply >= static_water_consumption)
			{
				waterSupply -= static_water_consumption;
				static_water_consumptionOff = STATIC_WATER_CONSUMPTION_RATE;
			}
			if(waterSupply < static_water_consumption)
			{
				waterSupply = 0;
				ills_list.at(pspace::special_diseases::DISEASE_THIRST).bActive = true;
				ills_list.at(pspace::special_diseases::DISEASE_THIRST).t_minutes = 2;
				ills_list.at(pspace::special_diseases::DISEASE_THIRST).t_second = 0.0;
			}
		}
	}

	//int i, j;
	//for (j = 0; j < nSectorsY; ++j)
	//{
	//	for (i = 0; i < nSectorsX; ++i)
	//	{
	//		cStarSystem k(currentPos.x + i, currentPos.y + j, 1);
	//		
	//	}
	//}
	if (GetKey(olc::Key::G).bPressed)
		space_grid = !space_grid;

	if ((!engine_dead) && (player->tx == -1.0f) && (player->ty == -1.0f))
	{
		if (GetKey(olc::Key::A).bHeld)
		{
			player->rotate(-60.0f * fElapsedTime, player->cord.x, player->cord.y);
		}
		if (GetKey(olc::Key::D).bHeld)
		{
			player->rotate(60.0f * fElapsedTime, player->cord.x, player->cord.y);
		}
		if (GetKey(olc::Key::W).bHeld)	player->acivateEngine(fElapsedTime);
		if (GetKey(olc::Key::S).bHeld && GetKey(olc::Key::SHIFT).bHeld)
			player->spaceBreak(fElapsedTime);
		else if (GetKey(olc::Key::S).bHeld) player->slowDown(fElapsedTime);
	}
	
	if (_move)
	{
		player->move(fElapsedTime);
		move_consumption += abs(player->speedFactor[0]) * fElapsedTime
			* MOVE_CONSUMPTION_MULTIPLIER;
		move_consumption += abs(player->speedFactor[1]) * fElapsedTime
			* MOVE_CONSUMPTION_MULTIPLIER;

		if (move_consumption >= UPDATE_CONSUMPTION_THRESH)
		{
			move_consumption -= UPDATE_CONSUMPTION_THRESH;
			if (spaceFuel >= UPDATE_CONSUMPTION_THRESH)
				spaceFuel -= UPDATE_CONSUMPTION_THRESH;
			else
				spaceFuel = 0;
		}
	}

	bool bCheck_curr = false;
	
	if (player->cord.x > ScreenWidth())
	{
		player->cord.x -= ScreenWidth();
		superLehmerSeed.x.inc();
		superLehmerSeed.x.inc();
		//superLehmerSeed.x++;
		bCheck_curr = true;

		for (objects_itr = space_objects.begin(); objects_itr != space_objects.end(); ++objects_itr)
		{
			delete* objects_itr;
		}
		space_objects.clear();
		std::list<pspace::deliver_item>::iterator quest_itr;
		for (quest_itr = _dir.quests.begin(); quest_itr != _dir.quests.end(); ++quest_itr)
			quest_itr->upon_going_right();

	}
	else if (player->cord.x < 0.0f)
	{
		player->cord.x += ScreenWidth();
		superLehmerSeed.x.dec();
		superLehmerSeed.x.dec();
		//superLehmerSeed.x--;
		bCheck_curr = true;

		for (objects_itr = space_objects.begin(); objects_itr != space_objects.end(); ++objects_itr)
		{
			delete* objects_itr;
		}
		space_objects.clear();
		std::list<pspace::deliver_item>::iterator quest_itr;
		for (quest_itr = _dir.quests.begin(); quest_itr != _dir.quests.end(); ++quest_itr)
			quest_itr->upon_going_left();
	}
	if (player->cord.y > ScreenHeight())
	{
		player->cord.y -= ScreenHeight();
		superLehmerSeed.y.inc();
		superLehmerSeed.y.inc();
		//superLehmerSeed.y++;
		bCheck_curr = true;

		for (objects_itr = space_objects.begin(); objects_itr != space_objects.end(); ++objects_itr)
		{
			delete* objects_itr;
		}
		space_objects.clear();
		std::list<pspace::deliver_item>::iterator quest_itr;
		for (quest_itr = _dir.quests.begin(); quest_itr != _dir.quests.end(); ++quest_itr)
			quest_itr->upon_going_down();
	}
	else if (player->cord.y < 0.0f)
	{
		player->cord.y += ScreenHeight();
		superLehmerSeed.y.dec();
		superLehmerSeed.y.dec();
		//superLehmerSeed.y++;
		bCheck_curr = true;
		for (objects_itr = space_objects.begin(); objects_itr != space_objects.end(); ++objects_itr)
		{
			delete* objects_itr;
		}
		space_objects.clear();
		std::list<pspace::deliver_item>::iterator quest_itr;
		for (quest_itr = _dir.quests.begin(); quest_itr != _dir.quests.end(); ++quest_itr)
			quest_itr->upon_going_up();
	}


NOBOX_HERE:
	std::list<swindow*>::iterator k;
	if (GetMouse(0).bPressed)
	{
		prev.x = mx;
		prev.y = my;

		//check colition with windows
		//first one in list should be found(if stacked on top eachother)
		

		olc::vi2d mouse = { mx / SIZE_OF_BLOCK, my / SIZE_OF_BLOCK };
		//olc::vi2d screen_sector = { 0,0 };

		for (k = windowList.begin(); k != windowList.end(); ++k)
		{
			swindow* currentWind = *k;

			if (currentWind->checkCollision(mx, my))
			{
				windowList.erase(k);
				windowList.push_front(currentWind);
				bHolding_window = true;
				goto NOBOX_HERE;
			}

		}
		//cStarSystem star(galaxy_mouse.x, galaxy_mouse.y);
		//cStarSystem star(camera.ScreenToWorld({ mx,my }).x, camera.ScreenToWorld({ mx,my }).y, 1);
		//systems.push_back(star);
		//if (star.starExists)
		//{
		//	vStarSelected = galaxy_mouse;
		//	newSystemWindow();
		//}
	}

	if (GetMouse(0).bHeld)
	{
		if (bHolding_window)
		{
			swindow* the_wind = windowList.front();
			olc::vi2d co_ord = the_wind->corner;
			co_ord.x = mx - co_ord.x;
			co_ord.y = my - co_ord.y;
			the_wind->shift(co_ord.x, co_ord.y);
		}
		
	}
	if (GetMouse(0).bReleased)
	{
		bHolding_window = false;
	}

FOUND_SOMETHING1:

	player_box = player->cord;
	player_box /= SIZE_OF_BLOCK;
	player_box *= SIZE_OF_BLOCK;

	player_target_box.x = player->tx;
	player_target_box.y = player->ty;
	player_target_box /= SIZE_OF_BLOCK;
	player_target_box *= SIZE_OF_BLOCK;
	
	if (player_box == player_target_box)
	{
		player->speedFactor[0] = player->speedFactor[1] = 0.0f;	//turn off engine
		player->tx = player->ty = -1.0f;	//no target
		player->setDir(backup_lookAngle);	//movementAngle != lookAngle
		backup_lookAngle = backup_movementAngle = NAN;//reset
		current_lookedStar = new cStarSystem(player_target_box.x, player_target_box.y, 2);
		if (current_lookedStar == nullptr)
			goto BREAK_CHECK1;
		gamestate = pspace::gamestates::STAR_SYSTEM_OVERLOOK;	//enetring a system
		vStarSelected = player_target_box;
		star_syst_local_offset = 0.0;
		goto BREAK_CHECK1;
	}

	if (_dir.current_quest != _dir.quests.end())
	{
		if (player_box == _dir.current_quest->target_place)
		{
			check_delivery();
		}
	}

	if ((spaceFuel == 0) && (player->speedFactor[0] != 0.0f) && (player->speedFactor[1] != 0.0f))
	{
		engine_dead = true;
		player->speedFactor[0] *= 0.999;
		player->speedFactor[1] *= 0.999;
	}

DONT_DRAW_WIND:

	//send array of void pointers that represent the parameters
	if (space_objects.empty() == false)
	{
		for (objects_itr = space_objects.begin(); objects_itr != space_objects.end(); )
		{

			if ((*objects_itr)->bKill)
			{
				delete* objects_itr;
				*objects_itr = nullptr;
				objects_itr = space_objects.erase(objects_itr);
				continue;
				//runner_space_objects = space_objects.erase(runner_space_objects);
			}
			uint32_t ret = (*objects_itr)->perFrame(fElapsedTime);
			execute_event(ret);
			++objects_itr;
		}
		
	}
BREAK_CHECK1:
	updateScreen(fElapsedTime);
	++beat;

	std::array<pspace::disease, pspace::special_diseases::NUMBER_OF_DISEASES>::iterator ills_itr;
	for (ills_itr = ills_list.begin(); ills_itr != ills_list.end(); ++ills_itr)
	{
		if (ills_itr->bActive == false)
			continue;

		ills_itr->t_second -= fElapsedTime;
		if (ills_itr->t_second <= 0.0)
		{
			if (ills_itr->t_minutes == 0)
			{
				//kill player
				gamestate = pspace::gamestates::GAME_OVER;
				return true;
			}
			else
			{
				ills_itr->t_minutes--;
				ills_itr->t_second = 60.0;
			}
		}
	}

	return true;
}
bool spaceoddity::UpdateStarSystem(float fElapsedTime)
{
	Clear(olc::DARK_BLUE);
	
	cStarSystem& refStar = *current_lookedStar;
	olc::Sprite* screen = GetDrawTarget();	//get screen sprite

	int mx, my;

	mx = GetMouseX();
	my = GetMouseY();


	for (auto& s : _star)
	{
		Draw(s.x, s.y);
	}

	int32_t diam = refStar.starDiameter;

	int32_t mouse_dead_zone_min = (SCREEN_WIDTH >> 1) - SYSTEM_MOUSE_DEAD_RANGE;
	int32_t mouse_dead_zone_max = (SCREEN_WIDTH >> 1) + SYSTEM_MOUSE_DEAD_RANGE;

	if (mx < mouse_dead_zone_min)
	{
		if (star_syst_local_offset > 0.0)
		{
			star_syst_local_offset -= (mouse_dead_zone_min - mx) * fElapsedTime;
			if (star_syst_local_offset < 0.0)	star_syst_local_offset = 0.0;
		}
	}
	else if (mx > mouse_dead_zone_max)
	{
		star_syst_local_offset += (mx - mouse_dead_zone_max) * fElapsedTime;
	}


	uint32_t current_planet = 0;
	uint32_t current_dist = diam * 2;
	std::list<sPlanet>::iterator planet_runner;
	
	if (star_syst_local_offset <= current_dist + diam)
		FillCircle(diam - star_syst_local_offset, ScreenHeight() >> 1, diam, refStar.starColour);



	for (planet_runner = refStar.planets.begin();
		planet_runner != refStar.planets.end(); ++planet_runner)
	{
		if (star_syst_local_offset <= planet_runner->offset + planet_runner->radius)
		{
			goto SKIP_LOOP1;
		}
		current_dist += planet_runner->offset;
		++current_planet;
	}

SKIP_LOOP1:

	
	while (planet_runner != refStar.planets.end())
	{
		//current_dist += planet_runner->offset;
		FillCircle(planet_runner->offset - star_syst_local_offset, ScreenHeight() >> 1, planet_runner->radius,
			planet_runner->color);


		if (current_planet == selectedPlanet)
		{
			DrawCircle(planet_runner->offset - star_syst_local_offset, ScreenHeight() >> 1, planet_runner->radius + 15
				, olc::YELLOW);
			if (GetKey(olc::Key::SPACE).bPressed)
			{
				planet_over.currentPlanet = &(*planet_runner);
				planet_over.seed = 0;
				planet_over.re_generate_plain = true;
				planet_over.seed_data = selectedPlanet;
				gamestate = pspace::gamestates::PLANET_OVERLOOK;
				planet_over.pCurrent_pos = { SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.5f };

				return true;
			}
		}

		++current_planet;
		++planet_runner;
	}
	
	if (GetKey(olc::Key::RIGHT).bPressed)
		++selectedPlanet;
	else if (GetKey(olc::Key::LEFT).bPressed)
		--selectedPlanet;

	if (GetKey(olc::ESCAPE).bPressed)
	{
		delete current_lookedStar;
		current_lookedStar = nullptr;
		_dir.current_quest->_planet = -1;
		gamestate = pspace::gamestates::SPACE_OVERLOOK;	//return to space
		selectedPlanet = 0;
		return true;
	}

	return true;
}
bool spaceoddity::UpdatePlanet(float fElapsedTime)
{
	olc::vi2d runner, mouse, mouse_tile;
	olc::vi2d x_off;
	olc::Decal* pDecal = renderables.at(sprites::CITY_SPRITE)->Decal();

	runner.x = renderables.at(sprites::CITY_SPRITE)->Sprite()->width;
	runner.y = renderables.at(sprites::CITY_SPRITE)->Sprite()->height;

	nLehmer128 = planet_over.seed_data + planet_over.seed;

	mouse = GetMousePos();
	mouse_tile = mouse / SIZE_OF_BLOCK;
	mouse_tile *= SIZE_OF_BLOCK;

	olc::Pixel sky_color = planet_over.currentPlanet->color;
	sky_color *= 3.5f;
	Clear(sky_color);
	FillRect(0, SCREEN_HEIGHT - (SCREEN_HEIGHT >> 2), SCREEN_WIDTH, SCREEN_HEIGHT >> 2, planet_over.currentPlanet->color);
	
	

	if (planet_over.pCurrent_pos.y >= (SCREEN_HEIGHT - (SCREEN_HEIGHT >> 2)))
	{
		gamestate = pspace::gamestates::GAME_OVER;
		current_lookedStar->planets.clear();
		delete current_lookedStar;
		current_lookedStar = nullptr;
		return true;
	}

	x_off.x = big_alternate_rndInt128(0, SCREEN_WIDTH / SIZE_OF_BLOCK) * SIZE_OF_BLOCK;
	x_off.y = SCREEN_HEIGHT - (SCREEN_HEIGHT >> 2) - runner.y;
	
	SetPixelMode(olc::Pixel::ALPHA);
	DrawDecal(x_off, pDecal);
	SetPixelMode(olc::Pixel::NORMAL);


	if (planet_over.pCurrent_pos.y >= x_off.y)
	{
		if ((planet_over.pCurrent_pos.x >= x_off.x) && (planet_over.pCurrent_pos.x <= x_off.x + runner.x))
		{
			gamestate = pspace::gamestates::CITY_INSIDE;
			planet_over.re_generate_city = true;
			planet_over.current_merch = 0;
			planet_over.current_city_mode = 0;
			return true;
		}
	}

	
	olc::vi2d points[3];
	
	if (GetKey(olc::Key::SHIFT).bHeld)
	{
		if (GetKey(olc::Key::D).bHeld)
		{
			planet_over.ship_speed.x += 10.0f * fElapsedTime;
		}
		else if (GetKey(olc::Key::D).bHeld)
		{
			planet_over.ship_speed.x -= 10.0f * fElapsedTime;
		}
	}
	else if (planet_over.ship_speed.x != 0.0f)
	{
		planet_over.ship_speed.x *= 0.999f;
	}

	if (GetKey(olc::Key::W).bHeld)
	{
		planet_over.pCurrent_pos.y -= 60.0f * fElapsedTime;
	}
	else if (GetKey(olc::Key::S).bHeld)
	{
		planet_over.pCurrent_pos.y += 60.0f * fElapsedTime;
	}
	if (GetKey(olc::Key::D).bHeld)
	{
		planet_over.pCurrent_pos.x += 60.0f * fElapsedTime;
		planet_over.spaceship_dir = 1;
	}
	else if (GetKey(olc::Key::A).bHeld)
	{
		planet_over.pCurrent_pos.x -= 60.0f * fElapsedTime;
		planet_over.spaceship_dir = -1;
	}
	
	planet_over.pCurrent_pos.x += planet_over.ship_speed.x * fElapsedTime;

	points[0] = planet_over.pCurrent_pos;
	points[1] = planet_over.pCurrent_pos;
	points[2] = planet_over.pCurrent_pos;

	points[0].x += (planet_over.points[0].x * planet_over.spaceship_dir);	points[0].y += planet_over.points[0].y;
	points[1].x += (planet_over.points[1].x * planet_over.spaceship_dir);	points[1].y += planet_over.points[1].y;
	points[2].x += (planet_over.points[2].x * planet_over.spaceship_dir);	points[2].y += planet_over.points[2].y;

	FillTriangle(points[0], points[1], points[2], olc::GREEN);

	if (planet_over.pCurrent_pos.x < 0.0f)
	{
		planet_over.pCurrent_pos.x = SCREEN_WIDTH;
		planet_over.seed--;
	}
	else if (planet_over.pCurrent_pos.x > SCREEN_WIDTH)
	{
		planet_over.pCurrent_pos.x = 0.0f;
		planet_over.seed++;
	}
	if (GetKey(olc::Key::ESCAPE).bPressed)
	{
		gamestate = pspace::gamestates::STAR_SYSTEM_OVERLOOK;
		planet_over.currentPlanet = nullptr;
		//planet_over.cities.clear();
		return true;
	}
	if (planet_over.pCurrent_pos.y < 0.0f)
	{
		gamestate = pspace::gamestates::STAR_SYSTEM_OVERLOOK;
		planet_over.currentPlanet = nullptr;
		//planet_over.cities.clear();
		return true;
	}	  //leave atmo

	return true;
}
bool spaceoddity::UpdateCinematic(float fElapsedTime)
{
	Clear(olc::BLACK);
	DrawPartialWarpedDecal(cinematicStart.spr.Decal(), cinematicStart.cor,
		{ 0.0f, 0.0f }, cinematicStart.size, olc::GREY);

	if (GetKey(olc::ESCAPE).bPressed)
		return false;
	if (GetKey(olc::SPACE).bPressed)
	{	
		olc::SOUND::StopSample(1);
		gamestate = pspace::gamestates::SPACE_OVERLOOK;
	}
	if (cinematicStart.time <= 0.0f)
		return false;
	cinematicStart.size.y += cinematicStart.speed * fElapsedTime;
	cinematicStart.time -= fElapsedTime;
	return true;
}
bool spaceoddity::UpdateEditor(float fElapsedTime)
{




	return true;
}
bool spaceoddity::UpdateSpaceship(float fElapsedTime)
{
	auto& cam = inter->mapObjects[0];
	cam->Stop();
	if (GetKey(olc::ESCAPE).bPressed)	return false;
	if (GetKey(olc::Key::W).bHeld) cam->Walk(inter->pspeed);
	if (GetKey(olc::Key::S).bHeld) cam->Walk(-inter->pspeed);
	if (GetKey(olc::Key::D).bHeld) cam->Strafe(inter->pspeed);
	if (GetKey(olc::Key::A).bHeld) cam->Strafe(-inter->pspeed);
	if (GetKey(olc::Key::Z).bPressed) gamestate = pspace::gamestates::SPACE_OVERLOOK;
	if (GetKey(olc::Key::RIGHT).bPressed) ++picture;
	if (GetKey(olc::Key::LEFT).bPressed) --picture;

	if (GetKey(olc::EQUALS).bHeld)
	{
		cam->Turn(1.0f * fElapsedTime);
	}
	if (GetKey(olc::MINUS).bHeld)
	{
		cam->Turn(-1.0f * fElapsedTime);
	}
	if (GetKey(olc::Key::RIGHT).bPressed)
		inter->pic++;
	if (GetKey(olc::Key::LEFT).bPressed)
		inter->pic--;

	inter->Update(fElapsedTime);

	inter->SetCamera(cam->pos, cam->fHeading);
	
	inter->Render();

	return true;
}
bool spaceoddity::UpdateStoreInterface(float fElapsedTime)
{
	Clear(olc::GREY);
	DrawString(0, 0, " NAME  PRICE  WEIGHT  AMOUNT", olc::WHITE, 2);
	

	if (GetKey(olc::Key::ESCAPE).bPressed)
	{
		return false;
	}

	int number_of_slots = 6;
	int size_of_slot = ScreenHeight() / number_of_slots;
	int i, val, j;
	val = 40;
	std::vector<slot>::iterator k = start_slot;
	for (i = 0; i < number_of_slots; ++i)
	{
		if (k == currentMerch->stock.end())
			break;
		if (k->amount == 0)	//delete item
		{
			currentMerch->stock.erase(k);
			return true;
		}
		string print;
		if (k == curr_slot)
		{
			print = ">";
			DrawRect(0, val, ScreenWidth(), size_of_slot);
			print += k->type.name;
			print += '\t';
			print += to_string(k->type.price);
			print += '\t';
			print += to_string(k->type.weight);
			print += ' ';
			print += to_string(k->amount);
			print += '\n';
			print += amount;
		}
		else
		{
			print = " ";
			DrawRect(0, val, ScreenWidth(), size_of_slot);
			print += k->type.name;
			print += ' ';
			print += to_string(k->type.price);
			print += ' ';
			print += to_string(k->type.weight);
			print += ' ';
			print += to_string(k->amount);
		}

		DrawString(0, val + 5, print, olc::WHITE, 2);
		val += size_of_slot;
		++k;
	}

	if (GetKey(olc::Key::NP0).bPressed)
	{
		amount[amount_slot++] = '0';
		amount_slot %= 3;
	}
	else if (GetKey(olc::Key::NP1).bPressed)
	{
		amount[amount_slot++] = '1';
		amount_slot %= 3;
	}
	else if (GetKey(olc::Key::NP2).bPressed)
	{
		amount[amount_slot++] = '2';
		amount_slot %= 3;
	}
	else if (GetKey(olc::Key::NP3).bPressed)
	{
		amount[amount_slot++] = '3';
		amount_slot %= 3;
	}
	else if (GetKey(olc::Key::NP4).bPressed)
	{
		amount[amount_slot++] = '4';
		amount_slot %= 3;
	}
	else if (GetKey(olc::Key::NP5).bPressed)
	{
		amount[amount_slot++] = '5';
		amount_slot %= 3;
	}
	else if (GetKey(olc::Key::NP6).bPressed)
	{
		amount[amount_slot++] = '6';
		amount_slot %= 3;
	}
	else if (GetKey(olc::Key::NP7).bPressed)
	{
		amount[amount_slot++] = '7';
		amount_slot %= 3;
	}
	else if (GetKey(olc::Key::NP8).bPressed)
	{
		amount[amount_slot++] = '8';
		amount_slot %= 3;
	}
	else if (GetKey(olc::Key::NP9).bPressed)
	{
		amount[amount_slot++] = '9';
		amount_slot %= 3;
	}

	if (GetKey(olc::Key::K0).bPressed)
	{
		amount[amount_slot++] = '0';
		amount_slot %= 3;
	}
	else if (GetKey(olc::Key::K1).bPressed)
	{
		amount[amount_slot++] = '1';
		amount_slot %= 3;
	}
	else if (GetKey(olc::Key::K2).bPressed)
	{
		amount[amount_slot++] = '2';
		amount_slot %= 3;
	}
	else if (GetKey(olc::Key::K3).bPressed)
	{
		amount[amount_slot++] = '3';
		amount_slot %= 3;
	}
	else if (GetKey(olc::Key::K4).bPressed)
	{
		amount[amount_slot++] = '4';
		amount_slot %= 3;
	}
	else if (GetKey(olc::Key::K5).bPressed)
	{
		amount[amount_slot++] = '5';
		amount_slot %= 3;
	}
	else if (GetKey(olc::Key::K6).bPressed)
	{
		amount[amount_slot++] = '6';
		amount_slot %= 3;
	}
	else if (GetKey(olc::Key::K7).bPressed)
	{
		amount[amount_slot++] = '7';
		amount_slot %= 3;
	}
	else if (GetKey(olc::Key::K8).bPressed)
	{
		amount[amount_slot++] = '8';
		amount_slot %= 3;
	}
	else if (GetKey(olc::Key::K9).bPressed)
	{
		amount[amount_slot++] = '9';
		amount_slot %= 3;
	}



	if (GetKey(olc::Key::ENTER).bPressed)
	{
		amount[0] -= '0';
		amount[1] -= '0';
		amount[2] -= '0';

		int num_amount = (100 * amount[0]) + (10 * amount[1]) + amount[2];
		slot& refSlot = *curr_slot;

		amount.assign("000");
		if (num_amount > refSlot.amount)
			goto IGNORE_SALE;

		refSlot.amount -= num_amount;
		if (inventory[refSlot.type.id].type.id == -1)
		{
			inventory[refSlot.type.id].amount = num_amount;
			inventory[refSlot.type.id].type = refSlot.type;
		}
		else
		{
			inventory[refSlot.type.id].amount += num_amount;
		}
	}
IGNORE_SALE:
	if (GetKey(olc::Key::UP).bPressed)
	{
		if (curr_slot == start_slot)
		{
			if (start_slot == currentMerch->stock.begin())
				goto IGNORE_DIR_INPUT_1;
			--start_slot;
			--curr_slot;
		}
		else
		{
			--curr_slot;
		}
	}
	if (GetKey(olc::Key::DOWN).bPressed)
	{
		if (curr_slot == k)		//k is final rendered slot
		{
			if (curr_slot == currentMerch->stock.end())
				goto IGNORE_DIR_INPUT_1;
			++start_slot;
			++curr_slot;
		}
		else
			++curr_slot;
	}
	if (GetKey(olc::Key::RIGHT).bPressed)
	{
		++nLehmer128;
	}
	if (GetKey(olc::Key::LEFT).bPressed)
	{
		--nLehmer128;
	}
IGNORE_DIR_INPUT_1:


	return true;
}
bool spaceoddity::UpdateCombat(float fElapsedTime)
{
	Clear(olc::DARK_BLUE);
	for (auto& s : _star)
	{
		Draw(s.x, s.y);
	}

	drawPlayer(fElapsedTime, 0);
	if (enemy_list.empty() == false)
	{
		std::list<enemy*>::iterator actor_run;
		SetPixelMode(olc::Pixel::Mode::ALPHA);
		for (actor_run = enemy_list.begin(); actor_run != enemy_list.end(); ++actor_run)
		{
			enemy* icurr = *actor_run;
			//camera.DrawSprite(sprites.at(pspr.spriteID), icurr->trans);
			//olc::Sprite* k = sprites.at(pspr.spriteID)->Duplicate(pspr.state.x, pspr.state.y);
			//if (whaleState[icurr->state1].partial)
			//{
			//	olc::GFX2D::DrawSprite(sprites.at(pspr.spriteID), icurr->trans);
			//}
			//else
			//	DrawPartialSprite(camera.WorldToScreen(icurr->cord), sprites.at(pspr.spriteID), pspr.state.x, pspr.state.y, icurr->localScale);
			icurr->draw(NULL);
			icurr->perFrame(fElapsedTime, 0);
			icurr->updateState(fElapsedTime);
			//myDrawPSprite(sprites.at(pspr.spriteID), icurr->trans, true);	
			//myDrawPSprite(sprites.at(pspr.spriteID), icurr->trans, true, pspr.state.x, pspr.state.y);
			if (collidewRect(player->cord.x, player->cord.y, icurr->cord.x, icurr->cord.y, icurr->width, icurr->height))
			{
				execute_event(director_event::ASTROID_COLLIDE);
				return true;
			}
		}
		SetPixelMode(olc::Pixel::Mode::NORMAL);
	}

	
	if (GetKey(olc::Key::W).bHeld)
	{
		player->cord.y -= 40.0f * fElapsedTime;
	}
	else if (GetKey(olc::Key::S).bHeld)
	{
		player->cord.y += 40.0f * fElapsedTime;
	}
	if (GetKey(olc::Key::A).bHeld)
	{
		player->cord.x -= 40.0f * fElapsedTime;
	}
	else if (GetKey(olc::Key::D).bHeld)
	{
		player->cord.x += 40.0f * fElapsedTime;
	}

	if (GetKey(olc::Key::RIGHT).bHeld)
	{
		player->rotate(60.0f * fElapsedTime, player->cord.x, player->cord.y);
	}
	else if (GetKey(olc::Key::LEFT).bHeld)
	{
		player->rotate(-60.0f * fElapsedTime, player->cord.x, player->cord.y);
	}

	if ((player->cord.x > SCREEN_WIDTH) || (player->cord.x < 0.0f) || (player->cord.y < 0.0f) || (player->cord.y > SCREEN_HEIGHT))
	{
		player->cord = outside_cord;
		gamestate = pspace::gamestates::SPACE_OVERLOOK;
		std::list<enemy*>::iterator enemy_itr;
		for (enemy_itr = enemy_list.begin(); enemy_itr != enemy_list.end(); ++enemy_itr)
		{
			delete* enemy_itr;
		}
		enemy_list.clear();
	}

	


	return true;
}
bool spaceoddity::UpdateGameOver(float fElapsedTime)
{
	FillRect(SCREEN_WIDTH >> 2, SCREEN_HEIGHT >> 2, SCREEN_WIDTH >> 1, SCREEN_HEIGHT >> 1, olc::BLACK);
	DrawRect(SCREEN_WIDTH >> 2, SCREEN_HEIGHT >> 2, SCREEN_WIDTH >> 1, SCREEN_HEIGHT >> 1);
	DrawString((SCREEN_WIDTH >> 2) + (SCREEN_WIDTH >> 3),
		(SCREEN_HEIGHT >> 2) + (SCREEN_HEIGHT >> 3), "GAME\nOVER", olc::WHITE, 8);

	if (GetKey(olc::ESCAPE).bPressed)
		return false;
	return true;
}
bool spaceoddity::UpdateCityInside(float fElapsedTime)
{
	Clear(olc::BLACK);
	if (planet_over.re_generate_city)
	{
		nLehmer128 = planet_over.seed_data;
		uint32_t i, j, number_of_merchants = 2 + big_alternate_rndInt128(0, 30);
		planet_over.vendors.clear();
		j = 0;
		for (i = 0; i < number_of_merchants; ++i)
		{
			merchant curr_m(planet_over.seed_data, j + planet_over.seed + i);
			j += SCREEN_HEIGHT / number_of_merchants;
			planet_over.vendors.push_back(curr_m);
		}
		currentMerch = planet_over.vendors.begin();
		curr_slot = start_slot = currentMerch->stock.begin();
		icurr_slot = istart_slot = inventory.begin();
		planet_over.current_merch = 0;
		planet_over.re_generate_city = false;
		j = 3 + big_alternate_rndInt128(0, 30);
		for (i = 0; i < j; ++i)
		{
			pspace::companion curr_peep(planet_over.seed_data
				, j + planet_over.seed + i, player_level);
			planet_over.peeps.push_back(curr_peep);

		}
		planet_over.current_peep = planet_over.peeps.begin();

	}
	string sOutput;
	
	int number_of_slots = 6;
	int size_of_slot = ScreenHeight() / number_of_slots;
	int i, val, j;
	auto merch_k = start_slot;
	double price_factor;
	bool city_ret = true;

	if (GetKey(olc::Key::ESCAPE).bPressed)
	{
		planet_over.vendors.clear();
		planet_over.currentCity = nullptr;
		planet_over.re_generate_city = true;
		gamestate = pspace::gamestates::PLANET_OVERLOOK;
		planet_over.pCurrent_pos = { SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.5f };
		return true;
	}

	switch (planet_over.current_city_mode)
	{
	case 0:
		city_ret = UpdateCityWelcome(fElapsedTime);
		break;
	case 1:
		city_ret = UpdateCityInventory(fElapsedTime);
		break;
	case 2:
		city_ret = UpdateCityBarter(fElapsedTime);
		break;
	case 3:
		city_ret = UpdateCityPeople(fElapsedTime);
		break;
	case 4:
		city_ret = UpdateCityQuest(fElapsedTime);
	default:
		goto END_OF_SUBMODE_CITY;
	}


END_OF_SUBMODE_CITY:
	
	if (GetKey(olc::Key::PGUP).bPressed && !GetKey(olc::Key::SHIFT).bHeld)
	{
		if (planet_over.current_city_mode != 0)
			planet_over.current_city_mode--;
	}
	else if (GetKey(olc::Key::PGDN).bPressed && !GetKey(olc::Key::SHIFT).bHeld)
	{
		planet_over.current_city_mode++;
		planet_over.current_city_mode %= 5;
	}

	return city_ret;
}

void shift_string_left(string& str, char end_ch)
{
	int i;
	for (i = 0; i < str.size() - 1; ++i)
	{
		str[i] = str[i + 1];
	}
	str[i] = end_ch;
}

bool spaceoddity::UpdateCityWelcome(float fElapsedTime)
{
	string sOutput = "1 - THIS SCREEN\n2 - MY INVENTORY\n3 - MERCHANT\n4 - MEET RESIDENTS\n USE PGUP AND PGDN \nTO MOVE BETWEEN SCREENS";
	DrawString(0, 0, sOutput, olc::WHITE, 3);
	return true;
}
bool spaceoddity::UpdateCityInventory(float fElapsedTime)
{
	int number_of_slots = 6;
	int size_of_slot = ScreenHeight() / number_of_slots;
	int i, val, j;
	auto k = istart_slot;
	auto merch_k = start_slot;
	double price_factor;

	val = 40;
	DrawString(0, 0, currentMerch->name + "\n" + "Balance " + to_string(balance), olc::WHITE, 2);
	for (i = 0; i < number_of_slots;)
	{
		if (k == inventory.end())
			break;
		if (k->amount == 0)
		{
			++k;
			continue;
		}

		string print;
		price_factor = 1.0 + (currentMerch->desire.at(k->type.id) / 1000.0);

		if (k == icurr_slot)
		{
			print = ">";
			DrawRect(0, val, ScreenWidth(), size_of_slot);
			print += k->type.name;
			print += '\t';
			print += to_string(k->type.price * price_factor);
			print += '\t';
			print += to_string(k->type.weight);
			print += ' ';
			print += to_string(k->amount);
			print += '\n';
			print += amount;

			if (GetKey(olc::Key::ENTER).bPressed)
			{
				amount[0] -= '0';
				amount[1] -= '0';
				amount[2] -= '0';
				iamount_slot = 0;
				amount_slot = 0;

				int num_amount = (100 * amount[0]) + (10 * amount[1]) + amount[2];

				amount.assign("000");
				if (num_amount > icurr_slot->amount)
					return true;

				icurr_slot->amount -= num_amount;
				planet_over.current_cargo_weight -= num_amount * icurr_slot->type.weight;
				balance += price_factor * num_amount * icurr_slot->type.price;
			}
		}
		else
		{
			print = " ";
			DrawRect(0, val, ScreenWidth(), size_of_slot);
			print += k->type.name;
			print += ' ';
			print += to_string(k->type.price * price_factor);
			print += ' ';
			print += to_string(k->type.weight);
			print += ' ';
			print += to_string(k->amount);
		}

		DrawString(0, val + 5, print, olc::WHITE, 2);
		val += size_of_slot;
		++k;
		++i;
	}

	if (GetKey(olc::Key::NP0).bPressed)
	{
		shift_string_left(amount, '0');
	}
	else if (GetKey(olc::Key::NP1).bPressed)
	{
		shift_string_left(amount, '1');
	}
	else if (GetKey(olc::Key::NP2).bPressed)
	{
		shift_string_left(amount, '2');
	}
	else if (GetKey(olc::Key::NP3).bPressed)
	{
		shift_string_left(amount, '3');
	}
	else if (GetKey(olc::Key::NP4).bPressed)
	{
		shift_string_left(amount, '4');
	}
	else if (GetKey(olc::Key::NP5).bPressed)
	{
		shift_string_left(amount, '5');
	}
	else if (GetKey(olc::Key::NP6).bPressed)
	{
		shift_string_left(amount, '6');
	}
	else if (GetKey(olc::Key::NP7).bPressed)
	{
		shift_string_left(amount, '7');
	}
	else if (GetKey(olc::Key::NP8).bPressed)
	{
		shift_string_left(amount, '8');
	}
	else if (GetKey(olc::Key::NP9).bPressed)
	{
		shift_string_left(amount, '9');
	}

	if (GetKey(olc::Key::K0).bPressed)
	{
		shift_string_left(amount, '0');
	}
	else if (GetKey(olc::Key::K1).bPressed)
	{
		shift_string_left(amount, '1');
	}
	else if (GetKey(olc::Key::K2).bPressed)
	{
		shift_string_left(amount, '2');
	}
	else if (GetKey(olc::Key::K3).bPressed)
	{
		shift_string_left(amount, '3');
	}
	else if (GetKey(olc::Key::K4).bPressed)
	{
		shift_string_left(amount, '4');
	}
	else if (GetKey(olc::Key::K5).bPressed)
	{
		shift_string_left(amount, '5');
	}
	else if (GetKey(olc::Key::K6).bPressed)
	{
		shift_string_left(amount, '6');
	}
	else if (GetKey(olc::Key::K7).bPressed)
	{
		shift_string_left(amount, '7');
	}
	else if (GetKey(olc::Key::K8).bPressed)
	{
		shift_string_left(amount, '8');
	}
	else if (GetKey(olc::Key::K9).bPressed)
	{
		shift_string_left(amount, '9');
	}


	if (GetKey(olc::Key::UP).bPressed)
	{
		if (icurr_slot == istart_slot)
		{
			if (istart_slot == inventory.begin())
				return true;
			while (istart_slot != inventory.begin())
			{
				--istart_slot;
				if (istart_slot->amount != 0)
				{
					icurr_slot = istart_slot;
					return true;
				}
				
			}
		}
		else
		{
			while (icurr_slot != inventory.begin())
			{
				--icurr_slot;
				if (icurr_slot->amount != 0)
				{
					return true;
				}
			}
		}
	}
	else if (GetKey(olc::Key::DOWN).bPressed)
	{
		if (icurr_slot == k)		//k is final rendered slot
		{
			if (icurr_slot == inventory.end())
				return true;
			while (icurr_slot != inventory.end())
			{
				if (icurr_slot->amount != 0)
				{
					break;
				}
				++icurr_slot;
			}
			while (istart_slot != inventory.end())
			{
				if (istart_slot->amount != 0)
				{
					break;
				}
				++istart_slot;
			}
		}
		else
		{
			while (icurr_slot != inventory.end())
			{
				++icurr_slot;
				if (icurr_slot->amount != 0)
				{
					return true;
				}
			}
		}
	}
	if (GetKey(olc::Key::LEFT).bPressed)
	{
		amount.assign("000");
		iamount_slot = amount_slot = 0;
		if (planet_over.current_merch != 0)
		{
			planet_over.current_merch--;
			--currentMerch;
			curr_slot = start_slot = currentMerch->stock.begin();
		}
	}
	else if (GetKey(olc::Key::RIGHT).bPressed)
	{
		amount.assign("000");
		iamount_slot = amount_slot = 0;
		if (planet_over.current_merch != planet_over.vendors.size())
		{
			planet_over.current_merch++;
			++currentMerch;
			curr_slot = start_slot = currentMerch->stock.begin();
		}
	}

	return true;
}
bool spaceoddity::UpdateCityBarter(float fElapsedTime)
{
	int number_of_slots = 10;
	int size_of_slot = ScreenHeight() / number_of_slots;
	int i, val, j;
	auto k = istart_slot;
	auto merch_k = start_slot;
	double price_factor;

	val = 60;
	string sOutput = currentMerch->name + "\n" + "Balance " + to_string(balance) + "\t" +
		+ "Weight " + to_string(planet_over.current_cargo_weight) 
		+ "/" + to_string(planet_over.max_cargo_weight) + "\n"
		+ " NAME  PRICE  WEIGHT  AMOUNT";
	DrawString(0, 0, sOutput, olc::WHITE, 2);
	for (i = 0; i < number_of_slots; ++i)
	{
		if (merch_k == currentMerch->stock.end())
			break;
		string print;
		price_factor = 1.0 + currentMerch->desire.at(merch_k->type.id) / 1000.0;
		if (merch_k == curr_slot)
		{
			if (merch_k->amount == 0)
			{
				if (start_slot == curr_slot)
					start_slot = curr_slot = merch_k = currentMerch->stock.erase(merch_k);
				else
					curr_slot = merch_k = currentMerch->stock.erase(merch_k);
				if (curr_slot == currentMerch->stock.end())
					continue;
			}

			print = ">";
			DrawRect(0, val, ScreenWidth(), size_of_slot);
			print += merch_k->type.name;
			print += '\t';
			print += to_string(merch_k->type.price * price_factor);
			print += '\t';
			print += to_string(merch_k->type.weight);
			print += ' ';
			print += to_string(merch_k->amount);
			print += '\n';
			print += amount;



			if (GetKey(olc::Key::ENTER).bPressed)
			{
				amount[0] -= '0';
				amount[1] -= '0';
				amount[2] -= '0';

				int num_amount = (100 * amount[0]) + (10 * amount[1]) + amount[2];
				double total_price = num_amount * price_factor *
					curr_slot->type.price;
				double total_weight = num_amount * curr_slot->type.weight;
				
				amount.assign("000");
				if (num_amount > curr_slot->amount)
					return true;
				if (total_price > balance)
					return true;
				if (total_weight + planet_over.current_cargo_weight > planet_over.max_cargo_weight)
					return true;

				curr_slot->amount -= num_amount;
				balance -= total_price;
				planet_over.current_cargo_weight += total_weight;
				inventory[curr_slot->type.id].amount += num_amount;
				re_evaluate_inv();
			}
		}
		else
		{
			if (merch_k->amount == 0)
			{
				if (start_slot == merch_k)
					start_slot = merch_k = currentMerch->stock.erase(merch_k);
				else
					merch_k = currentMerch->stock.erase(merch_k);
			}

			print = " ";
			DrawRect(0, val, ScreenWidth(), size_of_slot);
			print += merch_k->type.name;
			print += ' ';
			print += to_string(merch_k->type.price * price_factor);
			print += ' ';
			print += to_string(merch_k->type.weight);
			print += ' ';
			print += to_string(merch_k->amount);
		}

		DrawString(0, val + 5, print, olc::WHITE, 2);
		val += size_of_slot;
		++merch_k;
	}

	if (GetKey(olc::Key::NP0).bPressed)
	{
		shift_string_left(amount, '0');
	}
	else if (GetKey(olc::Key::NP1).bPressed)
	{
		shift_string_left(amount, '1');
	}
	else if (GetKey(olc::Key::NP2).bPressed)
	{
		shift_string_left(amount, '2');
	}
	else if (GetKey(olc::Key::NP3).bPressed)
	{
		shift_string_left(amount, '3');
	}
	else if (GetKey(olc::Key::NP4).bPressed)
	{
		shift_string_left(amount, '4');
	}
	else if (GetKey(olc::Key::NP5).bPressed)
	{
		shift_string_left(amount, '5');
	}
	else if (GetKey(olc::Key::NP6).bPressed)
	{
		shift_string_left(amount, '6');
	}
	else if (GetKey(olc::Key::NP7).bPressed)
	{
		shift_string_left(amount, '7');
	}
	else if (GetKey(olc::Key::NP8).bPressed)
	{
		shift_string_left(amount, '8');
	}
	else if (GetKey(olc::Key::NP9).bPressed)
	{
		shift_string_left(amount, '9');
	}

	if (GetKey(olc::Key::K0).bPressed)
	{
		shift_string_left(amount, '0');
	}
	else if (GetKey(olc::Key::K1).bPressed)
	{
		shift_string_left(amount, '1');
	}
	else if (GetKey(olc::Key::K2).bPressed)
	{
		shift_string_left(amount, '2');
	}
	else if (GetKey(olc::Key::K3).bPressed)
	{
		shift_string_left(amount, '3');
	}
	else if (GetKey(olc::Key::K4).bPressed)
	{
		shift_string_left(amount, '4');
	}
	else if (GetKey(olc::Key::K5).bPressed)
	{
		shift_string_left(amount, '5');
	}
	else if (GetKey(olc::Key::K6).bPressed)
	{
		shift_string_left(amount, '6');
	}
	else if (GetKey(olc::Key::K7).bPressed)
	{
		shift_string_left(amount, '7');
	}
	else if (GetKey(olc::Key::K8).bPressed)
	{
		shift_string_left(amount, '8');
	}
	else if (GetKey(olc::Key::K9).bPressed)
	{
		shift_string_left(amount, '9');
	}

	if (GetKey(olc::Key::UP).bPressed)
	{
		if (curr_slot == start_slot)
		{
			if (start_slot == currentMerch->stock.begin())
				return true;
			--start_slot;
			--curr_slot;
		}
		else
		{
			--curr_slot;
		}
	}
	if (GetKey(olc::Key::DOWN).bPressed)
	{
		if (curr_slot == merch_k)		//k is final rendered slot
		{
			if (curr_slot == currentMerch->stock.end())
				return true;
			++start_slot;
			++curr_slot;
		}
		else
			++curr_slot;
	}
	if (GetKey(olc::Key::LEFT).bPressed)
	{
		amount.assign("000");
		iamount_slot = amount_slot = 0;
		if (currentMerch != planet_over.vendors.begin())
		{
			planet_over.current_merch--;
			--currentMerch;
			curr_slot = start_slot = currentMerch->stock.begin();
			icurr_slot = istart_slot = inventory.begin();
		}
	}
	if (GetKey(olc::Key::RIGHT).bPressed)
	{
		amount.assign("000");
		iamount_slot = amount_slot = 0;
		if (currentMerch != planet_over.vendors.end())
		{
			if (planet_over.current_merch != planet_over.vendors.size() - 1)
			{
				planet_over.current_merch++;
				++currentMerch;
				if (currentMerch != planet_over.vendors.end())
				{
					curr_slot = start_slot = currentMerch->stock.begin();
					icurr_slot = istart_slot = inventory.begin();
				}
			}
			
			
		}
	}


	return true;
}
bool spaceoddity::UpdateCityPeople(float fElapsedTime)
{
	string sOutput = "E- RECRUIT    RIGHT- NEXT PERSON     LEFT- PREV PERSON\n";
	DrawString(0, SIZE_OF_BLOCK >> 1, sOutput, olc::WHITE, 2);

	if (GetKey(olc::Key::RIGHT).bPressed)
	{
		if (planet_over.current_peep != planet_over.peeps.end())
		{
			++planet_over.current_peep;
			
		}
	}
	else if (GetKey(olc::Key::LEFT).bPressed)
	{
		if (planet_over.current_peep != planet_over.peeps.begin())
		{
			--planet_over.current_peep;
			
		}
	}
	
	if (planet_over.current_peep == planet_over.peeps.end())
		return true;
	
	sOutput = "Name: " + planet_over.current_peep->name + "\n";
	sOutput += "Age: " + to_string(planet_over.current_peep->age) + "\n";
	sOutput += "Species: " + species_types[planet_over.current_peep->species] + "\n";
	sOutput += "Class: " + companion_class_types[planet_over.current_peep->class_type] + "\n";
	sOutput += "Level: " + to_string(planet_over.current_peep->level) + "\n";

	DrawString(0, SIZE_OF_BLOCK, sOutput, olc::WHITE, 3);
	if (GetKey(olc::Key::E).bPressed)
	{
		player->crew.push_back(*planet_over.current_peep);
		static_food_consumption++;
		static_water_consumption++;
		planet_over.current_peep = planet_over.peeps.erase(planet_over.current_peep);
	}


	return true;
}
bool spaceoddity::UpdateCityQuest(float fElapsedTime)
{
	return true;
}

void spaceoddity::updateScreen(float fElapsedTime)
{
	Clear(olc::DARK_BLUE);

	for (auto& s : _star)
	{
		Draw(s.x, s.y);
	}

	int nSectorsX = ScreenWidth() / (camera.GetWorldScale().x * SIZE_OF_BLOCK);
	int nSectorsY = ScreenHeight() / (camera.GetWorldScale().y * SIZE_OF_BLOCK);
	int mx, my;
	//save it so it doesnt change and ruin everything
	mx = GetMouseX();
	my = GetMouseY();

	olc::vf2d bmouse = { 0.0f,0.0f };
	olc::vi2d offs;


	offs.x = mx / SIZE_OF_BLOCK;
	offs.y = my / SIZE_OF_BLOCK;
	offs.x *= SIZE_OF_BLOCK;
	offs.y *= SIZE_OF_BLOCK;

	
		olc::vi2d screen_sector = { 0,0 };
		
		olc::vi2d pos = { 0,0 };

		
		for (screen_sector.x = 0; screen_sector.x < nSectorsX; screen_sector.x++)
		{
			pos.y = 0;
			for (screen_sector.y = 0; screen_sector.y < nSectorsY; screen_sector.y++)
			{
				if (space_grid)
					DrawRect(pos.x, pos.y, SIZE_OF_BLOCK, SIZE_OF_BLOCK, olc::YELLOW);

				double secx, secy;
				cStarSystem star(pos.x, pos.y, 1);

				if (star.starExists)
				{
					//TODO: check if window hides this area
					float diam;

					secx = screen_sector.x * SIZE_OF_BLOCK;
					//secx *= camera.GetWorldScale().x;

					secy = screen_sector.y * SIZE_OF_BLOCK;
					//secy *= camera.GetWorldScale().y;
					//olc::vi2d blck = { screen_sector.x * SIZE_OF_BLOCK, screen_sector.y * SIZE_OF_BLOCK };
					diam = (int)star.starDiameter;
					diam /= SIZE_OF_BLOCK;

					secx += (SIZE_OF_BLOCK >> 1);
					secy += (SIZE_OF_BLOCK >> 1);

					//draw star
					FillCircle(secx, secy, diam, star.starColour);
				}
				pos.y += SIZE_OF_BLOCK;
			}
			pos.x += SIZE_OF_BLOCK;
		}
		
		if (_dir.current_quest != _dir.quests.end())
		{
			if (_dir.current_quest->reached_chunk)
			{
				pos = _dir.current_quest->target_place;
				pos.x += SIZE_OF_BLOCK >> 1;
				pos.y += SIZE_OF_BLOCK >> 1;
				DrawCircle(pos, SIZE_OF_BLOCK >> 1, olc::GREEN);
			}
		}


	
		cStarSystem k_star_test(offs.x, offs.y);
		if (k_star_test.starExists)
		{
			offs.x += SIZE_OF_BLOCK >> 1;
			offs.y += SIZE_OF_BLOCK >> 1;
			DrawCircle(offs.x, offs.y, SIZE_OF_BLOCK, olc::YELLOW);
			if (GetMouse(0).bPressed && !engine_dead)
			{
				if (isnan<float>(backup_lookAngle))
				{
					backup_lookAngle = player->_lookAngle;
					backup_movementAngle = player->_movementAngle;
				}
				else
				{
					player->_lookAngle = backup_lookAngle;
					player->_movementAngle = backup_movementAngle;
				}

				double a, b;
				float finalDir;
				float slope;

				player->tx = offs.x;
				player->ty = offs.y;

				if (player->cord.x == player->tx)
				{
					backup_lookAngle = player->_lookAngle;
					backup_movementAngle = player->_movementAngle;
					if (player->cord.y < player->ty)
					{
						player->setDir(-90.0f);
					}
					else
					{
						player->setDir(90.0f);
					}
				}
				else if (player->cord.y == player->ty)
				{
					backup_lookAngle = player->_lookAngle;
					backup_movementAngle = player->_movementAngle;
					if (player->cord.x < player->tx)
					{
						player->setDir(0.0f);
					}
					else
					{
						player->setDir(180.0f);
					}
				}
				else
				{
					float dir;
					slope = player->cord.y - player->ty;
					slope /= (player->cord.x - player->tx);
					dir = atan2f(player->cord.y - player->ty, player->cord.x - player->tx);
					dir = toDEG(dir);

					backup_lookAngle = player->_lookAngle;
					backup_movementAngle = player->_movementAngle;
					player->setDir(dir);

					player->speedFactor[0] = -30.0f * cosf(toRAD(dir));
					player->speedFactor[1] = -30.0f * sinf(toRAD(dir));

				}

			}
		}



	drawPlayer(fElapsedTime, 0);

	
	if (space_objects.empty() == false)
	{
		std::list<pspace::space_object*>::iterator runner_space_objects;
		for (runner_space_objects = space_objects.begin(); runner_space_objects != space_objects.end(); ++runner_space_objects)
		{
			(*runner_space_objects)->draw(globalGame);
		}
	}

	//draw from back to end;
	std::list<swindow*>::reverse_iterator rk;
	for (rk = windowList.rbegin(); rk != windowList.rend(); ++rk)
	{
		//unsigned int windowrunner;
		//dfunc draww;
		//
		//draww = (*rk)->_draw;
		//
		//draww.func(draww.argnum, draww.args);//call a function this way, genius
		//
		//
		//for (windowrunner = 0; windowrunner < (*rk)->number_of_boxes; ++windowrunner)
		//{
		//	draww = (*rk)->_box[windowrunner].draw;
		//	draww.func(draww.argnum, draww.args);
		//}
		swindow* wind = *rk;
		DrawSprite(wind->getCorner().x, wind->getCorner().y, wind->sprite);
	}

	DrawString(8, 240, "Speed X = " + to_string(player->speedFactor[0]), olc::WHITE, 1);
	DrawString(8, 250, "Speed Y = " + to_string(player->speedFactor[1]), olc::WHITE, 1);
	DrawString(8, 260, "Fuel = " + to_string(spaceFuel), olc::WHITE, 1);
	DrawString(8, 270, "Food = " + to_string(foodSupply));
	DrawString(8, 280, "Water = " + to_string(waterSupply));

	

	/*

	int nSectorsX = ScreenWidth() / (_scale * SIZE_OF_BLOCK);
	int nSectorsY = ScreenHeight() / (_scale * SIZE_OF_BLOCK);

	int mx, my;
	//save it so it doesnt change and ruin everything
	mx = GetMouseX();
	my = GetMouseY();




	olc::vi2d mouse = { GetMouseX() / SIZE_OF_BLOCK, GetMouseY() / SIZE_OF_BLOCK };
	olc::vi2d galaxy_mouse;
	olc::vi2d screen_sector = { 0,0 };

	mouse.x /= _scale;
	mouse.y /= _scale;

	galaxy_mouse = mouse + vGalaxyOffset;

	for (screen_sector.x = 0; screen_sector.x < nSectorsX; ++screen_sector.x)
		for (screen_sector.y = 0; screen_sector.y < nSectorsY; ++screen_sector.y)
		{
			float secx, secy;
			secx = screen_sector.x + (uint32_t)vGalaxyOffset.x;

			secy = screen_sector.y + (uint32_t)vGalaxyOffset.y;

			cStarSystem star(secx, secy, 1);

			secx *= _scale;
			secy *= _scale;
			if (star.starExists)
			{
				//TODO: check if window hides this area
				float diam;

				secx = screen_sector.x * SIZE_OF_BLOCK + 8;
				secx *= _scale;
				secy = screen_sector.y * SIZE_OF_BLOCK + 8;
				secy *= _scale;

				diam = (int)star.starDiameter * _scale;
				diam /= SIZE_OF_BLOCK;

				//draw star
				FillCircle(secx, secy, diam, star.starColour);


				std::list<halfPlanet>::iterator k;
				for (k = star.hplanets.begin(); k != star.hplanets.end(); ++k)
				{
					f2 offset, loff;
					diam = (k->radius * _scale / 10.0f);



					offset.x = secx;
					offset.y = secy - (10 * double(_scale) + k->distance * _scale / SIZE_OF_BLOCK);
					loff = rotateAt(offset, (k->offset + orbit_offset), secx, secy);
					FillCircle(loff.x, loff.y, diam, k->color);

				}

				//change player force vectors

				if ((mouse.x == screen_sector.x) && (mouse.y == screen_sector.y))
				{
					DrawCircle(secx, secy,
						20 * _scale, olc::YELLOW);
					DrawString(8, 320, to_string(star.hplanets.size()));
				}
			}

		}

	drawPlayer(fElapsedTime, tick);



	//only for debugging for now
	DrawString(8, 240, "X = " + to_string(mx), olc::WHITE, 1);
	DrawString(8, 250, "Y = " + to_string(my), olc::WHITE, 1);
	DrawString(8, 260, "PX = " + to_string(player->x), olc::WHITE, 1);
	DrawString(8, 270, "PY = " + to_string(player->y), olc::WHITE, 1);
	DrawString(8, 280, "horspeed = " + to_string(player->getSpeed(0)), olc::WHITE, 1);
	DrawString(8, 290, "verspeed = " + to_string(player->getSpeed(1)), olc::WHITE, 1);
	DrawString(8, 300, "Scale = " + to_string(_scale), olc::WHITE, 1);
	//DrawString(8, 320, to_string(_scale* SIZE_OF_BLOCK));

	//Draw Sprite
	if (picture != -1)
	{
		DrawSprite({ 0,0 }, pics.at(picture));//dirty
	}



	//draw from back to end;
	std::list<swindow*>::reverse_iterator rk;

	for (rk = windowList.rbegin(); rk != windowList.rend(); ++rk)
	{
		unsigned int windowrunner;
		dfunc draww;

		draww = (*rk)->_draw;

		draww.func(draww.argnum, draww.args);//call a function this way, genius


		for (windowrunner = 0; windowrunner < (*rk)->number_of_boxes; ++windowrunner)
		{
			draww = (*rk)->_box[windowrunner].draw;
			draww.func(draww.argnum, draww.args);
		}


	}

	*/

	return;
	
}

void spaceoddity::generateSystem()
{
	return;
}
bool spaceoddity::generateNewGame()
{
	 
	


	return false;
}

void spaceoddity::execute_event(decimal id)
{
	if (id == 0)	return;
	int val;
	pspace::warzone* war_zone;
	olc::vi2d pos;
	pspace::epack* pack;
	pspace::black_hole* blck_ptr;
	std::vector<enemy*>::iterator enem_itr;
	enemy* enem;
	pspace::astroid* ast;

	switch (id)
	{
	case director_event::INCREASE_PLAYER_LEVEL:
		cout << "Good job you did a delivery" << endl;
		player_level++;
		break;
	case director_event::SPAWN_BLACK_HOLE:
		blck_ptr = new pspace::black_hole(player);
		if (blck_ptr == nullptr)
			return;
		space_objects.push_back(blck_ptr);
		break;
	case director_event::ACCIDENT_MONEY_TRANFER:
		balance += big_alternate_rndInt128(0, 2000 * player_level);
		break;
	case director_event::MONEY_ROBBED:
		balance -= std::min(balance, big_alternate_rndInt128(0, 200 * player_level));
		break;
	case director_event::EPACK_COLLIDE:
		gamestate = pspace::gamestates::COMBAT_MODE;
		pack = dynamic_cast<pspace::epack*>(* objects_itr);
		for (enem_itr = pack->members.begin(); enem_itr != pack->members.end(); ++enem_itr)
		{
			enemy_list.push_back(*enem_itr);
		}
		pack->members.clear();
		delete* objects_itr;
		outside_cord = player->cord;
		player->cord = { SCREEN_WIDTH >> 1, SCREEN_HEIGHT >> 1 };
		objects_itr = space_objects.erase(objects_itr);
		break;
	case director_event::SPAWN_WHALE_PACK:
		pack = new pspace::epack(player);
		if (pack == nullptr)
			return;
		pack->cord = player->cord;
		val = big_alternate_rndInt128(0, 5);
		pack->cord.x += (val - 5) * SIZE_OF_BLOCK;
		val = big_alternate_rndInt128(0, 5);
		pack->cord.y += (val - 5) * SIZE_OF_BLOCK;
		val = 1 + big_alternate_rndInt128(0, 5);
		while (val-- != 0)
		{
			enem = new killer_whale(big_alternate_rndInt128(0, SCREEN_WIDTH), SCREEN_HEIGHT >> 2
				, player);
			if (enem == nullptr)
			{
				delete pack;
				return;
			}
			
			pack->members.push_back(enem);
		}
		space_objects.push_back(pack);
		break;
	case director_event::SPAWN_ASTROID:
		ast = new pspace::astroid(player);
		if (ast == nullptr)
			return;
		space_objects.push_back(ast);
		break;
	case director_event::ASTROID_COLLIDE:
		gamestate = pspace::gamestates::GAME_OVER;
		break;
	case director_event::BLACK_HOLE_COLLIDE:
		gamestate = pspace::gamestates::GAME_OVER;
		break;
	case director_event::START_SPACE_BATTLE:
		
		pos.x = SIZE_OF_BLOCK * big_alternate_rndInt128(0, SCREEN_WIDTH / SIZE_OF_BLOCK);
		pos.y = SIZE_OF_BLOCK * big_alternate_rndInt128(0, SCREEN_HEIGHT / SIZE_OF_BLOCK);
		war_zone = new pspace::warzone(player, pos);
		if (war_zone == nullptr)
			return;
		war_zone->rePosition();
		space_objects.push_back(war_zone);
		break;
	case director_event::WARZONE_COLLIDE:
		gamestate = pspace::gamestates::GAME_OVER;
		break;
	case director_event::DELIVER_QUEST_FAIL:
		gamestate = pspace::gamestates::GAME_OVER;
		break;
	default:
		return;
	}

}


olc::Pixel raycastv::SelectSceneryPixel(const int tile_x, const int tile_y, const olc::rcw::Engine::CellSide side, const float sample_x, const float sample_y, const float distance)
{
	olc::Pixel p;

	
	if (side == olc::rcw::Engine::CellSide::Bottom)
		p = olc::DARK_CYAN;
	else if (side == olc::rcw::Engine::CellSide::East)
		p = olc::RED;
	else if (side == olc::rcw::Engine::CellSide::West)
		p = olc::GREEN;
	else if (side == olc::rcw::Engine::CellSide::North)
		p = olc::YELLOW;
	else if (side == olc::rcw::Engine::CellSide::South)
		p = olc::WHITE;
	else
		p = olc::BLACK;
	

	return p;
}
bool raycastv::IsLocationSolid(const float tile_x, const float tile_y)
{
	if ((tile_x >= mdim.x) || (tile_x < 0.0f))
		return true;
	if ((tile_y >= mdim.y) || (tile_y < 0.0f))
		return true;
	return false;

}

decimal object::updateState(float fElapsedTime)
{
	float cpy = fElapsedTime;

	if (stateTime <= cpy)
		while(stateTime <= cpy)
		{
			stateTime = whaleState[state1].ctime;
			//whaleState[state1].time = whaleState[state1].ctime;
			if (*(whaleState[state1].func) != NULL)
				whaleState[state1].func(first_p, second_p);
			state2 = state1;
			state1 = whaleState[state1].nextState;
			cpy -= whaleState[state1].time;			
		}
	else
	{
		stateTime -= fElapsedTime;
	}
	sprite_id = whaleState[state1].sspriteID;
	return whaleState[state1].sspriteID;
}

void object::setState(decimal state)
{
	state1 = state;
	this->stateTime = whaleState[state].ctime;
}
//generic actor funtions

void A_look(void* thee)
{
	
	return;
}
void A_speak(void* thee, void* world)
{

	return;
}

void enemy::setState(decimal state)
{
	state1 = state;
	this->stateTime = whaleState[state].ctime;
	this->bmove = whaleState[state].flags & eBits::bENEMY_MOVE;
}

void flip(olc::Sprite* spr, olc::vi2d og, olc::vi2d size)
{
	if (spr == NULL)
		return;

	olc::vi2d cord;
	olc::vi2d temp;

	for (cord.y = og.y; cord.y < (og.y + size.y); ++cord.y)
	{
		temp.y = cord.y;
		temp.x = (og.x + size.x);
		for (cord.x = og.x; cord.x < (og.x + (size.x >> 1)); ++cord.x)
		{
			olc::Pixel p = spr->GetPixel(cord);
			olc::Pixel p2 = spr->GetPixel(temp);
			spr->SetPixel(temp, p);
			spr->SetPixel(cord, p2);
			--temp.x;
		}
	}


}
void myDrawPSprite(olc::Sprite* sprite, olc::GFX2D::Transform2D& transform, bool flip)
{
	if (sprite == nullptr)
		return;

	// Work out bounding rectangle of sprite
	float ex, ey;
	float sx, sy;
	float px, py;

	transform.Forward(0.0f, 0.0f, sx, sy);
	px = sx; py = sy;
	sx = std::min(sx, px); sy = std::min(sy, py);
	ex = std::max(ex, px); ey = std::max(ey, py);

	transform.Forward((float)(sprite->width), (float)(sprite->height), px, py);
	sx = std::min(sx, px); sy = std::min(sy, py);
	ex = std::max(ex, px); ey = std::max(ey, py);

	transform.Forward(float(0.0f), (float)(sprite->height), px, py);
	sx = std::min(sx, px); sy = std::min(sy, py);
	ex = std::max(ex, px); ey = std::max(ey, py);

	transform.Forward((float)(sprite->width), float(0.0f), px, py);
	sx = std::min(sx, px); sy = std::min(sy, py);
	ex = std::max(ex, px); ey = std::max(ey, py);

	// Perform inversion of transform if required
	transform.Invert();

	if (ex < sx)
		std::swap(ex, sx);
	if (ey < sy)
		std::swap(ey, sy);

	if (flip == true)
	{
		for (float i = sx; i < ex; i++)
		{
			for (float j = sy; j < ey; j++)
			{
				float ox, oy;
				transform.Backward(ex - i, j, ox, oy);
				globalGame->Draw((int32_t)i, (int32_t)j, sprite->GetPixel((int32_t)(ox + 0.5f), (int32_t)(oy + 0.5f)));
			}
		}

		return;
	}


	// Iterate through render space, and sample Sprite from suitable texel location
	for (float i = sx; i < ex; i++)
	{
		for (float j = sy; j < ey; j++)
		{
			float ox, oy;
			transform.Backward(i, j, ox, oy);
			globalGame->Draw((int32_t)i, (int32_t)j, sprite->GetPixel((int32_t)(ox + 0.5f), (int32_t)(oy + 0.5f)));
		}
	}
}

void killer_whale::draw(olc::PixelGameEngine* game)
{
	ssprite pspr = ssprites[sprite_id];
	globalGame->DrawPartialSprite(cord,
		globalGame->renderables.at(pspr.spriteID)->Sprite(), pspr.state.x, pspr.state.y,
		localScale, (cord.x < globalGame->player->cord.x));
	

	return;
}
void space_pirate_ship::draw(olc::PixelGameEngine* game)
{
	olc::vi2d corners[3];
	corners[0] = globalGame->camera.WorldToScreen({ cord.x + sides[0].x, cord.y + sides[0].y });
	corners[1] = globalGame->camera.WorldToScreen({ cord.x + sides[1].x, cord.y + sides[1].y });
	corners[2] = globalGame->camera.WorldToScreen({ cord.x + sides[2].x, cord.y + sides[2].y });

	globalGame->FillTriangle(corners[0], corners[1], corners[2], olc::RED);
}
