#include <BSE_Client.h>
#include <EntryPoint.h>

#include "hacks.h"
//#include "data.h"

#include "./src/ParticleSystem.h"
// #include "ExampleLayer.h"
#include "Sandbox2D.h"


class SandboxGuiLayer : public BSE::ImGuiLayer {
	void OnImGuiRender(float time) {
		// TODO: find out what causes leak ~4 bytes per a couple of seconds
		FixImGuiContext(m_ImGuiContext);
			
		static char buf[256] = u8"Фыва";
		
		static char textinput[256] = u8"Wonder what это такое?";
		static float f = 0.0f;
		
		ImGui::Begin(u8"Начало");
		ImGui::Text(u8"Превед, мир!!!!! %d", 111);
		// ImGui::ColorPicker4("Color that Square", glm::value_ptr(m_SquareColor))
		ImGui::Button(u8"Сохранить");
		// Important: inputs with the same label are considered by ImGui as kind of the same object
		ImGui::InputText(u8"Строка", buf, IM_ARRAYSIZE(buf));
		ImGui::InputText(u8"Строка Другая", textinput, IM_ARRAYSIZE(textinput));
		ImGui::SliderFloat(u8"Внезапная дробь", &f, 0.0f, 1.0f);
		ImGui::Text(u8"Дробь равна: %f", f);
		
		//static char profileResults[200] = "";
		auto profileResults = BSE::Profiler::Read();
		for (auto kv : profileResults){
				auto name = kv.first;
				float time = kv.second;
			ImGui::Text((name + u8"  %.3f ms").c_str(), time);
		}
		ImGui::End();
	}
};

class Sandbox : public BSE::Application {
public:
	Sandbox(){
		// PushLayer(new ExampleLayer());
		PushLayer(new Sandbox2D());
		
		SetImGuiLayer(new SandboxGuiLayer());
		PushOverlay(GetImGuiLayer());
		
		m_ImGuiLayerEnabled = false;
		m_WinTitle = "BSE Sandbox";
		m_Window->SetTitle(m_WinTitle);
		// m_Window->SetVSync(false);
		m_Window->SetVSync(true);
	}
	
	~Sandbox(){
		BSE_INFO("Exit Sandbox");
	}
	
	std::string m_WinTitle;
};

BSE::Application* BSE::CreateApplication() {
	return new Sandbox();
}
