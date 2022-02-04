#include "pch.h"
#include "Lmino.h"

void Lmino::Create(int id)
{
	_minoId = id;
	_minoType = 1;

	// y : 0, x : 1
	_boxes.insert(make_pair(0, 0));
	_boxes.insert(make_pair(-1, 0));
	_boxes.insert(make_pair(1, 0));
	_boxes.insert(make_pair(1, 1));
}

void Lmino::ShapeChange()
{
	_shapeChangeCount = (_shapeChangeCount + 1) % 4;

	if (_shapeChangeCount == 0) {
		_boxes.clear();

		_boxes.insert(make_pair(0, 0));
		_boxes.insert(make_pair(-1, 0));
		_boxes.insert(make_pair(1, 0));
		_boxes.insert(make_pair(1, 1));
	}

	else if (_shapeChangeCount == 1) {
		_boxes.clear();

		_boxes.insert(make_pair(0, 0));
		_boxes.insert(make_pair(0, 1));
		_boxes.insert(make_pair(0, -1));
		_boxes.insert(make_pair(1, -1));
	}

	else if (_shapeChangeCount == 2) {
		_boxes.clear();

		_boxes.insert(make_pair(0, 0));
		_boxes.insert(make_pair(1, 0));
		_boxes.insert(make_pair(-1, 0));
		_boxes.insert(make_pair(-1, -1));
	}

	else if (_shapeChangeCount == 3) {
		_boxes.clear();

		_boxes.insert(make_pair(0, 0));
		_boxes.insert(make_pair(0, -1));
		_boxes.insert(make_pair(0, 1));
		_boxes.insert(make_pair(-1, 1));
	}
}
