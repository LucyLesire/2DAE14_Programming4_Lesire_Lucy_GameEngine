#if _DEBUG
#if __has_include(<vld.h>)
#include <vld.h>
#endif
#endif

#include "BurgerTimeGame.h"
#include "Minigin.h"



int main(int, char* []) {

	auto pCurrentGame = new dae::BurgerTimeGame();

	dae::Minigin engine;
	engine.Run(pCurrentGame);
	delete pCurrentGame;
	pCurrentGame = nullptr;
	return 0;
}