#include <Evadne.h>
#include <Evadne/Core/EntryPoint.h>

#include "Layers/EditorLayer.h"

namespace Evadne {

    class EvadneEditor : public Application
    {
    public:
        EvadneEditor(const Evadne::ApplicationSpecification& specification)
            :Application(specification)
        {
            PushLayer(new EditorLayer());
        }

        ~EvadneEditor()
        {

        }
    };

    Application* CreateApplication(ApplicationCommandLineArgs args)
    {
        ApplicationSpecification spec;
        spec.Name = "Evadne Editor";
        spec.CommandLineArgs = args;

        return new EvadneEditor(spec);
    }
}