#ifndef DYNAMICMAPOBJECTGEOMETRY_H
#define DYNAMICMAPOBJECTGEOMETRY_H

#include <QRectF>
#include <functional>
#include "DynamicMapObject.h"

using std::function;

class DynamicMapObjectGeometry
{
    Q_DISABLE_COPY(DynamicMapObjectGeometry)
public:
    // object returned by initializer will be deleted by DynamicMapObjectGeometry on destruction
    template<typename Lambda>
    explicit DynamicMapObjectGeometry(const QRectF & rect, Lambda & initializer) :
        rect(rect),
        dynamicMapObject(initializer(this->rect))
    {
    }

    ~DynamicMapObjectGeometry()
    {
        delete dynamicMapObject;
    }

    const QRectF & getRect() const { return rect; }
    QRectF & getRect() { return rect; }

    const DynamicMapObject * getObject() const { return dynamicMapObject; }
    DynamicMapObject * getObject() { return dynamicMapObject; }

private:
    QRectF rect;
    DynamicMapObject * dynamicMapObject;
};

#endif // DYNAMICMAPOBJECTGEOMETRY_H
