#pragma once

#include "Evadne/Utils/Buffer.h"

namespace Evadne {

    class FileSystem
    {
    public:
        static Buffer ReadFileBinary(const std::filesystem::path& filepath);
    };

}