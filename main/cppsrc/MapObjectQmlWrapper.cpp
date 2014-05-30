#include "MapObjectQmlWrapper.h"

unsigned int MapObjectQmlWrapper::nextId(1);

MapObjectQmlWrapper::MapObjectQmlWrapper(QObject * parent) :
    QObject(parent),
    id(nextId++),
    color("black"),
    dynamicMapObject(nullptr),
    staticMapObject(nullptr),
    width(1),
    height(1),
    staticObjectX(0),
    staticObjectY(0)
{
}

MapObjectQmlWrapper::MapObjectQmlWrapper(const DynamicMapObject & dynamicMapObject, QObject * parent) :
    QObject(parent),
    id(nextId++),
    color("green"),
    dynamicMapObject(&dynamicMapObject),
    staticMapObject(nullptr),
    width(dynamicMapObject.getRect().width()),
    height(dynamicMapObject.getRect().height()),
    staticObjectX(-1),
    staticObjectY(-1)
{
}

MapObjectQmlWrapper::MapObjectQmlWrapper(const StaticMapObject & staticMapObject,
                                         const QRectF & rect,
                                         const QColor & color,
                                         QObject * parent) :
    QObject(parent),
    id(nextId++),
    color(color),
    dynamicMapObject(nullptr),
    staticMapObject(&staticMapObject),
    width(rect.width()),
    height(rect.height()),
    staticObjectX(rect.x()),
    staticObjectY(rect.y())
{
}

unsigned int MapObjectQmlWrapper::getId() const
{
    return id;
}

const QColor & MapObjectQmlWrapper::getColor() const
{
    return color;
}

qreal MapObjectQmlWrapper::getX() const
{
    if (dynamicMapObject != nullptr)
    {
        return dynamicMapObject->getRect().x();
    }
    else if (staticMapObject != nullptr)
    {
        return staticObjectX;
    }
    else
    {
        return 0;
    }
}

qreal MapObjectQmlWrapper::getY() const
{
    if (dynamicMapObject != nullptr)
    {
        return dynamicMapObject->getRect().y();
    }
    else if (staticMapObject != nullptr)
    {
        return staticObjectY;
    }
    else
    {
        return 0;
    }
}

qreal MapObjectQmlWrapper::getWidth() const
{
    return width;
}

qreal MapObjectQmlWrapper::getHeight() const
{
    return height;
}

bool MapObjectQmlWrapper::isMadeFor(const DynamicMapObject & mapObject) const
{
    return &mapObject == dynamicMapObject;
}
