#pragma once
#include <XInput.h>
#include "Singleton.h"
#include "XboxController.h"

class Command;

namespace dae
{
	enum class ControllerButton
	{
		DpadUp = 0x0001,
		DpadDown = 0x0002,
		DpadLeft = 0x0004,
		DpadRight = 0x0008,
		Start = 0x0010,
		Back = 0x0020,
		LeftThumb = 0x0040,
		RightThumb = 0x0080,
		LeftShoulder = 0x0100,
		RightShoulder = 0x0200,
		ButtonA = 0x1000,
		ButtonB = 0x2002,
		ButtonX = 0x4000,
		ButtonY = 0x8000,
	};

	class InputManager final : public Singleton<InputManager>
	{
	public:
		InputManager();
		bool ProcessInput(std::vector<std::pair<unsigned int, std::shared_ptr<Command>>>& commands);
		bool IsPressed(ControllerButton button) const;

		void AddCommand(const std::map<ControllerButton, std::shared_ptr<Command>>& inputCommands, unsigned int id);
		void RemoveCommand(const ControllerButton& button, unsigned int id);
	private:
		XboxController* m_pController;
		bool GetControllerInput(std::vector<std::pair<unsigned int, std::shared_ptr<Command>>>& commands);
	};

}
