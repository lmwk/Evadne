#include <Evadne.h>
#include <Evadne/Core/EntryPoint.h>

#include "Layers/EditorLayer.h"

namespace Evadne {

    class EvadneEditor : public Application
    {
    public:
        EvadneEditor()
            :Application("Evadne Editor")
        {
            PushLayer(new EditorLayer());
        }

        ~EvadneEditor()
        {

        }
    };

    Application* CreateApplication()
    {
        return new EvadneEditor();
    }
}