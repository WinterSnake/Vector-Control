/*
    TextEngine
    - UNIX Terminal Window
*/
#include <stdio.h>
#include <sys/ioctl.h>
#include "engine/window.hpp"

#define STDIN  0
#define STDOUT 1
#define STDERR 2
#define SCREEN_SAVE  "\x1B[?47h"
#define SCREEN_LOAD  "\x1B[?47l"
#define SCREEN_CLEAR "\x1B[2J"
#define MOUSE_SAVE   "\x1B 7\x1B[s"
#define MOUSE_LOAD   "\x1B 8\x1B[u"
#define MOUSE_RESET  "\x1B[H"

namespace Engine
{
    /* Constructor / Deconstructor */
    Window::Window(Vector2 size): _size(size) {}
    /* Instance Methods */
    Vector2 Window::Get_Size()
    {
        return _size;
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
        tcsetattr(STDOUT, TCSANOW, &term);
        // Terminal State
        printf(MOUSE_SAVE SCREEN_SAVE SCREEN_CLEAR MOUSE_RESET);
        return Window(Vector2{.width=window.ws_col, .height=window.ws_row});
    }
    void Window::End_Screen()
    {
        Window::term.c_lflag |= ECHO | ICANON;
        tcsetattr(STDOUT, TCSANOW, &term);
        printf(SCREEN_LOAD MOUSE_LOAD);
    }
    /* Properties */
    struct termios Window::term;
}
