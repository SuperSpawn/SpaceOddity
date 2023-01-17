#pragma once
#include "object.h"



class projectile : public object
{
	//function of projectile effect
	void* (*func)(void*);//pointer to generic function
	

public:
	projectile();

	const bool& hitCheck();


	~projectile();
};

