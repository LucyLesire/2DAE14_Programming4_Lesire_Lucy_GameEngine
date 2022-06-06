#pragma once
#include "BaseComponent.h"
#include <memory>
#include <vector>

namespace dae
{
	class FPSComponent final : public BaseComponent
	{
	public:
		void Update(float dT) override;
		void LateUpdate(float) override {};
		void FixedUpdate(float) override{};
		void Initialize() override{};

		explicit FPSComponent(GameObject* pOwner);
		FPSComponent() = default;
		~FPSComponent() override = default;
		FPSComponent(const FPSComponent& other) = delete;
		FPSComponent(FPSComponent&& other) = delete;
		FPSComponent& operator=(const FPSComponent& other) = delete;
		FPSComponent& operator=(FPSComponent&& other) = delete;

	private:
		bool m_CanChange = true;
		float m_WaitBetweenUpdates = 0.f;
		const float m_MaxWait = 1.f;
	};
}


