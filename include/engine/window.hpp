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
        uint8_t bg_color = 0;
        uint8_t fg_color = 0;
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
    inline constexpr Attribute::MODE operator~(Attribute::MODE Mode)
    {
        return static_cast<Attribute::MODE>(~static_cast<int>(Mode));
    }
    inline constexpr Attribute::MODE operator|(Attribute::MODE ModeA, Attribute::MODE ModeB)
    {
        return static_cast<Attribute::MODE>(static_cast<int>(ModeA) | static_cast<int>(ModeB));
    }
    inline constexpr Attribute::MODE operator&(Attribute::MODE ModeA, Attribute::MODE ModeB)
    {
        return static_cast<Attribute::MODE>(static_cast<int>(ModeA) & static_cast<int>(ModeB));
    }
    inline constexpr void operator|=(Attribute::MODE& ModeA, Attribute::MODE ModeB)
    {
        ModeA = ModeA | ModeB;
    }
    inline constexpr void operator&=(Attribute::MODE& ModeA, Attribute::MODE ModeB)
    {
        ModeA = ModeA & ModeB;
    }
    class Window
    {
        /* Constructor / Deconstructor */
        private:
            Window(Vector2);
        /* Instance Methods */
        public:
            void      Clear_Screen();
            Attribute Get_Attribute();
            Vector2   Get_Cursor_Position();
            Vector2   Get_Size();
            void      Hide_Cursor();
            void      Move_Cursor(IVector2);
            void      Reset_Cursor_Position();
            void      Set_Attribute(Attribute);
            void      Set_Cursor_Position(Vector2);
            void      Show_Cursor();
        /* Static Methods */
        public:
            static Window Init_Screen();
            static void   End_Screen();
        /* Properties */
        private:
            Attribute             _attribute = Attribute{.mode = Attribute::MODE::RESET};
            Vector2               _size;
            static struct termios _term;
    };
}
