#include "pch.h"
#include "Omino.h"

void Omino::Create(int id)
{
	_minoId = id;
	_minoType = 3;

	_boxes.insert(make_pair(0, 0));
	_boxes.insert(make_pair(-1, 0));
	_boxes.insert(make_pair(0, 1));
	_boxes.insert(make_pair(-1, 1));
}

void Omino::ShapeChange()
{
}
