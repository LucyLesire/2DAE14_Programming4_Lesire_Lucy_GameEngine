#include "BurgerTimeGame.h"

#include "BurgerTimeMainScene.h"
#include "SceneManager.h"

dae::BurgerTimeGame::BurgerTimeGame(uint32_t windowWidth, uint32_t windowHeight)
	:BaseGame(windowWidth, windowHeight)
{
	
}

void dae::BurgerTimeGame::CreateGameScenes()
{
	dae::SceneManager::GetInstance().CreateScene(std::make_shared<BurgerTimeMainScene>("Main"));
}

