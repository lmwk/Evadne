#pragma once

#include <filesystem>
#include "Evadne/Rendering/Texture.h"

namespace Evadne {

    struct MSDFData;

    class Font
    {
    public:
        Font(const std::filesystem::path& filepath);
        ~Font();

        Ref<Texture2D> GetAtlasTexture() const { return m_AtlasTexture; }
    private:
        MSDFData* m_Data;
        Ref<Texture2D> m_AtlasTexture;
    };

}