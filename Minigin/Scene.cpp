#include "MiniginPCH.h"
#include "Scene.h"

#include <algorithm>

#include "GameObject.h"
#include "TextComponent.h"

using namespace dae;

Scene::Scene(const std::string& name, uint32_t width, uint32_t height, unsigned int id) : m_Name(name), m_Width(width), m_Height(height), m_IdCounter(id) {}

Scene::~Scene() = default;

void Scene::Add(const std::shared_ptr<GameObject>& object)
{
	object->Initialize();
	m_Objects.push_back(object);

	std::sort(m_Objects.begin(), m_Objects.end(), [](const std::shared_ptr<GameObject>& o1, const std::shared_ptr<GameObject>& o2)
		{
			return o1->GetRenderOrder() < o2->GetRenderOrder();
		});


}

void dae::Scene::FixedUpdate(float fDT)
{
	for (auto& object : m_Objects)
	{
		object->FixedUpdate(fDT);
	}
}

void Scene::Update(float dT)
{
	RemoveObjects();
	m_CollisionManager.Update(dT);
	for(auto& object : m_Objects)
	{
		object->Update(dT);
	}
}

void Scene::Render() const
{
	for (const auto& object : m_Objects)
	{
		object->Render();
	}
}

void dae::Scene::LateUpdate(float dT)
{
	for (const auto& object : m_Objects)
	{
		object->LateUpdate(dT);
	}
}

void dae::Scene::AddCollision(const std::shared_ptr<CollisionComponent>& cObject)
{
	m_CollisionManager.AddCollider(cObject.get());
}

std::shared_ptr<GameObject> dae::Scene::GetObjectWithName(const std::string& tag) const
{
	auto it = std::find_if(m_Objects.begin(), m_Objects.end(), [tag](const std::shared_ptr<GameObject>& o1)
		{
			return o1->GetTag() == tag;
		});

	return *it;
}

void dae::Scene::RemoveObjects()
{
	m_Objects.erase(std::remove_if(m_Objects.begin(), m_Objects.end(), [](std::shared_ptr<GameObject> obj)
		{
			return obj->GetDestroyed();
		}), m_Objects.end());
}

void dae::Scene::RemoveAll()
{
	m_Objects.erase(m_Objects.begin(), m_Objects.end());
}

