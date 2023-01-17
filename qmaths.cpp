#include "qmaths.h"


float* _sintable = NULL;
float* _tantable = NULL;
const decimal _partial_seed = activate_lbits((sizeof(decimal) << 3) / SEEDS_PER_NODE);

const double& qsqrtd(const double& number)
{
	return number;
}

const float& qsqrtf(const float& number)
{
	return number;
}

const double& generatePi(const unsigned long int& accuracy)
{
	//draw circle with radius 1
	//that circle's area is pi
	//draw 
	return PI;
}

float Q_rsqrt(float number)
{
	long i;
	float x2, y;
	const float threehalfs = 1.5f;

	x2 = number * 0.5f;
	y = number;

	i = *(long*)&y; //evil floating point bit hack
	i = 0x5f3759df - (i >> 1);
	y = *(float*)&i;
	y = y * (threehalfs - (x2 * y * y));
	y = y * (threehalfs - (x2 * y * y));

	return y;

}





const double& toRAD(const float& number)
{
	return double((double(number) * PI) / 180.0);
}
const double& toDEG(const float& number)
{
	return double((double(number) * 180.0) / PI);
}

float* generateSinTable()
{
	unsigned long long int i;
	if (_sintable != NULL)
		return _sintable;
	_sintable = new float[SIN_TABLE_ACCURACY];
	if (_sintable == NULL)
		throw - 1;
	for (i = 0; i < SIN_TABLE_ACCURACY; ++i)
		_sintable[i] = sinf(toRAD(i/100.0f));
	return _sintable;
}

float* generateTanTable()
{
	unsigned long long int i;
	if (_tantable != NULL)
		return _tantable;
	_tantable = new float[SIN_TABLE_ACCURACY];
	if (_tantable == NULL)
		throw - 1;
	for (i = 0; i < SIN_TABLE_ACCURACY; ++i)
	{
		_tantable[i] = tanf(toRAD(i/100.0f));
	}

	return _tantable;
}

const float& mysinf(const float& number)
{

	if (_sintable == NULL)
		return 2.0f;

	float result = number;
	bool neg = false;

	if (result < 0.0f)
	{
		neg = true;
		result = -result;
	}

	while (result >= 360.0f) result -= 360.0f;

	if (result >= 180.0f)
	{
		neg = !neg;
		result -= 180.0f;
	}

	if (result >= 90.0f)
		result = 180.0f - result;
	
	int index = result * 100;

	return (neg ? -_sintable[index] : _sintable[index]);
}

const float& mysinf2(const float& number)
{
	bool neg = false;
	float result = number;
	
	
	if (result < 0.0f)
	{
		result = -result;
		neg = !neg;
	}

	while (result >= 360.0f) result -= 360.0f;
	if (result >= 180.0f)
	{
		neg = !neg;
		result -= 180.0f;
	}

	result = _sintable[unsigned long long int(double(result) * 100)];
	
	if(neg) 
		result = -result;
	return result;
}


const float& mycosf(const float& number)
{
	float ang = number;
	while (ang >= 360.0f)	ang -= 360.0f;
	while (ang <= -360.0f)	ang += 360.0f;

	if (ang == 0.0f)
		return 1.0f;
	if (ang == 30.0f)
		return Q_rsqrt(4.0f/3.0f);
	if (ang == 45.0f)
		return Q_rsqrt(2);
	if (ang == 60.0f)
		return 0.5f;
	if (ang == 90.0f)
		return 0.0f;
	if (ang == 180.0f)
		return -1.0f;

	return mysinf(90.0f + ang);
}

const float& mycosf2(const float& number)
{
	float ang = number;
	while (ang >= 360.0f)	ang -= 360.0f;
	while (ang <= -360.0f)	ang += 360.0f;
	return mysinf2(90.0f + ang);
}


const float& mytanf(const float& number)
{
	float result = number;
	return number;
}

const float& mytanf2(const float& number)
{
	float result = number;

	return number;
}

const float& mytanf3(const float& number)
{
	float result, cosnum;

	cosnum = mycosf2(number);
	if (cosnum == 0.0f)
		return INFINITY;
	result = mysinf2(number) / cosnum;
}


const f2& rotateAt(const f2& origin, const float& rotate, const float& sx, const float& sy)
{
	float sink, cosk;
	f2 ting = origin;

	/*
	sink = sinf(toRAD(rotate));
	cosk = cosf(toRAD(rotate));
	*/

	sink = sinf(toRAD(rotate));
	cosk = sinf(toRAD(90.0f - rotate));

	ting.x -= sx;
	ting.y -= sy;//thanks cherry hill math

	//rotate
	ting.x = (ting.x * cosk) - (ting.y * sink);
	ting.y = (ting.x * sink) + (ting.y * cosk);
	
	ting.x += sx;
	ting.y += sy;

	return ting;
}

const float& degVec(const float& x1, const float& y1, const float& x2, const float& y2, 
	const float& stx, const float& sty)
{
	//we assume the vectors are normalized beforehand
	if ((stx != 0) || (sty != 0))
		return degVec(x1 - stx, y1 - sty, x2 - sty, y2 - sty, 0, 0);
	return toDEG(acosf(x1 * x2 + y1 * y2));
}







void superfloat::handleAddition(const int& other)
{
	std::list<decimal>::iterator runner;
	int t = other;


	for (runner = spec; runner != list.end(); t = 1)
	{
		if (*runner + t < *runner) //overflow
		{
			*runner += t;
			if (++runner == list.end())
			{
				list.push_back(1);//can't be more than 1
				return;
			}
		}
		else
		{
			*runner += t;
			return;//soft way tp exit the loop
		}
	}


	return;
}
void superfloat::handleAddition(const float& other)
{
	std::list<decimal>::iterator runner;

	float t = other;

	for (runner = spec; runner != list.end(); t = 1.0f)
	{
		if (*runner + t < *runner) //overflow
		{
			*runner += t;
			if (++runner == list.end())
			{
				list.push_back(1);//can't be more than 1
				return;
			}
		}
		else
		{
			*runner += t;
			return;//soft way tp exit the loop
		}
	}


	return;
}
void superfloat::handleAddition(const unsigned int& other)
{
	std::list<decimal>::iterator runner;

	unsigned int t = other;

	for (runner = spec; runner != list.end(); t = 1)
	{
		if (*runner + t < *runner) //overflow
		{
			*runner += t;
			if (++runner == list.end())
			{
				list.push_back(1);//can't be more than 1
				return;
			}
		}
		else
		{
			*runner += t;
			return;//soft way tp exit the loop
		}
	}


	return;
}
void superfloat::handleAddition(decimal other)
{
	std::list<decimal>::iterator runner;

	for (runner = spec; runner != list.end(); other = 1)
	{
		if (*runner + other < *runner) //overflow
		{
			*runner += other;
			if (++runner == list.end())
			{
				list.push_back(1);//can't be more than 1
				return;
			}
		}
		else
		{
			*runner += other;
			return;//soft way tp exit the loop
		}
	}


	return;
}
void superfloat::handleAddition(const superfloat& other)
{
	//useless
	return;
}

const byte& superfloat::iterateBigger(const superfloat& other)const
{
	
	std::list<decimal>::const_reverse_iterator k;
	std::list<decimal>::const_reverse_iterator j;

	byte retval = 0;

	j = other.list.rbegin();
	for (k = list.rbegin(); k != list.rend(); ++k)
	{
		if (*k != *j)
			return *k > *j;
		++j;
	}

	if (unitoff == other.unitoff)
		retval = 2;
	else
		retval = unitoff > other.unitoff;
	return retval;
	

	//return 0;
}
const byte& superfloat::iterateSmaller(const superfloat& other)const
{
	
	std::list<decimal>::const_reverse_iterator k;
	std::list<decimal>::const_reverse_iterator j;

	byte retval = 0;

	j = other.list.rbegin();

	for (k = list.rbegin(); k != list.rend(); ++k)
	{
		if (*k != *j)
			return *k < *j;
		++j;
	}

	if (unitoff == other.unitoff)
		retval = 2;//they are equal
	else
		retval = (unitoff < other.unitoff);

	return retval;
	
}

inline void superfloat::lshiftby1(const bool& staticmode)
{
	bool next = false;
	decimal thing = 1;
	const decimal val = thing << ((sizeof(decimal) * 8) - 1);//msb
	thing = 0;

	std::list<decimal>::iterator runner;

	for (runner = list.begin(); runner != list.end(); ++runner)
	{
		bool ifAdd = next;//if we should activate lsb after shifting in this iteration
		thing = *runner & val;
		if (thing)//check if not zero
			next = true;//we should activate lsb in next iteration
		else
			next = false;
		*runner <<= 1;//do the actual shifting
		if (ifAdd)
			*runner |= 1;//activate lsb
	}

	if (next)
		list.push_back(1);//if overall msb of the struct is 1 then we should enlarge it


	return;
}

inline void superfloat::rshiftby1(const bool& staticmode)
{
	bool prev = false;
	decimal thing = 1;
	const decimal msb = thing << ((sizeof(decimal) * 8) - 1);//msb
	thing = 0;

	std::list<decimal>::reverse_iterator runner;

	for (runner = list.rbegin(); runner != list.rend(); ++runner)
	{
		bool ifAdd = prev;//if we should activate msb after shifting in this iteration
		thing = *runner & 1;
		if (thing)//check if not zero
			prev = true;//we should activate msb in next iteration
		else
			prev = false;
		*runner >>= 1;//do the actual shifting
		if (ifAdd)
			*runner |= msb;//activate lsb
	}

	return;
}

const int& superfloat::moduleByint(const int& number)
{
	int ret;
	if (list.size() == 0)
		return 0;
	if (list.size() == 1)
		return (list.front() %= number);

	std::list<decimal>::reverse_iterator rk;

	for (rk = list.rbegin(); rk != list.rend(); ++rk)
		while (*rk > number) *rk -= number;
	while (operator>=(number)) operator-=(number);
	ret = *this;

	return ret;
}

inline void superfloat::decby1()
{

	collapse();

	if (list.empty())
	{
		negative = true;
		if (unitoff != 0.0f)
		{
			unitoff = 1.0f - unitoff;
			return;
		}
		list.push_front(1);
		return;
	}

	std::list<decimal>::iterator runner;

	for (runner = list.begin(); *runner == 0; ++runner);
	while (runner != list.begin())
	{
		--* runner;//0 values should underflow to heighest value
		--runner;
	}
	
	return;
}
inline void superfloat::incby1()
{

}

bool superfloat::cmp0(char mode)
{
	collapse();
	switch (mode)
	{
	case '=':
		if (list.empty())
			return (unitoff == 0.0f);
		return false;
	case '>':
		if (negative)
			return false;
		return (unitoff > 0.0f);
	case '<':
		if (negative)
			return true;
		return false;
	default:
		return true;
	}
}

superfloat& superfloat::pureAdd(const superfloat& other)
{

	//assuming this and other are possitive
	std::list<decimal>::iterator runner;
	std::list<decimal>::const_iterator i;

	unitoff += other.unitoff;
	decimal k;
	k = unitoff;//get the whole number
	unitoff -= k;
	*this += k;

	if (other.list.empty())
		return *this;

	while (list.size() < other.list.size())
		list.push_back(0);
	i = other.list.begin();

	for (runner = list.begin(); runner != list.end(); ++runner)
	{
		if (i != other.list.end())
		{
			spec = runner;
			handleAddition(*i);
			++i;
		}
	}


	return *this;
	

}
superfloat& superfloat::pureSub(const superfloat& other)
{
	
	//assuming this and other are possitive
	//assume this is bigger than other
	std::list<decimal>::iterator runner;
	std::list<decimal>::const_iterator k = other.list.begin();

	collapse();


	for(runner = list.begin(); runner != list.end(); ++runner)
	{
		if (k == other.list.end())
			continue;
		if (*runner < *k)
		{
			//guaranteed to not be the first one
			std::list<decimal>::iterator j;
			++runner;
			for (j = runner; *j == 0; ++j);
			--runner;
			--* j;
			const decimal val = -1;
			while (j != runner)
			{
				--j;
				*j = val;
				
			}
			
			*runner = val - *k + *runner;
			*runner += 2;
		}
		else
			*runner -= *k;
		++k;
	}

	collapse();

	unitoff -= other.unitoff;
	if (unitoff < 0)
	{
		decby1();
		++unitoff;
	}


	return *this;
	
}

void superfloat::collapse() //done
{
	if (list.empty())
		return;

	std::list<decimal>::reverse_iterator runner;

	for (runner = list.rbegin(); runner != list.rend(); )
	{
		if (*runner == 0) 
		{
			++runner;
			list.pop_back();
		}
		else return;
	}

	negative = false;
	return;
}
superfloat::superfloat()
{
	list.clear();
	unitoff = 0.0f;
	negative = false;
	spec = list.begin();
}
superfloat::superfloat(const int& value)
{
	unitoff = 0.0f;
	negative = (value < 0);

	decimal d;

	if (negative)
		d = -value;
	else
		d = value;

	list.push_front(d);

}
superfloat::superfloat(const float& value)
{
	decimal d;

	negative = (value < 0.0f);
	if (negative)
		d = -value;
	else
		d = value;
	unitoff = d - value;
	list.push_front(d);

}
superfloat::superfloat(const decimal& value)
{
	unitoff = 0.0f;
	negative = false;
	list.push_front(value);
}
superfloat::superfloat(const superfloat& other)
{
	unitoff = other.unitoff;
	negative = other.negative;
	list = other.list;

}

void superfloat::divbypow2(const int& num)
{
	int i, j = num;

	for (i = 0; j != 0; ++i)	j >>= 1;
	
	operator >>=(i);

}

void superfloat::divbypow2(const float& num)
{

}

void superfloat::divbypow2(const unsigned int& num)
{

}

void superfloat::divbypow2(const decimal& num)
{
	decimal shift = 0, copy = num;
	while (copy)
	{
		copy >>= 1;
		++shift;
	}


	operator>>=(shift);
	return;
}

void superfloat::appendSuper(const superfloat& other)
{
	std::list<decimal>::const_iterator runner;

	for (runner = other.list.cbegin(); runner != other.list.cend(); ++runner)
		list.push_back(*runner);
}

superfloat::operator int()	//risky on large numbers
{
	int val = list.front();
	if (negative)
		val = -val;
	return val;
}


superfloat::operator float()//risky on large numbers
{
	decimal id = 0;
	std::list<decimal>::iterator run;
	float val = unitoff;
	for (run = list.begin(); run != list.end(); ++run)
	{
		float thing = *run;
		thing += float((decimal(-1) * id * *run));
		//wtf
		++id;
		val += thing;
	}
	return val;
}

superfloat::operator unsigned int()
{
	unsigned int res = list.front();
	return res;
}

superfloat::operator decimal()
{
	return list.front();
}

superfloat& superfloat::operator++()
{
	incby1();
	return *this;
}
const superfloat& superfloat::operator++(int)
{
	superfloat copy = *this;
	incby1();
	return copy;
}

superfloat& superfloat::operator--()
{
	decby1();
	return *this;
}
const superfloat& superfloat::operator--(int)
{
	superfloat cpy = *this;
	decby1();
	return cpy;
}

const superfloat& superfloat::operator+(const superfloat& other)const
{
	superfloat copy = *this;
	copy += other;
	return copy;
}
const superfloat& superfloat::operator+(const int& other)const
{
	superfloat copy = *this;
	copy += other;
	return copy;
}
const superfloat& superfloat::operator+(const float& other)const
{
	superfloat copy = *this;
	copy += other;
	return copy;
}
const superfloat& superfloat::operator+(const unsigned int& other)const
{
	superfloat copy = *this;
	copy += other;
	return copy;
}
const superfloat& superfloat::operator+(const decimal& other) const
{
	superfloat copy = *this;
	copy += other;
	return copy;
}

const superfloat& superfloat::operator-(const superfloat& other)const
{
	superfloat copy = *this;
	copy -= other;
	return copy;
}
const superfloat& superfloat::operator-(const int& other)const
{
	superfloat copy = *this;
	copy -= other;
	return copy;
}
const superfloat& superfloat::operator-(const float& other)const
{
	superfloat copy = *this;
	copy -= other;
	return copy;
}
const superfloat& superfloat::operator-(const unsigned int& other)const
{
	superfloat copy = *this;
	copy -= other;
	return copy;
}
const superfloat& superfloat::operator-(const decimal& other)const
{
	superfloat copy = *this;
	copy -= other;
	return copy;
}
const superfloat& superfloat::operator-() const 
{
	superfloat copy(*this);
	copy.negative = !negative;

	return copy;
}


const superfloat& superfloat::operator*(const superfloat& other)const
{
	superfloat copy = *this;
	copy *= other;
	return copy;
}
const superfloat& superfloat::operator*(const int& other)const
{
	superfloat copy = *this;
	copy *= other;
	return copy;
}
const superfloat& superfloat::operator*(const float& other)const
{
	superfloat copy = *this;
	copy *= other;
	return copy;
}
const superfloat& superfloat::operator*(const unsigned int& other)const
{
	superfloat copy = *this;
	copy *= other;
	return copy;
}
const superfloat& superfloat::operator*(const decimal& other)const
{
	superfloat copy = *this;
	copy *= other;
	return copy;
}


const superfloat& superfloat::operator/(const superfloat& other)const
{
	superfloat copy = *this;
	copy /= other;
	return copy;
}
const superfloat& superfloat::operator/(const int& other)const
{
	superfloat copy = *this;
	copy /= other;
	return copy;
}
const superfloat& superfloat::operator/(const float& other)const
{
	superfloat copy = *this;
	copy /= other;
	return copy;
}
const superfloat& superfloat::operator/(const unsigned int& other)const
{
	superfloat copy = *this;
	copy /= other;
	return copy;
}
const superfloat& superfloat::operator/(const decimal& other)const
{
	superfloat copy = *this;
	copy /= other;
	return copy;
}



superfloat& superfloat::operator=(const superfloat& other)
{
	list.clear();

	list = other.list;
	negative = other.negative;
	unitoff = other.unitoff;
	
	return *this;
}
superfloat& superfloat::operator=(const int& other)
{
	list.clear();
	negative = (other < 0);

	if (negative)
		list.push_back(-other);
	else
		list.push_back(other);

	unitoff = 0.0f;

	return *this;
}
superfloat& superfloat::operator=(const float& other)
{
	*this = 0;
	*this += other;
	return *this;

	/*
	//assume a small number so no problems are caused
	list.clear();
	decimal d = 0;

	negative = (other < 0.0f);

	if (negative)
		unitoff = -other;
	else
		unitoff = other;

	while (unitoff >= 1.0f)
	{
		--unitoff;
		++d;
	}

	list.push_back(d);

	return *this;
	*/
}
superfloat& superfloat::operator=(const unsigned int& other)
{
	list.clear();
	unitoff = 0.0f;
	list.push_front(decimal(other));
	negative = false;

	return *this;
}
superfloat& superfloat::operator=(const decimal& other)
{
	list.clear();
	unitoff = 0.0f;
	list.push_back(other);
	negative = false;

	return *this;
}


//most complex
superfloat& superfloat::operator+=(const superfloat& other)
{
	//std::list<decimal>::iterator runner;
	//std::list<decimal>::const_iterator i;

	if (negative ^ other.negative)
	{
		if (iterateBigger(other) != 0)
		{
			pureSub(other);
		}
		else
		{
			superfloat copy = *this;
			*this = other;
			pureSub(copy);
		}
	}
	else
		pureAdd(other);
	/*
	unitoff += other.unitoff;
	decimal wholeval;
	wholeval = unitoff;//get the whole number
	unitoff -= wholeval;
	*this += wholeval;

	runner = list.begin();
	i = other.list.begin();

	while (list.size() < other.list.size())
		list.push_back(0);

	runner = list.begin();
	i = other.list.begin();
	
	for (runner = list.begin(); runner != list.end(); ++runner)
	{
		if (i != other.list.end())
		{
			spec = runner;
			handleAddition(*i);
			++i;
		}
	}
	*/

	return *this;
}
//ez pz
superfloat& superfloat::operator+=(const int& other)
{
	if (other < 0)
		return *this -= (-other);
	spec = list.begin();
	handleAddition(other);

	return *this;
}
//very bad
superfloat& superfloat::operator+=(const float& other)
{
	//float x = other;
	float x;
	int size = 8 * sizeof(decimal);
	//double x = other + (double)unitoff;
	unsigned int* ptr = (unsigned int*)&other;//very evil
	std::list<decimal>::iterator runner;
	
	if (other < 0.0f)
	{
		return ((*this) -= (-other));//so I can retain my sanity
	}
	int num = *ptr & 0x007fffff;//get mantissa
	num |= 0x00800000;//activate secret bit

	// 0      0      7     f    f    f    f    f
	// 0 000  0000 0 000 0000 0000 0000 0000 0000

	int exponent = *ptr & 0x7f800000;//evil floating point bit hack
	exponent >>= 23;//get exponent bits according to IEEE-754
	exponent -= 128;//the exponent is shifted by 128
	//now we have the raw exponent
	if (exponent >= 23)
	{
		//then number can't hold a fractional value
		//we're potentially dealing with a really big value
		superfloat k = num;

		k <<= exponent;//temporary fix
		return *this += k;

	}
	else
	{
		unitoff += other;

		if (unitoff >= 1.0f)
		{
			if (list.empty())
			{
				list.push_front(0);
			}

			decimal val = decimal(unitoff);

			spec = list.begin();
			handleAddition(val);
			unitoff = unitoff - val;

			//handleAddition(decimal(unitoff));
			//unitoff = unitoff - decimal(unitoff);
		}

		



	}


	return *this;

		//0 10010101 10100111101101011101010
		//0 10010101 10100111101101011101010
	//0100 1010 1101 0011 1101 1010 1110 1010 0100 1010 1101 0011 1101 1010 1110 1010
	// 0    0    0    0    0    1     f    f    f    f    f    f   f    f     f    f
	//0x0000 0000 ffff ffff
	
}
//even ezier
superfloat& superfloat::operator+=(const unsigned int& other)
{
	
	spec = list.begin();
	handleAddition(other);

	return *this;
}
//eziest
superfloat& superfloat::operator+=(const decimal& other)
{
	if (other == 0)
		return *this;

	if (negative)
	{
		if (list.empty())
		{
			if (unitoff == 0.0f)
			{
				negative = false;
				list.push_front(other);
				return *this;
			}
			
			negative = false;
			unitoff = 1.0f - unitoff;
			list.push_front(other - 1);
			return *this;
		}

		negative = false;
		*this -= other;
		negative = true;

		return *this;
	}

	if (list.empty())
	{
		list.push_front(other);
		return *this;
	}

	spec = list.begin();
	handleAddition(other);

	return *this;
}




superfloat& superfloat::operator-=(const superfloat& other)
{
	/*
	if (negative)
	{
		negative = false;
		*this += other;
		negative = true;
		return *this;
	}

	if (other.negative)
		return *this += (-other);
	*/
	superfloat copy;
	

	if (negative ^ other.negative)
	{
		pureAdd(other);
		return *this;
	}

	if (negative)
	{
		//other is also negative
		if (other > *this)
		{
			negative = false;
			copy = *this;
			*this = other;
			pureSub(copy);
			return *this;
		}

		pureSub(other);
		//negative = true; //already true
		return *this;
		
	}

	
	if (other > *this)
	{
		copy = *this;
		*this = other;
		pureSub(copy);
		return *this;
	}

	return pureSub(other);
	return *this;
}
superfloat& superfloat::operator-=(const int& other)
{
	if (other < 0)
		return *this += (-other);
	//if()

	return *this;
}

superfloat& superfloat::operator-=(const float& other)
{
	decimal whole = other;
	float off = other - whole;

	

	return *this;
}

superfloat& superfloat::operator-=(const unsigned int& other)
{
	return *this;
}

superfloat& superfloat::operator-=(const decimal& other)
{
	if (other == 0)
		return *this;



	if (list.empty())
	{
		negative = true;

		if (unitoff != 0.0f)
		{
			list.push_front(other - 1);
			unitoff = -unitoff;
			unitoff += 1.0f;
		}
		else
		{
			list.push_front(other);
		}

		return *this;
	}

	if (list.size() == 1)
	{
		if (list.front() < other)
		{
			negative = !negative;
			list.front() = other - list.front();
			

		}




	}


	return *this;
}

superfloat& superfloat::operator*=(const superfloat& other)
{
	//method 1: add many times
	//method 2: use bit shifting trick
	superfloat val = *this;



}

superfloat& superfloat::operator*=(const int& other)
{
	if (other == 0) return *this = other;
	if (other == 1) return *this;


	superfloat original = *this;

	int multby = other;
	if (other < 0)
	{
		multby = -other;
		negative = !negative;
	}


	--multby;

	int currpow = 1;

	while (currpow)//while currpow isn't 0
	{
		
		unitoff += original.unitoff;
		decimal whole = unitoff;
		if (whole)
		{
			unitoff -= whole;
			*this += whole;
		}
		

		if (multby & currpow)
		{
			*this += original;
		}

		currpow <<= 1;//next bit
		original.lshiftby1();
	}
	
	return *this;
}
superfloat& superfloat::operator*=(const float& other)
{
	superfloat cpy = *this;

	*this = 0;
	*this += other;

	return operator*=(cpy);
	
}
superfloat& superfloat::operator*=(const unsigned int& other)
{
	superfloat original = *this;

	

	int currpow = 1;

	while (currpow)//while currpow isn't 0
	{
		if (other & currpow)
		{
			*this += (original << currpow);
		}

		currpow <<= 1;//next bit
	}

	return *this;
}
superfloat& superfloat::operator*=(const decimal& other)
{
	superfloat original = *this;
	int currpow = 1;

	while (currpow)//while currpow isn't 0
	{
		if (other & currpow)
		{
			*this += (original << currpow);
		}

		currpow <<= 1;//next bit
	}

	return *this;
}




superfloat& superfloat::operator/=(const superfloat& other)
{

}
superfloat& superfloat::operator/=(const int& other)
{

}
superfloat& superfloat::operator/=(const float& other)
{
	if (other == 0.0f)
	{
		unitoff = INFINITY;
		list.clear();
		negative = false;

		return *this;
	}

	if (other < 0.0f)
	{
		negative = !negative;
		return *this /= (-other);
	}

	float inv = 1.0f / other;
	return operator*=(inv);
}
superfloat& superfloat::operator/=(const unsigned int& other)
{
	if (other == 0)
	{
		unitoff = INFINITY;
		negative = false;
		list.clear();
	}

	decimal val;

	if (val = ifPower2(other))
		return *this >>= val;


}
superfloat& superfloat::operator/=(const decimal& other)
{
	if (other == 0)
	{
		unitoff = INFINITY;
		negative = false;
		list.clear();
	}

	decimal val;
	if (val = ifPower2(other))
		return *this >>= val;


}


superfloat& superfloat::operator<<=(const int& other)
{
	//method 1: shift 1 bit at a time
	//method 2: shift constant i bits at a time
	if (other == 0)
		return *this;

	if (other < 0)
		return *this >>= -other;

	

	int k = other;

	while (k >= 8 * sizeof(decimal))
	{
		list.push_front(0);
		k -= 8 * sizeof(decimal);
	}

	//by now k is between [0, 63]
	while (k != 0)
	{
		lshiftby1();
		--k;
	}

	return *this;
}
superfloat& superfloat::operator>>=(const int& other)
{
	if (other == 0)
		return *this;

	if (other < 0)
		return *this <<= -other;

	int i = other;

	while (i > (8 * sizeof(decimal)))
	{
		list.pop_front();
		i -= (8 * sizeof(decimal));
	}

	while (i--)
		rshiftby1();
	return *this;
}
superfloat& superfloat::operator<<=(const unsigned int& other)
{
	if (other == 0)
		return *this;

	unsigned int k = other;

	while (k >= 8 * sizeof(decimal))
	{
		list.push_front(0);
		k -= 8 * sizeof(decimal);
	}

	while (k != 0)
	{
		lshiftby1();
		--k;
	}

	return *this;
}
superfloat& superfloat::operator>>=(const unsigned int& other)
{
	if (other == 0)
		return *this;


}
superfloat& superfloat::operator<<=(const decimal& other)
{
	if (other == 0)
		return *this;
	decimal k = other;

	while (k >= 8 * sizeof(decimal))
	{
		list.push_front(0);
		k -= 8 * sizeof(decimal);
	}

	while (k != 0)
	{
		lshiftby1();
		--k;
	}
	return *this;
}
superfloat& superfloat::operator>>=(const decimal& other)
{

}

const superfloat& superfloat::operator%(const superfloat& other) const
{
	superfloat copy = *this;
	return copy %= other;
}
const int& superfloat::operator%(const int& other) const
{
	superfloat copy = *this;
	return copy %= other;
}
const unsigned int& superfloat::operator%(const unsigned int& other) const
{
	superfloat copy = *this;
	copy %= other;

	return unsigned int(copy);

}
const decimal& superfloat::operator%(const decimal& other) const
{
	superfloat copy = *this;
	return copy %= other;
}
superfloat& superfloat::operator%=(const superfloat& other)
{
	while (*this >= other)
		*this -= other;
	return *this;
}
superfloat& superfloat::operator%=(const int& other)
{
	if (other == 0)
	{
		list.clear();
		unitoff = INFINITY;
		negative = false;

		return *this;
	}

	if (other < 0)
	{
		return *this %= -other;
	}



}
superfloat& superfloat::operator%=(const unsigned int& other)
{
	if (other == 0)
	{
		list.clear();
		unitoff = INFINITY;
		negative = false;

		return *this;
	}

	if (ifPower2(other))
		return *this &= (other - 1);
	


}
superfloat& superfloat::operator%=(const decimal& other)
{
	if (other == 0)
	{
		list.clear();
		unitoff = INFINITY;
		negative = false;

		return *this;
	}
	if (ifPower2(other))
		return *this &= (other - 1);
	while (*this >= other)
		*this -= other;
	return *this;
}

const superfloat& superfloat::operator<<(const int& other) const
{
	superfloat copy(*this);
	return copy <<= other;
}
const superfloat& superfloat::operator>>(const int& other) const
{
	superfloat copy(*this);
	return copy >>= other;
}
const superfloat& superfloat::operator<<(const decimal& other) const
{
	superfloat copy(*this);
	return copy <<= other;
}
const superfloat& superfloat::operator>>(const decimal& other) const
{
	superfloat copy(*this);
	return copy >>= other;
}
const superfloat& superfloat::operator&(const unsigned int& other) const
{
	if (other == 0)
		return 0;
	superfloat copy = *this;
	return copy &= other;
}
const superfloat& superfloat::operator&(const decimal& other)const
{
	if (other == 0)
		return 0;
	superfloat copy = *this;
	return copy &= other;
}
const superfloat& superfloat::operator&(const superfloat& other)const
{
	if (other == 0)
		return 0;
	superfloat copy = *this;
	return copy &= other;
}
const superfloat& superfloat::operator|(const unsigned int& other)const
{
	if (other == 0)
		return *this;
	superfloat copy = *this;
	return copy |= other;
}
const superfloat& superfloat::operator|(const decimal& other)const
{
	if (other == 0)
		return *this;
	superfloat copy = *this;
	return copy |= other;
}
const superfloat& superfloat::operator|(const superfloat& other)const
{
	superfloat copy = *this;
	return copy |= other;
}
const superfloat& superfloat::operator^(const unsigned int& other)const
{
	superfloat copy = *this;
	return copy ^= other;
}
const superfloat& superfloat::operator^(const decimal& other)const
{
	superfloat copy = *this;
	return copy ^= other;
}
const superfloat& superfloat::operator^(const superfloat& other)const
{
	superfloat copy = *this;
	return copy ^= other;
}

superfloat& superfloat::operator&=(const unsigned int& other)
{
	if (list.empty())
		return *this;
	decimal k = list.front();
	list.clear();
	k &= other;
	list.push_front(k);

	return *this;
}
superfloat& superfloat::operator&=(const decimal& other)
{
	if (list.empty())
		return *this;
	decimal k = list.front();
	list.clear();
	k &= other;
	list.push_front(k);

	return *this;
}
superfloat& superfloat::operator&=(const superfloat& other)
{	
	if (other.list.empty())
		return *this = 0;
	std::list<decimal>::iterator k;
	std::list<decimal>::const_iterator j;

	j = other.list.begin();
	for (k = list.begin(); k != list.end(); ++k)
	{
		if (j == other.list.end())
			*k = 0;
		else
		{
			*k &= *j;
			++j;
		}
		
	}


	return *this;
}


superfloat& superfloat::operator|=(const unsigned int& other)
{
	if (list.empty())
	{
		list.push_front(other);
		return *this;
	}

	list.front() |= other;
	return *this;
}
superfloat& superfloat::operator|=(const decimal& other)
{
	if (list.empty())
	{
		list.push_front(other);
		return *this;
	}

	list.front() |= other;
	return *this;
}
superfloat& superfloat::operator|=(const superfloat& other)
{
	if (other.list.empty())
		return *this;

	std::list<decimal>::iterator k;
	std::list<decimal>::const_iterator j;

	j = other.list.begin();

	for (k = list.begin(); k != list.end(); ++k)
	{
		if (j == other.list.end())
			return *this;
		*k |= *j;
		++j;
	}

	while (j != other.list.end())
	{
		list.push_back(*j);
		++j;
	}


	return *this;
}

superfloat& superfloat::operator^=(const unsigned int& other)
{
	if (list.empty())
	{
		list.push_front(other);
		return *this;
	}

	list.front() ^= other;
	return *this;
}
superfloat& superfloat::operator^=(const decimal& other)
{
	if (list.empty())
	{
		list.push_front(other);
		return *this;
	}

	list.front() ^= other;
	return *this;
}
superfloat& superfloat::operator^=(const superfloat& other)
{
	if (other.list.empty())
		return *this;

	std::list<decimal>::iterator k;
	std::list<decimal>::const_iterator j;

	j = other.list.begin();
	for (k = list.begin(); k != list.end(); ++k)
	{
		if (j == other.list.end())
			return *this;
		*k ^= *j;
		++j;
	}

	while (j != other.list.end())
	{
		list.push_back(*j);
		++j;
	}

	return *this;
}

const bool& superfloat::operator==(const superfloat& other) const
{
	//collapse();

	if (list.empty() && other.list.empty())
		return true;
	if (list.size() != other.list.size())
		return false;

	std::list<decimal>::const_iterator runner;
	std::list<decimal>::const_iterator i;
	i = other.list.begin();
	runner = list.begin();

	while (true)
	{
		if (runner == list.end())
			return true;
		if (*i != *runner)
			return false;
		++i;
		++runner;
	}
}
const bool& superfloat::operator!=(const superfloat& other)const
{
	return !(*this == other);
}
const bool& superfloat::operator>=(const superfloat& other)const
{
	if (negative ^ other.negative)
		return !negative;
	if (negative)
	{
		//other is also negative
		if (list.size() != other.list.size())
			return list.size() < other.list.size();
		return iterateSmaller(other) > 0;
	}

	//both aren't negative
	if (list.size() != other.list.size())
		return list.size() > other.list.size();
	return iterateBigger(other) > 0;
}
const bool& superfloat::operator<=(const superfloat& other)const
{
	if (negative ^ other.negative)
		return negative;
	if (negative)
	{
		//other is also negative
		if (list.size() != other.list.size())
			return list.size() > other.list.size();
		return iterateBigger(other);
	}

	//both aren't negative
	if (list.size() != other.list.size())
		return list.size() < other.list.size();
	return iterateSmaller(other) > 0;
}
const bool& superfloat::operator>(const superfloat& other)const
{
	if (negative ^ other.negative)
		return !negative;
	
	if (negative)
	{
		if (list.size() != other.list.size())
			return list.size() < other.list.size();
		return iterateSmaller(other) == 1;
	}

	if (list.size() != other.list.size())
		return list.size() > other.list.size();
	return iterateBigger(other) == 1;
}
const bool& superfloat::operator<(const superfloat& other)const
{
	if (negative ^ other.negative)
		return negative;
	if (negative)
	{
		if (list.size() != other.list.size())
			return list.size() > other.list.size();
		return iterateBigger(other) == 1;
	}

	if (list.size() != other.list.size())
		return list.size() < other.list.size();
	return iterateSmaller(other) == 1;
}
const bool& superfloat::operator==(const int& other)const
{
	if (unitoff != 0.0f)
		return false;
	if (list.empty())
		return other == 0;
	if ((other < 0) ^ (negative))
		return false;
	unsigned int val = other < 0 ? -other : other;
	if (list.size() == 1)
		return list.front() == val;
	return false;
}
const bool& superfloat::operator!=(const int& other)const
{
	return !(*this == other);
}
const bool& superfloat::operator>=(const int& other)const
{
	if (negative ^ (other < 0))
		return !negative;
	//if negative then we know that other < 0
	//if other < 0 then negative
	//if !negative then other >= 0
	if (negative)
	{	//other < 0 // other other <= -1
		if (list.empty())
			return true;
		if (list.size() == 1)
		{
			if (list.front() < -other)
				return true;
			return ((list.front() == -other) && (unitoff == 0.0f));
		}
		return false;
	}

	//other >= 0
	if (list.empty())
		return other == 0;
	if (list.size() == 1)
		return list.front() >= other;
	return true;
}
const bool& superfloat::operator<=(const int& other)const
{
	if (negative ^ (other < 0))
		return negative;
	if (negative)
	{
		//other < 0
		if (list.empty())
			return false;
		if (list.size() == 1)
			return list.front() >= -other;
		return true;
	}

	//other >= 0
	if (list.empty())
	{
		if (other == 0)
			return unitoff == 0.0f;
		return true;
	}
	if (list.size() == 1)
	{
		if (list.front() < other)
			return true;
		if (list.front() == other)
			return unitoff == 0.0f;
		return false;
	}

	return false;
}
const bool& superfloat::operator>(const int& other)const
{
	return !(*this <= other);
}
const bool& superfloat::operator<(const int& other) const
{
	return !(*this >= other);
}
const bool& superfloat::operator==(const unsigned int& other) const
{
	if (negative)
		return false;
	if (unitoff != 0.0f)
		return false;
	if (list.size() == 0)
		return (other == 0);
	if (list.size() == 1)
		return list.front() == other;
	return false;
}
const bool& superfloat::operator!=(const unsigned int& other) const
{
	return !(*this == other);
}
const bool& superfloat::operator>=(const unsigned int& other) const
{
	if (negative)
		return false;
	if (list.size() == 0)
		return other == 0;
	if (list.size() == 1)
		return list.front() >= other;
	return true;
}
const bool& superfloat::operator<=(const unsigned int& other) const
{
	if (negative)
		return true;
	if (list.empty())
		return (other != 0) || ((other == 0) && (unitoff == 0.0f));
	if (list.size() == 1)
	{
		if (list.front() < other)
			return true;
		if ((list.front() == other) && (unitoff == 0.0f))
			return true;
		return false;
	}
	return false;
}
const bool& superfloat::operator>(const unsigned int& other) const
{
	if (negative)
		return false;
	if (list.size() == 0)
		return (other == 0) && (unitoff > 0.0f);
	if (list.size() == 1)
		return (list.front() > other) || ((list.front() == other) && (unitoff != 0.0f));
	return true;//list has at least 2 values stored, impossible to be smaller
}
const bool& superfloat::operator<(const unsigned int& other) const
{
	if (negative)
		return true;
	if (list.size() == 0)
		return other != 0;
	if (list.size() == 1)
		return list.front() < other;
	return false;
}
const bool& superfloat::operator==(const decimal& other)const
{
	if (negative)
		return false;
	if (unitoff != 0.0f)
		return false;
	if (list.size() == 0)
		return (other == 0);
	if (list.size() == 1)
		return list.front() == other;
	return false;
}
const bool& superfloat::operator!=(const decimal& other)const
{
	return !(*this == other);
}
const bool& superfloat::operator>=(const decimal& other)const
{
	if (negative)
		return false;
	if (list.size() == 0)
		return other == 0;
	if (list.size() == 1)
		return list.front() >= other;
	return true;
}
const bool& superfloat::operator<=(const decimal& other)const
{
	if (negative)
		return false;
	if (list.size() == 0)
		return (other != 0) || ((other == 0) && (unitoff == 0.0f));
	if (list.size() == 1)
	{
		if (list.front() < other)
			return true;
		if ((list.front() == other) && (unitoff == 0.0f))
			return true;
		return false;
	}
	return false;
}
const bool& superfloat::operator>(const decimal& other)const
{
	if (negative)
		return false;
	if (list.size() == 0)
		return (other == 0) && (unitoff != 0.0f);
	if (list.size() == 1)
		return (list.front() > other) || ((list.front() == other) && (unitoff != 0.0f));
	return true;//list has at least 2 values stored, impossible to be smaller
}
const bool& superfloat::operator<(const decimal& other) const
{
	if (negative)
		return true;
	if (list.size() == 0)
		return other != 0;
	if (list.size() == 1)
		return list.front() < other;
	return false;

}



const bool& superfloat::operator==(const float& other)const
{
	superfloat x = 0;
	x += other;
	return *this == x;
}
const bool& superfloat::operator!=(const float& other)const
{
	return !(*this == other);
}
const bool& superfloat::operator>=(const float& other)const
{
	superfloat x = 0;
	x += other;
	return *this >= x;
}
const bool& superfloat::operator<=(const float& other) const
{
	superfloat x = 0;
	x += other;
	return *this <= x;
}
const bool& superfloat::operator>(const float& other) const
{
	superfloat x = 0;
	x += other;
	return *this > x;
}
const bool& superfloat::operator<(const float& other) const
{
	superfloat x = 0;
	x += other;
	return *this < x;
}



superfloat::~superfloat()
{
	list.clear();
}

inline const decimal& ifPower2(const decimal& num)
{
	if (num == 0)
		return 0;
	if (num == 1)
		return 0;
	decimal k = 0;
	decimal copy = num;
	while (copy != 1)
	{
		if (copy & 1)
			return 0;
		copy >>= 1;
		++k;
	}

	return k;
}

decimal activate_mbits(int num)
{
	int b;
	decimal a, c;
	a = 0b1000000000000000000000000000000000000000000000000000000000000000;
	b = 0;
	c = 0;

	for (b = 0; b < num; ++b)
	{
		c |= a;
		c >>= 1;
	}

	return c;
}
decimal activate_lbits(int num)
{
	int b;
	decimal a, c;
	a = 1;
	b = 0;
	c = 0;

	for (b = 0; b < num; ++b)
	{
		c |= a;
		c <<= 1;
	}

	return c;
}


bool collidewRect(float px, float py, float ox, float oy, uint32_t wwidth, uint32_t hheight)
{
	if ((px < ox) || (py < oy))
		return false;
	if ((px > ox + wwidth) || (py > oy + hheight))
		return false;
	return true;
}

void superint::dec()
{
	collapse();

	std::vector<int64_t>::iterator run;

	if (bZero)
	{
		bNegative = true;
		bZero = false;
		list.clear();
		list.push_back(-1);
		return;
	}

	if (!bNegative)
	{
		for (run = list.begin(); run != list.end(); ++run)
		{
			--(*run);
			if (*run < 0)
			{
				*run = LLONG_MAX;
			}
			else
				break;
		}

		collapse();
		if (list.empty())
		{
			bZero = true;
			bNegative = false;
			list.push_back(0);
		}
		return;
	}

	list.push_back(0);
	for (run = list.begin(); run != list.end(); ++run)
	{
		if (*run == LLONG_MIN)
		{
			*run = 0;
			continue;
		}
		else
		{
			--(*run);
			collapse();
			return;
		}
	}
	collapse();
	return;
}
void superint::inc()
{
	collapse();
	std::vector<int64_t>::iterator run;

	if (bZero)
	{
		bZero = false;
		bNegative = false;
		list.clear();
		list.push_back(1);
		return;
	}
	if (bNegative)
	{
		for (run = list.begin(); run != list.end(); ++run)
		{
			++(*run);
			if (*run > 0)
			{
				*run = LLONG_MIN;
			}
			else
				break;
		}

		collapse();
		if (list.empty())
		{
			bZero = true;
			bNegative = false;
			list.push_back(0); 
		}
		return;
	}
	
	list.push_back(0);
	for (run = list.begin(); run != list.end(); ++run)
	{
		if (*run == LLONG_MAX)
		{
			*run = 0;
			continue;
		}
		else
		{
			++(*run);
			collapse();
			return;
		}
	}
	collapse();
	return;
}
void superint::collapse()
{
	if (list.empty())
		return;

	std::vector<int64_t>::reverse_iterator runner;

	for (runner = list.rbegin(); runner != list.rend(); )
	{
		if (*runner == 0)
		{
			++runner;
			list.pop_back();
		}
		else return;
	}
	return;
}
bool superint::isPow2() const
{
	std::vector<int64_t>::const_reverse_iterator run;
	if (list.empty())
		return false;
	run = list.rbegin();
	if (ifPower2(*run) == 0)
		return false;
	++run;
	while (run != list.rend())
	{
		if (*run != 0)
			return false;
		++run;
	}

	return true;
}



superint::superint()
{
	bZero = false;
	bNegative = false;
}
superint::superint(int value)
{
	bZero = false;
	bNegative = false;

	if (value == 0)
		bZero = true;
	else if (value < 0)
		bNegative = true;

	list.push_back(value);
}
superint::superint(unsigned int value)
{
	bZero = false;
	bNegative = false;
	if (value == 0)
		bZero = true;

	list.push_back(value);
}
superint::superint(long int value)
{
	bZero = false;
	bNegative = false;
	if (value == 0)
		bZero = true;
	else if (value < 0)
		bNegative = true;

	list.push_back(value);
}
superint::superint(unsigned long int value)
{
	bZero = false;
	bNegative = false;
	if (value == 0)
		bZero = true;
	list.push_back(value);
}
superint::superint(long long int value)
{
	bZero = false;
	bNegative = false;
	if (value == 0)
		bZero = true;
	else if (value < 0)
		bNegative = true;
	list.push_back(value);
}
superint::superint(unsigned long long int value)
{
	bZero = false;
	bNegative = false;
	if (value == 0)
		bZero = true;
	list.push_back(value);
}


