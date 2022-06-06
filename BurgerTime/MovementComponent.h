#pragma once
#include "BaseComponent.h"
#include <memory>
#include <vector>
#pragma warning(push, 0)
#include <memory>
#include <glm/glm.hpp>

#include "TileManager.h"
#pragma warning (pop)

enum class TileType;

namespace dae
{
	class Subject;
	class MovementComponent final : public BaseComponent
	{
	public:
		void Update(float dT) override;
		void FixedUpdate(float fDT) override;
		void Initialize() override;
		void LateUpdate(float dT) override;

		MovementComponent(GameObject* pOwner, float speed);
		~MovementComponent() override = default;
		MovementComponent(const MovementComponent& other) = delete;
		MovementComponent(MovementComponent&& other) = delete;
		MovementComponent& operator=(const MovementComponent& other) = delete;
		MovementComponent& operator=(MovementComponent&& other) = delete;

		void MoveLeft(bool enable);
		void MoveRight(bool enable);

		void MoveDownLadder(bool enable);
		void MoveUpLadder(bool enable);

		Transform GetMoveDir() const { return  m_MoveDir; }

		void Died() { m_Dead = true; }
	private:

		glm::vec2 m_MaxY{};
		glm::vec4 m_FloorDim{};

		float m_Speed{};
		Transform m_MoveDir{};

		Tile* m_CurrentTile{};

		bool m_IsPlayer{};

		bool m_Dead{};

		bool m_WasStuck{};
	};
}

