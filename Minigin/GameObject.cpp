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
	if(GetComponent<RenderComponent>() != nullptr)
		GetComponent<RenderComponent>()->Render();
}

void dae::GameObject::SetPosition(float x, float y)
{
	m_WorldPos.SetPosition(x, y, 0.f);

	for (std::shared_ptr<BaseComponent> c : m_pComponents)
	{
		c->SetTransform(m_WorldPos);
	}
}

void dae::GameObject::SetParent(GameObject* parent, bool keepWorldPos)
{
	if (parent == nullptr)
		SetLocalPosition(GetWorldPosition());
	else
	{
		if (keepWorldPos)
		{
			SetLocalPosition(GetLocalPosition() - parent->GetWorldPosition());
			m_PositionDirty = true;
		}
	}

	if (m_pParent)
		m_pParent->RemoveChild(this);

	m_pParent = parent;

	if (m_pParent)
		m_pParent->AddChild(this);

}

void dae::GameObject::RemoveChild(GameObject* go)
{
	for(auto it{m_pChildren.begin()}; it != m_pChildren.end(); )
	{
		if (*it == go)
		{
			m_pChildren.erase(it);
			return;
		}

		++it;
	}
}

dae::GameObject::GameObject(const std::string& tag)
	:m_Tag{ tag }
{
}

dae::GameObject::~GameObject()
{
	delete m_pParent;
	m_pParent = nullptr;

	for(int i{}; i < m_pChildren.size(); ++i)
	{
		delete m_pChildren[i];
		m_pChildren[i] = nullptr;
	}

	m_pChildren.clear();
}

void dae::GameObject::SetLocalPosition(Transform trans)
{
	m_LocalPos = trans;
	m_PositionDirty = true;
}

void dae::GameObject::SetWorldPosition()
{
	if (m_PositionDirty)
	{
		if (m_pParent == nullptr)
			m_WorldPos = m_LocalPos;
		else
			m_WorldPos = m_pParent->GetWorldPosition() + m_LocalPos;
	}
	m_PositionDirty = false;
}

dae::Transform dae::GameObject::GetWorldPosition()
{
	if (m_PositionDirty)
		SetWorldPosition();
	return m_WorldPos;
}
