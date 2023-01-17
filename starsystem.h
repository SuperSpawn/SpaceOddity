#pragma once
#include "spaceship.h"
#define PLANET_COLOR_ARRAY_SIZE 5
#define STAR_COLOR_ARRAY_SIZE 10
#define WARZONE_RADIUS 12
#define MAX_STAR_SYSTEM_PLANETS 7

#define SPEED_OF_PACK 10.0f
#define SPEED_OF_ASTROID 10.0f
#define SPEED_OF_SYNDICATE_PATROL 50.0f
#define BLACK_HOLE_PULL_FORCE 10.0f


constexpr unsigned int g_starColours[PLANET_COLOR_ARRAY_SIZE] =
{
	0xffa3ffff			//light yellow		desert
	, 0xff9fafff			//beige
	, 0xff415eff			//orange			desert2
	, 0xff28199e			//red				lava
	, 0xffdaa520			//light dark blue	ocean
};

constexpr unsigned int g_planetColours[] = 
{
	0xff33ff33				//green				fauna
	, 0xffffffff			//white				snow
	, 0xffa3ffff			//light yellow		desert
	, 0xffffc8c8			//light blue		ice
	, 0xff9fafff			//beige				???
	, 0xff415eff			//orange			desert2
	, 0xff28199d			//red				lava
	, 0xffff3399			//purple			crystal
	, 0xfff08080			//light purple		???
	, 0xffdaa520			//light dark blue	ocean
};

namespace pspace
{
#define G_DRUG_NAME_FACTORS_SIZE 33
	const string g_drug_name_factors[] =
	{
		"ne", "zen", "nez", "da", "add", "zoid", "an", "ad", "am", "mma", "fi", "ez"
		, "led", "loid", "we", "ald", "hue", "fri", "re", "asm", "not", "xiao", "xi", "exe"
		, "que", "qu", "a", "b", "d", "e", "xin", "xian", "me"
	};

	

	struct city
	{
		olc::vi2d pos;
		decimal population;

		double water_pollution;
		double air_pollution;
		double population_density;
		double temprature;

		bool bExists;

		//std::vector<merchant> vendors;

		city(decimal idx, decimal idy)
		{
			nLehmer128 = idx;
			(nLehmer128 <<= 64) += idy;
			bExists = big_alternate_rndInt128(0, 600) <= 5;
			if (!bExists)
				return;
			pos.x = idx; pos.y = idy;
			population = big_alternate_rndInt128(0, 400000000);
			water_pollution = big_alternate_rndInt128(0, 10000) / 100.0;
			air_pollution = big_alternate_rndInt128(0, 10000) / 100.0;
			population_density = big_alternate_rndInt128(0, 100000000);
			temprature = big_alternate_rndInt128(0, 50000) / 100.0;
		}

	};

	struct space_object
	{
		olc::vf2d cord;
		olc::vf2d& target;

		float speed[2];
		float _angle;
		bool bKill;

		space_object(object* _target) : target(_target->cord)
		{
			speed[0] = speed[1] = 0.0f;
			_angle = 0.0f;
			bKill = false;
		}



		virtual void draw(olc::PixelGameEngine* game) = 0;
		virtual uint32_t perFrame(float fElapsedtime) = 0;

		virtual bool reachedTarget()
		{
			olc::vi2d current_tile, target_tile;
			current_tile = cord;
			target_tile = target;

			current_tile /= SIZE_OF_BLOCK;
			target_tile /= SIZE_OF_BLOCK;
			current_tile *= SIZE_OF_BLOCK;
			target_tile *= SIZE_OF_BLOCK;

			return current_tile == target_tile;
		}

		virtual ~space_object()
		{

		}
	};
	struct epack : public space_object
	{
		std::vector<enemy*> members;
		olc::Pixel color;
		float living_time;

		epack(object* _target) : space_object(_target)
		{
			living_time = 10.0f;
		}

		virtual void draw(olc::PixelGameEngine* game)
		{
			game->DrawCircle(cord, SIZE_OF_BLOCK >> 1, color);
			return;
		}
		virtual uint32_t perFrame(float fElapsedtime)
		{
			double a, b;
			float finalDir;
			float slope;

			fElapsedtime = std::max(fElapsedtime, -fElapsedtime);

			if (cord.x == target.x)
			{
				if (cord.y < target.y)
				{
					_angle = -90.0f;
				}
				else
				{
					_angle = 90.0f;
				}
			}
			else if (cord.y == target.y)
			{
				if (cord.x < target.x)
				{
					_angle = 0;
				}
				else
				{
					_angle = 180.0f;
				}
			}
			else
			{
				float dir;
				slope = cord.y - target.y;
				slope /= (cord.x - target.x);
				dir = atan2f(cord.y - target.y, cord.x - target.x);
				dir = toDEG(dir);

				_angle = dir;

				
			}

			speed[0] = -SPEED_OF_PACK * cosf(toRAD(_angle));
			speed[1] = -SPEED_OF_PACK * sinf(toRAD(_angle));

			cord.x += speed[0] * fElapsedtime;
			cord.y += speed[1] * fElapsedtime;

			living_time -= fElapsedtime;
			if (living_time <= 0.0f)
			{
				bKill = true;
			}
			if (reachedTarget())
				return director_event::EPACK_COLLIDE;
			return 0;
		}

		virtual ~epack()
		{
			std::vector<enemy*>::iterator k;
			for (k = members.begin(); k != members.end(); ++k) delete* k;
		}
	};
	struct astroid : public space_object
	{
		uint32_t radius;
		astroid(object* _target) : space_object(_target)
		{
			radius = big_alternate_rndInt128(7, 70);

			double a, b;
			float finalDir;
			float slope;

			int mode = big_alternate_rndInt128(0, 5);
			if (mode == 0)
			{
				cord.x = 0.0f;
				cord.y = big_alternate_rndInt128(0, SCREEN_HEIGHT);
			}
			else if (mode == 1)
			{
				cord.y = 0.0f;
				cord.x = big_alternate_rndInt128(0, SCREEN_WIDTH);
			}
			else if (mode == 2)
			{
				cord.x = SCREEN_WIDTH;
				cord.y = big_alternate_rndInt128(0, SCREEN_HEIGHT);
			}
			else
			{
				cord.y = SCREEN_HEIGHT;
				cord.x = big_alternate_rndInt128(0, SCREEN_WIDTH);
			}

			if (cord.x == target.x)
			{
				if (cord.y < target.y)
				{
					_angle = -90.0f;
				}
				else
				{
					_angle = 90.0f;
				}
			}
			else if (cord.y == target.y)
			{
				if (cord.x < target.x)
				{
					_angle = 0;
				}
				else
				{
					_angle = 180.0f;
				}
			}
			else
			{
				float dir;
				slope = cord.y - target.y;
				slope /= (cord.x - target.x);
				dir = atan2f(cord.y - target.y, cord.x - target.x);
				dir = toDEG(dir);

				_angle = dir;


			}

			speed[0] = -SPEED_OF_ASTROID * cosf(toRAD(_angle));
			speed[1] = -SPEED_OF_ASTROID * sinf(toRAD(_angle));
		}

		virtual void draw(olc::PixelGameEngine* game)
		{
			olc::Pixel brown(165, 42, 42);
			game->FillCircle(cord, radius, brown);
		}
		virtual uint32_t perFrame(float fElapsedtime)
		{
			if ((cord.x < 0.0f) || (cord.y < 0.0f) || (cord.x > SCREEN_WIDTH) || (cord.y > SCREEN_HEIGHT))
			{
				bKill = true;
				return 0;
			}
			cord.x += speed[0] * fElapsedtime;
			cord.y += speed[1] * fElapsedtime;

			if (reachedTarget())
				return director_event::ASTROID_COLLIDE;
			return 0;
		}

		virtual ~astroid()
		{

		}
	};
	struct black_hole : public space_object
	{
		float pull_force;
		float hawking_radiation;

		black_hole(object* _target) : space_object(_target)
		{
			pull_force = BLACK_HOLE_PULL_FORCE;
			hawking_radiation = 30.0f;
		}
		
		virtual void draw(olc::PixelGameEngine* game)
		{
			game->FillCircle(cord, SIZE_OF_BLOCK >> 1, olc::BLACK);
		}
		virtual uint32_t perFrame(float fElapsedtime)
		{
			olc::vf2d dist;
			float total_dist;
			hawking_radiation -= fElapsedtime;
			if (hawking_radiation <= 0.0f)
			{
				bKill = true;
				return 0;
			}

			dist.x = cord.x - target.x;
			dist.y = cord.y - target.y;

			total_dist = dist.x * dist.x + dist.y * dist.y;
			total_dist = Q_rsqrt(total_dist);		//quake 3 plagarism

			if(dist.x < 0.0f)
				target.x -= (pull_force / total_dist) * fElapsedtime;
			else
				target.x += (pull_force / total_dist) * fElapsedtime;
			if (dist.y < 0.0f)
				target.y -= (pull_force / total_dist) * fElapsedtime;
			else
				target.y += (pull_force / total_dist) * fElapsedtime;
			if (reachedTarget())
				return director_event::BLACK_HOLE_COLLIDE;
			return 0;
		}

		virtual ~black_hole()
		{

		}
	};
	struct warzone : public space_object
	{
		olc::vi2d sSlot;
		float living_time;
		int re_pos_tick;
		warzone(object* _target, olc::vi2d pos) : space_object(_target)
		{
			sSlot = pos;
			
			living_time = 15.0f;
			re_pos_tick = CLOCKS_PER_SEC << 1;
		}
		virtual void draw(olc::PixelGameEngine* game)
		{
			game->DrawCircle(cord, SIZE_OF_BLOCK >> 1, olc::RED);
		}
		virtual uint32_t perFrame(float fElapsedtime)
		{
			if (re_pos_tick-- == 0)	//special value case
			{
				re_pos_tick = CLOCKS_PER_SEC << 1;
				rePosition();	//for repositioning the warzone
			}
			living_time -= fElapsedtime;
			if (living_time <= 0.0f)
			{
				bKill = true;
				return 0;
			}

			if (reachedTarget())
				return director_event::WARZONE_COLLIDE;
			return 0;
		}

		void rePosition();
		virtual bool reachedTarget()
		{
			olc::vi2d dist;
			dist.x = target.x - cord.x;
			dist.y = target.y - cord.y;
			uint32_t totalDist = (dist.x * dist.x) + (dist.y * dist.y);

			if (totalDist <= WARZONE_RADIUS * WARZONE_RADIUS)
				return true;
			return false;
		}
	};

	enum special_diseases
	{
		DISEASE_STARVE = 0
		, DISEASE_THIRST
		, DISEASE_TIREDNESS
		, DISEASE_CUSTOM1
		, DISEASE_CUSTOM2
		, DISEASE_CUSTOM3
		, DISEASE_CUSTOM4
		, DISEASE_CUSTOM5
		, DISEASE_CUSTOM6
		, DISEASE_CUSTOM7
		, DISEASE_CUSTOM8
		, DISEASE_CUSTOM9
		, DISEASE_CUSTOM10
		, DISEASE_CUSTOM11
		, NUMBER_OF_DISEASES
	};

	class disease
	{
	public:
		string name;
		uint32_t level_to_detect, level_to_cure;
		uint32_t t_minutes;
		double t_second;
		bool detected;
		bool bActive;

		disease();
		disease(uint32_t dificulty, decimal id);
	};
	
}




struct sMoon
{
	float radius = 10;
	pspace::fscaled mass = { 4.02, 22 };
};
struct halfPlanet
{
	unsigned int color = 0;
	double distance = 0.0;
	double radius = 30.0;
	double offset = 0.0f;
	
};

struct sPlanet : public halfPlanet
{
	double foliage = 0.0;
	double minerals = 0.0;
	double water = 0.0;
	double gases = 0.0;
	double temperature = 0.0;
	decimal population = 0.0;
	
	std::unordered_map<uint32_t, double> exports, imports;
	//functions
	
};

class solarsystem
{
protected:
	byte number_planet;
	sPlanet** _system;
	bool destroyPlanetsToo;//default set to false so the planets still exist after destruction of
										//system
public:
	solarsystem(const byte& planetNum = 0, const bool& destroyPlanets = false);
	solarsystem(const solarsystem& copy);
	
	solarsystem& operator=(const solarsystem& other);
	
	//adds planet by value
	sPlanet* addPlanet(const sPlanet& planet);
	
	//adds planet by refrence/address
	sPlanet* addPlanet(sPlanet* planet);

	//adds an array of planets
	sPlanet* addPlanets(sPlanet* planets);

	//gets planet
	sPlanet* getPlanet(const byte& index);

	//calculate pull force
	const pspace::fscaled& calcPullForce(const pspace::fscaled& dist);

	/*comparing addresses is alot faster than comparing
	a dozen doubles and less prone to selecting 2 planet with the same values*/
	void destroyPlanet(sPlanet* planet);
	void destroyPlanet(const byte& index);

	~solarsystem();
};


class cStarSystem
{
public:
	bool starExists = false;
	bool can_hold_quest = false;

	double starDiameter = 0.0f;
	cord2<decimal> pos;
	std::list<sPlanet> planets;
	std::list<halfPlanet> hplanets;
	olc::Pixel starColour = olc::WHITE;

	olc::vf2d cord;

	cStarSystem(uint64_t x, uint64_t y, int bGenerateFullSystem = 0)
	{
		//sLehmer = (superfloat(decimal(x)) << 32) | (superfloat(decimal(y)));
		pos.x = x;
		pos.y = y;
		cord.x = 0.0f;
		cord.y = 0.0f;

		nLehmer128 = (((x) << 32) | y);
		//nLehmer = (x & 0xffff) << 16 | (y & 0xffff);
		decimal ren_val = big_alternate_rndInt128(0, 1000);
		starExists = (ren_val < 20);
		if (!starExists)
			return;
		can_hold_quest = (ren_val < 10);
		starDiameter = big_alternate_rndInt128(100, 300);
		starColour.n = g_starColours[big_alternate_rndInt128(0, PLANET_COLOR_ARRAY_SIZE)];

		double d;
		int num, i;
		double off;
		d = big_alternate_rndInt128(30, 150);//distance from star
		num = big_alternate_rndInt128(1, MAX_STAR_SYSTEM_PLANETS);//number of planets
		off = big_alternate_rndInt128(0, 100);

		if (bGenerateFullSystem == 0)
			return;
		if (bGenerateFullSystem == 1)
		{
			for (i = 0; i < num; ++i)
			{
				halfPlanet p;

				p.color = g_planetColours[big_alternate_rndInt128(0, PLANET_COLOR_ARRAY_SIZE)];
				p.offset = off;
				off += rndDouble128(15.0f, 30.0f);
				p.distance = d;
				d += rndDouble128(20.0, 200.0);
				p.radius = rndDouble128(8.0, 20.0);

				hplanets.push_back(p);
			}


			return;
		}


		int jump_dist = SCREEN_WIDTH / num;
		off += starDiameter * 2;
		for (i = 0; i < num; ++i)
		{
			sPlanet p;
			p.distance = d;
			d += big_alternate_rndInt128(20, 200);
			p.radius = big_alternate_rndInt128(20, 40);
			p.temperature = big_alternate_rndInt128(0, 300);
			p.population = big_alternate_rndInt128(0, 20000000000);
			p.color = g_planetColours[big_alternate_rndInt128(0, PLANET_COLOR_ARRAY_SIZE)];
			p.offset = off;
			off += jump_dist + p.radius;
			planets.push_back(p);
		}

	}


	~cStarSystem()
	{
		planets.clear();
		hplanets.clear();
	}
};
