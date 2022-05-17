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

		void SetTransform(dae::Transform transForm) { m_Transform = transForm; };
		Transform GetTransform() const { return m_Transform; };

		Subject* GetSubject() const { return m_Subject.get(); };

	private:
		dae::Transform m_Transform;
		std::weak_ptr<GameObject> m_pOwner;
		std::unique_ptr<Subject> m_Subject;

	protected:
		explicit BaseComponent(std::weak_ptr<GameObject> pOwner) : m_pOwner(pOwner)
		{
			m_Subject = std::make_unique<Subject>();
		}
		std::weak_ptr<GameObject> GetOwner() const { return m_pOwner; }
	};
}

