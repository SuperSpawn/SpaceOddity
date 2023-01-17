#pragma once
//#include "pscript.h"
#include "starsystem.h"

class timedevice
{
	struct astuff
	{
		unsigned int id;
		dfunc func;
		float ctime;
	};

	std::list<astuff> tlist;
	float leftover;

	static unsigned int ids;

public:
	timedevice();
	~timedevice();

	int progress(const float& shift);
	void addTimer(const dfunc& fun, const float& timeof = 0.0f);

};

