#pragma once
#include "timedevice.h"


struct inc_intVar : public polyFunc
{
	int& var;
	inc_intVar(int& the_var) : var(the_var)
	{

	}

	virtual void activate()
	{
		++var;
	} 


	virtual ~inc_intVar()
	{

	}
};


