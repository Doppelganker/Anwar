#pragma once

#include "Anwar/Core/Layer.h"

#include "Anwar/Events/MouseEvent.h"
#include "Anwar/Events/KeyEvent.h"
#include "Anwar/Events/ApplicationEvent.h"

namespace Anwar
{
    class ImGuiLayer : public Layer
    {
    public:
        ImGuiLayer();
        ~ImGuiLayer() = default;

        void OnAttach() override;
        void OnDetach() override;
        void OnEvent(Event& e) override;

        void Begin();
        void End();

        void BlockEvents(bool block)
        {
            m_BlockEvents = block;
        }
        
        void SetDarkThemeColors();
    private:
        bool m_BlockEvents = true;
    };
}