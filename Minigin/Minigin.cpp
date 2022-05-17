#include "MiniginPCH.h"
#include "Minigin.h"
#include <thread>
#include "InputManager.h"
#include "SceneManager.h"
#include "Renderer.h"
#include "ResourceManager.h"
#include "GameObject.h"
#include "Scene.h"
#include <chrono>

#include "Command.h"
#include "Time.h"
#include "ImageComponent.h"
#include "TextComponent.h"
#include "FPSComponent.h"

using namespace std;

void PrintSDLVersion()
{
	SDL_version compiled{};
	SDL_version linked{};

	SDL_VERSION(&compiled);
	SDL_GetVersion(&linked);
	printf("We compiled against SDL version %d.%d.%d ...\n",
		compiled.major, compiled.minor, compiled.patch);
	printf("We are linking against SDL version %d.%d.%d.\n",
		linked.major, linked.minor, linked.patch);
}

void dae::Minigin::Initialize()
{
	PrintSDLVersion();
	
	if (SDL_Init(SDL_INIT_VIDEO) != 0) 
	{
		throw std::runtime_error(std::string("SDL_Init Error: ") + SDL_GetError());
	}

	m_Window = SDL_CreateWindow(
		"Programming 4 assignment",
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		1280,
		720,
		SDL_WINDOW_OPENGL
	);
	if (m_Window == nullptr) 
	{
		throw std::runtime_error(std::string("SDL_CreateWindow Error: ") + SDL_GetError());
	}

	Renderer::GetInstance().Init(m_Window);
}

/**
 * Code constructing the scene world starts here
 */
void dae::Minigin::LoadGame() const
{
	auto& scene = SceneManager::GetInstance().CreateScene("Demo");

	auto go = std::make_shared<GameObject>("Background");
	go->AddComponent<ImageComponent>(std::make_shared<ImageComponent>("background.jpg"));
	
	scene.Add(go);

	go = std::make_shared<GameObject>("Logo");
	go->AddComponent<ImageComponent>(std::make_shared<ImageComponent>("logo.png"));
	go->SetPosition(216, 180);
	scene.Add(go);

	auto font = ResourceManager::GetInstance().LoadFont("Lingua.otf", 36);
	go = std::make_shared<GameObject>("Title");
	go->AddComponent<TextComponent>(std::make_shared<TextComponent>("Programming 4 Assignment", font));
	go->SetPosition(80, 20);
	scene.Add(go);

	go = std::make_shared<GameObject>("FPS");
	go->AddComponent<TextComponent>(std::make_shared<TextComponent>("FPS", font));
	go->AddComponent<FPSComponent>(std::make_shared<FPSComponent>(go));
	go->SetPosition(10, 10);
	scene.Add(go);



	auto goPlayer1 = std::make_shared<GameObject>("Peter Pepper");
	goPlayer1->SetPosition(10, 160);
	goPlayer1->AddComponent<PetterPepperComponent>(std::make_shared<PetterPepperComponent>(goPlayer1));
	scene.Add(goPlayer1);

	auto goPlayer2 = std::make_shared<GameObject>("Peter Pepper 2");
	goPlayer2->SetPosition(10, 260);
	goPlayer2->AddComponent<PetterPepperComponent>(std::make_shared<PetterPepperComponent>(goPlayer2));
	scene.Add(goPlayer2);

	std::map<ControllerButton, std::shared_ptr<Command>> inputMap{};
	inputMap[ControllerButton::ButtonA] = std::make_shared<DieCommand>(goPlayer1.get());
	inputMap[ControllerButton::ButtonB] = std::make_shared<PointCommand>(goPlayer1.get());

	inputMap[ControllerButton::ButtonX] = std::make_shared<DieCommand>(goPlayer2.get());
	inputMap[ControllerButton::ButtonY] = std::make_shared<PointCommand>(goPlayer2.get());

	InputManager::GetInstance().AddCommand(inputMap, 0);

	std::cout << "Player 1 input: A for Dying, B for Points (50)\n";
	std::cout << "Player 2 input: X for Dying, Y for Points (50)\n";
}

void dae::Minigin::Cleanup()
{
	Renderer::GetInstance().Destroy();
	SDL_DestroyWindow(m_Window);
	m_Window = nullptr;
	SDL_Quit();
}

void dae::Minigin::Run()
{
	Initialize();

	// tell the resource manager where he can find the game data
	ResourceManager::GetInstance().Init("../Data/");

	LoadGame();

	{
		auto& renderer = Renderer::GetInstance();
		auto& sceneManager = SceneManager::GetInstance();
		auto& input = InputManager::GetInstance();

		// todo: this update loop could use some work.
		auto lastTime = std::chrono::high_resolution_clock::now();
		bool doContinue = true;
		float lag = 0.0f;
		const float fixedTimeStep = 0.02f;
		while (doContinue)
		{
			std::vector<std::pair<unsigned int, std::shared_ptr<Command>>> commands{};
			auto currentTime = std::chrono::high_resolution_clock::now();
			float deltaTime = std::chrono::duration<float>(currentTime - lastTime).count();

			lastTime = currentTime;
			lag += deltaTime;
			doContinue = input.ProcessInput(commands);
			if(commands.size() != 0)
			{
				for (const auto& c : commands)
					c.second->Execute();
			}
			sceneManager.Update(deltaTime);

			while (lag >= fixedTimeStep)
			{
				sceneManager.FixedUpdate();
				lag -= fixedTimeStep;
			}

			renderer.Render();
		}
	}

	Cleanup();
}
