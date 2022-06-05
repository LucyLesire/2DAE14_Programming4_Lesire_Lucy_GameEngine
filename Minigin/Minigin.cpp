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

#include "BaseGame.h"
#include "Command.h"
#include "Time.h"
#include "ImageComponent.h"
#include "TextComponent.h"
#include "Observer.h"

#include "ServiceLocator.h"

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

void dae::Minigin::Initialize(dae::BaseGame* pCurrentGame)
{
	PrintSDLVersion();

	//SDL Init
	if (SDL_Init(SDL_INIT_VIDEO) != 0) 
	{
		throw std::runtime_error(std::string("SDL_Init Error: ") + SDL_GetError());
	}

	//Audio init
	SDL_Init(SDL_INIT_AUDIO);
	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
		std::cout << "Error: " << Mix_GetError() << "\n";

	m_Window = SDL_CreateWindow(
		"Programming 4 assignment",
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		pCurrentGame->GetWindowWidth(),
		pCurrentGame->GetWindowHeight(),
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
}

void dae::Minigin::Cleanup()
{
	Renderer::GetInstance().Destroy();
	SDL_DestroyWindow(m_Window);
	m_Window = nullptr;
	SDL_Quit();
}

void dae::Minigin::Run(dae::BaseGame* pCurrentGame)
{
	Initialize(pCurrentGame);

	// tell the resource manager where he can find the game data
	ResourceManager::GetInstance().Init("../Data/");

	pCurrentGame->CreateGameScenes();
	SceneManager::GetInstance().Initialize();
	//Game loop
	{
		auto& renderer = Renderer::GetInstance();
		auto& sceneManager = SceneManager::GetInstance();
		auto& input = InputManager::GetInstance();


		auto lastTime = std::chrono::high_resolution_clock::now();
		bool doContinue = true;
		float lag = 0.0f;
		const float fixedTimeStep = 0.02f;

		while (doContinue)
		{
			auto currentTime = std::chrono::high_resolution_clock::now();
			float deltaTime = std::chrono::duration<float>(currentTime - lastTime).count();
			lastTime = currentTime;
			lag += deltaTime;

			doContinue = input.ProcessInput();
			sceneManager.Update(deltaTime);

			//FixedUpdate
			while (lag >= fixedTimeStep)
			{
				sceneManager.FixedUpdate(fixedTimeStep);
				lag -= fixedTimeStep;
			}

			sceneManager.LateUpdate(deltaTime);

			renderer.Render();

			sceneManager.RestartSceneAtEndGameLoop();
		}
	}

	Cleanup();
}
