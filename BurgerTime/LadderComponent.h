#pragma once
#include "BaseComponent.h"

class LadderComponent : public dae::BaseComponent
{
public:
	LadderComponent() = default;
	~LadderComponent() override = default;
	LadderComponent(const LadderComponent& other) = delete;
	LadderComponent(LadderComponent&& other) noexcept = delete;
	LadderComponent& operator=(const LadderComponent& other) = delete;
	LadderComponent& operator=(LadderComponent&& other) noexcept = delete;

	bool GetBeingUsed() const { return m_Using; }
	void SetBeingUsed(bool enable) { m_Using = enable; }

	void Update(float) override {}
	void FixedUpdate(float ) override{}
	void Initialize() override{}
	void LateUpdate(float) override {};

private:
	bool m_Using{};
};
