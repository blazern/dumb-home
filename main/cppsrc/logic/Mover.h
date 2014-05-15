#ifndef MOVER_H
#define MOVER_H

#include <QPointF>
#include "DynamicMapObject.h"

class Mover
{
public:
    virtual ~Mover(){}
    virtual void move(const DynamicMapObject & mapObject, const qreal toX, const qreal toY) = 0;
};

#endif // MOVER_H
