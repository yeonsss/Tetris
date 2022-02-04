#include "pch.h"
#include "Mino.h"

void Mino::AutoDown()
{
	_y += 1;
}

void Mino::Create(int id)
{
}

void Mino::ShapeChange()
{
	//switch(_minoType){

	//case 0 : 

	//	break;

	//case 1:
	//	break;

	//default : 
	//	break;
	//}
}

void Mino::MoveLeft()
{
	_x -= 1;
}

void Mino::MoveRight()
{
	_x += 1;
}

void Mino::MoveUp()
{
	_y -= 1;
}