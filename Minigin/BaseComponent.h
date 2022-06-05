#pragma once
#include "Transform.h"
#include "Subject.h"

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
		virtual void FixedUpdate(float fDT) = 0;
		virtual void Initialize() = 0;
		virtual void LateUpdate(float dT) = 0;

		void SetWorldTransform(dae::Transform transForm) { m_WorldTransform = transForm + m_LocalTransform; };
		void SetLocalTransform(dae::Transform transForm) { m_LocalTransform = transForm; };
		Transform GetTransform() const { return m_WorldTransform; };
		Transform GetLocalTransform() const { return m_LocalTransform; };

		const std::unique_ptr<Subject>& GetSubject() const { return m_pSubject; };

		GameObject* GetOwner() const { return m_pOwner; }

	private:
		Transform m_WorldTransform;
		Transform m_LocalTransform;
		GameObject* m_pOwner;
		std::unique_ptr<Subject> m_pSubject;

	protected:
		explicit BaseComponent(GameObject* pOwner);
	};
}

