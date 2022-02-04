#include "pch.h"
#include "Jmino.h"

void Jmino::Create(int id)
{
	_minoId = id;
	_minoType = 2;

	_boxes.insert(make_pair(0, 0));
	_boxes.insert(make_pair(-1, 0));
	_boxes.insert(make_pair(1, 0));
	_boxes.insert(make_pair(1, -1));
}

void Jmino::ShapeChange()
{
	_shapeChangeCount = (_shapeChangeCount + 1) % 4;

	if (_shapeChangeCount == 0) {
		_boxes.clear();

		_boxes.insert(make_pair(0, 0));
		_boxes.insert(make_pair(-1, 0));
		_boxes.insert(make_pair(1, 0));
		_boxes.insert(make_pair(1, -1));
	}

	else if (_shapeChangeCount == 1) {
		_boxes.clear();

		_boxes.insert(make_pair(0, 0));
		_boxes.insert(make_pair(0, 1));
		_boxes.insert(make_pair(0, -1));
		_boxes.insert(make_pair(-1, -1));
	}

	else if (_shapeChangeCount == 2) {
		_boxes.clear();

		_boxes.insert(make_pair(0, 0));
		_boxes.insert(make_pair(1, 0));
		_boxes.insert(make_pair(-1, 0));
		_boxes.insert(make_pair(-1, 1));
	}

	else if (_shapeChangeCount == 3) {
		_boxes.clear();

		_boxes.insert(make_pair(0, 0));
		_boxes.insert(make_pair(0, -1));
		_boxes.insert(make_pair(0, 1));
		_boxes.insert(make_pair(1, 1));
	}
}
