#pragma once
#include "BaseComponent.h"

namespace dae
{
	class FloorComponent : public dae::BaseComponent
	{
	public:
		FloorComponent() = default;
		~FloorComponent() override = default;
		FloorComponent(const FloorComponent& other) = delete;
		FloorComponent(FloorComponent&& other) noexcept = delete;
		FloorComponent& operator=(const FloorComponent& other) = delete;
		FloorComponent& operator=(FloorComponent&& other) noexcept = delete;

		bool GetBeingUsed() const { return m_Using; }
		void SetBeingUsed(bool enable) { m_Using = enable; }

		void Update(float) override {}
		void FixedUpdate(float) override {}
		void Initialize() override {}
		void LateUpdate(float) override {};

	private:
		bool m_Using{};
	};
}


