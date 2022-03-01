#include "MiniginPCH.h"
#include "GraphObject.h"

#include <chrono>

#include "imgui.h"
#include "imgui_plot.h"
#include "backends/imgui_impl_opengl2.h"
#include "backends/imgui_impl_sdl.h"


struct Transform
{
	std::vector<float> arr{
		1, 0, 0, 0,
		0, 1, 0, 0,
		0, 0, 1, 0,
		0, 0, 0, 1,
	};
};

class GameObject3D
{
public:
	Transform transform;
	int ID = 5;
};

class GameObjectAlt3D
{
public:
	Transform* transform;
	int ID = 5;
};

dae::GraphObject::GraphObject(SDL_Window* window)
	:m_Window(window)
{
	std::vector<int> arrInts{};
	std::vector<GameObject3D> arrGameObjects{};
	std::vector<GameObjectAlt3D> arrAltGameObjects{};

	arrInts.resize(1024 * 1024);
	arrGameObjects.resize(1024 * 1024);
	arrAltGameObjects.resize(1024 * 1024);

	std::fill(arrInts.begin(), arrInts.end(), 24);

	for (int stepsize = 1; stepsize <= 1024; stepsize *= 2)
	{
		{
			auto start = std::chrono::high_resolution_clock::now();
			for (int i = 0; i < arrInts.size(); i += stepsize)
			{
				arrInts[i] *= 2;
			}

			auto end = std::chrono::high_resolution_clock::now();
			auto elapsedTime = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
			m_XValuesInts.push_back(float(stepsize));
			m_YValuesInts.push_back(float(elapsedTime));
		}

		{
			auto start = std::chrono::high_resolution_clock::now();
			for (int i = 0; i < arrInts.size(); i += stepsize)
			{
				arrGameObjects[i].ID *= 2;
			}

			auto end = std::chrono::high_resolution_clock::now();
			auto elapsedTime = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
			m_XValuesGo.push_back(float(stepsize));
			m_YValuesGo.push_back(float(elapsedTime));
		}

		{
			auto start = std::chrono::high_resolution_clock::now();
			for (int i = 0; i < arrInts.size(); i += stepsize)
			{
				arrInts[i] *= 2;
			}

			auto end = std::chrono::high_resolution_clock::now();
			auto elapsedTime = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
			m_XValuesAltGo.push_back(float(stepsize));
			m_YValuesAltGo.push_back(float(elapsedTime));

		}

	}
}
void dae::GraphObject::Render()
{
	ImGui_ImplOpenGL2_NewFrame();
	ImGui_ImplSDL2_NewFrame(m_Window);
	ImGui::NewFrame();
	ImGui::PlotConfig conf;
	int data_count = int(m_XValuesInts.size());
	conf.values.xs = &m_XValuesInts[0]; // this line is optional
	conf.values.ys = &m_YValuesInts[0];
	conf.values.count = data_count + 1;
	conf.scale.min = *(std::max(m_YValuesInts.begin(), m_YValuesInts.end()));
	conf.scale.max = *(std::min(m_YValuesInts.begin(), m_YValuesInts.end()));
	conf.tooltip.show = true;
	conf.tooltip.format = "x=%.2f, y=%.2f";
	conf.frame_size = ImVec2(500.f, 500.f);
	conf.line_thickness = 2.f;

	ImGui::Plot("plot", conf);

	conf.values.ys = &m_YValuesGo[0];
	conf.scale.min = *(std::max(m_YValuesGo.begin(), m_YValuesGo.end()));
	conf.scale.max = *(std::min(m_YValuesGo.begin(), m_YValuesGo.end()));
	ImGui::Plot("plot2", conf);


	conf.values.ys = &m_YValuesAltGo[0];
	conf.scale.min = *(std::max(m_YValuesAltGo.begin(), m_YValuesAltGo.end()));
	conf.scale.max = *(std::min(m_YValuesAltGo.begin(), m_YValuesAltGo.end()));
	ImGui::Plot("plot3", conf);

	ImGui::Render();
	ImGui_ImplOpenGL2_RenderDrawData(ImGui::GetDrawData());


}


