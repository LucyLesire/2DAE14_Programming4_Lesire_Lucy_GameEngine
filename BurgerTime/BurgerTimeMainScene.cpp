#include "BurgerTimeMainScene.h"

#define WIN32_LEAN_AND_MEAN
#include <Windows.h>


#include <memory>
#include <SDL_scancode.h>
#include <vector>
#include <rapidjson/istreamwrapper.h>
#include <iostream>
#include <fstream>

#include "AIComponent.h"
#include "CollisionComponent.h"
#include "EnemyComponent.h"
#include "FoodComponent.h"
#include "ImageComponent.h"
#include "MovementComponent.h"
#include "PetterPepperComponent.h"
#include "GameObject.h"
#include "InputManager.h"
#include "MoveCommands.h"
#include "EnemyComponent.h"
#include "FPSComponent.h"
#include "PeterPepperObserver.h"
#include "PetterPepperCommands.h"
#include "PetterPepperDisplays.h"
#include "ResourceManager.h"
#include "rapidjson/rapidjson.h"
#include "rapidjson/document.h"
#include "TileManager.h"

dae::BurgerTimeMainScene::BurgerTimeMainScene(const std::string& name, uint32_t width, uint32_t height, unsigned int id, const std::string& levelFile)
	:Scene(name, width, height, id)
	,m_LevelFile(levelFile)
{
}

void dae::BurgerTimeMainScene::Initialize()
{
	GameInstance::GetInstance().Reset();
	GameInstance::GetInstance().Init(4);

	//Level
	std::shared_ptr<GameObject> goLevel = std::make_shared<GameObject>("Level", -1);
	std::string levelImg{ m_LevelFile };
	levelImg += ".png";
	goLevel->AddComponent(std::make_shared<dae::ImageComponent>(levelImg));
	goLevel->GetComponent<ImageComponent>()->SetSize({ 748.8f, 720 });
	Add(goLevel);

	//Font
	auto font = ResourceManager::GetInstance().LoadFont("Lingua.otf", 36);

	//Player Init
	std::shared_ptr<dae::GameObject> goPlayer1 = std::make_shared<dae::GameObject>("Peter Pepper", 1);
	goPlayer1->AddComponent<dae::PetterPepperComponent>(std::make_shared<dae::PetterPepperComponent>(goPlayer1.get()));
	goPlayer1->AddComponent(std::make_shared<dae::ImageComponent>("PetterPepperSprites.png"));
	goPlayer1->AddComponent(std::make_shared<dae::MovementComponent>(goPlayer1.get(), 100.f));
	goPlayer1->GetComponent<ImageComponent>()->SetSize({ 50.f, 50.f });
	goPlayer1->GetComponent<ImageComponent>()->SetSheetSize({ 144.f, 32.f });
	AddCollision(goPlayer1->AddComponent(std::make_shared<CollisionComponent>(goPlayer1.get() ,true, 5.f, 10.f)));
	goPlayer1->GetComponent<CollisionComponent>()->SetLocalTransform(Transform{ 25.f, 20.f, 0.f });
	goPlayer1->GetComponent<ImageComponent>()->SetLocalTransform(Transform{ 0.f, -50.f/4.f, 0.f });

	//Add pepper
	auto goPepper = std::make_shared<dae::GameObject>("Pepper", 2);
	auto pPepperImage = goPepper->AddComponent(std::make_shared<ImageComponent>("Pepper.png"));
	pPepperImage->SetSheetSize({ 32.f, 8.f });
	pPepperImage->SetSize({ 50.f, 50.f });
	pPepperImage->SetSrcRect(SDL_Rect{ 0, 0, 32 / 4, 8 });
	pPepperImage->SetActive(false);
	pPepperImage->SetLocalTransform({ 0.f, -12.5f, 0.f });

	Add(goPepper);
	goPepper->SetParent(goPlayer1.get(), false);
	goPlayer1->GetComponent<PetterPepperComponent>()->GetSubject()->AddObserver(std::make_shared<PetterPepperObserver>());

	Add(goPlayer1);

	//Collision
	const auto& collideObserver = std::make_shared<CollisionObserver>(goPlayer1.get());
	goPlayer1->GetComponent<CollisionComponent>()->GetSubject()->AddObserver(collideObserver);

	//Input
	std::map<SDL_Scancode, std::shared_ptr<Command>> kInputMap{};
	kInputMap[SDL_SCANCODE_A] = std::make_shared<MoveLeftCommand>(goPlayer1.get());
	kInputMap[SDL_SCANCODE_D] = std::make_shared<MoveRightCommand>(goPlayer1.get());
	kInputMap[SDL_SCANCODE_W] = std::make_shared<MoveUpLadderCommand>(goPlayer1.get());
	kInputMap[SDL_SCANCODE_S] = std::make_shared<MoveDownLadderCommand>(goPlayer1.get());
	kInputMap[SDL_SCANCODE_F] = std::make_shared<PepperCommand>(goPlayer1.get());
	InputManager::GetInstance().AddCommand(kInputMap, 0);


	ReadJson(m_LevelFile);

	//FPS
	auto goFPSCounter = std::make_shared<GameObject>("FPS");
	goFPSCounter->AddComponent(std::make_shared<TextComponent>("FPS", font));
	goFPSCounter->AddComponent(std::make_shared<FPSComponent>(goFPSCounter.get()));
	goFPSCounter->SetPosition(0, 0);
	Add(goFPSCounter);

	//Sound
	std::map<unsigned short, std::string> soundClips{};
	soundClips[0] = "../Data/Sounds/Music.wav";
	m_pSoundSystem = std::make_shared<SDLSoundSystem>(soundClips);
	ServiceLocator::RegisterSoundSystem(m_pSoundSystem.get());
	ServiceLocator::GetSoundSystem().Play(0, 80);

	//Displays
	auto goPoints = std::make_shared<GameObject>("Points Display", 1);
	goPoints->AddComponent(std::make_shared<TextComponent>("Score: 000", font));
	goPoints->SetPosition(GetWidth()/2.f, 0);
	Add(goPoints);
	goPlayer1->GetComponent<PetterPepperComponent>()->GetSubject()->AddObserver(std::make_shared<PointDisplay>(goPoints->GetComponent<TextComponent>()));

	auto goLives = std::make_shared<GameObject>("Live Display", 1);
	auto livesImgComp = goLives->AddComponent(std::make_shared<ImageComponent>("Lives.png"));
	goLives->SetPosition(GetWidth() / 3.f, 0);
	livesImgComp->SetSheetSize({ 24.f, 8.f });
	livesImgComp->SetSize({ 36.f * 3.f , 36.f});
	Add(goLives);
	goPlayer1->GetComponent<PetterPepperComponent>()->GetSubject()->AddObserver(std::make_shared<HealthDisplay>(goLives->GetComponent<ImageComponent>()));

}

void dae::BurgerTimeMainScene::Update(float dT)
{
	Scene::Update(dT);
	if(GameInstance::GetInstance().GetAllBurgersDropped())
	{
		SceneManager::GetInstance().SetActiveScene(SceneManager::GetInstance().GetSceneAtIndex(GetId() + 1));
	}
}

void dae::BurgerTimeMainScene::ReadJson(const std::string& fileLoc)
{
	std::string fileJsonLoc{ "../Data/Json/" };
	fileJsonLoc += fileLoc;
	fileJsonLoc += ".json";

	if (std::ifstream is{ fileJsonLoc })
	{
		//Set console code page to UTF-8 so console knows how to interpret string data
		SetConsoleOutputCP(CP_UTF8);

		//Enable buffering to prevent VS from chopping up UTF-8 byte sequences
		setvbuf(stdout, nullptr, _IOFBF, 1000);

		rapidjson::IStreamWrapper isw{ is };

		rapidjson::Document jsonDoc;
		jsonDoc.ParseStream(isw);

		const std::string ladderTag = "Ladder";
		const std::string floorTag = "Floor";
		const std::string gridTag = "Grid";
		const std::string foodTag = "Food";
		const std::string trayTag = "Tray";
		const std::string enemyTag = "Enemy";
		const std::string playerTag = "Player";

		auto& tileManager = TileManager::GetInstance();

		int width = 0;
		int height = 0;
		m_Rows = 0;
		int cols = 0;
		float scale = 3.6f;
		for (auto itr = jsonDoc.Begin(); itr != jsonDoc.End(); ++itr)
		{
			const auto& levelJson = *itr;
			const auto& objectJson = levelJson["object"];
			const char* object = objectJson.GetString();
			std::string objectString{ object };

			if (objectString == gridTag.c_str())
			{
				const auto& gridTransformJson = levelJson["transform"];
				auto transform = gridTransformJson.GetArray();

				const auto& gridAmountJson = levelJson["amount"];
				auto gridAmount = gridAmountJson.GetArray();

				width = transform[0].GetInt();
				height = transform[1].GetInt();

				m_Rows = gridAmount[0].GetInt();
				cols = gridAmount[1].GetInt();

				std::vector<Tile*> tiles{};
		

				for (int i{}; i < m_Rows; i++)
				{
					for (int j{}; j < cols; j++)
					{
						tiles.emplace_back(new Tile(glm::vec4{ i * width * scale, j * height * scale, (i + 1) * width * scale, (j + 1) * height * scale }, true, i * m_Rows + j));
					}
				}

				tileManager.InitializeTiles(tiles, m_Rows, cols, 748, 720);
				tileManager.SetTileWidth(width * scale);

			}

			if (objectString == ladderTag.c_str())
			{
				const auto& gridPositionsJson = levelJson["gridPositions"];
				auto gridPositions = gridPositionsJson.GetArray();

				for (unsigned int i{}; i < gridPositions.Size(); i++)
				{
					auto gridPosition = gridPositions[i].GetArray();
					for (int j{ gridPosition[0].GetInt() }; j <= gridPosition[1].GetInt(); ++j)
					{
						for(int k{gridPosition[2].GetInt()}; k <= gridPosition[3].GetInt(); ++k)
						{
							tileManager.SetTileType(TileType::Ladder, j * m_Rows + k);
						}
					}
				}
			}
			if(objectString == floorTag.c_str())
			{
				const auto& gridPositionsJson = levelJson["gridPositions"];
				auto gridPositions = gridPositionsJson.GetArray();

				for (unsigned int i{}; i < gridPositions.Size(); i++)
				{
					auto gridPosition = gridPositions[i].GetArray();
					for (int j{ gridPosition[0].GetInt() }; j <= gridPosition[1].GetInt(); ++j)
					{
						for (int k{ gridPosition[2].GetInt() }; k <= gridPosition[3].GetInt(); ++k)
						{
							tileManager.SetTileType(TileType::Floor, j * m_Rows + k);
						}
					}
				}
			}
			if(objectString == foodTag.c_str())
			{
				const auto& gridPositionsJson = levelJson["gridPositions"];
				auto gridPositions = gridPositionsJson.GetArray();

				const std::string topBun = "TopBun";
				const std::string cheese = "Cheese";
				const std::string tomato = "Tomato";
				const std::string lettuce = "Lettuce";
				const std::string burger = "Burger";
				const std::string bottomBun = "BottomBun";

				for (unsigned int i{}; i < gridPositions.Size(); i++)
				{
					auto gridPosition = gridPositions[i].GetArray();
					auto foodObject = std::make_shared<GameObject>("Food");
					std::vector<Tile*> tiles{};
					auto type = gridPosition[4].GetString();
					std::string typeString{ type };
					for (int j{ gridPosition[0].GetInt() }; j <= gridPosition[1].GetInt(); ++j)
					{
						for (int k{ gridPosition[2].GetInt() }; k <= gridPosition[3].GetInt(); ++k)
						{
							tiles.emplace_back(tileManager.GetTileAtIndex(j * m_Rows + k));
		
							if(typeString == topBun.c_str())
							{
								tileManager.SetExtraTileType(ExtraType::TopBun, j * m_Rows + k);
							}


							else if (typeString == cheese.c_str())
							{
								tileManager.SetExtraTileType(ExtraType::Cheese, j * m_Rows + k);
							}


							else if (typeString == lettuce.c_str())
							{
								tileManager.SetExtraTileType(ExtraType::Lettuce, j* m_Rows + k);
							}


							else if (typeString == tomato.c_str())
							{
								tileManager.SetExtraTileType(ExtraType::Tomato, j* m_Rows + k);
							}


							else if (typeString == burger.c_str())
							{
								tileManager.SetExtraTileType(ExtraType::Burger, j* m_Rows + k);
							}


							else if (typeString == bottomBun.c_str())
							{
								tileManager.SetExtraTileType(ExtraType::BottomBun, j * m_Rows + k);
							}

						}
					}
					std::string foodImage{ type };
					foodImage += ".png";
					auto pFoodImgComp = foodObject->AddComponent(std::make_shared<ImageComponent>(foodImage));
					pFoodImgComp->SetSize({ 4 * width * scale, height * scale });

					auto foodComp = foodObject->AddComponent(std::make_shared<FoodComponent>(foodObject.get(), GetObjectWithName("Peter Pepper").get(), 80.f));
					foodComp->SetTiles(tiles);
					foodObject->SetPosition(tiles[0]->m_Boundingbox.x, tiles[0]->m_Boundingbox.y);
					Add(foodObject);
				}
			}

			if (objectString == trayTag.c_str())
			{
				const auto& gridPositionsJson = levelJson["gridPositions"];
				auto gridPositions = gridPositionsJson.GetArray();


				for (unsigned int i{}; i < gridPositions.Size(); i++)
				{
					auto gridPosition = gridPositions[i].GetArray();

					for (int j{ gridPosition[0].GetInt() }; j <= gridPosition[1].GetInt(); ++j)
					{
						for (int k{ gridPosition[2].GetInt() }; k <= gridPosition[3].GetInt(); ++k)
						{
							tileManager.SetTileType(TileType::Tray, j* m_Rows + k);

						}
					}
				}
			}

			if(objectString == enemyTag.c_str())
			{
				const auto& gridPositionsJson = levelJson["gridPositions"];
				auto gridPositions = gridPositionsJson.GetArray();

				std::string MrHotDogTag = "HotDog";
				std::string MrEggTag = "Egg";
				std::string MrPickleTag = "Pickle";

				for (unsigned int i{}; i < gridPositions.Size(); i++)
				{
					auto gridPosition = gridPositions[i].GetArray();

					for (int j{ gridPosition[0].GetInt() }; j <= gridPosition[1].GetInt(); ++j)
					{
						for (int k{ gridPosition[2].GetInt() }; k <= gridPosition[3].GetInt(); ++k)
						{
							std::shared_ptr<dae::GameObject> goEnemy = std::make_shared<dae::GameObject>(gridPosition[4].GetString(), 1);

							std::string enemyImage{ "Mr"};
							enemyImage += gridPosition[4].GetString();
							enemyImage += ".png";

							goEnemy->AddComponent(std::make_shared<ImageComponent>(enemyImage));
							goEnemy->AddComponent(std::make_shared<MovementComponent>(goEnemy.get(), 50.f));
							goEnemy->AddComponent(std::make_shared<AIComponent>(goEnemy.get(), GetObjectWithName("Peter Pepper").get(), gridPosition[5].GetBool()));
							goEnemy->GetComponent<ImageComponent>()->SetSize({ 50.f, 50.f });
							goEnemy->GetComponent<ImageComponent>()->SetSheetSize({ 96.f, 32.f });

							if(gridPosition[4].GetString() == MrHotDogTag)
							{
								goEnemy->AddComponent(std::make_shared<EnemyComponent>(goEnemy.get(), 100, GetObjectWithName("Peter Pepper").get()));

							}
							else if (gridPosition[4].GetString() == MrEggTag)
							{
								goEnemy->AddComponent(std::make_shared<EnemyComponent>(goEnemy.get(), 300, GetObjectWithName("Peter Pepper").get()));
							}
							else if(gridPosition[4].GetString() == MrPickleTag)
							{
								goEnemy->AddComponent(std::make_shared<EnemyComponent>(goEnemy.get(), 200, GetObjectWithName("Peter Pepper").get()));
							}
							goEnemy->SetPosition(TileManager::GetInstance().GetTileAtIndex(j* m_Rows + k)->m_Boundingbox.x, TileManager::GetInstance().GetTileAtIndex(j* m_Rows + k)->m_Boundingbox.y);
							auto pEnemyCol = goEnemy->AddComponent(std::make_shared<CollisionComponent>(goEnemy.get(), true, 50.f, 50.f, false));
							AddCollision(pEnemyCol);

							goEnemy->GetComponent<ImageComponent>()->SetLocalTransform(Transform{ 0.f, -50.f / 4.f, 0.f });
							Add(goEnemy);
						}
					}
				}
			}

			if (objectString == playerTag.c_str())
			{
				const auto& gridPositionsJson = levelJson["gridPositions"];
				auto gridPositions = gridPositionsJson.GetArray();

				for (unsigned int i{}; i < gridPositions.Size(); i++)
				{
					auto gridPosition = gridPositions[i].GetArray();

					for (int j{ gridPosition[0].GetInt() }; j <= gridPosition[1].GetInt(); ++j)
					{
						for (int k{ gridPosition[2].GetInt() }; k <= gridPosition[3].GetInt(); ++k)
						{
							GetObjectWithName("Peter Pepper")->SetPosition(TileManager::GetInstance().GetTileAtIndex(j* m_Rows + k)->m_Boundingbox.x, TileManager::GetInstance().GetTileAtIndex(j* m_Rows + k)->m_Boundingbox.y - height/2.f);
						}
					}
				}
			}
		}
	}
	else
	{
		std::cerr << "File not found";
	}
}
