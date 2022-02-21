#pragma once
#include "Transform.h"
#include <vector>
#include "BaseComponent.h"
namespace dae
{
	class GameObject final
	{
	public:
		void Update(float deltaTime);
		void Render();

		void SetPosition(float x, float y);
		std::string GetTag() const { return m_Tag; };

		template <typename T> T* AddComponent(BaseComponent* pBaseComponent);
		template <typename T> T* GetComponent() const;
		template <typename T> void RemoveComponent();

		void SetParent(GameObject* parent) { m_pParent = parent; };
		GameObject* GetParent() const { return m_pParent; };

		size_t GetChildCount() const { return m_pChildren.size(); };
		GameObject* GetChildAt(int index) const { return m_pChildren[index]; };
		void RemoveChild(int index) { m_pChildren.erase(m_pChildren.begin() + index); };
		void AddChild(GameObject* go) { m_pChildren.push_back(go); };

		explicit GameObject(const std::string& tag);
		GameObject() = default;
		virtual ~GameObject() = default;
		GameObject(const GameObject& other) = delete;
		GameObject(GameObject&& other) = delete;
		GameObject& operator=(const GameObject& other) = delete;
		GameObject& operator=(GameObject&& other) = delete;

	private:
		Transform m_Transform;
		std::vector<BaseComponent*> m_pComponents;

		GameObject* m_pParent = nullptr;
		std::vector<GameObject*> m_pChildren;

		std::string m_Tag;
	};

	template<typename T>
	inline T* GameObject::AddComponent(BaseComponent* pBaseComponent)
	{
		pBaseComponent->SetPosition(m_Transform);
		m_pComponents.push_back(pBaseComponent);
		return dynamic_cast<T*>(pBaseComponent);
	}

	template<typename T>
	inline T* GameObject::GetComponent() const
	{
		for (BaseComponent* c : m_pComponents)
		{
			if (dynamic_cast<T*>(c) != nullptr)
			{
				return dynamic_cast<T*>(c);
			}
		}
		return nullptr;
	}

	template<typename T>
	inline void GameObject::RemoveComponent()
	{
		for (int i{}; i < m_pComponents.size(); i++)
		{
			if (dynamic_cast<T*>(m_pComponents[i]) != nullptr)
			{
				m_pComponents.erase(m_pComponents.begin() + i);
			}
		}
	}
}