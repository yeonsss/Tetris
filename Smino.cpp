#include "pch.h"
#include "Smino.h"

void Smino::Create(int id)
{
	_minoId = id;
	_minoType = 4;

	_boxes.insert(make_pair(0, 0));
	_boxes.insert(make_pair(0, -1));
	_boxes.insert(make_pair(-1, 0));
	_boxes.insert(make_pair(-1, 1));
}

void Smino::ShapeChange()
{
	_shapeChangeCount = (_shapeChangeCount + 1) % 2;

	if (_shapeChangeCount == 0) {
		_boxes.clear();

		_boxes.insert(make_pair(0, 0));
		_boxes.insert(make_pair(0, -1));
		_boxes.insert(make_pair(-1, 0));
		_boxes.insert(make_pair(-1, 1));
	}

	else if (_shapeChangeCount == 1) {
		_boxes.clear();

		_boxes.insert(make_pair(0, 0));
		_boxes.insert(make_pair(-1, 0));
		_boxes.insert(make_pair(0, 1));
		_boxes.insert(make_pair(1, 1));
	}
}
