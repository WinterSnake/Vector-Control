/*
    TextEngine
    - UNIX Terminal Window
*/
#include <sys/ioctl.h>
#include <iostream>
#include <numeric>
#include <string>
#include <vector>
#include "engine/window.hpp"

#define STDIN  0
#define STDOUT 1
#define STDERR 2
#define SCREEN_SAVE  "\x1B[?47h"
#define SCREEN_LOAD  "\x1B[?47l"
#define SCREEN_CLEAR "\x1B[2J"
#define MOUSE_GET    "\x1B[6n"
#define MOUSE_SAVE   "\x1B 7\x1B[s"
#define MOUSE_LOAD   "\x1B 8\x1B[u"
#define MOUSE_RESET  "\x1B[H"
#define MOUSE_HIDE   "\x1B[?25l"
#define MOUSE_SHOW   "\x1B[?25h"

namespace Engine
{
    /* Constructor / Deconstructor */
    Window::Window(Vector2 size): _size(size) {}
    /* Instance Methods */
    void Window::Clear_Screen()
    {
        std::cout << SCREEN_CLEAR << MOUSE_RESET;
    }
    Attribute Window::Get_Attribute()
    {
        return _attribute;
    }
    Vector2 Window::Get_Cursor_Position()
    {
        int8_t c, index = 0;
        uint32_t counter = 0;
        Vector2 position;
        std::cout << MOUSE_GET;
        while (index >= 0)
        {
            c = getchar();
            switch(c)
            {
                case 0x1B:  // ESC
                case '[':   // [
                    continue;
                case ';':
                    position.y = counter;
                    index = counter = 0;
                    continue;
                case 'R':
                    position.x = counter;
                    index = -1;
                    break;
                default:
                    counter = counter * 10 + (c - '0');
            }
        }
        return position;
    }
    Vector2 Window::Get_Size()
    {
        return _size;
    }
    void Window::Hide_Cursor()
    {
        std::cout << MOUSE_HIDE;
    }
    void Window::Move_Cursor(IVector2 vector)
    {
        // Move cursor horizontally
        if (vector.x > 0)
        {
            std::cout << "\x1B[" << vector.x << 'C';
        }
        else if (vector.x < 0)
        {
            std::cout << "\x1B[" << vector.x * -1 << 'D';
        }
        // Move cursor vertically
        if (vector.y > 0)
        {
            std::cout << "\x1B[" << vector.y << 'B';
        }
        else if (vector.y < 0)
        {
            std::cout << "\x1B[" << vector.y * -1 << 'A';
        }
    }
    void Window::Reset_Cursor_Position()
    {
        std::cout << MOUSE_RESET;
    }
    void Window::Set_Attribute(Attribute attribute)
    {
        if (static_cast<int>(attribute.mode) == static_cast<int>(_attribute.mode))
        {
            return;
        }
        // Base Output
        std::vector<std::string> modifiers;
        // Mode: Bold
        if (static_cast<bool>(attribute.mode & Attribute::MODE::BOLD))
        {
            modifiers.push_back("1");
        }
        else if (!static_cast<bool>(attribute.mode & Attribute::MODE::BOLD) && static_cast<bool>(_attribute.mode & Attribute::MODE::BOLD))
        {
            modifiers.push_back("22");
        }
        // Mode: Dim
        if (static_cast<bool>(attribute.mode & Attribute::MODE::DIM))
        {
            modifiers.push_back("2");
        }
        else if (!static_cast<bool>(attribute.mode & Attribute::MODE::DIM) && static_cast<bool>(_attribute.mode & Attribute::MODE::DIM))
        {
            modifiers.push_back("22");
        }
        // Mode: Italic
        if (static_cast<bool>(attribute.mode & Attribute::MODE::ITALIC) && !static_cast<bool>(_attribute.mode & Attribute::MODE::ITALIC))
        {
            modifiers.push_back("3");
        }
        else if (!static_cast<bool>(attribute.mode & Attribute::MODE::ITALIC) && static_cast<bool>(_attribute.mode & Attribute::MODE::ITALIC))
        {
            modifiers.push_back("23");
        }
        // Mode: Underline
        if (static_cast<bool>(attribute.mode & Attribute::MODE::UNDERLINE) && !static_cast<bool>(_attribute.mode & Attribute::MODE::UNDERLINE))
        {
            modifiers.push_back("4");
        }
        else if (!static_cast<bool>(attribute.mode & Attribute::MODE::UNDERLINE) && static_cast<bool>(_attribute.mode & Attribute::MODE::UNDERLINE))
        {
            modifiers.push_back("24");
        }
        // Mode: Blink
        if (static_cast<bool>(attribute.mode & Attribute::MODE::BLINK) && !static_cast<bool>(_attribute.mode & Attribute::MODE::BLINK))
        {
            modifiers.push_back("5");
        }
        else if (!static_cast<bool>(attribute.mode & Attribute::MODE::BLINK) && static_cast<bool>(_attribute.mode & Attribute::MODE::BLINK))
        {
            modifiers.push_back("25");
        }
        // Mode: Reverse
        if (static_cast<bool>(attribute.mode & Attribute::MODE::REVERSE) && !static_cast<bool>(_attribute.mode & Attribute::MODE::REVERSE))
        {
            modifiers.push_back("7");
        }
        else if (!static_cast<bool>(attribute.mode & Attribute::MODE::REVERSE) && static_cast<bool>(_attribute.mode & Attribute::MODE::REVERSE))
        {
            modifiers.push_back("27");
        }
        // Mode: Hidden
        if (static_cast<bool>(attribute.mode & Attribute::MODE::HIDDEN) && !static_cast<bool>(_attribute.mode & Attribute::MODE::HIDDEN))
        {
            modifiers.push_back("8");
        }
        else if (!static_cast<bool>(attribute.mode & Attribute::MODE::HIDDEN) && static_cast<bool>(_attribute.mode & Attribute::MODE::HIDDEN))
        {
            modifiers.push_back("28");
        }
        // Mode: Strikethrough
        if (static_cast<bool>(attribute.mode & Attribute::MODE::STRIKETHROUGH) && !static_cast<bool>(_attribute.mode & Attribute::MODE::STRIKETHROUGH))
        {
            modifiers.push_back("9");
        }
        else if (!static_cast<bool>(attribute.mode & Attribute::MODE::STRIKETHROUGH) && static_cast<bool>(_attribute.mode & Attribute::MODE::STRIKETHROUGH))
        {
            modifiers.push_back("29");
        }
        // Color: Background
        if (static_cast<bool>(attribute.mode & Attribute::MODE::BG_COLOR) && attribute.bg_color != _attribute.bg_color)
        {
            modifiers.push_back("48;5;" + std::to_string(attribute.bg_color));
        }
        // Color: Foreground
        if (static_cast<bool>(attribute.mode & Attribute::MODE::FG_COLOR) && attribute.fg_color != _attribute.fg_color)
        {
            modifiers.push_back("38;5;" + std::to_string(attribute.fg_color));
        }
        // Write Output
        if (!modifiers.empty())
        {
            std::string output;
            for (std::string &str : modifiers)
            {
                output += str;
                if (&str != &modifiers.back())
                {
                    output += ';';
                }
            }
            std::cout << "\x1B[" << output << 'm';
        }
        attribute.mode &= ~(Attribute::MODE::BG_COLOR | Attribute::MODE::FG_COLOR);
        _attribute = attribute;
    }
    void Window::Set_Cursor_Position(Vector2 position)
    {
        std::cout << "\x1B[" << position.y << ';' << position.x << 'H';
    }
    void Window::Show_Cursor()
    {
        std::cout << MOUSE_SHOW;
    }
    /* Static Methods */
    Window Window::Init_Screen()
    {
        // Terminal Size
        struct winsize window;
        ioctl(0, TIOCGWINSZ, &window);
        // Terminal Attributes
        tcgetattr(STDOUT, &Window::_term);
        Window::_term.c_lflag &= ~(ECHO | ICANON);
        tcsetattr(STDOUT, TCSANOW, &Window::_term);
        // Terminal State
        std::cout << MOUSE_SAVE << SCREEN_SAVE << SCREEN_CLEAR << MOUSE_RESET;
        return Window(Vector2{.x=window.ws_col, .y=window.ws_row});
    }
    void Window::End_Screen()
    {
        Window::_term.c_lflag |= ECHO | ICANON;
        tcsetattr(STDOUT, TCSANOW, &Window::_term);
        std::cout << SCREEN_LOAD << MOUSE_LOAD << MOUSE_SHOW;
    }
    /* Properties */
    struct termios Window::_term;
}
