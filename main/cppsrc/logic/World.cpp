#include "World.h"
#include <stdexcept>

World::World(Map * const map, MapPhysics * const mapPhysics) :
    map(map),
    mapPhysics(mapPhysics)
{
    if (map == nullptr)
    {
        throw new std::invalid_argument("map must not be null");
    }
    else if (mapPhysics == nullptr)
    {
        throw new std::invalid_argument("mapPhysics must not be null");
    }
}

World::~World()
{
    delete map;
    delete mapPhysics;
}

Map & World::getMap()
{
    return *map;
}

MapPhysics & World::getMapPhysics()
{
    return *mapPhysics;
}
