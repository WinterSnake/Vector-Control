/*
    Vector Control
    - Map System
*/
#include "map.hpp"

/* Constructor / Deconstructor */
Map::Map(Engine::Vector2 size): _size(size)
{
    tile = new TILE*[size.x];
    for (uint32_t x = 0; x < size.x; ++x)
    {
       tile[x] = new TILE[size.y];
    }
}
Map::~Map()
{
    for (uint32_t x = 0; x < _size.x; ++x)
    {
        delete[] tile[x];
    }
    delete[] tile;
}
/* Instance Methods */
Engine::Vector2 Map::Get_Size()
{
    return _size;
}
/* Static Methods */
Map Map::Generate(Engine::Vector2 size)
{
    Map m(size);
    for (uint32_t y = 0; y < size.y; ++y)
    {
        for (uint32_t x = 0; x < size.x; ++x)
        {
            m.tile[x][y] = TILE::GRASS;
        }
    }
    return m;
}
