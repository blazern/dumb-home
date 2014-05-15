#include "MapPhysics.h"
#include "DynamicMapObjectGeometry.h"
#include "Wall.h"

#ifdef QT_DEBUG
#include <QDebug>
#endif

MapPhysics::MapPhysics(Map & map) :
    map(map),
    listeners()
{
    map.getDynamicLayer().getPlayer().setMover(*this);
}

void MapPhysics::move(const DynamicMapObject & mapObject, const qreal toX, const qreal toY)
{
    DynamicMapLayer & dynamicLayer = map.getDynamicLayer();
    DynamicMapObjectGeometry * requester = nullptr;
    for (auto iterator = dynamicLayer.begin(); iterator != dynamicLayer.end(); iterator++)
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
            const QPointF oldPosition = rect.topLeft();

            const qreal oldWidth = rect.width();
            const qreal oldHeight = rect.height();
            rect.setX(toX);
            rect.setWidth(oldWidth);
            rect.setY(toY);
            rect.setHeight(oldHeight);
            for (auto & listener : listeners)
            {
                listener->onObjectChangedPosition(*(requester->getObject()), oldPosition, rect.topLeft());
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

bool MapPhysics::isNewPositionValid(const QRectF & rect, const qreal x, const qreal y) const
{
    if (isNewPositionWithinMap(rect, x, y))
    {
        StaticMapLayer & staticLayer = map.getStaticLayer();

        // static objects represent a grid, therefore it is easy to check
        // if there is any static object underneath the rect
        const int left = floor(x / map.getStaticMapObjectWidth());
        const int right = floor((x - 1 + rect.width()) / map.getStaticMapObjectWidth());
        const int top = floor(y / map.getStaticMapObjectHeight());
        const int bottom = floor((y - 1 + rect.height()) / map.getStaticMapObjectHeight());

        for (int hor = left; hor <= right; hor++)
        {
            for (int ver = top; ver <= bottom; ver++)
            {
                if (dynamic_cast<Wall*>(&staticLayer.get(hor, ver)) != nullptr)
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

bool MapPhysics::isNewPositionWithinMap(const QRectF & rect, const qreal x, const qreal y) const
{
    StaticMapLayer & staticLayer = map.getStaticLayer();

    return 0 <= x
            && 0 <= y
            && x + rect.width() <= staticLayer.getWidth() * map.getStaticMapObjectWidth()
            && y + rect.height() <= staticLayer.getHeight() * map.getStaticMapObjectHeight();
}

void MapPhysics::addListener(MapPhysicsListener & listener)
{
    listeners.append(&listener);
}

void MapPhysics::removeListener(MapPhysicsListener & listener)
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

