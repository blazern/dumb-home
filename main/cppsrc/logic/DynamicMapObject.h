#ifndef DYNAMICMAPOBJECT_H
#define DYNAMICMAPOBJECT_H

#include <QRectF>
#include <QPointF>

class DynamicMapObject
{
public:
    virtual const QRectF & getRect() const = 0;
    virtual ~DynamicMapObject(){}
};

#endif // DYNAMICMAPOBJECT_H
