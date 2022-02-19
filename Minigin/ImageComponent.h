#pragma once
#include "RenderComponent.h"
#include "Texture2D.h"
#include "Renderer.h"
#include "Transform.h"
#include "Font.h"
#include "ResourceManager.h"

class ImageComponent final : public RenderComponent
{
public:

	void Update(float deltaTime) override;

	explicit ImageComponent(const std::string& fileName);
	ImageComponent() = default;
	virtual ~ImageComponent() = default;
	ImageComponent(const ImageComponent& other) = delete;
	ImageComponent(ImageComponent&& other) = delete;
	ImageComponent& operator=(const ImageComponent& other) = delete;
	ImageComponent& operator=(ImageComponent&& other) = delete;

private:
	std::string m_Text;
	std::shared_ptr<dae::Font> m_Font;
	bool m_NeedsUpdate;
};

