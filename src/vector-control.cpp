/*
    Vector Control
*/
#define STDIN 0
#define STDOUT 1
#define STDERR 2
#include <stdio.h>

#include "engine/window.hpp"

int main(int argc, char** argv)
{
    Engine::Window wind = Engine::Window::Init_Screen();
    getchar();
    Engine::Window::End_Screen();
    return 0;
}
