#include "MiniginPCH.h"
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <Xinput.h>
#pragma comment (lib, "xinput.lib")

#include "XboxController.h"
#include "Command.h"
#include <memory>
#include <map>
#include <vector>


class dae::XboxController::XboxControllerImpl
{
	using ControllerKey = std::pair<unsigned, ControllerButton>;
	using ControllerCommandsMap = std::map<ControllerKey, std::shared_ptr<Command>>;
	ControllerCommandsMap m_ControllerCommands{};

	XINPUT_STATE* m_CurrentState{};
	XINPUT_STATE* m_PreviousState{};

public:
	XboxControllerImpl()
		:m_CurrentState(new XINPUT_STATE[XUSER_MAX_COUNT]), m_PreviousState(new XINPUT_STATE[XUSER_MAX_COUNT])
	{
		ZeroMemory(m_PreviousState, sizeof(XINPUT_STATE) * XUSER_MAX_COUNT);
		ZeroMemory(m_CurrentState, sizeof(XINPUT_STATE) * XUSER_MAX_COUNT);
	}

	~XboxControllerImpl()
	{
		delete[] m_CurrentState;
		m_CurrentState = nullptr;

		delete[] m_PreviousState;
		m_PreviousState = nullptr;
	}

	std::vector<std::pair<unsigned int, std::shared_ptr<Command>>> ProcessInput()
	{
		std::swap(m_PreviousState, m_CurrentState);

		for (DWORD i{}; i < XUSER_MAX_COUNT; ++i)
		{
			XInputGetState(i, &m_CurrentState[i]);
		}

		std::vector<std::pair<unsigned int, std::shared_ptr<Command>>> tempCommand{};

		for (auto& b : m_ControllerCommands)
		{
			if (IsDown(b.first))
			{
				tempCommand.push_back(std::make_pair(b.first.first, (b.second)));
			}
		}

		return tempCommand;

	}

	bool IsDown(const std::pair<unsigned, ControllerButton>& controllerButton) const
	{
		auto buttonChanges = m_CurrentState[controllerButton.first].Gamepad.wButtons ^ m_PreviousState[controllerButton.first].Gamepad.wButtons;
		int down = buttonChanges & m_CurrentState[controllerButton.first].Gamepad.wButtons;
		return down & static_cast<unsigned int>(controllerButton.second);
	}

	bool IsUp(const std::pair<unsigned, ControllerButton>& controllerButton) const
	{
		auto buttonChanges = m_CurrentState[controllerButton.first].Gamepad.wButtons ^ m_PreviousState[controllerButton.first].Gamepad.wButtons;
		int up = buttonChanges & ~(m_CurrentState[controllerButton.first].Gamepad.wButtons);
		return up & static_cast<unsigned int>(controllerButton.second);
	}

	bool IsPressed(const std::pair<unsigned, ControllerButton>& controllerButton) const
	{
		return m_CurrentState[controllerButton.first].Gamepad.wButtons & static_cast<unsigned int>(controllerButton.second);
	}

	void AddCommand(const std::map<ControllerButton, std::shared_ptr<Command>>& inputCommands, unsigned int id)
	{
		for( auto& c: inputCommands)
		{
			m_ControllerCommands[std::make_pair(id, c.first)] = std::move(c.second);
		}
	}

	void RemoveCommand(const ControllerButton& button, unsigned int id)
	{
		m_ControllerCommands[std::make_pair(id, button)] = nullptr;
	}

	void RemoveCommands()
	{
		m_ControllerCommands.clear();
	}
};

std::vector<std::pair<unsigned int, std::shared_ptr<Command>>> dae::XboxController::ProcessInput()
{
	return pImpl->ProcessInput();
}

bool dae::XboxController::IsPressed(const std::pair<unsigned, ControllerButton>& controllerButton) const
{
	return pImpl->IsPressed(controllerButton);
}

bool dae::XboxController::IsDown(const std::pair<unsigned, ControllerButton>& controllerButton) const
{
	return pImpl->IsDown(controllerButton);
}

bool dae::XboxController::IsUp(const std::pair<unsigned, ControllerButton>& controllerButton) const
{
	return pImpl->IsUp(controllerButton);
}

void dae::XboxController::AddCommand(const std::map<ControllerButton, std::shared_ptr<Command>>& inputCommands, unsigned int id)
{
	pImpl->AddCommand(inputCommands, id);
}

void dae::XboxController::RemoveCommand(const ControllerButton& button, unsigned int id)
{
	pImpl->RemoveCommand(button, id);
}

void dae::XboxController::RemoveCommands()
{
	pImpl->RemoveCommands();
}

dae::XboxController::XboxController()
{
	pImpl = new XboxControllerImpl();
}

dae::XboxController::~XboxController()
{
	delete pImpl;
	pImpl = nullptr;
}


