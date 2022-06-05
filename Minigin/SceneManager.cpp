#include "MiniginPCH.h"
#include "SceneManager.h"
#include "Scene.h"

void dae::SceneManager::Initialize()
{
	for (auto& scene : m_Scenes)
	{
		scene->Initialize();
	}
}

void dae::SceneManager::Update(float dT)
{
	for(auto& scene : m_Scenes)
	{
		scene->Update(dT);
	}
}

void dae::SceneManager::Render()
{
	for (const auto& scene : m_Scenes)
	{
		scene->Render();
	}
}

void dae::SceneManager::FixedUpdate(float fDT)
{
	for (const auto& scene : m_Scenes)
	{
		scene->FixedUpdate(fDT);
	}
}

void dae::SceneManager::LateUpdate(float dT)
{
	for(const auto& scene: m_Scenes)
	{
		scene->LateUpdate(dT);
	}
}


dae::Scene& dae::SceneManager::CreateScene(const std::shared_ptr<Scene>& scene)
{
	m_Scenes.push_back(scene);
	return *scene;
}
