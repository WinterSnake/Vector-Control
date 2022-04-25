/*
    TextEngine
    - UNIX Terminal Window
*/
#include <stdio.h>
#include <sys/ioctl.h>
#include <string>
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
#define BUFFER 10

namespace Engine
{
    /* Constructor / Deconstructor */
    Window::Window(Vector2 size): _size(size) {}
    /* Instance Methods */
    Vector2 Window::Get_Size()
    {
        return _size;
    }
    Vector2 Window::Get_Mouse_Position()
    {
        bool parse = true;
        int c, index = 0;
        char buffer[BUFFER] = {0};
        Vector2 position;
        printf(MOUSE_GET);
        while (parse)
        {
            c = getchar();
            switch(c)
            {
                case 0x1B:  // ESC
                case '[':   // [
                    continue;
                case ';':
                    position.y = std::stoul(buffer);
                    index = 0;
                    continue;
                case 'R':
                    position.x = std::stoul(buffer);
                    parse = false;
                    break;
                default:
                    buffer[index++] = (char)c;
            }
        }
        return position;
    }
    void Window::Set_Mouse_Position(Vector2 position)
    {
        printf("\x1B[%u;%uH", position.y, position.x);
    }
    /* Static Methods */
    Window Window::Init_Screen()
    {
        // Terminal Size
        struct winsize window;
        ioctl(0, TIOCGWINSZ, &window);
        // Terminal Attributes
        tcgetattr(STDOUT, &Window::term);
        Window::term.c_lflag &= ~ECHO & ~ICANON;
        tcsetattr(STDOUT, TCSANOW, &Window::term);
        // Terminal State
        printf(MOUSE_SAVE SCREEN_SAVE SCREEN_CLEAR MOUSE_RESET);
        return Window(Vector2{.width=window.ws_col, .height=window.ws_row});
    }
    void Window::End_Screen()
    {
        Window::term.c_lflag |= ECHO | ICANON;
        tcsetattr(STDOUT, TCSANOW, &Window::term);
        printf(SCREEN_LOAD MOUSE_LOAD);
    }
    /* Properties */
    struct termios Window::term;
}
