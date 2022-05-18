#pragma once

#include "Anwar.h"

class ExampleLayer : public Anwar::Layer
{
public:
    ExampleLayer();
    virtual ~ExampleLayer();

    virtual void OnAttach() override;
    virtual void OnDetach() override;

    void OnUpdate(Anwar::Timestep ts) override;
    void OnImGuiRender() override;
    void OnEvent(Anwar::Event& e) override;
private:
    Anwar::ShaderLibrary m_ShaderLibrary;
    Anwar::Ref<Anwar::Shader> m_Shader;
    Anwar::Ref<Anwar::VertexArray> m_VertexArray;

    Anwar::Ref<Anwar::VertexArray> m_SquareVA;

    Anwar::Ref<Anwar::Texture2D> m_Texture, m_ChernoTexture;

    Anwar::OrthographicCameraController m_CameraController;

    glm::vec3 m_TrianglePosition;
    float m_TriangleMoveSpeed = 0.1f;
};