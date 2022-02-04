#include "pch.h"
#include "Imino.h"

void Imino::Create(int id)
{
	_minoId = id;
	_minoType = 0;

	// y : 0, x : 1
	_boxes.insert(make_pair(0, 0));
	_boxes.insert(make_pair(0, -1));
	_boxes.insert(make_pair(0, 1));
	_boxes.insert(make_pair(0, 2));
}

void Imino::ShapeChange()
{
	_shapeChangeCount = (_shapeChangeCount + 1) % 2;

	if (_shapeChangeCount == 0) {
		_boxes.clear();
		
		_boxes.insert(make_pair(0, 0));
		_boxes.insert(make_pair(0, -1));
		_boxes.insert(make_pair(0, 1));
		_boxes.insert(make_pair(0, 2));
	}

	else {
		_boxes.clear();

		_boxes.insert(make_pair(0, 0));
		_boxes.insert(make_pair(-1, 0));
		_boxes.insert(make_pair(1, 0));
		_boxes.insert(make_pair(2, 0));
	}
	
}
