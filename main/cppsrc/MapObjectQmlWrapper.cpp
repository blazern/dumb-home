#include "MapObjectQmlWrapper.h"

long MapObjectQmlWrapper::nextId(0);

MapObjectQmlWrapper::MapObjectQmlWrapper(QObject * parent) :
    QObject(parent),
    id(nextId++),
    color("black"),
    dynamicMapObject(nullptr),
    staticMapObject(nullptr),
    width(1),
    height(1)
{
}

MapObjectQmlWrapper::MapObjectQmlWrapper(const DynamicMapObject & dynamicMapObject, QObject * parent) :
    QObject(parent),
    id(nextId++),
    color("green"),
    dynamicMapObject(&dynamicMapObject),
    staticMapObject(nullptr),
    width(dynamicMapObject.getRect().width()),
    height(dynamicMapObject.getRect().height())
{
}

MapObjectQmlWrapper::MapObjectQmlWrapper(
        const StaticMapObject & staticMapObject,
        const qreal width,
        const qreal height,
        QObject * parent) :
    QObject(parent),
    id(nextId++),
    color("red"),
    dynamicMapObject(nullptr),
    staticMapObject(&staticMapObject),
    width(width),
    height(height)
{
}

long MapObjectQmlWrapper::getId() const
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
        return staticMapObject->getPosition().x() * width;
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
        return staticMapObject->getPosition().y() * height;
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
