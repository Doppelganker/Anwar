#pragma once

#include <Anwar.h>

class Sandbox2D : public Anwar::Layer
{
public:
    Sandbox2D();
    virtual ~Sandbox2D() = default;

    virtual void OnAttach() override;
    virtual void OnDetach() override;

    void OnUpdate(Anwar::Timestep ts) override;
    virtual void OnImGuiRender() override;
    void OnEvent(Anwar::Event& e) override;
private:
    Anwar::OrthographicCameraController m_CameraController;

    Anwar::Ref<Anwar::VertexArray> m_SquareVA;
    Anwar::Ref<Anwar::Shader> m_FlatColorShader;

    Anwar::Ref<Anwar::Texture2D> m_CheckerboardTexture;

    glm::vec4 m_SquareColor = { 0.2f, 0.3f, 0.8f, 1.0f };
};