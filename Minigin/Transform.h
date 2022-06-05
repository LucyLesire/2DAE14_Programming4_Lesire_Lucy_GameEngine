#pragma once
#pragma warning(push)
#pragma warning (disable:4201)
#include <glm/vec3.hpp>
#include <glm/vec2.hpp>
#pragma warning(pop)
namespace dae
{
	class Transform final
	{
	public:
		Transform(float x, float y, float z)
			:m_Position(x, y, z){}
		Transform()
			:m_Position(0,0,0){}
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

	class Transform2D final
	{
	public:
		Transform2D(float x, float y)
			:m_Position(x, y) {}
		Transform2D()
			:m_Position(0, 0) {}
		const glm::vec2& GetPosition() const { return m_Position; }
		void SetPosition(float x, float y);
		Transform2D operator+(const Transform2D& other)
		{
			Transform2D temp{};
			auto tempPos = m_Position + other.GetPosition();
			temp.SetPosition(tempPos.x, tempPos.y);
			return temp;
		};
		Transform2D operator-(const Transform2D& other)
		{
			Transform2D temp{};
			auto tempPos = m_Position - other.GetPosition();
			temp.SetPosition(tempPos.x, tempPos.y);
			return temp;
		};
	private:
		glm::vec2 m_Position;
	};
}
