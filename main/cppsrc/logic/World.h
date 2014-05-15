#ifndef WORLD_H
#define WORLD_H

#include "Map.h"
#include "MapPhysics.h"

class World
{
public:
    // throws std::invalid_argument if map and/or mapPhysics is nullptr
    explicit World(Map * const map, MapPhysics * const mapPhysics);
    ~World();

    Map & getMap();
    MapPhysics & getMapPhysics();

private:
    Map * const map;
    MapPhysics * const mapPhysics;
};

#endif // WORLD_H
