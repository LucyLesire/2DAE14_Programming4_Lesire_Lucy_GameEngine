#pragma once
#include "BaseComponent.h"

namespace dae
{
	class Subject;
	class PetterPepperComponent final : public BaseComponent, public std::enable_shared_from_this<PetterPepperComponent>
	{
	public:
		void Update(float dT) override;

		PetterPepperComponent(std::weak_ptr<GameObject> pOwner);
		virtual ~PetterPepperComponent() = default;
		PetterPepperComponent(const PetterPepperComponent& other) = delete;
		PetterPepperComponent(PetterPepperComponent&& other) = delete;
		PetterPepperComponent& operator=(const PetterPepperComponent& other) = delete;
		PetterPepperComponent& operator=(PetterPepperComponent&& other) = delete;

		void Die();
		void AddPoints();
		int GetLives() const { return m_Lives; };
		int GetPoints() const { return m_Points; };

	private:
		int m_Lives{ 3 };
		int m_Points{ 0 };
	};
}


