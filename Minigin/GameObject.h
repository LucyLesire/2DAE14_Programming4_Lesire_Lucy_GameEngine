#pragma once
#include <vector>
#include "BaseComponent.h"
#include "Transform.h"
#include <vector>
#include <memory>
#include <iostream>
namespace dae
{
	class GameObject final
	{
	public:
		void Initialize();
		void Update(float deltaTime);
		void Render();
		void FixedUpdate(float fixedDT);
		void LateUpdate(float deltaTime);

		void SetPosition(float x, float y);
		Transform GetWorldPosition();
		std::string GetTag() const { return m_Tag; };

		template <typename T> std::shared_ptr<T> AddComponent(std::shared_ptr<T> pBaseComponent);
		template <typename T> std::shared_ptr<T> GetComponent() const;
		template <typename T> void RemoveComponent();

		void SetParent(GameObject* parent, bool keepWorldPos);
		GameObject* GetParent() const { return m_pParent; };

		size_t GetChildCount() const { return m_pChildren.size(); };
		GameObject* GetChildAt(int index) const { return m_pChildren[index]; };
		void RemoveChildAtIndex(int index) { m_pChildren.erase(m_pChildren.begin() + index); };

		int GetRenderOrder() const { return m_RenderOrder; }

		void Destroy() { m_Destroy = true; }
		bool GetDestroyed() const { return m_Destroy; }

		explicit GameObject(const std::string& tag, int renderOrder = 0);
		GameObject() = default;
		virtual ~GameObject();
		GameObject(const GameObject& other) = delete;
		GameObject(GameObject&& other) = delete;
		GameObject& operator=(const GameObject& other) = delete;
		GameObject& operator=(GameObject&& other) = delete;

	private:
		Transform m_LocalPos;
		Transform m_WorldPos;
		std::vector<std::shared_ptr<BaseComponent>> m_pComponents;

		GameObject* m_pParent = nullptr;
		std::vector<GameObject*> m_pChildren;

		std::string m_Tag;

		bool m_PositionDirty = false;

		int m_RenderOrder{};

		bool m_Destroy{};

	protected:
		void AddChild(GameObject* go) { m_pChildren.push_back(go); };
		void RemoveChild(GameObject* go);

		void SetLocalPosition(Transform trans);
		void SetWorldPosition();
		Transform GetLocalPosition() const { return m_LocalPos; };
	};

	template<typename T>
	inline std::shared_ptr<T> GameObject::AddComponent(std::shared_ptr<T> pBaseComponent)
	{
		pBaseComponent->SetWorldTransform(m_LocalPos);
		m_pComponents.push_back(pBaseComponent);
		return std::shared_ptr<T>(pBaseComponent);
	}

	template<typename T>
	inline std::shared_ptr<T> GameObject::GetComponent() const
	{
		for (std::shared_ptr<BaseComponent> c : m_pComponents)
		{
			if (std::dynamic_pointer_cast<T>(c) != nullptr)
			{
				return std::dynamic_pointer_cast<T>(c);
			}
		}
		return nullptr;
	}

	template<typename T>
	inline void GameObject::RemoveComponent()
	{
		for (int i{}; i < m_pComponents.size(); i++)
		{
			if (dynamic_cast<std::shared_ptr<T>>(m_pComponents[i]) != nullptr)
			{
				m_pComponents.erase(m_pComponents.begin() + i);
			}
		}
	}
}