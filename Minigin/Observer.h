#pragma once
#include "GameObject.h"
#include "TextComponent.h"


namespace dae
{
	class GameObject;

	enum class Event
	{
		Died,
		BurgerCompleted,
		BurgerDropped,
		EnemyKilled,
		Collide,
		Restart,
		NoLives
	};

	class Observer
	{
	public:
		virtual ~Observer() {};
		virtual void OnNotify(GameObject* pGo, Event event) = 0;
	protected:
		Observer() = default;
	};

}


