#include <BSE_Client.h>
// #include "BSE_Client.h"
// #include <vendor/imgui/imgui.h>
// #include <Core.h>
// #include <log.h>
// #include <Application.h>
// #include <EntryPoint.h>

class ExampleLayer : public BSE::Layer {
public:
	ExampleLayer()
		: BSE::Layer("Example")
	{};
	
	void OnUpdate() override {
		//BSE_INFO("ExampleLayer - Update!");
	}
	
	void OnEvent(BSE::Event& event) override {
		// BSE_TRACE("ExampleLayer: {0}", event);
	}
};


class SandboxGuiLayer : public BSE::ImGuiLayer {
	void OnImGuiRender() {
		// ------------------------------------------------------------------------------------
		// Hard-copy from FixImGuiContext defined in ImGuiLayer.h/cpp	-----------------------
		if (m_ImGuiContext != nullptr){									// --------------------
			if (m_ImGuiContext != ImGui::GetCurrentContext()){ 			// --------------------
				// from imgui.h & imgui.cpp comments: 					-----------------------
				// if using Dear ImGui as a shared library, it is necessary to use
				// SetCurrentContext() and SetAllocatorFunctions() to restore normal behaviour
				BSE_TRACE("SandboxGui: Current Context is different!"); // --------------------
				ImGui::SetCurrentContext(m_ImGuiContext);				// --------------------
				BSE_TRACE("SandboxGui: Current Context is set again!"); // --------------------
			} // ------------------------------------------------------------------------------
		} // ----------------------------------------------------------------------------------
		// ------------------------------------------------------------------------------------
			
		static char buf[256] = u8"Фыва";
		
		static char textinput[256] = u8"Wonder what это такое?";
		static float f = 0.0f;
		
		// DONE: find out why this crashes the app
		// calling to ImGui::GetIO() tells that no context is availiable
		// GetCurrentContext returned wrong context! Synchronized it with m_ImGuiContext
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
		//PushOverlay(new BSE::ImGuiLayer());
		
		m_ImGuiLayerEnabled = false;
	}
	
	~Sandbox(){
	}
};

BSE::Application* BSE::CreateApplication() {
	return new Sandbox();
}
