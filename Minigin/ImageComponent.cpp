#include "MiniginPCH.h"
#include "ImageComponent.h"
#include "ResourceManager.h"

void dae::ImageComponent::Update(float)
{
}

void dae::ImageComponent::FixedUpdate(float)
{
}

void dae::ImageComponent::Initialize()
{
}

dae::ImageComponent::ImageComponent(const std::string& fileName, float zPos)
{
	m_zPos = zPos;
	m_Texture = dae::ResourceManager::GetInstance().LoadTexture(fileName);
}
