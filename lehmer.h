#pragma once
#include "qmaths.h"
#include <cstdint>




typedef long double(*f_ffunc)();

extern unsigned int nLehmer;
extern decimal nLehmer64;
extern decimal nLehmer128;

extern superfloat sLehmer;

struct superProb
{
	superint val;

};



extern cord2<superint> superLehmerSeed;
extern std::vector<decimal> seeds;


unsigned int Lehmer32();//generate random number
decimal Lehmer64();
decimal Lehmer128();

int rndInt(int min, int max);
double rndDouble(double min, double max);

int rndInt64(int min, int max);
decimal urndInt64(decimal min, decimal max);
double rndDouble64(double min, double max);

int srndInt128(int min, int max);
decimal rndInt128(decimal min, decimal max);
decimal urndInt128(decimal min, decimal max);
long double rndDouble128(long double min, long double max);


int alternate_rndInt128(int min, int max);
decimal big_alternate_rndInt128(decimal min, decimal max);
decimal alternate_urndInt128(decimal min, decimal max);
long double alternate_rndDouble128(long double min, long double max);


const superfloat& superLehmer();
superfloat rndSuperfloat(const superfloat& min, const superfloat& max);

int srndInt(int min, int max);//sLehmer is universe offset


decimal P_modulotrix1();
long double dP_modulotrix1();
