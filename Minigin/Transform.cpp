#include "MiniginPCH.h"
#include "Transform.h"

void dae::Transform::SetPosition(const float x, const float y, const float z)
{
	m_Position.x = x;
	m_Position.y = y;
	m_Position.z = z;
}

void dae::Transform2D::SetPosition(float x, float y)
{
	m_Position.x = x;
	m_Position.y = y;
}

