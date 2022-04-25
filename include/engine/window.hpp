/*
    TextEngine
    - UNIX Terminal Window
*/
#pragma once
#include <termios.h>
#include "engine/vector.hpp"

namespace Engine
{
    class Window
    {
        /* Constructor / Deconstructor */
        private:
            Window(Vector2);
        /* Instance Methods */
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
