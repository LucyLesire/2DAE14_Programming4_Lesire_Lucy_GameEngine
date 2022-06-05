#pragma once
#include "GameObject.h"
#include "TextComponent.h"


namespace dae
{
	class GameObject;

	enum class Event
	{
		Died,
		GotPoints,
		CollideFloor,
		UnCollideFloor,
		CollideLadder,
		UnCollideLadder,
		Collide
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


