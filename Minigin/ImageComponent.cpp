#include "MiniginPCH.h"
#include "ImageComponent.h"

void ImageComponent::Update(float)
{
}

ImageComponent::ImageComponent(const std::string& fileName)
{
	m_Texture = dae::ResourceManager::GetInstance().LoadTexture(fileName);
}
