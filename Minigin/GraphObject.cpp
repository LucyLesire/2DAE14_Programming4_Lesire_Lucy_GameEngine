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
	Transform transform{};
	int ID = 5;
};

class GameObjectAlt3D
{
public:
	Transform* transform{};
	int ID = 5;
};

dae::GraphObject::GraphObject(SDL_Window* window)
	:m_Window(window)
{

}
void dae::GraphObject::Render()
{
	ImGui_ImplOpenGL2_NewFrame();
	ImGui_ImplSDL2_NewFrame(m_Window);
	ImGui::NewFrame();

	ImGui::Begin("Exercise 1");

	if (ImGui::Button("Trash the Cashe"))
		Calculate(Type::ints);

	if(m_CalulcatedInts)
	{
		ImGui::PlotConfig conf;
		int data_count = int(m_XValues.size() + 1);
		conf.values.xs = &m_XValues[0]; // this line is optional
		conf.values.ys = &m_YValues[0];
		conf.values.count = data_count;

		conf.scale.min = *(std::max(m_YValues.begin(), m_YValues.end() - 1));
		conf.scale.max = *(std::min(m_YValues.begin(), m_YValues.end() - 1));
		conf.tooltip.show = true;
		conf.tooltip.format = "x=%.2f, y=%.2f";
		conf.frame_size = ImVec2(500.f, 500.f);
		conf.line_thickness = 2.f;

		ImGui::Plot("plot", conf);
	}

	ImGui::End();

	ImGui::Begin("Exercise 2");

	if (ImGui::Button("Trash the Cashe with GameObjects"))
		Calculate(Type::go);

	if (m_CalulcatedGo)
	{
		ImGui::PlotConfig conf;
		int data_count = int(m_XValuesGo.size() + 1);
		conf.values.xs = &m_XValuesGo[0]; // this line is optional
		conf.values.ys = &m_YValuesGo[0];
		conf.values.count = data_count;

		conf.scale.min = *(std::max(m_YValuesGo.begin(), m_YValuesGo.end() - 1));
		conf.scale.max = *(std::min(m_YValuesGo.begin(), m_YValuesGo.end() - 1));
		conf.tooltip.show = true;
		conf.tooltip.format = "x=%.2f, y=%.2f";
		conf.frame_size = ImVec2(500.f, 500.f);
		conf.line_thickness = 2.f;

		ImGui::Plot("plot", conf);
	}

	if (ImGui::Button("Trash the Cashe with AltGameObjects"))
		Calculate(Type::altGo);

	if(m_CalulcatedAltGo)
	{
		ImGui::PlotConfig conf;
		int data_count = int(m_XValuesAltGo.size() + 1);
		conf.values.xs = &m_XValuesAltGo[0]; // this line is optional
		conf.values.ys = &m_YValuesAltGo[0];
		conf.values.count = data_count;
		conf.scale.min = *(std::max(m_YValuesAltGo.begin(), m_YValuesAltGo.end() - 1));
		conf.scale.max = *(std::min(m_YValuesAltGo.begin(), m_YValuesAltGo.end() - 1));
		conf.tooltip.show = true;
		conf.tooltip.format = "x=%.2f, y=%.2f";
		conf.frame_size = ImVec2(500.f, 500.f);
		conf.line_thickness = 2.f;

		ImGui::Plot("plot2", conf);

		if(m_CalulcatedGo)
		{
			ImGui::Text("Combined:");

			constexpr size_t buf_size = 11;
			static float y_data1[buf_size];
			static float y_data2[buf_size];

			for (int i{}; i < m_YValuesGo.size(); ++i)
			{
				y_data1[i] = m_YValuesGo[i];
			}

			for (int i{}; i < m_YValuesAltGo.size(); ++i)
			{
				y_data2[i] = m_YValuesAltGo[i];
			}

			static const float* y_data[] = { y_data1, y_data2 };

			ImGui::PlotConfig conf2;
			conf2.values.xs = &m_XValuesAltGo[0]; // this line is optional
			conf2.values.count = data_count;
			conf2.values.ys_list = y_data;
			conf2.values.ys_count = 2;
			conf2.scale.min = *(std::max(m_YValuesGo.begin(), m_YValuesGo.end() - 1));
			conf2.scale.max = *(std::min(m_YValuesGo.begin(), m_YValuesGo.end() - 1));
			conf2.tooltip.show = true;
			conf2.tooltip.format = "x=%.2f, y=%.2f";
			conf2.frame_size = ImVec2(500.f, 500.f);
			conf2.line_thickness = 2.f;

			ImGui::Plot("plot3", conf2);
		}

	}


	ImGui::End();

	ImGui::Render();
	ImGui_ImplOpenGL2_RenderDrawData(ImGui::GetDrawData());
}

void dae::GraphObject::Calculate(const Type& type)
{
	if(type == Type::ints)
	{
		m_XValues.clear();
		m_YValues.clear();

		std::vector<int> arrInts{};
		arrInts.resize(1024 * 1024);
		std::fill(arrInts.begin(), arrInts.end(), 24);

		for (int stepsize = 1; stepsize <= 1024; stepsize *= 2)
		{
			auto start = std::chrono::high_resolution_clock::now();
			for (int i = 0; i < arrInts.size(); i += stepsize)
			{
				arrInts[i] *= 2;
			}

			auto end = std::chrono::high_resolution_clock::now();
			auto elapsedTime = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
			m_XValues.push_back(float(stepsize));
			m_YValues.push_back(float(elapsedTime));
		}

		m_CalulcatedInts = true;
	}

	if (type == Type::go)
	{
		m_XValuesGo.clear();
		m_YValuesGo.clear();

		std::vector<GameObject3D> arrGameObjects{};
		arrGameObjects.resize(1024 * 1024);

		for (int stepsize = 1; stepsize <= 1024; stepsize *= 2)
		{
			auto start = std::chrono::high_resolution_clock::now();
			for (int i = 0; i < arrGameObjects.size(); i += stepsize)
			{
				arrGameObjects[i].ID *= 2;
			}

			auto end = std::chrono::high_resolution_clock::now();
			auto elapsedTime = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
			m_XValuesGo.push_back(float(stepsize));
			m_YValuesGo.push_back(float(elapsedTime));
		}

		m_CalulcatedGo = true;
	}

	if (type == Type::altGo)
	{
		m_XValuesAltGo.clear();
		m_YValuesAltGo.clear();

		std::vector<GameObjectAlt3D> arrAltGameObjects{};
		arrAltGameObjects.resize(1024 * 1024);

		for (int stepsize = 1; stepsize <= 1024; stepsize *= 2)
		{
			auto start = std::chrono::high_resolution_clock::now();
			for (int i = 0; i < arrAltGameObjects.size(); i += stepsize)
			{
				arrAltGameObjects[i].ID *= 2;
			}

			auto end = std::chrono::high_resolution_clock::now();
			auto elapsedTime = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
			m_XValuesAltGo.push_back(float(stepsize));
			m_YValuesAltGo.push_back(float(elapsedTime));
		}

		m_CalulcatedAltGo = true;
	}
}


