#pragma once
#include <iostream>

#include "BaseComponent.h"
#include "GameObject.h"
#include "PetterPepperComponent.h"

class Command
{
protected:
	dae::GameObject* GetObject() const { return m_GameObject; };
public:
	explicit Command(dae::GameObject* go)
		:m_GameObject(go)
	{

	};
	virtual ~Command()
	{
		delete m_GameObject;
		m_GameObject = nullptr;
	};
	virtual void Execute() = 0;

private:
	dae::GameObject* m_GameObject = nullptr;
};

class FireCommand : public Command
{
public:
	void Execute() override { Fire(); };
private:
	void Fire() { std::cout << "Fire\n"; };
};

class JumpCommand : public Command
{
public:
	void Execute() override { Jump(); };
private:
	void Jump() { std::cout << "Jump\n"; };
};

class DuckCommand : public Command
{
public:
	void Execute() override { Duck(); };
private:
	void Duck() { std::cout << "Duck\n"; };
};

class FartCommand : public Command
{
public:
	void Execute() override { Fart(); };
private:
	void Fart() { std::cout << "Fart\n"; };
};

class DieCommand : public Command
{
public:
	void Execute() override
	{
		GetObject()->GetComponent<dae::PetterPepperComponent>()->Die();
	}

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

	PointCommand(dae::GameObject* go)
		:Command(go)
	{

	};
};

