#ifndef BSESANDBOX_DATA_H
#define BSESANDBOX_DATA_H

#include <BSE_Client.h>

namespace Game {
	/*
	void DrawThings(){
		// SETUP variables --------------------------
		// triangle things
		BSE::VertexArray* m_VertexArray;
		BSE::ShaderExample* m_Shader;
		
		// square things
		BSE::VertexArray* m_SquareVA;
		BSE::ShaderExample* m_BlueShader;
		// ------------------------------------------
		
		// PROCESS VARIABLES ------------------------
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
		float squareVertices[3 * 4] = {
			// one vertice, three-component vector X,Y,Z clipping -1...1
			-0.5f, -0.5f,  0.0f,  
			0.5f, -0.5f,  0.0f,
			0.5f,  0.5f,  0.0f,
			-0.5f,  0.5f,  0.0f,
		};
		BSE_TRACE("Square Vertices defined");
		
		BSE::VertexBuffer* m_SquareVB = BSE::VertexBuffer::Create(squareVertices, sizeof(squareVertices));	
		
		m_SquareVB->SetLayout({
			{BSE::ShaderDataType::Float3, "a_Position"},
		});
		m_SquareVA->AddVertexBuffer(m_SquareVB);
		BSE_TRACE("Square Vertex buffer layout construction successful");
		
		uint32_t squareIndices[6] = { 0, 1, 2, 2, 3, 0 };
		m_SquareVA->SetIndexBuffer(BSE::IndexBuffer::Create(squareIndices, (sizeof(squareIndices) / sizeof(uint32_t))));
		BSE_TRACE("Square Index buffer bind successful");
		// ------------------------------------------
		
		// ATTACH SHADERS ---------------------------
		// Shader 1
		std::string vertexShaderSource = BSE::FileIO::GetRawText("./shaders/Vertex1.txt");
		std::string fragmentShaderSource = BSE::FileIO::GetRawText("./shaders/Fragment1.txt");
		
		// Shader 2
		std::string BlueShaderVertexShaderSource = BSE::FileIO::GetRawText("./shaders/Vertex2.txt");
		std::string BlueShaderFragmentShaderSource = BSE::FileIO::GetRawText("./shaders/Fragment2.txt");
		
		m_Shader = new BSE::ShaderExample(vertexShaderSource, fragmentShaderSource);
		m_BlueShader = new BSE::ShaderExample(BlueShaderVertexShaderSource, BlueShaderFragmentShaderSource);
		// ------------------------------------------
		
		// SEND DATA TO BSE ENGINE ------------------
		// TODO: resources manager should be there to control:
		// - what is on the scene,
		// - with what resources in mind it should be built,
		// - when it should be removed,
		// - what should be done with its resources.
		// ------------------------------------------
	}
	*/
}

#endif
