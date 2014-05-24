#ifndef MOVEMENT_H
#define MOVEMENT_H

#include "DynamicMapLayer.h"

class Movement
{
    friend class MapPhysics;
    friend class std::vector<Movement>;

protected:
    explicit Movement(const DynamicMapObject & mapObject, const qreal angle) :
        mapObject(mapObject), angle(angle) {}

    const DynamicMapObject & getMapObject() const { return mapObject; }
    qreal getAngle() const { return angle; }

private:
    const DynamicMapObject & mapObject;
    const qreal angle;
};

#endif // MOVEMENT_H
