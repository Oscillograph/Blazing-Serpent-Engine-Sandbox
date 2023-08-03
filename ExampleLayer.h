#ifndef BSESANDBOX_EXAMPLELAYER_H
#define BSESANDBOX_EXAMPLELAYER_H

#include <BSE_Client.h>

class ExampleLayer : public BSE::Layer {
public:
	ExampleLayer()
		: BSE::Layer("Example")
	{
		m_Window = BSE::Application::Get()->GetWindow();
		m_Title = m_Window->GetTitle();
		
		// ------------------------------------------------
		// OpenGL drawing a simple triangle
		unsigned int w = BSE::Application::Get()->GetWindow()->GetWidth();
		unsigned int h = BSE::Application::Get()->GetWindow()->GetHeight();
		float uw = (float)w/(float)h;
		float uh = 2*(float)h/(float)h;
		// m_Camera = new OrthographicCamera(-2.0f, 2.0f, 2.0f, -2.0f);
		m_CameraController = new BSE::OrthographicCameraController(uw, 1.5f, true);
		// m_Camera = new BSE::OrthographicCamera(-uw, uw, uh, -uh);
		m_ShaderLibrary = BSE::Renderer::GetShaderLibrary();
		
		// TODO: move this all to Sandbox, for data shouldn't be in engine modules
		
		// Triangle Vertex array
		m_VertexArray = BSE::VertexArray::Create();
		
		float vertices[3 * 7] = {
			// one vertice, three-component vector X,Y,Z clipping -1...1
			// and, also, 4 numbers for color ov vertices
			-0.5f, -0.5f,  0.0f,  0.8f, 0.2f, 0.8f, 1.0f,  
			 0.5f, -0.5f,  0.0f,  0.2f, 0.8f, 0.8f, 1.0f,
			 0.25f, 0.25f, 0.0f,  0.8f, 0.8f, 0.2f, 1.0f
		};
		BSE_TRACE("Vertices defined");
		
		BSE::VertexBuffer* m_VertexBuffer = BSE::VertexBuffer::Create(vertices, sizeof(vertices));
		BSE::BufferLayout layout = {
			{BSE::ShaderDataType::Float3, "a_Position"},
			{BSE::ShaderDataType::Float4, "a_Color"}
		};	
		
		m_VertexBuffer->SetLayout(layout);
		m_VertexArray->AddVertexBuffer(m_VertexBuffer);
		BSE_TRACE("Vertex buffer layout construction successful");
		
		uint32_t indices[3] = { 0, 1, 2 };
		m_VertexArray->SetIndexBuffer(BSE::IndexBuffer::Create(indices, (sizeof(indices) / sizeof(uint32_t))));
		BSE_TRACE("Index buffer bind successful");
		
		// Square Vertex Array
		m_SquareVA = BSE::VertexArray::Create();
		float squareVertices[5 * 4] = {
			// one vertice, three-component vector X,Y,Z clipping -1...1
			// two numbers for texture coords
			-0.5f, -0.5f,  0.0f, 	0.0f, 0.0f,
			 0.5f, -0.5f,  0.0f, 	1.0f, 0.0f,
			 0.5f,  0.5f,  0.0f, 	1.0f, 1.0f,
			-0.5f,  0.5f,  0.0f, 	0.0f, 1.0f
		};
		BSE_TRACE("Square Vertices defined");
		
		BSE::VertexBuffer* m_SquareVB = BSE::VertexBuffer::Create(squareVertices, sizeof(squareVertices));	
		
		m_SquareVB->SetLayout({
			{BSE::ShaderDataType::Float3, "a_Position"},
			{BSE::ShaderDataType::Float2, "a_TextureCoordinates"},
		});
		m_SquareVA->AddVertexBuffer(m_SquareVB);
		BSE_TRACE("Square Vertex buffer layout construction successful");
		
		uint32_t squareIndices[6] = { 0, 1, 2, 2, 3, 0 };
		m_SquareVA->SetIndexBuffer(BSE::IndexBuffer::Create(squareIndices, (sizeof(squareIndices) / sizeof(uint32_t))));
		BSE_TRACE("Square Index buffer bind successful");
		
		// ============
		
		
		// Shader 1
		std::string vertexShaderSource = BSE::FileIO::GetRawText("./shaders/vertex/Vertex1.txt");
		std::string fragmentShaderSource = BSE::FileIO::GetRawText("./shaders/fragment/Fragment1.txt");
		m_Shader = BSE::Shader::Create("Triangle", vertexShaderSource, fragmentShaderSource);
		m_ShaderLibrary->Add(m_Shader);
		
		// Shader 2
		std::string FlatColorShaderVertexShaderSource = BSE::FileIO::GetRawText("./shaders/vertex/Vertex2.txt");
		std::string FlatColorShaderFragmentShaderSource = BSE::FileIO::GetRawText("./shaders/fragment/Fragment2.txt");
		m_FlatColorShader = BSE::Shader::Create("Flat Color", FlatColorShaderVertexShaderSource, FlatColorShaderFragmentShaderSource);
		m_ShaderLibrary->Add(m_FlatColorShader);
		
		// Shader 3
		
		//m_TextureShader = BSE::Shader::Create("Texture", "./shaders/glsl/Example.glsl");
		m_TextureShader = m_ShaderLibrary->Load("Texture", "./shaders/glsl/Example.glsl");
		
		m_SquareTexture = BSE::Texture2D::Create("./assets/img/broscillograph.png");
		m_TransparentTexture = BSE::Texture2D::Create("./assets/img/broscillograph-transparent-screen.png");
		m_TextureShader->UploadUniformInt("u_Texture", 0);
	};
	
	~ExampleLayer(){
		if (m_CameraController != nullptr){
			delete m_CameraController;
			m_CameraController = nullptr;
		}
		if (m_VertexArray != nullptr){
			delete m_VertexArray;
			m_VertexArray = nullptr;
		}
		if (m_SquareVA != nullptr){
			delete m_SquareVA;
			m_SquareVA = nullptr;
		}
		if (m_Shader != nullptr){
			delete m_Shader;
			m_Shader = nullptr;
		}
		if (m_FlatColorShader != nullptr){
			delete m_FlatColorShader;
			m_FlatColorShader = nullptr;
		}
	}
	
	int OnUpdate(float time) override {
		// Camera control and rendering stuff
		
		// accumulate layer time
		layerTime += time;
		
		// --------------------------------------------------
		// CAMERA
		m_CameraController->OnUpdate(time);
		KeyBoardUpdate(time);
		
		// --------------------------------------------------
		// RENDER
		if (BSE::RenderCommand::GetAPI() != nullptr){
			if (layerTime >= BSE_FPS30){
				// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
				// Show some info about FPS on WindowTitle
				int fps = round(1 / layerTime);
				char buf[5];
				sprintf(buf, "%d", fps);
				m_Window->SetTitle(m_Title + " :: FPS = " + buf);
				// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
				
				//RenderCommand::SetClearColor(glm::vec4(0.2f, 0.2f, 0.4f, 1));
				BSE::RenderCommand::SetClearColor({0.2f, 0.2f, 0.4f, 1});
				BSE::RenderCommand::Clear();
				
				// transform matrix preparation
				// glm::mat4 transform = glm::translate(glm::mat4(1.0f), m_SquareTransform);
				static glm::mat4 scale = glm::scale(glm::mat4(1.0f), glm::vec3(0.1f));
				
				// Renderer::BeginScene(camera, lights, environment);
				BSE::Renderer::BeginScene(m_CameraController->GetCamera());
				
				// TODO:: shader inside material, material inside mesh, mesh is submitted to Renderer
				
				/*
				// TODO: Material API
				BSE::MaterialRef* material = new BSE::Material(m_FlatColorShader); // create a material in Shader object and return a link to it
				BSE::MaterialInstance mi = new BSE::MaterialInstance(material); // make a material instance for that specific material
				mi->Set("u_Color", blueColor); // set parameters of the material
				mi->Set("u_Texture", texture); // set parameters of the material
				SquareMesh->SetMaterial(mi); // add the material to mesh object
				
				// Then in Render.h/cpp Submit becomes Submit(MaterialInstance mi, ...),
				// and the first lines of the method become:
				mi.Bind(); // which binds shader and sets up variables corresponding to the material instance of the material
				*/
				
				m_BlueColor.x = m_BlueColor.x + layerTime - round(m_BlueColor.x + layerTime);
				for (int x = 0; x < 25; x++){
					for (int y = 0; y < 25; y++){
						glm::vec3 pos(x * 0.11f, y * 0.11f, 0.0f);
						pos = pos + m_SquareTransform;
						glm::mat4 transform = glm::translate(glm::mat4(1.0f), pos) * scale;
						
						// m_FlatColorShader->Bind();
						if (((x + y) % 2) == 0){
							m_FlatColorShader->UploadUniformVec4("u_Color", m_BlueColor);
						} else {
							m_FlatColorShader->UploadUniformVec4("u_Color", m_RedColor);
						}
						BSE::Renderer::Submit(m_ShaderLibrary->Get("Flat Color"), m_SquareVA, transform);
					}
				}
				
				m_SquareTexture->Bind();
				BSE::Renderer::Submit(
					//m_TextureShader,
					m_ShaderLibrary->Get("Texture"), 
					m_SquareVA, 
					glm::scale(glm::mat4(1.0f), glm::vec3(1.5f))
					);
				m_TransparentTexture->Bind();
				//BSE::Renderer::Submit(
				//	m_TextureShader, 
				//	m_SquareVA, 
				//	glm::scale(glm::mat4(1.0f), glm::vec3(1.5f))
				//	);
				BSE::Renderer::Submit(
					m_ShaderLibrary->Get("Texture"),
					m_SquareVA, 
					glm::translate(glm::mat4(1.0f), glm::vec3(0.25f, -0.25f, 0.25f)) * glm::scale(glm::mat4(1.0f), glm::vec3(1.5f))
					);
				
				//Triangle
				BSE::Renderer::Submit(m_ShaderLibrary->Get("Triangle"), m_VertexArray);
				
				BSE::Renderer::EndScene();
				// Renderer::Flush();
				
				// reset layer time
				layerTime = 0.0f;
				return 1; // 1 - changed something
			} else {
				return 0; // 0 - no changes on screen
				// Warning! This will affect result of worl from ALL layers
				// glReadBuffer(GL_BACK);
				// glDrawBuffer(GL_FRONT);
				// Which means this should be done via much higher abstract construct like window
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
	void KeyBoardUpdate(float time){
		if (BSE::Input::IsKeyPressed(BSE_KEY_I)){
			m_SquareTransform.y += m_SquareMoveSpeed * time;
		}
		
		if (BSE::Input::IsKeyPressed(BSE_KEY_J)){
			m_SquareTransform.x -= m_SquareMoveSpeed * time;
		}
		
		if (BSE::Input::IsKeyPressed(BSE_KEY_K)){
			m_SquareTransform.y -= m_SquareMoveSpeed * time;
		}
		
		if (BSE::Input::IsKeyPressed(BSE_KEY_L)){
			m_SquareTransform.x += m_SquareMoveSpeed * time;
		}
	}
private:
	// triangle things
	BSE::VertexArray* m_VertexArray;
	BSE::Shader* m_Shader;
	
	// square things
	BSE::VertexArray* m_SquareVA;
	BSE::Shader* m_FlatColorShader;
	BSE::Shader* m_TextureShader;
	
	BSE::Texture2D* m_SquareTexture;
	BSE::Texture2D* m_TransparentTexture;
	
	BSE::ShaderLibrary* m_ShaderLibrary;
	BSE::OrthographicCameraController* m_CameraController;
	
	float layerTime = 0.0f;
	float m_CameraMoveSpeed = 0.5f;
	float m_CameraRotateSpeed = 5.0f;
	
	glm::vec3 m_SquareTransform = glm::vec3(0.0f);
	float m_SquareMoveSpeed = 1.0f;
	
	glm::vec4 m_RedColor  = {0.7, 0.4, 0.5, 1.0};
	glm::vec4 m_BlueColor = {0.2, 0.3, 0.7, 1.0};
	
	BSE::Window* m_Window;
	std::string m_Title;
};

#endif
