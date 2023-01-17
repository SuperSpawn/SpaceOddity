#include "enemy.h"


enemy::~enemy()
{

}






killer_whale::killer_whale(float x, float y, object* _target)
{
	this->i = 0;
	this->j = 0;

	//dir = 0; //left

	cord.x = x;
	cord.y = y;

	bmove = true;


	hpov = 100.0f;
	vpov = 80.0f;

	width = 100;
	height = 30;

	target = _target;
	previousTarget = NULL;
	first_p = this;
	second_p = NULL;

	reactionTime = 0.5f + rndInt(0, 5);

	setDir(90.0f);

	this->localScale = 1.0f;

	state2 = 0;
	state1 = nStates::WHALE_MOVE1;
	stateTime = 0.0f;
	sprite_id = 1;

	speedFactor[0] = 0.0f;
	speedFactor[1] = 0.0f;
	_terminalSpeed = 30.0f;//speed of light
	speedFactor[2] = 2.0f;//acceleration TODO: change it later
	speedModifier = 1.2f;

	_mass.frac = 2.5f;
	_mass.scale = 6;

}


void* killer_whale::setmove(olc::vf2d ctarget)
{
	if (this->cord.x > ctarget.x)
	{
		speedFactor[0] = -_terminalSpeed;
	}
	else if (this->cord.x == ctarget.x)
	{
		speedFactor[0] = 0.0f;
	}
	else
		speedFactor[0] = _terminalSpeed;

	if (this->cord.y > ctarget.y)
	{
		speedFactor[1] = -_terminalSpeed;
	}
	else if (this->cord.y == ctarget.y)
	{
		speedFactor[1] = 0.0f;
	}
	else
		speedFactor[1] = _terminalSpeed;

	/*
	if (this->cord.y == ctarget.y)
	{
		if (this->cord.x < ctarget.x)
			this->setDir(0.0f);
		else
			this->setDir(-180.0f);
	}
	else if (this->cord.x == ctarget.x)
	{
		if (this->cord.y < ctarget.y)
			this->setDir(90.0f);
		else
			this->setDir(-90.0f);
	}

	if (this->cord.x < ctarget.x)
	{
		if (this->cord.y < ctarget.y)
			this->setDir(45.0f);
		else
			this->setDir(-45.0f);
	}

	else if (this->cord.x > ctarget.x)
	{
		if (this->cord.y < ctarget.y)
			this->setDir(135.0f);
		else
			this->setDir(-135.0f);
	}
	*/
	//bool ans1 = (this->cord.x < ctarget.x);
	//bool ans2 = (this->_lookAngle < 0.0f);
	//
	//ans1 = ans1 ^ ans2;
	//if (!ans1)
	//	this->setDir(-(this->_lookAngle));//flip enemy

	//speedFactor[0] = _terminalSpeed * sinval;
	//speedFactor[1] = _terminalSpeed * cosval;

	return nullptr;
}
bool killer_whale::checkCollide(olc::vf2d upperLeft, olc::vf2d bottomRight)
{
	if ((cord.x > upperLeft.x) && (cord.x < bottomRight.x))
	{
		if ((cord.y > upperLeft.y) && (cord.y < bottomRight.y))
			return true;
		if (((cord.y + height) > upperLeft.y) && ((cord.y + height) < bottomRight.y))
			return true;
	}
	if (((cord.x + width) > upperLeft.x) && ((cord.x + width) < bottomRight.x))
	{
		if ((cord.y > upperLeft.y) && (cord.y < bottomRight.y))
			return true;
		if (((cord.y + height) > upperLeft.y) && ((cord.y + height) < bottomRight.y))
			return true;
	}
	return false;
}
void* killer_whale::move(olc::vf2d ctarget)
{
	this->cord.x += speedFactor[0] * speedModifier;
	this->cord.y += speedFactor[1] * speedModifier;
	
	this->trans.Translate(speedFactor[0] * speedModifier, speedFactor[1] * speedModifier);

	//if ((this->cord.x < ctarget.x) && (this->_lookAngle < 0.0f))
	//	this->setDir(-(this->_lookAngle));//flip enemy
	//if((this->cord.x > ctarget.x) && (this->_lookAngle > 0.0f))
	//	this->setDir(-(this->_lookAngle));
	


	return NULL;
}

void killer_whale::changeStrat()
{
	return;
}

void killer_whale::perFrame(float fElapsedTime, decimal misc)
{	
	if (bmove)
	{
		if (target == NULL)
		{
			bmove = false;
			return;
		}
		float oval = speedModifier;
		speedModifier *= fElapsedTime;
		move(target->cord);
		speedModifier = oval;

		if (reactionTime < fElapsedTime)
		{
			this->setmove(target->cord);
			reactionTime = 3.5f;
			return;
		}
		reactionTime -= fElapsedTime;
	}


	return;
}



decimal killer_whale::type()
{
	return o_types::KILLER_WHALE;
}

bool killer_whale::pcheckCollide(olc::Sprite* spr)
{
	return false;
}

killer_whale::~killer_whale()
{
	
}

space_pirate_ship::space_pirate_ship(float x, float y)
{
	this->cord = { x,y };
	this->r = 5.0f;
	sides[0].x = -5.0f;
	sides[0].y = -5.0f;
	sides[1].x = 5.0f;
	sides[1].y = -5.0f;
	sides[2].x = 0.0f;
	sides[2].y = 5.0f;
	misc1 = 0;
	misc2 = 0;
	flags = 0;
	setDir(-90.0f);
	_terminalSpeed = 50.0f;
	target = NULL;
	previousTarget = NULL;
	bmove = false;
	this->localScale = 1.0f;
	this->tmodifier = 1.0f;
	this->speedModifier = 1.0f;
	speedFactor[0] = speedFactor[1] = speedFactor[2] = 0.0f;
	this->sprite_id = 0;
	this->_mass = { 1.0f, 100 };
	first_p = NULL;
	second_p = NULL;
	_rotateThresh = 90.0f;
	reactThresh = 0.5f;
	prevSlope = NAN;
	tmodifier = 1.0f;
}

void* space_pirate_ship::think(int param, ...)
{
	return nullptr;
}

void* space_pirate_ship::observe(int param, ...)
{
	return nullptr;
}

void* space_pirate_ship::setmove(olc::vf2d ctarget)
{
	double a, b;
	float finalDir;
	/*
	if (isnan(_lookAngle))
	{
		_lookAngle = atan2f(cord.y - ctarget.y, cord.x - ctarget.x);
		_lookAngle = toDEG(_lookAngle);
		return NULL;
	}
	if (cord.x == ctarget.x)
	{
		if (cord.y > ctarget.y)
		{
			finalDir = -90.0f;
		}
		else
		{
			finalDir = 90.0f;
		}

		
	}
	else if (cord.y == ctarget.y)
	{
		if (cord.x < ctarget.x)
			finalDir = 0.0f;
		else
			finalDir = 180.0f;
	
	}
	else
	{
		finalDir = atan2f(cord.y - ctarget.y, cord.x - ctarget.x);
		finalDir = toDEG(finalDir);
	}
	
	if (_lookAngle == finalDir)
		return NULL;
	if (_lookAngle > finalDir)
	{
		float delta = (_lookAngle - finalDir);
		delta = (delta > _rotateThresh) ? _rotateThresh : delta;
		_lookAngle -= delta;

		
	}
	else
	{
		float delta = (finalDir - _lookAngle);
		delta = (delta > _rotateThresh) ? _rotateThresh : delta;
		_lookAngle += delta;
		
	}

	*/
	float slope;


	if (isnan(prevSlope))
	{
		if (cord.x == ctarget.x)
		{
			if (cord.y < ctarget.y)
			{
				prevSlope = INFINITE;
				setDir(-90.0f);
			}
			else
			{
				prevSlope = INFINITE;
				setDir(90.0f);
			}
		}
		else if (cord.y == ctarget.y)
		{
			prevSlope = 0.0f;
			if (cord.x < ctarget.x)
			{
				setDir(0.0f);
			}
			else
			{
				setDir(180.0f);
			}
		}
		else
		{
			float dir;
			slope = cord.y - ctarget.y;
			slope /= (cord.x - ctarget.x);
			dir = atan2f(cord.y - ctarget.y, cord.x - ctarget.x);
			dir = toDEG(dir);
			prevSlope = slope;
			setDir(dir);

			speedFactor[0] = -_terminalSpeed * cosval;
			speedFactor[1] = -_terminalSpeed * sinval;

		}

		return NULL;
	}
	float dir;
	dir = atan2f(cord.y - ctarget.y, cord.x - ctarget.x);
	dir = toDEG(dir);


	if (diff(_lookAngle, dir) > _rotateThresh)
	{
		if (_lookAngle > dir)
			_lookAngle -= _rotateThresh;
		else
			_lookAngle += _rotateThresh;
		dir = _lookAngle;
		
	}
	
	setDir(dir);
	prevSlope = tanf(dir);

	speedFactor[0] = -_terminalSpeed * cosval;
	speedFactor[1] = -_terminalSpeed * sinval; 


	return nullptr;
}

void* space_pirate_ship::move(olc::vf2d ctarget)
{
	cord.x += speedFactor[0] * speedModifier;
	cord.y += speedFactor[1] * speedModifier;

	return nullptr;
}

void* space_pirate_ship::attack(int param, ...)
{
	return nullptr;
}

void* space_pirate_ship::die(int param, ...)
{
	return nullptr;
}

void* space_pirate_ship::interact(int param, ...)
{
	return nullptr;
}

void space_pirate_ship::changeStrat()
{

}

void space_pirate_ship::perFrame(float fElapsedTime, decimal misc)
{
	float orig = speedModifier;
	speedModifier *= fElapsedTime;
	speedModifier *= tmodifier;

	if (reactThresh < speedModifier)
	{

		if (target == NULL)
		{
			target = previousTarget;
			previousTarget = NULL;
		}

		if (target != NULL)
			setmove(target->cord);
		reactThresh = 0.5f;
	}
	else
		reactThresh -= speedModifier;
	if (target != NULL)
		move(target->cord);


	speedModifier = orig;

}

decimal space_pirate_ship::type()
{
	return o_types::SPACE_PIRATE_SHIP;
}

bool space_pirate_ship::pcheckCollide(olc::Sprite* spr)
{
	return false;
}

space_pirate_ship::~space_pirate_ship()
{

}

giant_killer_whale::giant_killer_whale(float x, float y, uint32_t _width, uint32_t _height)
{
	cord.x = x;
	cord.y = y;

	hpov = 0.0f;
	vpov = 0.0f;

	width = _width;
	height = _height;

	target = NULL;
	previousTarget = NULL;
	first_p = this;
	second_p = NULL;

	setDir(180.0f);

	this->localScale = 16.0f;

	state2 = 0;
	state1 = 0;
	stateTime = 0.0f;
	sprite_id = 1;

	speedFactor[0] = 0.0f;
	speedFactor[1] = 0.0f;
	_terminalSpeed = 30.0f;//speed of light
	speedFactor[2] = 2.0f;//acceleration TODO: change it later
	speedModifier = 1.2f;

	_mass.frac = 2.5f;
	_mass.scale = 6;

}



void* giant_killer_whale::setmove(olc::vf2d ctarget)
{
	return nullptr;
}

bool giant_killer_whale::checkCollide(olc::vf2d upperLeft, olc::vf2d bottomRight)
{
	return false;
}

void* giant_killer_whale::move(olc::vf2d ctarget)
{
	return nullptr;
}


void giant_killer_whale::changeStrat()
{
}

void giant_killer_whale::perFrame(float fElapsedTime, decimal misc)
{
}

bool giant_killer_whale::pcheckCollide(olc::Sprite* spr)
{
	return false;
}

decimal giant_killer_whale::type()
{
	return o_types::GIANT_KILLER_WHALE;
}

void giant_killer_whale::draw(olc::PixelGameEngine* game)
{


	return;
	
}

giant_killer_whale::~giant_killer_whale()
{
}
