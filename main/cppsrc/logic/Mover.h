#ifndef MOVER_H
#define MOVER_H

#include <QPointF>
#include "DynamicMapObject.h"

class Mover
{
public:
    virtual ~Mover(){}
    virtual void move(const DynamicMapObject & mapObject, const qreal angle) = 0;
    virtual void stop(const DynamicMapObject & mapObject) = 0;
};

#endif // MOVER_H
