#include "pch.h"
#include "Zmino.h"

void Zmino::Create(int id)
{
	_minoId = id;
	_minoType = 5;

	_boxes.insert(make_pair(0, 0));
	_boxes.insert(make_pair(-1, 0));
	_boxes.insert(make_pair(-1, -1));
	_boxes.insert(make_pair(0, 1));
}

void Zmino::ShapeChange()
{
	_shapeChangeCount = (_shapeChangeCount + 1) % 2;

	if (_shapeChangeCount == 0) {
		_boxes.clear();

		_boxes.insert(make_pair(0, 0));
		_boxes.insert(make_pair(-1, 0));
		_boxes.insert(make_pair(-1, -1));
		_boxes.insert(make_pair(0, 1));
	}

	else if (_shapeChangeCount == 1) {
		_boxes.clear();

		_boxes.insert(make_pair(0, 0));
		_boxes.insert(make_pair(0, 1));
		_boxes.insert(make_pair(1, 0));
		_boxes.insert(make_pair(-1, 1));
	}
}
