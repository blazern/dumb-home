#ifndef MOVER_H
#define MOVER_H

#include <QPointF>
#include "DynamicMapObject.h"

class Mover
{
    friend class DynamicMapObject;
    friend class Player;
protected:
    virtual void move(const DynamicMapObject & mapObject, const qreal toX, const qreal toY) = 0;
};

#endif // MOVER_H
