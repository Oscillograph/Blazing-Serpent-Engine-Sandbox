#ifndef BSESANDBOX_SANDBOX2D_H
#define BSESANDBOX_SANDBOX2D_H

#include <BSE_Client.h>

class Sandbox2D : public BSE::Layer {
public:
	Sandbox2D()
		: BSE::Layer("Sandbox2D")
	{
		BSE_TRACE("Layer Constructor Enter");
		m_Window = BSE::Application::Get()->GetWindow();
		m_Title = m_Window->GetTitle();
	}
	
	~Sandbox2D(){
		if (m_CameraController != nullptr){
			delete m_CameraController;
			m_CameraController = nullptr;
		}
		/*
		if (m_SquareVA != nullptr){
			delete m_SquareVA;
			m_SquareVA = nullptr;
		}
		if (m_FlatColorShader != nullptr){
			delete m_FlatColorShader;
			m_FlatColorShader = nullptr;
		}
		*/
		if (m_SquareTexture != nullptr){
			delete m_SquareTexture;
			m_SquareTexture = nullptr;
		}
		if (m_TransparentTexture != nullptr){
			delete m_TransparentTexture;
			m_TransparentTexture = nullptr;
		}
	}
	
	void OnAttach() override {
		// ------------------------------------------------
		// OpenGL camera controller
		unsigned int w = BSE::Application::Get()->GetWindow()->GetWidth();
		unsigned int h = BSE::Application::Get()->GetWindow()->GetHeight();
		float uw = (float)w/(float)h;
		float uh = 2*(float)h/(float)h;
		m_CameraController = new BSE::OrthographicCameraController(uw, 1.5f, true);
		// ------------------------------------------------
		
		m_SquareTexture = BSE::Texture2D::Create("./assets/img/broscillograph.png");
		m_SquareTexture->Bind(1);
		m_TransparentTexture = BSE::Texture2D::Create("./assets/img/broscillograph-transparent-screen.png");
		m_TransparentTexture->Bind(2);
	}
	
	void OnDetach() override {
		
	}
	
	int OnUpdate(float time) override {
		BSE_PROFILER(u8"Sandbox2D Layer OnUpdate");
		layerTime += time;
		// BSE_TRACE("Layer time counter increased");
		
		// --------------------------------------------------
		// RENDER
		if (BSE::RenderCommand::GetAPI() != nullptr){
			if (layerTime >= BSE_FPS30){
				BSE_PROFILE_SCOPE("Sandbox2D OnUpdate");

				// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
				// CAMERA
				m_CameraController->OnUpdate(layerTime);
				// BSE_TRACE("Camera controller updated");
				// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
				
				// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
				// Show some info about FPS on WindowTitle
				int fps = round(1 / layerTime);
				char buf[5];
				sprintf(buf, "%d", fps);
				m_Window->SetTitle(m_Title + " :: FPS = " + buf);
				// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
				// BSE_TRACE("Window Title changed");
				
				BSE::Renderer2D::Clear({0.2f, 0.2f, 0.4f, 1});
				// BSE_TRACE("Clear screen");
				
				BSE::Renderer2D::BeginScene(m_CameraController->GetCamera());
				// BSE_TRACE("Begin scene");
				
				// int x = 0;
				// int y = 0;
				for (int x = 0; x < 100; x++){
					for (int y = 0; y < 100; y++){
						BSE::Renderer2D::DrawFilledRect(
							{-1.0f + x*0.06f, -1.0f + y*0.06f}, 
							{0.05f, 0.05f}, 
							{0.2f, 0.7f, 0.3f, 1.0f}
							);
					}
					// BSE_INFO("x = {0}, y = {1}", x , y);
				}
				// BSE_TRACE("Quads drawn");
				BSE::Renderer2D::DrawTextureQuad(
					{-1.0f, -1.0f, 0.0f}, 
					{1.0f, 1.0f}, 
					m_SquareTexture,
					1.0f
					// {1.0f, 0.5f, 1.0f, 1.0f}
					);
				
				BSE::Renderer2D::DrawTextureQuad(
					{0.50f, 0.50f, 0.0f}, 
					{1.5f, 1.5f}, 
					m_TransparentTexture,
					1.0f
					// {1.0f, 0.5f, 1.0f, 1.0f}
					);
				
				//BSE::Renderer2D::DrawTextureRectRotated(
				//	{-1.0f, -1.0f}, 
				//	{1.0f, 1.0f}, 
				//	glm::radians(45.0f),
				//	m_TransparentTexture,
				//	1.0f,
				//	{1.0f, 0.5f, 1.0f, 1.0f}
				//	);
				
				
				BSE::Renderer2D::EndScene();
				
				layerTime = 0.0f;
				return 1; // 1 - changed something
			} else {
				return 0; // 0 - no changes on screen
			}
		} else {
			BSE_ERROR("No Render API set");
		}
		
		return 0; // 0 - no changes on screen
	}
	
	void OnEvent(BSE::Event& event) override {
		m_CameraController->OnEvent(event);
	}
	
private:
	float layerTime = 0.0f;
	
	BSE::Window* m_Window;
	std::string m_Title;
	
	BSE::OrthographicCameraController* m_CameraController;
	
	// Temp
	BSE::Texture2D* m_SquareTexture = nullptr;
	BSE::Texture2D* m_TransparentTexture = nullptr;
	
	//BSE::VertexArray* m_SquareVA;
	//BSE::Shader* m_FlatColorShader;
	glm::vec4 m_RedColor  = {0.7, 0.4, 0.5, 1.0};
	glm::vec4 m_BlueColor = {0.2, 0.3, 0.7, 1.0};
};

#endif
