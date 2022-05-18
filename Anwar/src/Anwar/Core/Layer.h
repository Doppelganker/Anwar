#pragma once

#include "Anwar/Core/Base.h"
#include "Anwar/Core/Timestep.h"
#include "Anwar/Events/Event.h"

namespace Anwar
{
    class Layer
    {
    public:
        Layer(const std::string& name = "Layer");
        virtual ~Layer() = default;

        virtual void OnAttach()
        {}
        virtual void OnDetach()
        {}
        virtual void OnUpdate(Timestep ts)
        {}
        virtual void OnImGuiRender()
        {}
        virtual void OnEvent(Event& event)
        {}

        inline const std::string& GetName() const
        {
            return m_DebugName;
        }
    protected:
        std::string m_DebugName;
    };
}