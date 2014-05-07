#ifndef MAPLISTENER_H
#define MAPLISTENER_H

#include "DynamicMapObject.h"
#include <QPointF>

class MapListener
{
public:
    virtual ~MapListener(){}
    // just "object" because StaticObjects can't change their position yet
    virtual void onObjectChangedPosition(const DynamicMapObject & object, const QPointF & position) = 0;
};

#endif // MAPLISTENER_H
