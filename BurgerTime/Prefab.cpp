#include "Prefab.h"
#include "GameObject.h"
#include "CollisionComponent.h"

dae::Prefab::Prefab(glm::vec4 transformInfo, std::shared_ptr<GameObject> pGameObject)
	:m_TransformInformation(transformInfo)
	,m_pGameObject(pGameObject)
{
	m_pCol = pGameObject->AddComponent(std::make_shared<CollisionComponent>(m_pGameObject.get(), true, transformInfo.z, transformInfo.w, false));
}

void dae::Prefab::Initialize()
{
	m_pGameObject->SetPosition(m_TransformInformation.x, m_TransformInformation.y);
}
