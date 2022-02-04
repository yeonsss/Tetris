#pragma once
class Mino
{
public : 

	virtual			~Mino() {};
	virtual void	Create(int id);
	virtual void	ShapeChange();
	void			AutoDown();
	void			MoveLeft();
	void			MoveRight();
	void			MoveUp();
	//bool			CheckMyBoxCoor(int x, int y);

public : 

	int	_x = static_cast<int>(RightEndIndex / 2);
	int	_y = TopEndIndex;
	int _shapeChangeCount = 0;
	int _minoType = 0;
	int	_minoId = 0;
	int _color = 0;
	// <y, x>
	set<pair<int, int>>	_boxes;
};

