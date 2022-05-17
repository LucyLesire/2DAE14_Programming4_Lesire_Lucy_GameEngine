#include "MiniginPCH.h"
#include "InputManager.h"
#include "backends/imgui_impl_sdl.h"
#include "Command.h"
#include "SceneManager.h"

dae::InputManager::InputManager()
{
	m_pController = new XboxController();
}

bool dae::InputManager::ProcessInput(std::vector<std::pair<unsigned int, std::shared_ptr<Command>>>& commands)
{
	SDL_Event e;
	while (SDL_PollEvent(&e)) {
		if (e.type == SDL_QUIT) {
			return false;
		}
		if (e.type == SDL_KEYDOWN) {
			
		}
		if (e.type == SDL_MOUSEBUTTONDOWN) {
			
		}

		
		//Process ImGui Input Events
		ImGui_ImplSDL2_ProcessEvent(&e);
	}

	if (GetControllerInput(commands))
	{

	}

	return true;
}

void dae::InputManager::AddCommand(const std::map<ControllerButton, std::shared_ptr<Command>>& inputCommands, unsigned int id)
{
	m_pController->AddCommand(inputCommands, id);
}

void dae::InputManager::RemoveCommand(const ControllerButton& button, unsigned int id)
{
	m_pController->RemoveCommand(button, id);
}

bool dae::InputManager::GetControllerInput(std::vector<std::pair<unsigned int, std::shared_ptr<Command>>>& commands)
{
	commands = m_pController->ProcessInput();
	if (commands.size() != 0)
		return true;

	return false;
}

