#ifndef MAPOBJECT_H
#define MAPOBJECT_H

#include <QPointF>

class MapObject
{
public:
    virtual const QPointF & getPosition() const = 0;
};

#endif // MAPOBJECT_H
