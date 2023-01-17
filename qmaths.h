#pragma once
#include <list>
#include <cmath>
#include <algorithm>
#include <vector>
#include <cstdint>



#define diff(a,b) (((a) > (b))?((a)-(b)):((b)-(a)))
#define PI 3.14159265359

//array is big but saves alot of calculation 
#define SIN_TABLE_ACCURACY 9001
#define SUPERFLOAT_SHIFT_AMOUNT 1
#define SEEDS_PER_NODE 4

#define myminimum(a,b) ((a)<(b)?(a):(b))
#define myminimum3(a,b,c) ((c) < ((a)<(b)?(a):(b)) ? (c) : ((a)<(b)?(a):(b)))
#define mymaximum3(a,b,c) ((c) > ((a)>(b)?(a):(b)) ? (c) : ((a)>(b)?(a):(b)))

typedef unsigned char byte;
typedef unsigned long long int decimal;

extern float* _sintable;
extern float* _tantable;
extern const decimal _partial_seed;



struct superfloat
{
private:
	void handleAddition(const int& other);
	void handleAddition(const float& other);
	void handleAddition(const unsigned int& other);
	void handleAddition(decimal other);
	void handleAddition(const superfloat& other);
	const byte& iterateBigger(const superfloat& other) const;
	const byte& iterateSmaller(const superfloat& other) const;
	inline void lshiftby1(const bool& staticmode = false);
	inline void rshiftby1(const bool& staticmode = false);
	const int& moduleByint(const int& number);


	inline void decby1();
	inline void incby1();

	bool cmp0(char mode);

	//friend const superfloat& pureSub2(const superfloat& first, const superfloat& second);

	superfloat& pureAdd(const superfloat& other);
	superfloat& pureSub(const superfloat& other);

	void collapse();//delete end nodes with value 0

	std::list<decimal>::iterator spec;

	

public:

	bool negative;
	std::list<decimal> list;
	float unitoff;
	//double unitoff;

	superfloat();
	superfloat(const int& value);
	superfloat(const float& value);
	superfloat(const decimal& value);
	superfloat(const superfloat& other);

	void divbypow2(const int& num);
	void divbypow2(const float& num);
	void divbypow2(const unsigned int& num);
	void divbypow2(const decimal& num);

	void appendSuper(const superfloat& other);

	operator int();//risky on large numbers
	operator float();//risky on large numbers
	operator unsigned int();
	operator decimal();

	superfloat& operator++();
	const superfloat& operator++(int);

	superfloat& operator--();
	const superfloat& operator--(int);

	friend int srndInt(int min, int max);


	const superfloat& operator+(const superfloat& other)	const;
	const superfloat& operator+(const int& other)			const;
	const superfloat& operator+(const float& other)			const;
	const superfloat& operator+(const unsigned int& other)	const;
	const superfloat& operator+(const decimal& other)		const;


	const superfloat& operator-(const superfloat& other)	const;
	const superfloat& operator-(const int& other)			const;
	const superfloat& operator-(const float& other)			const;
	const superfloat& operator-(const unsigned int& other)	const;
	const superfloat& operator-(const decimal& other)		const;
	const superfloat& operator-() const;

	const superfloat& operator*(const superfloat& other)	const;
	const superfloat& operator*(const int& other)			const;
	const superfloat& operator*(const float& other)			const;
	const superfloat& operator*(const unsigned int& other)	const;
	const superfloat& operator*(const decimal& other)		const;


	const superfloat& operator/(const superfloat& other)	const;
	const superfloat& operator/(const int& other)			const;
	const superfloat& operator/(const float& other)			const;
	const superfloat& operator/(const unsigned int& other)	const;
	const superfloat& operator/(const decimal& other)		const;

	superfloat& operator=(const superfloat& other);
	superfloat& operator=(const int& other);
	superfloat& operator=(const float& other);
	superfloat& operator=(const unsigned int& other);
	superfloat& operator=(const decimal& other);

	superfloat& operator+=(const superfloat& other);
	superfloat& operator+=(const int& other);
	superfloat& operator+=(const float& other);
	superfloat& operator+=(const unsigned int& other);
	superfloat& operator+=(const decimal& other);

	superfloat& operator-=(const superfloat& other);
	superfloat& operator-=(const int& other);
	superfloat& operator-=(const float& other);
	superfloat& operator-=(const unsigned int& other);
	superfloat& operator-=(const decimal& other);

	superfloat& operator*=(const superfloat& other);
	superfloat& operator*=(const int& other);
	superfloat& operator*=(const float& other);
	superfloat& operator*=(const unsigned int& other);
	superfloat& operator*=(const decimal& other);

	superfloat& operator/=(const superfloat& other);
	superfloat& operator/=(const int& other);
	superfloat& operator/=(const float& other);
	superfloat& operator/=(const unsigned int& other);
	superfloat& operator/=(const decimal& other);

	superfloat& operator<<=(const int& other);
	superfloat& operator>>=(const int& other);
	superfloat& operator<<=(const unsigned int& other);
	superfloat& operator>>=(const unsigned int& other);
	superfloat& operator<<=(const decimal& other);
	superfloat& operator>>=(const decimal& other);
	//superfloat& operator<<=(const superfloat& other);
	//superfloat& operator>>=(const superfloat& other);


	const superfloat& operator%(const superfloat& other) const;
	const int& operator%(const int& other) const;
	const unsigned int& operator%(const unsigned int& other) const;
	const decimal& operator%(const decimal& other) const;
	
	superfloat& operator%=(const superfloat& other);
	superfloat& operator%=(const int& other);
	superfloat& operator%=(const unsigned int& other);
	superfloat& operator%=(const decimal& other);

	


	const superfloat& operator<<(const int& other)			const;
	const superfloat& operator>>(const int& other)			const;
	const superfloat& operator<<(const decimal& other)		const;
	const superfloat& operator>>(const decimal& other)		const;
	const superfloat& operator&(const unsigned int& other)	const;
	const superfloat& operator&(const decimal& other)		const;
	const superfloat& operator&(const superfloat& other)	const;
	const superfloat& operator|(const unsigned int& other)	const;
	const superfloat& operator|(const decimal& other)		const;
	const superfloat& operator|(const superfloat& other)	const;
	const superfloat& operator^(const unsigned int& other)	const;
	const superfloat& operator^(const decimal& other)		const;
	const superfloat& operator^(const superfloat& other)	const;		

	superfloat& operator&=(const unsigned int& other);
	superfloat& operator&=(const decimal& other);
	superfloat& operator&=(const superfloat& other);


	superfloat& operator|=(const unsigned int& other);
	superfloat& operator|=(const decimal& other);
	superfloat& operator|=(const superfloat& other);
	
	
	superfloat& operator^=(const unsigned int& other);
	superfloat& operator^=(const decimal& other);
	superfloat& operator^=(const superfloat& other);

	//const superfloat& operator<<(const superfloat& other);
	//const superfloat& operator>>(const superfloat& other);

	const bool& operator==(const superfloat& other) const;
	const bool& operator!=(const superfloat& other) const;
	const bool& operator>=(const superfloat& other) const;
	const bool& operator<=(const superfloat& other) const;
	const bool& operator>(const superfloat& other) const;
	const bool& operator<(const superfloat& other) const;

	const bool& operator==(const int& other) const;
	const bool& operator!=(const int& other) const;
	const bool& operator>=(const int& other) const;
	const bool& operator<=(const int& other) const;
	const bool& operator>(const int& other) const;
	const bool& operator<(const int& other) const;

	const bool& operator==(const unsigned int& other) const;
	const bool& operator!=(const unsigned int& other) const;
	const bool& operator>=(const unsigned int& other) const;
	const bool& operator<=(const unsigned int& other) const;
	const bool& operator>(const unsigned int& other) const;
	const bool& operator<(const unsigned int& other) const;

	const bool& operator==(const decimal& other) const;
	const bool& operator!=(const decimal& other) const;
	const bool& operator>=(const decimal& other) const;
	const bool& operator<=(const decimal& other) const;
	const bool& operator>(const decimal& other) const;
	const bool& operator<(const decimal& other) const;

	const bool& operator==(const float& other) const;
	const bool& operator!=(const float& other) const;
	const bool& operator>=(const float& other) const;
	const bool& operator<=(const float& other) const;
	const bool& operator>(const float& other) const;
	const bool& operator<(const float& other) const;





	~superfloat();
};


struct superint
{
private:
	void collapse();
	bool isPow2() const;
	
public:

	bool bZero, bNegative;

	std::vector<int64_t> list;

	void dec();
	void inc();

	superint();
	superint(int value);
	superint(unsigned int value);
	superint(long int value);
	superint(unsigned long int value);
	superint(long long int value);
	superint(unsigned long long int value);
};

template<typename t>
struct cord2
{
	t x, y;


	cord2()
	{

	}
	cord2(t _x, t _y)
	{
		x = _x;
		y = _y;
	}

	cord2& operator+=(const cord2& other)
	{
		x += other.x;
		y += other.y;

		return *this;
	}
	cord2& operator-=(const cord2& other)
	{
		x -= other.x;
		y -= other.y;

		return *this;
	}
	cord2& operator=(const cord2& other)
	{
		x = other.x;
		y = other.y;

		return *this;
	}
};

struct f2
{
	float x, y;

	f2& operator+=(const f2& other)
	{
		x += other.x;
		y += other.y;

		

		return *this;
	}

	f2& operator-=(const f2& other)
	{
		x -= other.x;
		y -= other.y;

		return *this;
	}

	f2& operator=(const f2& other)
	{
		x = other.x;
		y = other.y;

		return *this;
	}
};


const double& qsqrtd(const double& number);
const float& qsqrtf(const float& number);
const double& generatePi(const unsigned long int& accuracy);


//const float& Q_rsqrt(float number);

float Q_rsqrt(float number);//copied from Quake 3
											//thanks John Carmack
const double& toRAD(const float& number);
const double& toDEG(const float& number);


float* generateSinTable();
float* generateTanTable();

const float& mysinf(const float& number);
const float& mysinf2(const float& number);

const float& mycosf(const float& number);
const float& mycosf2(const float& number);

const float& mytanf(const float& number);
const float& mytanf2(const float& number);
const float& mytanf3(const float& number);

const f2& rotateAt(const f2& origin, const float& rotate, const float& sx = 0.0f, const float& sy = 0.0f);

//normalize vector before using this
const float& degVec(const float& x1, const float& y1, const float& x2 = 0, const float& y2 = 0,
	const float& stx = 0, const float& sty = 0);

inline const decimal& ifPower2(const decimal& num);

decimal activate_mbits(int num);
decimal activate_lbits(int num);

bool collidewRect(float px, float py, float ox, float oy, uint32_t wwidth, uint32_t hheight);
