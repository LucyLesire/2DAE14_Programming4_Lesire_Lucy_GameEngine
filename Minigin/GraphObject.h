#pragma once

namespace dae
{

	class GraphObject final
	{
	public:

		enum class Type
		{
			ints = 0,
			go = 1,
			altGo = 2
		};

		explicit GraphObject(SDL_Window* window);
		GraphObject() = default;
		~GraphObject() = default;
		GraphObject(const GraphObject& other) = delete;
		GraphObject(GraphObject&& other) noexcept = delete;
		GraphObject& operator=(const GraphObject& other) = delete;
		GraphObject& operator=(GraphObject&& other) noexcept = delete;

		void Render();

		void Calculate(const Type& type);

	private:
		std::vector<float> m_XValues;
		std::vector<float> m_YValues;

		std::vector<float> m_XValuesGo;
		std::vector<float> m_YValuesGo;

		std::vector<float> m_XValuesAltGo;
		std::vector<float> m_YValuesAltGo;
		SDL_Window* m_Window{};

		bool m_CalulcatedInts = false;
		bool m_CalulcatedGo = false;
		bool m_CalulcatedAltGo = false;
	};
}


