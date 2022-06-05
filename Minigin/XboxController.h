#pragma once
#include <map>
#include <memory>
#include <vector>


class Command;

namespace dae
{
	enum class ControllerButton;

	class XboxController
	{
		class XboxControllerImpl;
		XboxControllerImpl* pImpl;
	public:

		std::vector<std::pair<unsigned int, std::shared_ptr<Command>>> ProcessInput();
		bool IsPressed(const std::pair<unsigned, ControllerButton>& controllerButton) const;
		bool IsDown(const std::pair<unsigned, ControllerButton>& controllerButton) const;
		bool IsUp(const std::pair<unsigned, ControllerButton>& controllerButton) const;

		void AddCommand(const std::map<ControllerButton, std::shared_ptr<Command>>& inputCommands, unsigned int id);
		void RemoveCommand(const ControllerButton& button, unsigned int id);

		explicit XboxController();
		~XboxController();

	};
}
