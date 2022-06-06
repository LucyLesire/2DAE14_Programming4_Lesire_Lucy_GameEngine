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
		virtual ~MovementComponent() = default;
		MovementComponent(const MovementComponent& other) = delete;
		MovementComponent(MovementComponent&& other) = delete;
		MovementComponent& operator=(const MovementComponent& other) = delete;
		MovementComponent& operator=(MovementComponent&& other) = delete;


		void Move(glm::vec2 dir, bool enable);

		void SetOnLadder(bool enable, glm::vec2 maxY = glm::vec2{ 0.f, 1000.f }) { m_OnLadder = enable; m_MaxY = maxY; }
		void SetOnFloor(bool enable, glm::vec4 currentFloorDimension = glm::vec4{ 0.f, 1000.f, 0.f, 1000.f }) { m_OnFloor = enable; m_FloorDim = currentFloorDimension; }

		bool GetOnLadder() const { return m_OnLadder; }

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
		Transform m_Acceleration{};
		bool m_OnLadder{};
		bool m_OnFloor{};
		bool m_UsingLadder{};

		Tile* m_CurrentTile{};

		bool m_IsPlayer{};

		bool m_Dead{};

		bool m_WasStuck{};
	};
}

