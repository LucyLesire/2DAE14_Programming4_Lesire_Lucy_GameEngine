#include "MiniginPCH.h"
#include "InputManager.h"
#include "backends/imgui_impl_sdl.h"
#include "Command.h"
#include "SceneManager.h"

dae::InputManager::InputManager()
{
	m_pController = new XboxController();
}

dae::InputManager::~InputManager()
{
	delete m_pController;
	m_pController = nullptr;

}

bool dae::InputManager::ProcessInput()
{
	std::vector<std::pair<ControllerInput, std::shared_ptr<Command>>> commands{};

	//Check keyboard input
	SDL_Event e;
	while (SDL_PollEvent(&e)) {
		if (e.type == SDL_QUIT) {
			return false;
		}
		if (e.type == SDL_KEYDOWN)
		{
			for (auto& k : m_KeyboardCommands)
			{
				if (e.key.keysym.scancode == k.first.second)
				{
					k.second->Execute();
				}
			}
		}
		if(e.type == SDL_KEYUP)
		{
			for (auto& k : m_KeyboardCommands)
			{
				if (e.key.keysym.scancode == k.first.second)
				{
					k.second->Release();
				}
			}
		}

		if (e.type == SDL_MOUSEBUTTONDOWN) {
		}

		
		//Process ImGui Input Events
		ImGui_ImplSDL2_ProcessEvent(&e);
	}

	//Check controller input
	if (GetControllerInput(commands))
	{
		for (const auto& c : commands)
		{
			if (c.first.pressed)
				c.second->Execute();
			else
				c.second->Release();
		}
	}

	return true;
}

void dae::InputManager::AddCommand(const std::map<ControllerButton, std::shared_ptr<Command>>& inputCommands, unsigned int id)
{
	m_pController->AddCommand(inputCommands, id);
}

void dae::InputManager::AddCommand(const std::map<SDL_Scancode, std::shared_ptr<Command>>& inputCommands, unsigned int id)
{
	for (auto& c : inputCommands)
	{
		m_KeyboardCommands[std::make_pair(id, c.first)] = std::move(c.second);
	}
}

void dae::InputManager::RemoveCommand(const ControllerButton& button, unsigned int id)
{
	m_pController->RemoveCommand(button, id);
}

bool dae::InputManager::GetControllerInput(std::vector<std::pair<ControllerInput, std::shared_ptr<Command>>>& commands) const
{
	commands = m_pController->ProcessInput();
	if (commands.size() != 0)
		return true;

	return false;
}

void dae::InputManager::ResetCommands()
{
	m_KeyboardCommands.clear();
	m_pController->RemoveCommands();
}


