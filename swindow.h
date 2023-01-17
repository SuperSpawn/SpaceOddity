#pragma once
#include "genericfunc.h"


extern decimal windid;

class swindow
{
	string _name;
	olc::vi2d corner;
	uint32_t width, height;
	decimal _priority;

		
	unsigned int color;

	//dfunc _draw;

	decimal id, box_ids;
public:

	std::list<float> list;
	decimal number_of_boxes;
	std::vector<pspace::dcp> _box;

	olc::Sprite* sprite;

	//properties of the window
	
	swindow(const f2& nw, const f2& se, const string& name = "BLANK", const decimal& priority = 0);
	swindow(const f2& origin, decimal _width = 0, decimal _height = 0, const string& name = "BLANK", const decimal& priority = 0);
	swindow(float ox, float oy, decimal _width, decimal _height, const string& name, decimal priority);

	f2 _offset;
	void shift(const f2& shiftby);
	void shift(const float& shiftx = 0, const float& shifty = 0);

	void setScale(const f2& northw, const f2& southe);
	void setScale(float nwx, float nwy, float sex, float sey);

	void adjustScale(const f2& nwadj, const f2& seadj);
	void adjustScale(const float& nwxadj = 0, const float& nwyadj = 0, const float& sexadj = 0, const float& seyadj = 0);

	bool ifDraw();

	void addBox(cord2<uint32_t> box_pos, uint32_t box_width, uint32_t box_height, polyFunc* func);
	bool checkCollision(int mouse_x, int mouse_y);

	const olc::vi2d& getCorner();
	
	float getWidth();
	float getHeight();

	friend class spaceoddity;

	~swindow();
};

