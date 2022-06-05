#pragma once
struct SDL_Window;
namespace dae
{
	class BaseGame;

	class Minigin
	{
	public:
		void Initialize(dae::BaseGame* pCurrentGame);
		void LoadGame() const;
		void Cleanup();
		void Run(dae::BaseGame* pCurrentGame);
	private:
		static const int MsPerFrame = 16; //16 for 60 fps, 33 for 30 fps
		SDL_Window* m_Window{};
	};
}