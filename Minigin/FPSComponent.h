#pragma once
#include "BaseComponent.h"

namespace dae
{
	class FPSComponent final : public BaseComponent
	{
	public:
		void Update(float dT) override;

		explicit FPSComponent(std::shared_ptr<GameObject> owner);
		FPSComponent() = default;
		virtual ~FPSComponent() = default;
		FPSComponent(const FPSComponent& other) = delete;
		FPSComponent(FPSComponent&& other) = delete;
		FPSComponent& operator=(const FPSComponent& other) = delete;
		FPSComponent& operator=(FPSComponent&& other) = delete;

	private:
		bool m_CanChange = true;
		float m_WaitBetweenUpdates = 0.f;
		const float m_MaxWait = 0.1f;
	};
}


