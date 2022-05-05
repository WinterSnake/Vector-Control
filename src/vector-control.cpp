/*
    Vector Control
*/
#include <iostream>
#include <unistd.h>
#include "engine/window.hpp"
#include "map.hpp"
#include "bot.hpp"

int main(int argc, char** argv)
{
    Engine::Window window = Engine::Window::Init_Screen();
    window.Hide_Cursor();
    Engine::Vector2 size = window.Get_Size();
    Map map = Map::Generate(size);
    getchar();
    Engine::Window::End_Screen();
    return 0;
}
