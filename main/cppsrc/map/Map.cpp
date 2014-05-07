#include "Map.h"
#include "StaticMapObjectImpl.h"
#include <math.h>

#ifdef QT_DEBUG
#include <QDebug>
#endif

Map::Map(StaticMapLayer * staticLayer, DynamicMapLayer * dynamicLayer, const qreal staticObjectWidth, const qreal staticObjectHeight) :
    staticLayer(staticLayer),
    staticMapObjectWidth(staticObjectWidth),
    staticMapObjectHeight(staticObjectHeight),
    dynamicLayer(dynamicLayer),
    listeners()
{
    dynamicLayer->getPlayer().setMover(*this);
}

Map::Map(const int width, const int height, const qreal staticMapObjectWidth, const qreal staticMapObjectHeight) :
    staticLayer(new StaticMapLayer(width, height)),
    staticMapObjectWidth(staticMapObjectWidth),
    staticMapObjectHeight(staticMapObjectHeight),
    dynamicLayer(new DynamicMapLayer(QRectF(20, 20, 10, 10), this)),
    listeners()
{
}

Map::~Map()
{
    delete staticLayer;
    delete dynamicLayer;
}

const StaticMapLayer & Map::getStaticLayer() const
{
    return *staticLayer;
}

qreal Map::getStaticMapObjectWidth() const
{
    return staticMapObjectWidth;
}

qreal Map::getStaticMapObjectHeight() const
{
    return staticMapObjectHeight;
}

const QRectF Map::getRectOfStaticObjectWith(const int horPos, const int verPos) const
{
    return QRectF(horPos * staticMapObjectWidth,
                  verPos * staticMapObjectHeight,
                  staticMapObjectWidth,
                  staticMapObjectHeight);
}

const DynamicMapLayer & Map::getDynamicLayer() const
{
    return *dynamicLayer;
}

DynamicMapLayer & Map::getDynamicLayer()
{
    return *dynamicLayer;
}

void Map::addListener(MapListener & listener)
{
    listeners.append(&listener);
}

void Map::removeListener(MapListener & listener)
{
    for (auto iterator = listeners.begin(); iterator != listeners.end(); )
    {
        if (*iterator == &listener)
        {
            iterator = listeners.erase(iterator);
            continue;
        }
        iterator++;
    }
}

void Map::move(const DynamicMapObject & mapObject, const qreal toX, const qreal toY)
{
    DynamicMapObjectGeometry * requester = nullptr;
    for (auto iterator = dynamicLayer->begin(); iterator != dynamicLayer->end(); iterator++)
    {
        QSharedPointer<DynamicMapObjectGeometry> & object = *iterator;

        if (object->getObject() == &mapObject)
        {
            requester = object.data();
        }
    }


    if (requester != nullptr)
    {
        QRectF & rect = requester->getRect();
        if (isNewPositionValid(rect, toX, toY))
        {
            const qreal oldWidth = rect.width();
            const qreal oldHeight = rect.height();
            rect.setX(toX);
            rect.setWidth(oldWidth);
            rect.setY(toY);
            rect.setHeight(oldHeight);
            for (auto & listener : listeners)
            {
                listener->onObjectChangedPosition(*(requester->getObject()), rect.topLeft());
            }
        }
    }
#ifdef QT_DEBUG
    else
    {
        qDebug() << "requester of move() was not found for some reason";
    }
#endif
}

bool Map::isNewPositionValid(const QRectF & rect, const qreal x, const qreal y) const
{
    if (isRectangleWithNewPositionValid(rect, x, y))
    {
        // static objects represent a grid, therefore it is easy to check
        // if there is any static object underneath the rect
        const int left = floor(x / staticMapObjectWidth);
        const int right = floor((x - 1 + rect.width()) / staticMapObjectWidth);
        const int top = floor(y / staticMapObjectHeight);
        const int bottom = floor((y - 1 + rect.height()) / staticMapObjectHeight);

        for (int hor = left; hor <= right; hor++)
        {
            for (int ver = top; ver <= bottom; ver++)
            {
                if (staticLayer->get(hor, ver) != nullptr)
                {
                    return false;
                }
            }
        }
        return true;
    }
    else
    {
        return false;
    }
}

bool Map::isRectangleWithNewPositionValid(const QRectF & rect, const qreal x, const qreal y) const
{
    return 0 <= x
            && 0 <= y
            && x + rect.width() <= staticLayer->getWidth() * staticMapObjectWidth
            && y + rect.height() <= staticLayer->getHeight() * staticMapObjectHeight;
}
