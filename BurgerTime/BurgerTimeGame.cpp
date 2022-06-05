#include "BurgerTimeGame.h"

#include "BurgerTimeMainScene.h"
#include "BurgerTimeMenu.h"
#include "SceneManager.h"

dae::BurgerTimeGame::BurgerTimeGame(uint32_t windowWidth, uint32_t windowHeight)
	:BaseGame(windowWidth, windowHeight)
{
	
}

void dae::BurgerTimeGame::CreateGameScenes()
{
	std::shared_ptr<BurgerTimeMenu> menuScene = std::make_shared<BurgerTimeMenu>("Menu", GetWindowWidth(), GetWindowHeight(), 0);
	dae::SceneManager::GetInstance().CreateScene(menuScene);
	dae::SceneManager::GetInstance().CreateScene(std::make_shared<BurgerTimeMainScene>("Main", GetWindowWidth(), GetWindowHeight(), 1));

	dae::SceneManager::GetInstance().SetActiveScene(menuScene);
}

