#include "pch.h"
#include "Game.h"

//
// todo
// ��Ƽ �÷��̾� �߰�
//
//

int main() {



	Game game;
	
	// Ű �� �˾Ƴ��� �ڵ�
	/*while (true) {
		game.InputCommand();
	}*/
	

	game.TitlePage();
	game.SelectGameType();
	
	if (game.GetGameType() == SINGLE) {

	}
	else if (game.GetGameType() == MULTI) {

	}

	game.Init();


	// todo
	// ��Ƽ�÷��� ���� �� ������� �÷��̾� ���ÿ� �Է¹ް� ������ �Ѵ�.
	//p1->InputCommand();
	
	//game.CreateMino(); // �̸� 3�� ���� ����
	//game.InsertMino();

	ULONGLONG lastTick = 0;

	

	game.CreateMino();
	game.InsertMino();
	game.InputMinoFromBoard();
	
	while (true) {
		const auto currentTick = ::GetTickCount64();
		const auto deltaTick = currentTick - lastTick;

		lastTick = currentTick;
		game.InputCommand();

		game.Update(deltaTick);
		
	}
	
	
	return 0;
}