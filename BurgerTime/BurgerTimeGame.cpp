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
	dae::SceneManager::GetInstance().CreateScene(std::make_shared<BurgerTimeMainScene>("Level1", GetWindowWidth(), GetWindowHeight(), 1, "Level1"));
	dae::SceneManager::GetInstance().CreateScene(std::make_shared<BurgerTimeMainScene>("Level2", GetWindowWidth(), GetWindowHeight(), 1, "Level2"));

	dae::SceneManager::GetInstance().SetActiveScene(menuScene);
}

