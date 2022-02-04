#include "pch.h"
#include "Game.h"

//
// todo
// 멀티 플레이어 추가
//
//

int main() {



	Game game;
	
	// 키 값 알아내는 코드
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
	// 멀티플레이 구현 시 스레드로 플레이어 동시에 입력받게 만들어야 한다.
	//p1->InputCommand();
	
	//game.CreateMino(); // 미리 3번 정도 진행
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