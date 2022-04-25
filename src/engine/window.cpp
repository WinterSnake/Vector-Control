/*
    TextEngine
    - UNIX Terminal Window
*/
#define STDIN  0
#define STDOUT 1
#define STDERR 2
#include <stdio.h>
#include "engine/window.hpp"

namespace Engine
{
    struct termios Window::term;

    Window Window::Init_Screen()
    {
        tcgetattr(STDOUT, &Window::term);
        Window::term.c_lflag &= ~ECHO & ~ICANON;
        tcsetattr(STDOUT, TCSANOW, &term);
    }

    void Window::End_Screen()
    {
        Window::term.c_lflag |= ECHO | ICANON;
        tcsetattr(STDOUT, TCSANOW, &term);
    }
}
