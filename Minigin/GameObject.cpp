#include "MiniginPCH.h"
#include "GameObject.h"
#include "RenderComponent.h"

void dae::GameObject::Initialize() const
{
	for (auto c : m_pComponents)
	{
		c->Initialize();
	}
}

void dae::GameObject::Update(float deltaTime) const
{
	for (auto c : m_pComponents)
	{
		c->Update(deltaTime);
	}
}

void dae::GameObject::Render() const
{
	if(GetComponent<RenderComponent>() != nullptr)
		GetComponent<RenderComponent>()->Render();
}

void dae::GameObject::FixedUpdate(float fixedDT) const
{
	for (auto c : m_pComponents)
	{
		c->FixedUpdate(fixedDT);
	}
}

void dae::GameObject::LateUpdate(float deltaTime) const
{
	for (auto c : m_pComponents)
	{
		c->LateUpdate(deltaTime);
	}
}


void dae::GameObject::SetPosition(float x, float y)
{
	Transform newPos{x, y, 0};
	SetLocalPosition(newPos);
	SetWorldPosition();

	for(GameObject* c : m_pChildren)
	{
		c->SetPosition(c->GetLocalPosition().GetPosition().x, c->GetLocalPosition().GetPosition().y);
	}

	for (std::shared_ptr<BaseComponent> c : m_pComponents)
	{
		c->SetWorldTransform(m_WorldPos);
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

dae::GameObject::GameObject(const std::string& tag, int renderOrder)
	:m_Tag{ tag }
	,m_RenderOrder(renderOrder)
	,m_PositionDirty(false)
{
}

dae::GameObject::~GameObject()
{
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
