#pragma once
#include "Command.h"
#include "PetterPepperComponent.h"
#include <memory>

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
