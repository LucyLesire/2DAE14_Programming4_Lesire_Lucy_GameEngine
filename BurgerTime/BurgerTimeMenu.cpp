#include "BurgerTimeMenu.h"

#define WIN32_LEAN_AND_MEAN
#include <Windows.h>

#include "GameObject.h"
#include "ResourceManager.h"
#include "TextComponent.h"

#include <iostream>
#include <fstream>
#include <SDL_scancode.h>
#include <string>

#include "Command.h"
#include "GameInstance.h"
#include "InputManager.h"
#include "MenuCommands.h"

dae::BurgerTimeMenu::BurgerTimeMenu(const std::string& name, uint32_t width, uint32_t height, unsigned int id)
	:Scene(name, width, height, id)
{
}

void dae::BurgerTimeMenu::Initialize()
{
	//Update highscores
	auto score = GameInstance::GetInstance().GetScore();
	if(score > 0)
	{
		UpdateHighScores(score);
	}
	GameInstance::GetInstance().FullReset();

	//Add Menu
	auto font = ResourceManager::GetInstance().LoadFont("Lingua.otf", 80);

	//Title
	auto titleObject = std::make_shared<GameObject>("Title");
	auto imgComponent = titleObject->AddComponent(std::make_shared<TextComponent>("BURGER TIME!", font, SDL_Color{255, 131, 0, 255}, true));
	titleObject->SetPosition(GetWidth() / 2.f, GetHeight() / 5.f);

	imgComponent->SetSize({ GetWidth() / 2.f, GetHeight() / 8.f });
	Add(titleObject);

	ReadHighScores();

	//Start
	auto startObject = std::make_shared<GameObject>("Start");
	auto imgComponent2 = startObject->AddComponent(std::make_shared<TextComponent>("PRESS START TO PLAY!", font, SDL_Color{ 255, 131, 0, 255 }, true));
	startObject->SetPosition(GetWidth() / 2.f, GetHeight() - GetHeight() / 5.f);
	imgComponent2->SetSize({ GetWidth() / 1.5f, GetHeight() / 8.f });

	Add(startObject);

	//Commands
	std::map<SDL_Scancode, std::shared_ptr<Command>> kInputMap{};
	kInputMap[SDL_SCANCODE_RETURN] = std::make_shared<StartCommand>(nullptr);
	InputManager::GetInstance().AddCommand(kInputMap, 0);

	std::map<ControllerButton, std::shared_ptr<Command>> cInputMap{};
	cInputMap[ControllerButton::Start] = std::make_shared<StartCommand>(nullptr);
	InputManager::GetInstance().AddCommand(cInputMap, 0);
}

void dae::BurgerTimeMenu::ReadHighScores()
{
	auto font = ResourceManager::GetInstance().LoadFont("Lingua.otf", 36);
	std::string fileLoc = "../Data/Highscores.txt";
	if (std::ifstream is{ fileLoc })
	{
		auto heightOffset = GetHeight() / 11.f;
		auto initHeight = GetHeight() / 8.f + heightOffset * 2.f;
		std::string line{};
		if(is.is_open())
		{
			int i{};
			while (std::getline(is, line))
			{
				auto object = std::make_shared<GameObject>("Title");
				auto imgComponent = object->AddComponent(std::make_shared<TextComponent>(line, font, SDL_Color{ 255, 131, 0, 255 }, true));
				imgComponent->SetSize({ GetWidth() / 30.f * line.size(), GetHeight()/12.f });

				object->SetPosition(GetWidth() / 2.f, initHeight + i * heightOffset);
				i++;
				Add(object);
			}
			is.close();
		}
	}
}

void dae::BurgerTimeMenu::UpdateHighScores(unsigned int newScore)
{
	std::string fileLoc = "../Data/Highscores.txt";
	std::ifstream is{};
	is.open(fileLoc, std::ifstream::in);
	std::string line{};
	unsigned int score[5]{};
	if (is.is_open())
	{
		int i{};
		while (std::getline(is, line))
		{
			score[i] = std::stoi(line);
			++i;
		}

		auto it = std::find_if(std::begin(score), std::end(score), [newScore](unsigned int currentScore)
			{
				return newScore > currentScore;
			});

		if (it != std::end(score))
		{
			score[4] = GameInstance::GetInstance().GetScore();
			std::sort(std::begin(score), std::end(score), [](unsigned int currentScore, unsigned int nextScore)
			{
					return currentScore > nextScore;
			});
		}

		is.close();
	}

	std::ofstream ofs;
	ofs.open(fileLoc, std::ofstream::out | std::ofstream::trunc);

	if(ofs.is_open())
	{
		for (int i{}; i < 5; ++i)
		{
			ofs << std::to_string(score[i]) << "\n";
		}

		ofs.close();
	}

}
