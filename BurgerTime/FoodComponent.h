#pragma once
#include "BaseComponent.h"

enum class ExtraType;
struct Tile;

class FoodComponent : public dae::BaseComponent
{
public:
	explicit FoodComponent(dae::GameObject* pOwner, dae::GameObject* pPlayer, float fallSpeed = 50.f);
	~FoodComponent() override = default;
	FoodComponent(const FoodComponent& other) = delete;
	FoodComponent(FoodComponent&& other) noexcept = delete;
	FoodComponent& operator=(const FoodComponent& other) = delete;
	FoodComponent& operator=(FoodComponent&& other) noexcept = delete;

	void Update(float dT) override;
	void FixedUpdate(float fDT) override;
	void Initialize() override;
	void LateUpdate(float ) override{};

	void Fall(float fDt);

	void SetTiles(std::vector<Tile*> tiles) { m_CurrentTiles = tiles; }
	void SetType(ExtraType type) { m_Type = type; }
	void SetPlayer(dae::GameObject* pPlayer) { m_pPlayer = pPlayer; }

private:
	std::vector<Tile*> m_CurrentTiles{};
	bool m_Walked[4];
	float m_FallSpeed{};

	float m_MaxY{};

	ExtraType m_Type{};

	dae::GameObject* m_pPlayer{};
};

