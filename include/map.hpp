/*
    Vector Control
    - Map System
*/
#pragma once
#include <vector>
#include "engine/window.hpp"
#include "engine/vector.hpp"

enum class TILE
{
    EMPTY = 0,
    GRASS,
    WATER,
};
class Object
{
    /* Instance Methods */
    public:
        virtual void update();
        virtual void draw(Engine::Window);
    /* Properties */
    private:
        Engine::Vector2 _position;
};
class Map
{
    /* Constructor / Deconstructor */
    public:
        Map(Engine::Vector2);
        ~Map();
    /* Instance Methods */
    public:
        Engine::Vector2 Get_Size();
        TILE            Get_Tile(Engine::Vector2);
    /* Static Methods */
    public:
        static Map Generate(Engine::Vector2);
    /* Properties */
    public:
        TILE**              tile;
    private:
        Engine::Vector2     _size;
        std::vector<Object> _objects;
};
