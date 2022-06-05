#pragma once
#include "Command.h"
#include "MovementComponent.h"
#include <memory>
#include <vector>

class MoveLeftCommand : public Command
{
public:
	void Execute() override { GetObject()->GetComponent<dae::MovementComponent>()->MoveLeft(true); }
	void Release() override { GetObject()->GetComponent<dae::MovementComponent>()->MoveLeft(false); }

	MoveLeftCommand(dae::GameObject* go)
		:Command(go)
	{

	};
};

class MoveRightCommand : public Command
{
public:
	void Execute() override { GetObject()->GetComponent<dae::MovementComponent>()->MoveRight(true); }
	void Release() override
	{
		GetObject()->GetComponent<dae::MovementComponent>()->MoveRight(false);
	}

	MoveRightCommand(dae::GameObject* go)
		:Command(go)
	{

	};
};

class MoveDownLadderCommand : public Command
{
public:
	void Execute() override { GetObject()->GetComponent<dae::MovementComponent>()->MoveDownLadder(true); }
	void Release() override
	{
		GetObject()->GetComponent<dae::MovementComponent>()->MoveDownLadder(false);
	}

	MoveDownLadderCommand(dae::GameObject* go)
		:Command(go)
	{
		
	}
};

class MoveUpLadderCommand : public Command
{
public:
	void Execute() override { GetObject()->GetComponent<dae::MovementComponent>()->MoveUpLadder(true); }
	void Release() override { GetObject()->GetComponent<dae::MovementComponent>()->MoveUpLadder(false); }

	MoveUpLadderCommand(dae::GameObject* go)
		:Command(go)
	{

	}
};

