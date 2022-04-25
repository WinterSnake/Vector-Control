#pragma once
#include <cstdint>

namespace Engine
{
    struct Vector2
    {
        // Properties
        public:
            union
            {
                uint32_t x, width;
            };
            union
            {
                uint32_t y, height;
            };
    };
}
