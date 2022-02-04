#pragma once
// 만약 헤더안에서 
#include "Player.h"
#include "Imino.h"
#include "Lmino.h"
#include "Jmino.h"
#include "Omino.h"
#include "Smino.h"
#include "Zmino.h"
#include "Tmino.h"
//
// 여기서 고민한 점
// class Player와 class Mino를 통해 전방선언을 해주고
// game CPP 파일에 #include 를 해줬는데 오류가 발생.
// 헤더에선 전방선언을 통해 백터나 리스트가 참고하게 끔 했으나
// 전방선언은 어디까지나 있을 수 있다는 조언일 뿐 
// 실제로 값을 볼수있는 건 아니기에 vector나 리스트가 사이즈를 계산해야 하는
// 헤더에서 지금 당장 플레이어와 미노 클래스를 참조해야 하는데 그러지 못하는 것.
// 헤더가 먼저 컴파일 되고 난 뒤에 cpp파일이 컴파일 되는 것 같다.
// 만일 전방 선언을 하고 싶다면 가장먼서 컴파일 되는 pch에 #include를 해주면 되나
// 필요없는 곳에서도 mino와 player 클래스를 인클루드 시키기에 이게 맞는 방법인 것 같다.
// 게임을 인클루드하게 되면 하는 곳마다 플레이어와 미노 헤더가 같이 인클루드 되는데
// 게임은 main이라는 파일 한곳만 인클루드 하기 때문에 더욱더 맞는 방법이다.
class Game
{
public : 
	// 게임 초기화 관련 함수
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
	// 블록 생성 관련 함수
	int		CreateMino();
	void	InsertMino();
	void	SwapUsedMino();

public : 
	// 랜더링 관련 함수
	void	Render(void (Game::* PMEMFUNC)(void));
	void	Update(ULONGLONG deltaTick);
	int		GetFrontBufferIndex() { return (_BackBufferIndex + 1) % 2; };
	int		GetBackBufferIndex() { return _BackBufferIndex; };
	void	SwapBufferIndex() { _BackBufferIndex = (_BackBufferIndex + 1) % 2; };
	void	DrawFrontBuffer();

public : 
	// 블럭 조작 관련 함수
	void	RightMove();
	void	LeftMove();
	void	FullDown();
	void	AutoDownMove();
	void	InputMinoFromBoard();
	void	EraseMinoFromBoard();
	bool	Collusion();
	void	MinoShapeChange();

public : 
	// 블럭 삭제 관련 함수
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
	// 데이터 업데이트용
	vector<vector<int>>			_mainBoard;

	ULONGLONG					_sumTick = 0;
	int							_BackBufferIndex = 0;

	vector<Player>				_playerList;
	// <y, x>
	vector<pair<int, int>>		_collutionCoorList;

	map<int, shared_ptr<Mino>>				_usedMinoList;
	map<int, shared_ptr<Mino>>				_unUsedMinoList;

	queue<int>					_minoqueue;
	// 고민 
	// https://m.blog.naver.com/PostView.naver?isHttpsRedirect=true&blogId=bosskim185&logNo=150076487319
	map<int, shared_ptr<Mino>>::iterator	_currentMino;

};

//typedef void (Game::*PMEMFUNC)(void);

