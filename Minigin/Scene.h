#pragma once
#include "SceneManager.h"
#include <vector>
#include <memory>
#include <iostream>

#include "CollisionManager.h"

namespace dae
{
	class GameObject;
	class Scene
	{
		friend Scene& SceneManager::CreateScene(const std::shared_ptr<Scene>& scene);
	public:
		void Add(const std::shared_ptr<GameObject>& object);

		virtual void Initialize() = 0;
		virtual void FixedUpdate(float fDT);
		virtual void Update(float dT);
		virtual void Render() const;
		virtual void LateUpdate(float dT);

		virtual void AddCollision(const std::shared_ptr<CollisionComponent>& cObject);

		std::vector <std::shared_ptr<GameObject>> GetObjects() const { return m_Objects; }
		std::shared_ptr<GameObject> GetObjectWithName(const std::string& tag) const;

		virtual void RemoveObjects();

		~Scene();
		Scene(const Scene& other) = delete;
		Scene(Scene&& other) = delete;
		Scene& operator=(const Scene& other) = delete;
		Scene& operator=(Scene&& other) = delete;

	protected:
		explicit Scene(const std::string& name);

	private: 
		CollisionManager m_CollisionManager;
		std::string m_Name;
		std::vector < std::shared_ptr<GameObject>> m_Objects{};

		static unsigned int m_IdCounter; 
	};

}
