#include "swindow.h"

decimal windid = 0;


swindow::swindow(const f2& nw, const f2& se, const string& name, const decimal& priority)
{
	_name = name;
	_priority = priority;
	_offset = nw;
	number_of_boxes = 0;
	corner = { 0,0 };
	box_ids = 0;
	width = se.x - nw.x;
	height = se.y - nw.y;
	id = windid++;
	sprite = NULL;
}


swindow::swindow(const f2& origin, decimal _width, decimal _height, const string& name, const decimal& priority)
{
	_offset = origin;
	corner = { 0,0 };
	width = _width;
	height = _height;
	_name = name;
	_priority = priority;
	box_ids = 0;
	id = windid++;
	sprite = new olc::Sprite(width, height);
}

swindow::swindow(float ox, float oy, decimal _width = 0, decimal _height = 0, const string& name = "BLANK", decimal priority = 0)
{
	_priority = priority;
	_name = name;

	if ((width == 0) || (height == 0))
		return;
	_offset = { 0,0 };
	corner.x = ox;
	corner.y = oy;
	width = _width;
	height = _height;
	box_ids = 0;
	id = windid++;
	sprite = new olc::Sprite(width, height);
}
void swindow::shift(const f2& shiftby)
{
	corner.x += shiftby.x;
	corner.y += shiftby.y;

	return;
}

void swindow::shift(const float& shiftx, const float& shifty)
{
	corner.x += shiftx;
	corner.y += shifty;

	return;
}

void swindow::setScale(const f2& northw, const f2& southe)
{
	return;
}

void swindow::setScale(float nwx = 0, float nwy = 0, float sex = 0, float sey = 0)
{
	_offset.x = nwx;
	_offset.y = nwy;
	//should I reset corner[0]?
	corner.x = sex;
	corner.y = sey;

	return;
}

void swindow::adjustScale(const f2& nwadj, const f2& seadj)
{
	_offset.x += nwadj.x;
	_offset.y += nwadj.y;
	//should I reset corner[0]
	

	return;
}

void swindow::adjustScale(const float& nwxadj, const float& nwyadj, const float& sexadj, const float& seyadj)
{
	_offset.x += nwxadj;
	_offset.y += nwyadj;
	//TODO: Figure out if should reset corner[0]
	

	return;
}

bool swindow::ifDraw()
{
	return true;
}

void swindow::addBox(cord2<uint32_t> box_pos, uint32_t box_width, uint32_t box_height, polyFunc* func)
{
	if (func == nullptr)
		return;
	pspace::dcp bbox;
	bbox.function = func;
	bbox.pos = box_pos;
	bbox.width = box_width;
	bbox.height = box_height;
	bbox.id = box_ids++;
	_box.push_back(bbox);
}

bool swindow::checkCollision(int mouse_x, int mouse_y)
{
	if ((mouse_x < corner.x) || (mouse_y < corner.y))
		return false;
	if ((mouse_x > (corner.x + width)) || (mouse_y > (corner.y + height)))
		return false;
	std::vector<pspace::dcp>::iterator k;
	for (k = _box.begin(); k != _box.end(); ++k)
	{
		pspace::dcp& refK = *k;
		if ((mouse_x < refK.pos.x) || (mouse_y < refK.pos.y))
			continue;
		if((mouse_x > (refK.pos.x + refK.width)) || (mouse_y > (refK.pos.y + refK.height)))
			continue;
		refK.function->activate();
	}
	return true;
}


const olc::vi2d& swindow::getCorner()
{
	return corner;
}

float swindow::getWidth()
{
	return corner.x;
}

float swindow::getHeight()
{
	return corner.y;
}


swindow::~swindow()
{
	unsigned int i, j;
	//convention: place pointers to existing objects in begining, color is their number
	/*
	for (i = 0; i < number_of_boxes; ++i)
	{

		if (_box[i].function.color == -1)
			continue;

		for (j = 0; j < _box[i].function.color; ++j)
			_box[i].function.args[j] = NULL;
		while (j < _box[i].function.argnum)
		{
			delete _box[i].function.args[j++];
		}

		if (_box[i].function.argnum == 1)
			delete _box[i].function.args;
		else
			delete[] _box[i].function.args;
	}
	*/
	_box.clear();
	list.clear();
	delete sprite;
}






