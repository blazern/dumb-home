#include "World.h"
#include <stdexcept>

World::World(Map * const map, MapPhysics * const mapPhysics) :
    map(map),
    mapPhysics(mapPhysics)
{
    if (map == nullptr)
    {
        freeResources();
        throw new std::invalid_argument("map must not be null");
    }
    else if (mapPhysics == nullptr)
    {
        freeResources();
        throw new std::invalid_argument("mapPhysics must not be null");
    }
}

void World::freeResources()
{
    delete map;
    delete mapPhysics;
}

World::~World()
{
    freeResources();
}

Map & World::getMap()
{
    return *map;
}

MapPhysics & World::getMapPhysics()
{
    return *mapPhysics;
}
