#ifndef WALL_H
#define WALL_H

#include "StaticMapObject.h"

class Wall : public StaticMapObject
{
public:
    explicit Wall();
    Wall(const Wall & other) = default;
    Wall & operator=(const Wall & other) = default;
};

#endif // WALL_H
