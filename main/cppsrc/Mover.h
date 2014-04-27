#ifndef MOVER_H
#define MOVER_H

#include <QPointF>
#include "MapObject.h"

class Mover
{
    friend class MapObject;
    friend class Player;
protected:
    virtual void move(const MapObject & mapObject, const QPointF & destination) = 0;
};

#endif // MOVER_H
