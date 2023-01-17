#pragma once
#include "species.h"
//#define toRAD(a) ((a) * PI / 180.0f)
//#define toDEG(a) ((a) * 180.0f / PI)





class spaceship: public object 
{
	string _name; 

	unsigned short crew_size;

	unsigned short faces;

	dfunc drawfunc;		//pointer to draw function
	void accelerate(const float& fix);	
	void deccelerate(const float& fix); 

public:
	//TODO: move to private later
	//pspace::dunit<3000> fuel;
	pspace::dunit pfuel;

	float tx, ty;
	
	//target
	bool onJourney;
	f2 _sides[3];

	std::vector<pspace::companion> crew;

	spaceship(const string& name, float sx, float sy, unsigned short sides, float sr, const dfunc& draw = nillfunc);
	/*
	const float& getDir();
	void adjustDir(const float& angle);//change direction of ship
	void setDir(const float& angle);
	*/
	const float& getSpeed(byte index);
	const bool& reachedTarget(const float& errorx = 0, const float& errory = 0);

	void setTarget(const float& tarx, const float& tary);
	void move(float fix);
	
	void rotate(float rotateby, float rx, float ry);

	void acivateEngine(float fix);
	void slowDown(float fix);
	void spaceBreak(float fix);
	//translate
	virtual void translatex(const float& translate = 0);
	virtual void translatey(const float& translate = 0);

	virtual void translate(const float& sx = 0, const float& sy = 0);
	virtual void translate(const f2& sh);
	virtual decimal type()
	{
		return 1;
	}

	//virtual void flush(const f2& point);
	virtual bool pcheckCollide(olc::Sprite* spr);
	virtual bool checkCollide(olc::vf2d upperLeft, olc::vf2d bottomRight);

	void pullTowards(const f2& origin, const float& acc);
	void pullTowards(const float& ox, const float& oy, const float& acc);

	//G (m1* m2) / r^2

	friend class spaceoddity;

	~spaceship();
};

namespace pspace
{
	class projectile : public object
	{
	public:
		bool bKill;
		olc::vf2d start_pos;
		olc::vi2d living_space;

		virtual decimal type();

		projectile(olc::vf2d _pos);
		virtual ~projectile();
	};

	struct weapon
	{
		string name;
		uint32_t level, damage, max_ammo, current_ammo, id, speed;
		bool bCooldown;
		float coolDown;

		
	};


};