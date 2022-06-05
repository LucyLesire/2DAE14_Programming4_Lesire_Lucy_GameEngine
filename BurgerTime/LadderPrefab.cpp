#include "LadderPrefab.h"

#include "CollisionComponent.h"
#include "GameObject.h"
#include "ImageComponent.h"
#include "LadderComponent.h"

dae::LadderPrefab::LadderPrefab(glm::vec4 transformInfo, std::shared_ptr<GameObject> pGameObject)
	:Prefab(transformInfo, pGameObject)
{
	GetObject()->AddComponent(std::make_shared<ImageComponent>("blue.jpg"));
	GetObject()->GetComponent<ImageComponent>()->SetSize({ transformInfo.z, transformInfo.w });
	pGameObject->AddComponent(std::make_shared<LadderComponent>());
}
