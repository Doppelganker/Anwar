#include "ExampleLayer.h"

#include <imgui/imgui.h>

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

ExampleLayer::ExampleLayer() : Layer("Example"), m_TrianglePosition(0.0f), m_CameraController(1280.0f / 720.0f)
{
    m_VertexArray = Anwar::VertexArray::Create();

    float vertices[3 * 7] = {
        -0.5f, -0.5f, 0.0f, 0.8f, 0.2f, 0.8f, 1.0f,
        0.5f, -0.5f, 0.0f, 0.2f, 0.3f, 0.8f, 1.0f,
        0.0f, 0.5f, 0.0f, 0.8f, 0.8f, 0.2f, 1.0f
    };

    Anwar::Ref<Anwar::VertexBuffer> vertexBuffer = Anwar::VertexBuffer::Create(vertices, sizeof(vertices));


    Anwar::BufferLayout layout = {
        {Anwar::ShaderDataType::Float3, "a_Position"},
        {Anwar::ShaderDataType::Float4, "a_Color"},
    };

    vertexBuffer->SetLayout(layout);
    m_VertexArray->AddVertexBuffer(vertexBuffer);

    uint32_t indices[3] = { 0, 1, 2 };

    Anwar::Ref<Anwar::IndexBuffer> indexBuffer = Anwar::IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t));
    m_VertexArray->SetIndexBuffer(indexBuffer);

    m_SquareVA = Anwar::VertexArray::Create();

    float squareVertices[5 * 4] = {
        -0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
        0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
        0.5f, 0.5f, 0.0f, 1.0f, 1.0f,
        -0.5f, 0.5f, 0.0f, 0.0f, 1.0f
    };

    Anwar::Ref<Anwar::VertexBuffer> squareVB = Anwar::VertexBuffer::Create(squareVertices, sizeof(squareVertices));

    squareVB->SetLayout({
        {Anwar::ShaderDataType::Float3, "a_Position"},
        {Anwar::ShaderDataType::Float2, "a_TexCoord"},
                        });
    m_SquareVA->AddVertexBuffer(squareVB);

    uint32_t squareIndices[6] = { 0, 1, 2, 2, 3, 0 };

    Anwar::Ref<Anwar::IndexBuffer> squareIB = Anwar::IndexBuffer::Create(squareIndices, sizeof(squareIndices) / sizeof(uint32_t));
    m_SquareVA->SetIndexBuffer(squareIB);

    std::string vertexSrc = R"(
            #version 330 core

            layout(location = 0) in vec3 a_Position;
            layout(location = 1) in vec4 a_Color;

            uniform mat4 u_ViewProjection;
            uniform mat4 u_Transform;

            out vec3 v_Position;
            out vec4 v_Color;

            void main()
            {
                v_Position = a_Position;
                v_Color = a_Color;
                gl_Position = u_ViewProjection * u_Transform * vec4(a_Position, 1.0);
            }
        )";
    std::string fragmentSrc = R"(
            #version 330 core

            layout(location = 0) out vec4 color;

            in vec3 v_Position;
            in vec4 v_Color;

            void main()
            {
                color = vec4(v_Position * 0.5 + 0.5, 1.0);
                color = v_Color;
            }
        )";

    m_Shader = Anwar::Shader::Create("VertexPosColor", vertexSrc, fragmentSrc);

    auto textureShader = m_ShaderLibrary.Load("assets/shaders/TextureVertex.glsl", "assets/shaders/TextureFragment.glsl");

    m_Texture = Anwar::Texture2D::Create("assets/textures/Checkerboard.png");
    m_ChernoTexture = Anwar::Texture2D::Create("assets/textures/ChernoLogo.png");

    textureShader->Bind();
    textureShader->SetInt("u_Texture", 0);
}

ExampleLayer::~ExampleLayer()
{}

void ExampleLayer::OnAttach()
{}

void ExampleLayer::OnDetach()
{}

void ExampleLayer::OnUpdate(Anwar::Timestep ts)
{
    m_CameraController.OnUpdate(ts);

    if (Anwar::Input::IsKeyPressed(Anwar::Key::J))
    {
        m_TrianglePosition.x -= m_TriangleMoveSpeed * ts;
    }
    else if (Anwar::Input::IsKeyPressed(Anwar::Key::L))
    {
        m_TrianglePosition.x += m_TriangleMoveSpeed * ts;
    }

    if (Anwar::Input::IsKeyPressed(Anwar::Key::I))
    {
        m_TrianglePosition.y += m_TriangleMoveSpeed * ts;
    }
    else if (Anwar::Input::IsKeyPressed(Anwar::Key::K))
    {
        m_TrianglePosition.y -= m_TriangleMoveSpeed * ts;
    }

    Anwar::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
    Anwar::RenderCommand::Clear();

    Anwar::Renderer::BeginScene(m_CameraController.GetCamera());

    auto textureShader = m_ShaderLibrary.Get("TextureVertex-TextureFragment");

    m_Texture->Bind();
    Anwar::Renderer::Submit(textureShader, m_SquareVA, glm::scale(glm::mat4(1.0f), glm::vec3(1.5f)));
    m_ChernoTexture->Bind();
    Anwar::Renderer::Submit(textureShader, m_SquareVA, glm::scale(glm::mat4(1.0f), glm::vec3(1.5f)));

    // Anwar::Renderer::Submit(m_Shader, m_VertexArray);

    Anwar::Renderer::EndScene();
}

void ExampleLayer::OnImGuiRender()
{}

void ExampleLayer::OnEvent(Anwar::Event& e)
{
    m_CameraController.OnEvent(e);
}