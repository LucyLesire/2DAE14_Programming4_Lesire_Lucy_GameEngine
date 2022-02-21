#include "MiniginPCH.h"
#include "ImageComponent.h"

void dae::ImageComponent::Update(float)
{
}

dae::ImageComponent::ImageComponent(const std::string& fileName)
{
	m_Texture = dae::ResourceManager::GetInstance().LoadTexture(fileName);
}
