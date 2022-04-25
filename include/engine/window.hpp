/*
    TextEngine
    - UNIX Terminal Window
*/
#pragma once
#include <termios.h>
#include "engine/vector.hpp"

namespace Engine
{
    struct Color
    {
        uint8_t red, green, blue;
    };

    class Window
    {
        /* Constructor / Deconstructor */
        private:
            Window(Vector2);
        /* Instance Methods */
        public:
            Vector2 Get_Size();
        /* Static Methods */
        public:
            static Window Init_Screen();
            static void End_Screen();
        /* Properties */
        private:
            Vector2 _size;
            static struct termios term;
    };
}
