#pragma once
#include "Command.h"
#include "PetterPepperComponent.h"
#include <memory>
#include <vector>
class DieCommand : public Command
{
public:
	void Execute() override
	{
		//GetObject()->GetComponent<dae::PetterPepperComponent>()->Die();
		std::cout << GetObject()->GetWorldPosition().GetPosition().x << " " << GetObject()->GetWorldPosition().GetPosition().y << " \n";
	}
	void Release() override {};
	DieCommand(dae::GameObject* go)
		:Command(go)
	{

	};
};

class PointCommand : public Command
{
public:
	void Execute() override
	{
		GetObject()->GetComponent<dae::PetterPepperComponent>()->AddPoints();
	}
	void Release() override {};
	PointCommand(dae::GameObject* go)
		:Command(go)
	{

	};
};

class PepperCommand : public Command
{
public:
	void Execute() override
	{
		GetObject()->GetComponent<dae::PetterPepperComponent>()->Pepper();
	}
	void Release() override{};

	PepperCommand(dae::GameObject* pGo)
		:Command(pGo)
	{
		
	}
};
