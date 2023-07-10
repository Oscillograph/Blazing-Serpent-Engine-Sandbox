#include <BSE_Client.h>

#include "hacks.h"

class ExampleLayer : public BSE::Layer {
public:
	ExampleLayer()
		: BSE::Layer("Example")
	{};
	
	void OnUpdate() override {
	}
	
	void OnEvent(BSE::Event& event) override {
	}
};


class SandboxGuiLayer : public BSE::ImGuiLayer {
	void OnImGuiRender() {
		FixImGuiContext(m_ImGuiContext);
			
		static char buf[256] = u8"Фыва";
		
		static char textinput[256] = u8"Wonder what это такое?";
		static float f = 0.0f;
		
		ImGui::Begin(u8"Начало");
		ImGui::Text(u8"Превед, мир!!!!! %d", 111);
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
		PushLayer(new ExampleLayer());
		
		SetImGuiLayer(new SandboxGuiLayer());
		PushOverlay(GetImGuiLayer());
		
		m_ImGuiLayerEnabled = false;
	}
	
	~Sandbox(){
	}
};

BSE::Application* BSE::CreateApplication() {
	return new Sandbox();
}
