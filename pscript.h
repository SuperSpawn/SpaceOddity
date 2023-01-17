#pragma once
#include "object.h"

class pscript
{
	decimal _id;
	string _type;
	
	bool repeat;
	dfunc _function;
	bool destructActivator;

public:
	pscript(const string& type, void* (*fun)(void**,int), const int& argnum = 0, void** args = NULL);
	
	const bool& toggleDestructActivator();



	void activate(const bool& ifloop = false);

	~pscript();
};

