/*
    Vector Control
    - Map System
*/
#pragma once
#include "engine/vector.hpp"

enum class TILE
{
    EMPTY = 0,
    GRASS,
    WATER,
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
        TILE**          tile;
    private:
        Engine::Vector2 _size;
};
