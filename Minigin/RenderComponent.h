#pragma once
#include "BaseComponent.h"
#include "Texture2D.h"

namespace dae
{
	class Texture2D;
	class RenderComponent : public BaseComponent
	{
	public:

		virtual void Update(float deltaTime) = 0;

		void Render();

		RenderComponent() = default;
		virtual ~RenderComponent() = default;
		RenderComponent(const RenderComponent& other) = delete;
		RenderComponent(RenderComponent&& other) = delete;
		RenderComponent& operator=(const RenderComponent& other) = delete;
		RenderComponent& operator=(RenderComponent&& other) = delete;

	protected:
		std::shared_ptr<dae::Texture2D> m_Texture;
		bool m_NeedsUpdate = false;
	};
}


