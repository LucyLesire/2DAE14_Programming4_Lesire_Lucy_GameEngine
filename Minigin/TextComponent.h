#pragma once
#include "RenderComponent.h"
#include "Texture2D.h"
#include "Renderer.h"
#include "Transform.h"
#include "Font.h"

class TextComponent final : public RenderComponent
{
public:

	void Update(float deltaTime) override;

	explicit TextComponent(const std::string& text, const std::shared_ptr<dae::Font>& font);
	TextComponent() = default;
	virtual ~TextComponent() = default;
	TextComponent(const TextComponent& other) = delete;
	TextComponent(TextComponent&& other) = delete;
	TextComponent& operator=(const TextComponent& other) = delete;
	TextComponent& operator=(TextComponent&& other) = delete;

private:
	std::string m_Text;
	std::shared_ptr<dae::Font> m_Font;
	bool m_NeedsUpdate = true;
};

