#pragma once
#include <iostream>

#include "BaseComponent.h"
#include "GameObject.h"
#include "ServiceLocator.h"

class Command
{
protected:
	dae::GameObject* GetObject() const { return m_pGameObject; };
public:
	explicit Command(dae::GameObject* go)
		:m_pGameObject(go)
	{

	};
	virtual ~Command() = default;
	virtual void Execute() = 0;
	virtual void Release() = 0;

private:
	dae::GameObject* m_pGameObject = nullptr;
};

class AudioCommand : public Command
{
public:
	void Execute() override
	{
		dae::ServiceLocator::GetSoundSystem().Play(0, 100);
	};

	void Release() override {};

	AudioCommand()
		:Command(nullptr)
	{

	};
};



