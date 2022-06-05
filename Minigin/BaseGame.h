#pragma once
namespace dae
{
	class BaseGame
	{
	public:
		BaseGame(uint32_t windowWidth = 800, uint32_t windowHeight = 1240);
		~BaseGame() = default;
		BaseGame(const BaseGame& other) = delete;
		BaseGame(BaseGame&& other) noexcept = delete;
		BaseGame& operator=(const BaseGame& other) = delete;
		BaseGame& operator=(BaseGame&& other) noexcept = delete;

		virtual void CreateGameScenes() = 0;

		//Returns width of the game window
		uint32_t GetWindowWidth() const { return m_WindowWidth; }

		//Returns height of the game window
		uint32_t GetWindowHeight() const { return m_WindowHeight; }


	private:
		uint32_t m_WindowWidth;
		uint32_t m_WindowHeight;
	};
}


