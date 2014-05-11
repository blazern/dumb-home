#ifndef AIR_H
#define AIR_H

#include "StaticMapObject.h"

class Air : public StaticMapObject
{
public:
    explicit Air();
    Air(const Air & other) = default;
    Air & operator=(const Air & other) = default;
};

#endif // AIR_H
