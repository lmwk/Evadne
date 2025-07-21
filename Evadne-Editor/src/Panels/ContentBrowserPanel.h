#pragma once

#include <filesystem>

#include "Evadne/Rendering/Texture.h"

namespace Evadne {

    class ContentBrowserPanel
    {
    public:
        ContentBrowserPanel();

        void OnImGuiRender();
    private:
        std::filesystem::path m_BaseDirectory;
        std::filesystem::path m_CurrentDirectory;

        Ref<Texture2D> m_FolderIcon;
        Ref<Texture2D> m_FileIcon;
    };

}