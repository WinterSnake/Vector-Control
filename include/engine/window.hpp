/*
    TextEngine
    - UNIX Terminal Window
*/
#pragma once
#include <termios.h>
#include "engine/vector.hpp"

namespace Engine
{
    struct Attribute
    {
        uint8_t fg_color;
        uint8_t bg_color;
        enum class MODE
        {
            RESET         = 0,
            BOLD          = 1 << 0,
            DIM           = 1 << 1,
            ITALIC        = 1 << 2,
            UNDERLINE     = 1 << 3,
            BLINK         = 1 << 4,
            REVERSE       = 1 << 5,
            HIDDEN        = 1 << 6,
            STRIKETHROUGH = 1 << 7,
            FG_COLOR      = 1 << 8,
            BG_COLOR      = 1 << 9,
        } mode;
    };
    class Window
    {
        /* Constructor / Deconstructor */
        private:
            Window(Vector2);
        /* Instance Methods */
        public:
            void    Clear_Screen();
            Vector2 Get_Size();
            Vector2 Get_Mouse_Position();
            void    Reset_Mouse_Position();
            void    Set_Mouse_Position(Vector2);
        /* Static Methods */
        public:
            static Window Init_Screen();
            static void   End_Screen();
        /* Properties */
        private:
            Vector2               _size;
            static struct termios _term;
    };
}
