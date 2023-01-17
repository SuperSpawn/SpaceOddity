#include "spaceship.h"


//spaceship::spaceship(const string& name, const float& sx, const float& sy, const unsigned short& sides, const float& sr)

unsigned long long int num_ships = 0;

spaceship::spaceship(const string& name, float sx = 0, float sy = 0, unsigned short sides = 1, float sr = 10, const dfunc& draw)
{
	if (name == "F-")
		_name = "F-" + std::to_string(num_ships++);
	else
		_name = name;

	
	r = sr;
	faces = 3;
	
	onJourney = false;
	
	state1 = state2 = 0;

	drawfunc = draw;

	cord.x = sx;//galaxycoord is useless for now
	cord.y = sy;
	r = sr;
	faces = sides;

	localScale = 1.0f;
	tx = ty = -1.0f;
	
	speedFactor[0] = 0;
	speedFactor[1] = 0;
	_terminalSpeed = 299792458.0f;//speed of light
	speedFactor[2] = 5.0f;//acceleration TODO: change it later
	_mass = { 1.0f, 6};
	onJourney = false;
	crew_size = 0;//the player
	
	

	//_fuel = { 1.0, 6 };

	setDir(-90.0f);

}




void spaceship::accelerate(const float& fix)
{
	float acc = speedFactor[2] * fix;
	speedFactor[0] += acc;
	speedFactor[1] += acc;
	return;
}

void spaceship::deccelerate(const float& fix)
{
	float dec = -speedFactor[2] * fix;
	speedFactor[0] += dec;
	speedFactor[1] += dec;
	return;
}



const float& spaceship::getSpeed(byte index)
{
	return speedFactor[index % 3];
}

const bool& spaceship::reachedTarget(const float& errorx, const float& errory)
{
	if (diff(cord.x, tx) <= errorx)
		if (diff(cord.y, ty) <= errory)
			return true;
	return false;
}


void spaceship::setTarget(const float& tarx, const float& tary)
{

	return;
}

void spaceship::move(float fix)
{

	cord.x += (speedFactor[0] * fix);
	cord.y += (speedFactor[1] * fix);

	return;
}

void spaceship::rotate(float rotateby, float rx = 0, float ry = 0)
{
	unsigned short i = 0;
	float _sink, _cosk;

	if (_sides == NULL)
		return;//circles don't rotate

	
	adjustDir(rotateby);
	//_lookAngle += rotateby;
	
	_sink = sinf(toRAD(rotateby));
	_cosk = cosf(toRAD(rotateby));


	_sides[0].x = (_sides[0].x * _cosk) - (_sides[0].y * _sink);
	_sides[0].y = (_sides[0].x * _sink) + (_sides[0].y * _cosk);
	_sides[1].x = (_sides[1].x * _cosk) - (_sides[1].y * _sink);
	_sides[1].y = (_sides[1].x * _sink) + (_sides[1].y * _cosk);
	_sides[2].x = (_sides[2].x * _cosk) - (_sides[2].y * _sink);
	_sides[2].y = (_sides[2].x * _sink) + (_sides[2].y * _cosk);

	return;
}


void spaceship::acivateEngine(float fix)
{
	float da;

	da = (speedFactor[2] * fix);

	speedFactor[0] += (cosval * da);//mycosf2 skips private case checks
	speedFactor[1] += (sinval * da);//same with mysin2

	return;
}
void spaceship::slowDown(float fix)
{
	float da;

	da = (speedFactor[2] * fix);

	speedFactor[0] -= (cosval * da);//mycosf2 skips private case checks
	speedFactor[1] -= (sinval * da);//same with mysin2

	return;
}
void spaceship::spaceBreak(float fix)
{
	float da = speedFactor[2] * fix;
	if (speedFactor[0] != 0.0f)
	{
		speedFactor[0] -= (cosval * da);
		if (speedFactor[0] <= 0.0f)
			speedFactor[0] = 0.0f;
	}
	if (speedFactor[1] != 0.0f)
	{
		speedFactor[1] -= (sinval * da);
		if (speedFactor[1] <= 0.0f)
			speedFactor[1] = 0.0f;
	}
	return;
}

void spaceship::translatex(const float& translate)
{
	unsigned short i;
	if (translate == 0)
		return;
	cord.x += translate;
	tx += translate;
	
	/*
	for (i = 0; i < faces; ++i)
		_sides[i].x += translate;
	*/

	return;
}

void spaceship::translatey(const float& translate)
{
	unsigned short i;
	if (translate == 0)
		return;
	cord.y += translate;
	ty += translate;
	
	/*
	for (i = 0; i < faces; ++i)
	{
		_sides[i].y += translate;
	}
	*/


	return;
}


void spaceship::translate(const float& sx, const float& sy)
{
	translatex(sx);
	translatey(sy);

	return;
}

void spaceship::translate(const f2& sh)
{
	translatex(sh.x);
	translatey(sh.y);

	return;
}

bool spaceship::pcheckCollide(olc::Sprite* spr)
{
	return false;
}

bool spaceship::checkCollide(olc::vf2d upperLeft, olc::vf2d bottomRight)
{
	int i;
	for (i = 0; i < 3; ++i)
	{
		f2 curr = _sides[i];

		if ((curr.x < upperLeft.x) || (curr.x > bottomRight.x))
			continue;
		if ((curr.y < upperLeft.y) || (curr.y > bottomRight.y))
			continue;
		return true;
	}
	return false;
}

spaceship::~spaceship()
{
	
	//delete[] _sides;
}

decimal pspace::projectile::type()
{
	return 0;
}

pspace::projectile::projectile(olc::vf2d _pos)
{
	cord = _pos;
	start_pos = _pos;
	bKill = false;
}

pspace::projectile::~projectile()
{
}
