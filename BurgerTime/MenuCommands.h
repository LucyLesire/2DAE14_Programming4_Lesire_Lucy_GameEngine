#pragma once
#include "Command.h"
#include "SceneManager.h"

class StartCommand : public Command
{
public:
	void Execute() override { dae::SceneManager::GetInstance().SetActiveScene(dae::SceneManager::GetInstance().GetSceneAtIndex(1)); }
	void Release() override { }

	StartCommand(dae::GameObject* go)
		:Command(go)
	{

	};
};

