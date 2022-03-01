#pragma once

namespace dae
{

	class GraphObject final
	{
	public:
		explicit GraphObject(SDL_Window* window);
		GraphObject() = default;
		~GraphObject() = default;
		GraphObject(const GraphObject& other) = delete;
		GraphObject(GraphObject&& other) noexcept = delete;
		GraphObject& operator=(const GraphObject& other) = delete;
		GraphObject& operator=(GraphObject&& other) noexcept = delete;

		void Render();


	private:
		std::vector<float> m_XValuesInts;
		std::vector<float> m_YValuesInts;

		std::vector<float> m_XValuesGo;
		std::vector<float> m_YValuesGo;

		std::vector<float> m_XValuesAltGo;
		std::vector<float> m_YValuesAltGo;
		SDL_Window* m_Window{};
	};
}


