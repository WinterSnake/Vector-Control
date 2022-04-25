/*
    TextEngine
    - UNIX Terminal Window
*/
#include <stdio.h>
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
    struct termios Window::term;

    Window Window::Init_Screen()
    {
        tcgetattr(STDOUT, &Window::term);
        Window::term.c_lflag &= ~ECHO & ~ICANON;
        tcsetattr(STDOUT, TCSANOW, &term);
        printf(MOUSE_SAVE SCREEN_SAVE SCREEN_CLEAR MOUSE_RESET);
    }

    void Window::End_Screen()
    {
        Window::term.c_lflag |= ECHO | ICANON;
        tcsetattr(STDOUT, TCSANOW, &term);
        printf(SCREEN_LOAD MOUSE_LOAD);
    }
}
