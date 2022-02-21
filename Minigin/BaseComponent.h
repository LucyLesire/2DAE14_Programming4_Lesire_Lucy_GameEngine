#pragma once
#include "Transform.h"

namespace dae
{
	class GameObject;

	class BaseComponent
	{
	public:
		BaseComponent() = default;
		virtual ~BaseComponent() = default;
		BaseComponent(const BaseComponent& other) = delete;
		BaseComponent(BaseComponent&& other) = delete;
		BaseComponent& operator=(const BaseComponent& other) = delete;
		BaseComponent& operator=(BaseComponent&& other) = delete;

		virtual void Update(float dT) = 0;

		void SetPosition(dae::Transform transForm) { m_Transform = transForm; };

	protected:
		dae::Transform m_Transform;
		std::shared_ptr<GameObject> m_Owner;
	};
}

