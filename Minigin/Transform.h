#pragma once
#pragma warning(push)
#pragma warning (disable:4201)
#include <glm/vec3.hpp>
#pragma warning(pop)
namespace dae
{
	class Transform final
	{
	public:
		const glm::vec3& GetPosition() const { return m_Position; }
		void SetPosition(float x, float y, float z);
		Transform operator+(const Transform& other)
		{
			Transform temp{};
			auto tempPos = m_Position + other.GetPosition();
			temp.SetPosition(tempPos.x, tempPos.y, tempPos.z);
			return temp;
		};
		Transform operator-(const Transform& other)
		{
			Transform temp{};
			auto tempPos = m_Position - other.GetPosition();
			temp.SetPosition(tempPos.x, tempPos.y, tempPos.z);
			return temp;
		};
	private:
		glm::vec3 m_Position;
	};
}
