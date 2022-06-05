#include "FloorPrefab.h"

#include "CollisionComponent.h"
#include "FloorComponent.h"
#include "GameObject.h"
#include "ImageComponent.h"

dae::FloorPrefab::FloorPrefab(glm::vec4 transformInfo, std::shared_ptr<GameObject> pGameObject)
	:Prefab(transformInfo, pGameObject)
{
	GetObject()->AddComponent(std::make_shared<ImageComponent>("red.png"));
	GetObject()->GetComponent<ImageComponent>()->SetSize({ transformInfo.z, transformInfo.w });
	pGameObject->AddComponent(std::make_shared<FloorComponent>());
}
