#pragma once

#include "Evadne.h"
#include "../Panels/SceneHierarchyPanel.h"

#include "Evadne/Camera/EditorCamera.h"
#include "../Panels/ContentBrowserPanel.h"

namespace Evadne {

    class EditorLayer : public Layer
    {
    public:
        EditorLayer();
        virtual ~EditorLayer() = default;

        virtual void OnAttach() override;
        virtual void OnDetach() override;

        void OnUpdate(Timestep ts) override;
        virtual void OnImGuiRender() override;
        void OnEvent(Event& e) override;
    private:
        bool OnKeyPressed(KeyPressedEvent& e);
        bool OnMouseButtonPressed(MouseButtonPressedEvent& e);

        void NewScene();
        void OpenScene();
        void OpenScene(const std::filesystem::path& path);
        void SaveSceneAs();

        void UI_Toolbar();

        void OnScenePlay();
        void OnSceneStop();
    private:
        OrthographicCameraController m_CameraController;

        Ref<VertexArray> m_SquareVA;
        Ref<Shader> m_FlatColorShader;
        Ref<Framebuffer> m_Framebuffer;

        Ref<Scene> m_ActiveScene;
        Entity m_SquareEntity;
        Entity m_CameraEntity;
        Entity m_SecondCamera;

        Entity m_HoveredEntity;

        bool m_PrimaryCamera = true;

        EditorCamera m_EditorCamera;

        Ref<Texture2D> m_BackgroundTexture;

        bool m_ViewportFocused = false, m_ViewportHovered = false;
        glm::vec2 m_ViewportSize = { 0.0f, 0.0f };
        glm::vec2 m_ViewportBounds[2];

        glm::vec4 m_SquareColor = { 0.2f, 0.3f, 0.8f, 1.0f };

        int m_GizmoType = -1;

        enum class SceneState 
        {
            Edit = 0, Play = 1
        };
        SceneState m_SceneState = SceneState::Edit;

        SceneHierarchyPanel m_SceneHierarchyPanel;
        ContentBrowserPanel m_ContentBrowserPanel;

        Ref<Texture2D> m_IconPlay, m_IconStop;
    };
}



