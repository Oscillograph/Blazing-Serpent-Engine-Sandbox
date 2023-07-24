#include <BSE_Client.h>

#include "hacks.h"
//#include "data.h"

// #include "ExampleLayer.h"
#include "Sandbox2D.h"

class SandboxGuiLayer : public BSE::ImGuiLayer {
	void OnImGuiRender(float time) {
		// TODO: find out what causes leak ~4 bytes per a couple of seconds
		
		//FixImGuiContext(m_ImGuiContext);
		if (m_ImGuiContext != nullptr){									
			if (m_ImGuiContext != ImGui::GetCurrentContext()){ 			
				BSE_TRACE("SandboxGui: Current Context is different!"); 
				ImGui::SetCurrentContext(m_ImGuiContext);				
				BSE_TRACE("SandboxGui: Current Context is set again!");
			}
		}
			
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
