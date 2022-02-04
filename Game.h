#pragma once
// ���� ����ȿ��� 
#include "Player.h"
#include "Imino.h"
#include "Lmino.h"
#include "Jmino.h"
#include "Omino.h"
#include "Smino.h"
#include "Zmino.h"
#include "Tmino.h"
//
// ���⼭ ����� ��
// class Player�� class Mino�� ���� ���漱���� ���ְ�
// game CPP ���Ͽ� #include �� ����µ� ������ �߻�.
// ������� ���漱���� ���� ���ͳ� ����Ʈ�� �����ϰ� �� ������
// ���漱���� �������� ���� �� �ִٴ� ������ �� 
// ������ ���� �����ִ� �� �ƴϱ⿡ vector�� ����Ʈ�� ����� ����ؾ� �ϴ�
// ������� ���� ���� �÷��̾�� �̳� Ŭ������ �����ؾ� �ϴµ� �׷��� ���ϴ� ��.
// ����� ���� ������ �ǰ� �� �ڿ� cpp������ ������ �Ǵ� �� ����.
// ���� ���� ������ �ϰ� �ʹٸ� ����ռ� ������ �Ǵ� pch�� #include�� ���ָ� �ǳ�
// �ʿ���� �������� mino�� player Ŭ������ ��Ŭ��� ��Ű�⿡ �̰� �´� ����� �� ����.
// ������ ��Ŭ����ϰ� �Ǹ� �ϴ� ������ �÷��̾�� �̳� ����� ���� ��Ŭ��� �Ǵµ�
// ������ main�̶�� ���� �Ѱ��� ��Ŭ��� �ϱ� ������ ����� �´� ����̴�.
class Game
{
public : 
	// ���� �ʱ�ȭ ���� �Լ�
	void	SelectGameType();
	void	Init();
	void	TitlePage();
	int		GetGameType() { return _gameType; };
	void	CreatePlayer();
	void	BoardInit();
	bool	InputCommand();
	void	InitCollutionCoorList();
	void	ScorePage();
	void	ScoreUpdate();

public : 
	// ��� ���� ���� �Լ�
	int		CreateMino();
	void	InsertMino();
	void	SwapUsedMino();

public : 
	// ������ ���� �Լ�
	void	Render(void (Game::* PMEMFUNC)(void));
	void	Update(ULONGLONG deltaTick);
	int		GetFrontBufferIndex() { return (_BackBufferIndex + 1) % 2; };
	int		GetBackBufferIndex() { return _BackBufferIndex; };
	void	SwapBufferIndex() { _BackBufferIndex = (_BackBufferIndex + 1) % 2; };
	void	DrawFrontBuffer();

public : 
	// �� ���� ���� �Լ�
	void	RightMove();
	void	LeftMove();
	void	FullDown();
	void	AutoDownMove();
	void	InputMinoFromBoard();
	void	EraseMinoFromBoard();
	bool	Collusion();
	void	MinoShapeChange();

public : 
	// �� ���� ���� �Լ�
	bool	LineDelete();
	bool	LineCheck(int y);

private : 
	const wchar_t* wall = L"\U00002620";
	const wchar_t* block = L"\U00002605";
	int							_minoCount = 0;
	int							_gameType = SINGLE;

	// Double Rendering
	// 0 => Front, 1 => Back
	vector<vector<vector<int>>>	_board;
	// ������ ������Ʈ��
	vector<vector<int>>			_mainBoard;

	ULONGLONG					_sumTick = 0;
	int							_BackBufferIndex = 0;

	vector<Player>				_playerList;
	// <y, x>
	vector<pair<int, int>>		_collutionCoorList;

	map<int, shared_ptr<Mino>>				_usedMinoList;
	map<int, shared_ptr<Mino>>				_unUsedMinoList;

	queue<int>					_minoqueue;
	// ��� 
	// https://m.blog.naver.com/PostView.naver?isHttpsRedirect=true&blogId=bosskim185&logNo=150076487319
	map<int, shared_ptr<Mino>>::iterator	_currentMino;

};

//typedef void (Game::*PMEMFUNC)(void);

