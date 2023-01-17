#include "lehmer.h"

unsigned int nLehmer = 7564638;
decimal nLehmer64 = 7564638;
decimal nLehmer128 = 7564638;
superfloat sLehmer = 7564638;

cord2<superint> superLehmerSeed = { superint(0),superint(0) };

std::vector<decimal> seeds(SEEDS_PER_NODE, 7564638);


unsigned int Lehmer32()//generate random number
{
	//unsigned int nLehmer = 7564638;
	unsigned int m;
	unsigned long long int tmp;
	nLehmer += 0xe120fc15;
	tmp = (unsigned long long int)nLehmer * 0x4a39b70d;
	m = (tmp >> 32) ^ tmp;
	tmp = (unsigned long long int)m * 0x12fad5c9;
	m = (tmp >> 32) ^ tmp;
	return m;

	/*
	m = tmp >> 32
	m = m ^ tmp
	return m
	
	m ^= tmp
	m <<= 32

	m /= 0x12fad5c9;
	m ^= tmp
	m <<= 32
	m /= 0x4a39b70d
	m -= 0xe120fc15
	return m;

	*/
}


decimal Lehmer64()
{
	decimal m;
	decimal tmp;
	nLehmer64 += 0xe120fc15;
	tmp = (nLehmer64) * 0x4a39b70d;
	m = ((tmp >> 32) ^ tmp);
	tmp = (m) * 0x12fad5c9;
	m = ((tmp >> 64) ^ tmp);
	return m;
}

decimal Lehmer128()
{
	uint64_t m;
	uint64_t tmp;
	nLehmer128 += 0xe120fc15;
	tmp = nLehmer128 * 0x4a39b70d;
	m = ((tmp >> 32) ^ tmp);
	tmp = (m) * 0x12fad5c9;
	m = ((tmp >> 32) ^ tmp);
	return m;
}




int rndInt(int min, int max)
{
	return (Lehmer32() % (max - min)) + min;
}

double rndDouble(double min, double max)
{
	return ((double)Lehmer32() / (double)(0x7fffffff) * (max - min) + min);
}

int rndInt64(int min, int max)
{
	return (Lehmer64() % (max - min)) + min;
}

decimal urndInt64(decimal min, decimal max)
{
	return (Lehmer64() % (max - min)) + min;
}
double rndDouble64(double min, double max)
{
	return ((double)Lehmer64() / (double)(0x7fffffff) * (max - min) + min);
}

int srndInt128(int min, int max)
{
	return (Lehmer64() % (max - min)) + min;
}
decimal rndInt128(decimal min, decimal max)
{
	return ((Lehmer128() % (max - min)) + min);
}
decimal urndInt128(decimal min, decimal max)
{
	return ((Lehmer128() % (max - min)) + min);
}
long double rndDouble128(long double min, long double max)
{
	return ((long double)Lehmer128() / (long double)(0x7fffffff) * (max - min) + min);
}


int alternate_rndInt128(int min, int max)
{
	decimal val = Lehmer128();
	decimal original = nLehmer64;
	decimal k;
	decimal i;
	std::vector<int64_t>::iterator curr;
	constexpr decimal shift = (sizeof(decimal) << 3) / SEEDS_PER_NODE;

	for (curr = superLehmerSeed.x.list.begin(); curr != superLehmerSeed.x.list.end(); ++curr)
	{
		k = *curr;
		for (i = 0; i < SEEDS_PER_NODE; ++i)
		{
			nLehmer64 = k & _partial_seed;
			val += Lehmer64();
			k >>= shift;
		}

	}
	for (curr = superLehmerSeed.y.list.begin(); curr != superLehmerSeed.y.list.end(); ++curr)
	{
		k = *curr;
		for (i = 0; i < SEEDS_PER_NODE; ++i)
		{
			nLehmer64 = k & _partial_seed;
			val += Lehmer64();
			k >>= shift;
		}

	}

	nLehmer64 = original;

	return int((val % (max - min)) + min);
}
decimal big_alternate_rndInt128(decimal min, decimal max)
{
	decimal val = Lehmer128();
	decimal original = nLehmer64;
	decimal k;
	decimal i;
	std::vector<int64_t>::iterator curr;
	constexpr decimal shift = (sizeof(decimal) << 3) / SEEDS_PER_NODE;

	for (curr = superLehmerSeed.x.list.begin(); curr != superLehmerSeed.x.list.end(); ++curr)
	{
		k = *curr;
		for (i = 0; i < SEEDS_PER_NODE; ++i)
		{
			nLehmer64 = k & _partial_seed;
			val += Lehmer64();
			k >>= shift;
		}

	}
	for (curr = superLehmerSeed.y.list.begin(); curr != superLehmerSeed.y.list.end(); ++curr)
	{
		k = *curr;
		for (i = 0; i < SEEDS_PER_NODE; ++i)
		{
			nLehmer64 = k & _partial_seed;
			val += Lehmer64();
			k >>= shift;
		}

	}

	nLehmer64 = original;

	return ((val % (max - min)) + min);
}
decimal alternate_urndInt128(decimal min, decimal max)
{
	decimal val = Lehmer128();
	decimal original = nLehmer64;
	decimal k;
	decimal i;
	std::vector<int64_t>::iterator curr;
	constexpr decimal shift = (sizeof(decimal) << 3) / SEEDS_PER_NODE;

	for (curr = superLehmerSeed.x.list.begin(); curr != superLehmerSeed.x.list.end(); ++curr)
	{
		k = *curr;
		for (i = 0; i < SEEDS_PER_NODE; ++i)
		{
			nLehmer64 = k & _partial_seed;
			val += Lehmer64();
			k >>= shift;
		}

	}
	for (curr = superLehmerSeed.y.list.begin(); curr != superLehmerSeed.y.list.end(); ++curr)
	{
		k = *curr;
		for (i = 0; i < SEEDS_PER_NODE; ++i)
		{
			nLehmer64 = k & _partial_seed;
			val += Lehmer64();
			k >>= shift;
		}

	}

	nLehmer64 = original;

	return ((val % (max - min)) + min);
}
long double alternate_rndDouble128(long double min, long double max)
{
	//I hate this so much!!!
	return 0.0;
}


const superfloat& superLehmer()
{
	superfloat m;
	superfloat tmp;
	sLehmer += 0xe120fc15;
	tmp = sLehmer;
	tmp *= 0x4a39b70d;
	m = tmp;
	m >>= 32;
	m ^= tmp;
	tmp = m; 
	tmp *= 0x12fad5c9;
	m = tmp;
	m >>= 32;
	m ^= tmp;
	return m;

}
superfloat rndSuperfloat(const superfloat& min, const superfloat& max)
{
	superfloat k = max;
	k -= min;
	superfloat res = superLehmer();
	res %= k;
	k = res;
	k += min;
	return k;
}


int srndInt(int min, int max)
{
	int ret;
	superfloat val;

	val = superLehmer();
	val.moduleByint(max - min);
	ret = val;
	ret += min;
	return ret;
}








long double dP_modulotrix1()
{

}















