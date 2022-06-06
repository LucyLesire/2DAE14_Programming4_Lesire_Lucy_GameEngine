#include "MiniginPCH.h"
#include "SceneManager.h"

#include "InputManager.h"
#include "Scene.h"

void dae::SceneManager::Initialize()
{
	m_ActiveScene->Initialize();
	m_ActiveScene->SetInitialized();
	//for (auto& scene : m_Scenes)
	//{
	//	scene->Initialize();
	//}
}

void dae::SceneManager::Update(float dT)
{
	if(m_ActiveScene->GetInitialized())
		m_ActiveScene->Update(dT);
	//for(auto& scene : m_Scenes)
	//{
	//	scene->Update(dT);
	//}
}

void dae::SceneManager::Render()
{
	if (m_ActiveScene->GetInitialized())
		m_ActiveScene->Render();
	//for (const auto& scene : m_Scenes)
	//{
	//	scene->Render();
	//}
}

void dae::SceneManager::FixedUpdate(float fDT)
{
	if (m_ActiveScene->GetInitialized())
		m_ActiveScene->FixedUpdate(fDT);
	//for (const auto& scene : m_Scenes)
	//{
	//	scene->FixedUpdate(fDT);
	//}
}

void dae::SceneManager::LateUpdate(float dT)
{
	if (m_ActiveScene->GetInitialized())
		m_ActiveScene->LateUpdate(dT);
	//for(const auto& scene: m_Scenes)
	//{
	//	scene->LateUpdate(dT);
	//}
}

void dae::SceneManager::SetActiveScene(std::shared_ptr<Scene> scene)
{
	if (!m_ActiveScene)
	{
		m_ActiveScene = scene;
		m_ActiveScene->Initialize();
	}
	else
	{
		m_SceneToChangeTo = scene;
		m_SceneChange = true;
	}

}

void dae::SceneManager::SetSceneAtEndGameLoop()
{
	if(m_SceneChange)
	{
		if (m_ActiveScene)
		{
			m_ActiveScene->SetInitialized(false);
			m_ActiveScene->RemoveAll();
		}
		m_ActiveScene = m_SceneToChangeTo;
		InputManager::GetInstance().ResetCommands();
		m_ActiveScene->Initialize();
		m_ActiveScene->SetInitialized(true);
		m_SceneChange = false;
	}
}

void dae::SceneManager::RestartScene()
{
	m_RestartScene = true;
}

void dae::SceneManager::EndGameLoop()
{
	RestartSceneAtEndGameLoop();
	SetSceneAtEndGameLoop();
}

void dae::SceneManager::RestartSceneAtEndGameLoop()
{
	if(m_RestartScene)
	{
		auto id = m_ActiveScene->GetId();
		m_ActiveScene->SetInitialized(false);
		m_ActiveScene->RemoveAll();

		m_ActiveScene = m_Scenes[id];
		m_ActiveScene->Initialize();
		m_ActiveScene->SetInitialized(true);

		m_RestartScene = false;
	}
}


dae::Scene& dae::SceneManager::CreateScene(const std::shared_ptr<Scene>& scene)
{
	m_Scenes.push_back(scene);
	return *scene;
}
