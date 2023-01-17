#include "timedevice.h"

unsigned int timedevice::ids = 0;


timedevice::timedevice()
{
	leftover = 0.0f;
	ids = 0;

}

timedevice::~timedevice()
{

}

int timedevice::progress(const float& shift)
{
	if (tlist.empty())
		return 0;

	int execNum = 0;
	float sshift = shift;
	
	

	std::list<astuff>::iterator itr = tlist.begin();

	
	while (sshift >= 0.0f)
	{
		if (tlist.empty())
		{
			leftover = sshift;
			return execNum;
		}
		if (sshift < itr->ctime)
		{
			itr->ctime -= sshift;
			return execNum;
		}
		if (sshift >= itr->ctime)
		{
			itr->func.func(itr->func.argnum, itr->func.args);//call function
			++execNum;
			sshift -= itr->ctime;
			tlist.pop_front();
			if(!tlist.empty()) itr = tlist.begin();
		}
	}
}


void timedevice::addTimer(const dfunc& fun, const float& timeof)
{
	if (timeof == 0.0f)
	{
		fun.func(fun.argnum, fun.args);//call function right away
		return;
	}

	float tim = timeof;

	if (tlist.empty())
	{
		if (tim <= leftover)
		{
			leftover -= tim;
			fun.func(fun.argnum, fun.args);//run func

			return;
		}

		tim -= leftover;
	}

	

	std::list<astuff>::iterator itr;
	for (itr = tlist.begin(); itr != tlist.end(); ++itr)
	{
		if (tim < itr->ctime)
		{
			astuff k;
			k.func = fun;
			k.ctime = tim;
			k.id = ids;
			tlist.insert(itr, k);
			++ids;

			return;
		}
		tim -= itr->ctime;
	}

	astuff k;
	k.ctime = tim;
	k.func = fun;
	k.id = ids;
	tlist.push_back(k);
	++ids;

	return;
}





