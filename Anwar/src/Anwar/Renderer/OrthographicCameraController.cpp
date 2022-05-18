#include "anwpch.h"
#include "Anwar/Renderer/OrthographicCameraController.h"

#include "Anwar/Core/Input.h"
#include "Anwar/Core/KeyCodes.h"

namespace Anwar
{
    OrthographicCameraController::OrthographicCameraController(float aspectRatio, bool rotation)
        : m_AspectRatio(aspectRatio), m_Camera(-aspectRatio * m_ZoomLevel, aspectRatio * m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel), m_Rotation(rotation)
    {}

    void OrthographicCameraController::OnUpdate(Timestep ts)
    {
        ANW_PROFILE_FUNCTION();

        if (Input::IsKeyPressed(Key::A))
        {
            m_CameraPosition.x -= m_CameraTranslationSpeed * ts;
        }
        else if (Input::IsKeyPressed(Key::D))
        {
            m_CameraPosition.x += m_CameraTranslationSpeed * ts;
        }

        if (Input::IsKeyPressed(Key::W))
        {
            m_CameraPosition.y += m_CameraTranslationSpeed * ts;
        }
        else if (Input::IsKeyPressed(Key::S))
        {
            m_CameraPosition.y -= m_CameraTranslationSpeed * ts;
        }

        if (m_Rotation)
        {
            if (Input::IsKeyPressed(Key::Q))
            {
                m_CameraRotation += m_CameraRotationSpeed * ts;
            }
            else if (Input::IsKeyPressed(Key::E))
            {
                m_CameraRotation -= m_CameraRotationSpeed * ts;
            }

            m_Camera.SetRotation(m_CameraRotation);
        }

        m_Camera.SetPosition(m_CameraPosition);
    }

    void OrthographicCameraController::OnEvent(Event & e)
    {
        ANW_PROFILE_FUNCTION();

        EventDispatcher dispatcher(e);
        dispatcher.Dispatch<MouseScrolledEvent>(ANW_BIND_EVENT_FN(OrthographicCameraController::OnMouseScrolled));
        dispatcher.Dispatch<WindowResizeEvent>(ANW_BIND_EVENT_FN(OrthographicCameraController::OnWindowResized));
    }

    void OrthographicCameraController::OnResize(float width, float height)
    {
        m_AspectRatio = width / height;
        m_Camera.SetProjection(-m_AspectRatio * m_ZoomLevel, m_AspectRatio * m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel);
    }

    bool OrthographicCameraController::OnMouseScrolled(MouseScrolledEvent & e)
    {
        ANW_PROFILE_FUNCTION();

        m_ZoomLevel -= e.GetYOffset() * 0.25f;
        m_ZoomLevel = std::max(m_ZoomLevel, 0.25f);
        m_Camera.SetProjection(-m_AspectRatio * m_ZoomLevel, m_AspectRatio * m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel);
        return false;
    }

    bool OrthographicCameraController::OnWindowResized(WindowResizeEvent& e)
    {
        ANW_PROFILE_FUNCTION();

        OnResize((float) e.GetWidth(), (float) e.GetHeight());
        return false;
    }
}
