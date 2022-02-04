#include "pch.h"
#include "ConsoleTool.h"
#include <fcntl.h>
#include <io.h>
#include "Game.h"

void Game::SelectGameType()
{
	int type = 0;
	while (true) {
		if (_kbhit()) {
			// todo
			// 방향키로 게임 타입 선택
			system("cls");
			if (type == SINGLE) {
				_gameType = SINGLE;
				return;
			}
			if (type == MULTI) {
				_gameType = MULTI;
				return;
			}
		}
	}
}

void Game::Init()
{
	ConsoleTool::ShowConsoleCursor(false);

	if (_gameType == SINGLE) {
		srand(static_cast<unsigned int>(time(NULL)));
		_board = vector<vector<vector<int>>>(2, vector<vector<int>>(Vertical, vector<int>(Horizontal, -1)));
		_mainBoard = vector<vector<int>>(vector<vector<int>>(Vertical, vector<int>(Horizontal, -1)));

		Player p1;
		_playerList.push_back(p1);
		system("mode con cols=70 lines=40 | title Console Tetris");
		BoardInit();
		InitCollutionCoorList();
		ScorePage();
	}
	else {

	}

}

void Game::TitlePage()
{
	system("mode con cols=110 lines=50 | title Console Tetris");
	ConsoleTool::SetCursorPosition(15, 10);
	cout << "    TTTTTTTTTT   EEEEEEEEE   TTTTTTTTTT   RRRRR        IIIIII      sssssssss    " << endl;
	ConsoleTool::SetCursorPosition(15, 11);
	cout << "        TT       E               TT       R     R        II       s             " << endl;
	ConsoleTool::SetCursorPosition(15, 12);
	cout << "        TT       E               TT       R      R       II      s              " << endl;
	ConsoleTool::SetCursorPosition(15, 13);
	cout << "        TT       E               TT       R      R       II       s             " << endl;
	ConsoleTool::SetCursorPosition(15, 14);
	cout << "        TT       EEEEEEEEE       TT       R     R        II        sssssssss    " << endl;
	ConsoleTool::SetCursorPosition(15, 15);
	cout << "        TT       E               TT       RRRRR          II                 s   " << endl;
	ConsoleTool::SetCursorPosition(15, 16);
	cout << "        TT       E               TT       R     R        II                  s  " << endl;
	ConsoleTool::SetCursorPosition(15, 17);
	cout << "        TT       E               TT       R      R       II                 s   " << endl;
	ConsoleTool::SetCursorPosition(15, 18);
	cout << "        TT       EEEEEEEEE       TT       R       R    IIIIII      sssssssss    " << endl;
	cout << endl;
	cout << endl;
	cout << endl;
	cout << endl;
	cout << endl;
	cout << endl;
	ConsoleTool::SetCursorPosition(40, 25);
	cout << "Enter any key to start the game." << endl;
}

void Game::Render(void (Game::*PMEMFUNC)(void))
{
	int FI = GetFrontBufferIndex();
	int BI = GetBackBufferIndex();

	for (int i = 0; i < Vertical; i++) {
		for (int j = 0; j < Horizontal; j++) {
			if (_board[BI][i][j] != _mainBoard[i][j]) {
				_board[BI][i][j] = _mainBoard[i][j];
			}
		}
	}

	//EraseMinoFromBoard(BI);
	if (PMEMFUNC != nullptr) {
		(this->*PMEMFUNC)();
		PMEMFUNC = nullptr;
	}
	
	//AutoRightMove();
	//AutoDownMove();
	//InputMinoFromBoard(BI);

	DrawFrontBuffer();
	SwapBufferIndex();
}

int Game::CreateMino()
{
	int type = rand() % 7;
	
	// 보드의 총 크기는 200칸이므로 반드시 미노가 200개 이상일 순 없다.
	if (_minoCount >= 200) {
		_minoCount = (_minoCount % 200) + 1;
	}
	else {
		++_minoCount;
	}

	int id = _minoCount;
	shared_ptr<Mino> mino;
	_minoqueue.push(id);

	switch (type) {

	case 0:
		mino = make_shared<Imino>();
		mino->Create(id);
		_unUsedMinoList.insert(make_pair(_minoCount, mino));
		break;

	case 1:
		mino = make_shared<Lmino>();
		mino->Create(id);
		_unUsedMinoList.insert(make_pair(_minoCount, mino));
		break;

	case 2:
		mino = make_shared<Jmino>();
		mino->Create(id);
		_unUsedMinoList.insert(make_pair(_minoCount, mino));
		break;

	case 3:
		mino = make_shared<Omino>();
		mino->Create(id);
		_unUsedMinoList.insert(make_pair(_minoCount, mino));
		break;

	case 4:
		mino = make_shared<Smino>();
		mino->Create(id);
		_unUsedMinoList.insert(make_pair(_minoCount, mino));
		break;

	case 5:
		mino = make_shared<Zmino>();
		mino->Create(id);
		_unUsedMinoList.insert(make_pair(_minoCount, mino));
		break;

	case 6:
		mino = make_shared<Tmino>();
		mino->Create(id);
		_unUsedMinoList.insert(make_pair(_minoCount, mino));
		break;

	default : 
		break;
	}
	
	return id;
}

void Game::CreatePlayer()
{
}

void Game::BoardInit()
{
	_setmode(_fileno(stdout), _O_U8TEXT);
	for (int k = 0; k < 2; k++) {
		for (int i = 0; i < Vertical; i++) {
			if (i < TopEndIndex || i >= BottomEndIndex) {
				for (int j = 0; j < Horizontal; j++) {
					_board[k][i][j] = -1;
					if (k == 0) {
						wprintf(wall);
					}
				}
			}
			else {
				for (int j = 0; j < Horizontal; j++) {
					if (j < LeftEndIndex || j >= RightEndIndex) {
						_board[k][i][j] = -1;
						if (k == 0) {
							wprintf(wall);
						}
					}
					else {
						_board[k][i][j] = 0;
						if (k == 0) {
							wprintf(L"  ");
						}
					}
				}
			}
			if (k == 0) {
				wprintf(L"\n");
			}
		}
	}

	
	for (int i = 0; i < Vertical; i++) {
		if (i < TopEndIndex || i >= BottomEndIndex) {
			for (int j = 0; j < Horizontal; j++) {
				_mainBoard[i][j] = -1;
			}
		}
		else {
			for (int j = 0; j < Horizontal; j++) {
				if (j < LeftEndIndex || j >= RightEndIndex) {
					_mainBoard[i][j] = -1;
				}
				else {
					_mainBoard[i][j] = 0;
				}
			}
		}
	}
	

}

void Game::InsertMino()
{
	_currentMino = _unUsedMinoList.find(_minoqueue.front());
	_minoqueue.pop();

	InputMinoFromBoard();
}

void Game::SwapUsedMino()
{
	_usedMinoList.insert(make_pair(_currentMino->first, _currentMino->second));
	_unUsedMinoList.erase(_currentMino->first);
}

void Game::Update(ULONGLONG deltaTick)
{
	_sumTick += deltaTick;
	if (_sumTick >= MOVE_TICK) {
		_sumTick = 0;

		if (Collusion() == true) {
			SwapUsedMino();
			if (LineDelete() == true) {
				Render(nullptr);
				ScoreUpdate();
			}
			CreateMino();
			InsertMino();
		}

		Render(&Game::AutoDownMove);
	}
}

void Game::DrawFrontBuffer()
{
	_setmode(_fileno(stdout), _O_U8TEXT);

	int Idx = GetFrontBufferIndex();

	for (int i = TopEndIndex; i < BottomEndIndex; i++) {
		for (int j = LeftEndIndex; j < RightEndIndex; j++) {
			ConsoleTool::SetCursorPosition((j+1) * 2, i);
			if (_board[Idx][i][j] == 0) {
				wprintf(L"\b\b");
				wprintf(L"  ");
			}
			else if (_board[Idx][i][j] > 0) {
				wprintf(L"\b\b");
				wprintf(block);
			}
		}
	}
}

void Game::InputMinoFromBoard()
{
	for (auto it = _currentMino->second->_boxes.begin(); it != _currentMino->second->_boxes.end(); ++it) {
		_mainBoard[it->first + _currentMino->second->_y][it->second + _currentMino->second->_x] = _currentMino->first;
	}
}

void Game::EraseMinoFromBoard()
{
	for (auto it = _currentMino->second->_boxes.begin(); it != _currentMino->second->_boxes.end(); ++it) {
		_mainBoard[it->first + _currentMino->second->_y][it->second + _currentMino->second->_x] = 0;
	}
}

bool Game::InputCommand()
{
	char c;
	/*if (_kbhit()) {
		c = _getch();
		printf("%d", c);
	}*/

	if (_kbhit()) {
		c = _getch();
		if (c == 32) {
			Render(&Game::FullDown);
			return true;
		}
		else if (c == SHAPECHANGE) {
			Render(&Game::MinoShapeChange);
			return true;
		}
		else if(c == -32) {
			c = _getch();
			switch (c) {
			case LEFT:
				Render(&Game::LeftMove);
				return true;
				
			case RIGHT:
				Render(&Game::RightMove);
				return true;
				
			default:
				return false;
			}
		}
		else {
			return false;
		}
	}
	return false;
}

void Game::RightMove()
{
	EraseMinoFromBoard();
	_currentMino->second->MoveRight();
	if (Collusion() == true) {
		_currentMino->second->MoveLeft();
	}
	InputMinoFromBoard();
}

void Game::LeftMove()
{
	EraseMinoFromBoard();
	_currentMino->second->MoveLeft();
	if (Collusion() == true) {
		_currentMino->second->MoveRight();
	}
	InputMinoFromBoard();
}

void Game::FullDown()
{
	EraseMinoFromBoard();
	while (Collusion() == false) {
		_currentMino->second->AutoDown();
	}
	InputMinoFromBoard();
}

void Game::AutoDownMove()
{
	EraseMinoFromBoard();
	_currentMino->second->AutoDown();
	InputMinoFromBoard();
}

bool Game::Collusion()
{
	int x = _currentMino->second->_x;
	int y = _currentMino->second->_y;
	int id = _currentMino->second->_minoId;


	for (auto it = _currentMino->second->_boxes.begin(); it != _currentMino->second->_boxes.end(); it++) {
		if ((it->second + x) <= LeftEndIndex - 1 || (it->second + x) > RightEndIndex-1) {
			return true;
		}
		else if ((it->first + y + 1) > BottomEndIndex) {
			return true;
		}
		else {
			if (_mainBoard[(it->first + y) + 1][(it->second + x)] != id) {
				if (_mainBoard[(it->first + y) + 1][(it->second + x)] > 0 || _mainBoard[(it->first + y) + 1][(it->second + x)] == -1) {
					return true;
				}
			}		
		}
	}
	return false;
}

void Game::MinoShapeChange()
{
	EraseMinoFromBoard();

	_currentMino->second->ShapeChange();

	int x = _currentMino->second->_x;
	int y = _currentMino->second->_y;

	for (auto it = _currentMino->second->_boxes.begin(); it != _currentMino->second->_boxes.end(); it++) {
		if (_mainBoard[(it->first + y)][it->second + x] == -1 || _mainBoard[(it->first + y)][it->second + x] > 0) {
			if (y - (it->first + y) > 0) {
				_currentMino->second->MoveUp();
			}
			if (x - (it->second + x) < 0) {
				_currentMino->second->MoveLeft();
			}
			if (x - (it->second + x) > 0) {
				_currentMino->second->MoveRight();
			}
		}
	}

	InputMinoFromBoard();
}

bool Game::LineDelete()
{
	// <라인 개수, 시작 y 좌표>
	stack<pair<int, int>> q;
	bool returnType = false;
	bool lineConnectionStatus = false;
	int count = 0;
	int lastY = 0;
	int totalLineCheckCount = 0;
	int Back = GetBackBufferIndex();

	while (true) {
		for (int y = BottomEndIndex - 1; y >= TopEndIndex; y--) {
			if (LineCheck(y) == true) {
				lineConnectionStatus = true;
				if (returnType == false) {
					returnType = true;
				}
				if (lastY < 1) {
					lastY = y;
				}
				count++;
			}
			else {
				if (lineConnectionStatus == true) {
					lineConnectionStatus = false;
					q.push(make_pair(count, lastY));
					lastY = 0;
					count = 0;
					break;
				}
				else {
					totalLineCheckCount++;
					continue;
					
				}
			}
		}

		while (!q.empty()) {
			auto temp = q.top();

			// 플레이어 객체의 맴버변수가 수정된다.
			_playerList[0].LineDeleteSuccess(temp.first);
			q.pop();

			for (int y = temp.second; y > (temp.second - temp.first); y--) {
				for (int x = LeftEndIndex; x < RightEndIndex; x++) {
					
					int index = _mainBoard[y][x];
					auto block = _usedMinoList.find(index);

					auto DeleteIterator = block->second->_boxes.find(make_pair((y - block->second->_y), (x - block->second->_x)));
					if (DeleteIterator != block->second->_boxes.end()) {
						block->second->_boxes.erase(DeleteIterator);
					}

					if (block->second->_boxes.size() == 0) {
						_usedMinoList.erase(block);
					}

					_mainBoard[y][x] = 0;
				}
			}

			for (int y = (temp.second - temp.first); y >= TopEndIndex; y--) {
				for (int x = LeftEndIndex; x < RightEndIndex; x++) {

					_mainBoard[y + temp.first][x] = _mainBoard[y][x];
					_mainBoard[y][x] = 0;
				}
			}
		}

		if (totalLineCheckCount >= BottomEndIndex - TopEndIndex) {
			break;
		}
		else {
			totalLineCheckCount = 0;
		}
	}

	return returnType;
}

bool Game::LineCheck(int y)
{
	int Back = GetBackBufferIndex();
	int count = 0;
	for (int x = LeftEndIndex; x < RightEndIndex; x++) {
		if (_mainBoard[y][x] > 0) {
			count++;
		}
	}
	if (count == (RightEndIndex - LeftEndIndex)) {
		return true;
	}
	return false;
}

void Game::InitCollutionCoorList()
{
	// <y, x>
	_collutionCoorList.push_back(make_pair(0, -1));
	_collutionCoorList.push_back(make_pair(0, +1));
	_collutionCoorList.push_back(make_pair(1, 0));
}

void Game::ScorePage()
{
	ConsoleTool::SetCursorPosition(40, 5);
	wprintf(L"SCORE : 0");

}

void Game::ScoreUpdate()
{
	int score = _playerList[0].GetScore();
	int count = 0;

	while (score > 0) {
		score = score / 10;
		count++;
	}

	ConsoleTool::SetCursorPosition(48 + count, 5);
	
	for (int i = 0; i < count; i++) {
		wprintf(L"\b");
	}
	wprintf(L"%d", _playerList[0].GetScore());
}
