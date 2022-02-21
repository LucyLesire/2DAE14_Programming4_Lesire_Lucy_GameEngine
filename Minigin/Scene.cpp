#include "MiniginPCH.h"
#include "Scene.h"
#include "GameObject.h"
#include "TextComponent.h"

using namespace dae;

unsigned int Scene::m_IdCounter = 0;

Scene::Scene(const std::string& name) : m_Name(name) {}

Scene::~Scene() = default;

void Scene::Add(const std::shared_ptr<GameObject>& object)
{
	m_Objects.push_back(object);
}

void Scene::Update(float dT)
{
	const std::string fpsTag = "FPS";
	for(auto& object : m_Objects)
	{
		object->Update(dT);
		if (object->GetTag() == fpsTag)
		{
			object->GetComponent<TextComponent>()->SetText(std::to_string(int(std::roundf(1 / dT))));
		}
	}


}

void Scene::Render() const
{
	for (const auto& object : m_Objects)
	{
		object->Render();
	}
}

