#include <Evadne.h>
#include <Evadne/Core/EntryPoint.h>

#include "Layers/EditorLayer.h"

namespace Evadne {

    class EvadneEditor : public Application
    {
    public:
        EvadneEditor(ApplicationCommandLineArgs args)
            :Application("Evadne Editor", args)
        {
            PushLayer(new EditorLayer());
        }

        ~EvadneEditor()
        {

        }
    };

    Application* CreateApplication(ApplicationCommandLineArgs args)
    {
        return new EvadneEditor(args);
    }
}