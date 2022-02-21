#include "MiniginPCH.h"
#include "GameObject.h"
#include "ResourceManager.h"
#include "Renderer.h"
#include "RenderComponent.h"

void dae::GameObject::Update(float deltaTime)
{
	for (auto c : m_pComponents)
	{
		c->Update(deltaTime);
	}
}

void dae::GameObject::Render()
{
	GetComponent<RenderComponent>()->Render();
}

void dae::GameObject::SetPosition(float x, float y)
{
	m_Transform.SetPosition(x, y, 0.f);

	for (BaseComponent* c : m_pComponents)
	{
		c->SetPosition(m_Transform);
	}
}

dae::GameObject::GameObject(const std::string& tag)
	:m_Tag{tag}
{
}

