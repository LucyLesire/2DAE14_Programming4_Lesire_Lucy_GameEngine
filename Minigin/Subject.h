#pragma once
#include <vector>
#include <memory>
#include <iostream>

#define MAX_OBSERVERS = 10;

namespace dae
{
	class GameObject;
	enum class Event;
	class Observer;

	class Subject
	{
	public:
		Subject();

		void AddObserver(std::shared_ptr<Observer> pObserver);
		void RemoveObserver(std::shared_ptr<Observer> pObserver);

		void Notify(GameObject* pGo, Event event) const;
		~Subject() = default;

	private:
		std::vector<std::shared_ptr<Observer>> m_pObservers{};
		int m_AmountObservers{};
	};
}


