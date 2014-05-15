#ifndef MAPPHYSICSLISTENER_H
#define MAPPHYSICSLISTENER_H

#include "DynamicMapObject.h"
#include <QPointF>

class MapPhysicsListener
{
public:
    virtual ~MapPhysicsListener(){}
    virtual void onObjectChangedPosition(
            const DynamicMapObject & object,
            const QPointF & oldPosition,
            const QPointF & newPosition) = 0;
};

#endif // MAPPHYSICSLISTENER_H
