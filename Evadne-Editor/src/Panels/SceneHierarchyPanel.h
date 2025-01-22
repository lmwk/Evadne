#pragma once

#include "Evadne/Core/Core.h"
#include "Evadne/Scene/Scene.h"
#include "Evadne/ECS/Entity.h"


namespace Evadne {

    class SceneHierarchyPanel
    {
    public:
        SceneHierarchyPanel() = default;
        SceneHierarchyPanel(const Ref<Scene>& scene);

        void SetContext(const Ref<Scene>& scene);

        void OnImGuiRender();
    private:
        void DrawEntityNode(Entity entity);
        void DrawComponents(Entity entity);
    private:
        Ref<Scene> m_Context;
        Entity m_SelectionContext;
    };

}



