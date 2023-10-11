#ifndef BSESANDBOX_SANDBOX2D_H
#define BSESANDBOX_SANDBOX2D_H

#include <BSE_Client.h>
// #include "./src/ParticleSystem.h"

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
		BSE_PROFILE_FUNCTION();
		// ------------------------------------------------
		// OpenGL camera controller
		unsigned int w = BSE::Application::Get()->GetWindow()->GetWidth();
		unsigned int h = BSE::Application::Get()->GetWindow()->GetHeight();
		float uw = (float)w/(float)h;
		float uh = 2*(float)h/(float)h;
		m_CameraController = new BSE::OrthographicCameraController(uw, 1.5f, true);
		// ------------------------------------------------
		
		BSE::FrameBufferSpecification fbSpec;
		fbSpec.Width = m_Window->GetWidth();
		fbSpec.Height = m_Window->GetHeight();
		// ------------------------------------------------
		
		m_SquareTexture = BSE::Texture2D::Create("./assets/img/broscillograph.png");
		m_SquareTexture->Bind(1);
		m_TransparentTexture = BSE::Texture2D::Create("./assets/img/broscillograph-transparent-screen.png");
		m_TransparentTexture->Bind(2);
		m_SpriteSheet = BSE::Texture2D::Create("./assets/img/kenney.nl_spritesheet_retina.png");
		m_SpriteSheet->Bind(3);
		
		BSE::BSE_Rect sprite = { 128.0f, 384.0f, 128.0f, 128.0f };
		m_HandSprite = new BSE::Texture2DSprite(m_SpriteSheet, sprite);
		// m_HandSprite->FlipHorizontally();
		// m_HandSprite->FlipVertically();
		
		// Particles Init here
		m_Particle.ColorBegin = { 255 / 255.0f, 255 / 255.0f, 255 / 255.0f, 1.0f };
		m_Particle.ColorEnd = { 0 / 255.0f, 255 / 255.0f, 255 / 255.0f, 0.25f };
		m_Particle.SizeBegin = 0.2f; 
		m_Particle.SizeVariation = 0.1f;
		m_Particle.SizeEnd = 0.0f;
		m_Particle.LifeTime = 2.0f;
		m_Particle.Velocity = { 0.0f, 0.0f };
		m_Particle.VelocityVariation = { 2.0f, 2.0f };
		m_Particle.Position = { 0.0f, 0.0f };
		
		// Scene init
		m_ActiveScene = new BSE::Scene();
		m_Square = m_ActiveScene->CreateEntity("Square");
		// TODO: find out why SpriteComponent breaks the app
		m_Square->AddComponent<BSE::SpriteComponent>(glm::vec4({1.0f, 0.3f, 0.2f, 1.0f}));
		if (m_Square->HasComponent<BSE::SpriteComponent>())
			BSE_INFO("Added sprite component");
		auto name = m_Square->GetComponent<BSE::NameComponent>();
		BSE_ERROR("Entity <{0}> created", name.Name);
		//if (square.HasComponent<BSE::NameComponent>()){
		//	auto name = square.GetComponent<BSE::NameComponent>();
		//	BSE_ERROR("Entity <{0}> created", name.Name);
		//}
		
	}
	
	void OnDetach() override {
		
	}
	
	int OnUpdate(float time) override {
		BSE_PROFILE_FUNCTION();
		layerTime += time;
		static int frame = 0;
		// BSE_TRACE("Layer time counter increased");
		
		// m_ActiveScene->OnUpdate();
		
		// --------------------------------------------------
		// RENDER
		if (BSE::RenderCommand::GetAPI() != nullptr){
			if (layerTime >= BSE_FPS60){
				BSE_PROFILE_SCOPE("Sandbox2D OnUpdate");

				// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
				// CAMERA
				m_CameraController->OnUpdate(layerTime);
				// BSE_TRACE("Camera controller updated");
				// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
				
				// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
				// Show some info about FPS on WindowTitle
				int fps = round(1 / layerTime);
				if (frame == fps){
					frame = 0;
				}
				char buf[5];
				sprintf(buf, "%d", fps);
				m_Window->SetTitle(m_Title + " :: FPS = " + buf);
				// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
				// BSE_TRACE("Window Title changed");
				
				BSE::Renderer2D::Clear({0.2f, 0.0f + frame*layerTime, 0.4f, 1});
				// BSE_TRACE("Clear screen");
				// m_CameraController->SetProjectionDefault();
				BSE::Renderer2D::BeginScene(m_CameraController->GetCamera());
				
				// m_ActiveScene->OnUpdate(layerTime);
				auto group = m_ActiveScene->Registry().view<BSE::TransformComponent, BSE::SpriteComponent>();
				for (auto entity : group){
					auto [transform, sprite] = group.get<BSE::TransformComponent, BSE::SpriteComponent>(entity);
					// Renderer::Submit(sprite, transform);
					// TODO: remove temporary usage of renderer
					BSE::Renderer2D::DrawQuadGeneral(transform.Transform, nullptr, 1.0f, sprite.Color);
				}
				
				BSE::Renderer2D::EndScene();
				
				// Particles
				if (BSE::Input::IsMouseButtonPressed(BSE_MOUSE_BUTTON_LEFT)) {
					auto [x, y] = BSE::Input::GetMousePosition();
					auto width = BSE::Application::Get()->GetWindow()->GetWidth();
					auto height = BSE::Application::Get()->GetWindow()->GetHeight();
					
					auto bounds = m_CameraController->GetBounds();
					auto pos = m_CameraController->GetCamera()->GetPosition();
					x = ((x / width) - 0.5f) * bounds.GetWidth();
					y = (0.5f - (y / height)) * bounds.GetHeight();
					m_Particle.Position = { x + pos.x, y + pos.y };
					for (int i = 0; i < 10; i++)
						m_ParticleSystem.Emit(m_Particle);
				}
				
				m_ParticleSystem.OnUpdate(layerTime);
				m_ParticleSystem.OnRender(m_CameraController->GetCamera());
				
				layerTime = 0.0f;
				frame++;
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
	
	BSE::Window* m_Window = nullptr;
	std::string m_Title;
	// BSE::ImGuiLayer* m_ImGuiLayer = nullptr;
	
	BSE::OrthographicCameraController* m_CameraController = nullptr;
	
	// Temp
	BSE::Texture2D* m_SquareTexture = nullptr;
	BSE::Texture2D* m_TransparentTexture = nullptr;
	BSE::Texture2D* m_SpriteSheet = nullptr;
	BSE::Texture2DSprite* m_HandSprite = nullptr;
	
	//BSE::VertexArray* m_SquareVA;
	//BSE::Shader* m_FlatColorShader;
	glm::vec4 m_RedColor  = {0.7, 0.4, 0.5, 1.0};
	glm::vec4 m_BlueColor = {0.2, 0.3, 0.7, 1.0};
	
	ParticleSystem m_ParticleSystem;
	ParticleProps m_Particle;
	
	BSE::Scene* m_ActiveScene;
	BSE::Entity* m_Square;
};

#endif
