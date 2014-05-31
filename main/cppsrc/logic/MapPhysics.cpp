#include "MapPhysics.h"
#include "DynamicMapObjectGeometry.h"
#include "MapToolKit.h"
#include "StaticMapObject.h"
#include <QLineF>

#ifdef QT_DEBUG
#include <QDebug>
#endif

MapPhysics::MapPhysics(Map & map, QObject * parent) :
    QObject(parent),
    map(map),
    momentsTimer(),
    speed(100),
    movements(),
    objectsInAir(),
    listeners()
{
    DynamicMapLayer & dynamicLayer = map.getDynamicLayer();

    dynamicLayer.getPlayer().setMover(*this);

    for (auto iterator = dynamicLayer.begin(); iterator != dynamicLayer.end(); iterator++)
    {
        QSharedPointer<DynamicMapObjectGeometry> & object = *iterator;

        if (MapToolKit::isInAir(object->getRect(), map))
        {
            objectsInAir.push_back(object->getObject());
        }
    }

    connect(&momentsTimer, &QTimer::timeout,
            this, &MapPhysics::onMomentsTimerTimeout);

    momentsTimer.setSingleShot(false);
    momentsTimer.setInterval(timeBetweenMoments);
    momentsTimer.start();
}

void MapPhysics::setSpeed(const qreal speed)
{
    this->speed = speed;
}

qreal MapPhysics::getSpeed() const
{
    return speed;
}

void MapPhysics::move(const DynamicMapObject & mapObject, const qreal angle)
{
    stop(mapObject);
    movements.push_back(new Movement(mapObject, angle));
    if (!momentsTimer.isActive())
    {
        momentsTimer.start();
    }
}

void MapPhysics::stop(const DynamicMapObject & mapObject)
{
    for (auto iterator = movements.begin(); iterator != movements.end(); )
    {
        const Movement * const movement = *iterator;
        if (&movement->getMapObject() == &mapObject)
        {
            iterator = movements.erase(iterator);
            delete movement;
            continue;
        }
        iterator++;
    }
}

int MapPhysics::getTimeBetweenMoments() const
{
    return momentsTimer.interval();
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

void MapPhysics::onMomentsTimerTimeout()
{
    for (auto iterator = movements.constBegin(); iterator != movements.constEnd(); iterator++)
    {
        const Movement & movement = **iterator;

        if (!objectsInAir.contains(&movement.getMapObject()))
        {
            if (MapToolKit::isInAir(movement.getMapObject().getRect(), map))
            {
                objectsInAir.push_back(&movement.getMapObject());
                continue;
            }

            moveToCalculatedPosition(movement.getMapObject(), movement.getAngle());
        }
    }

    for (auto iterator = objectsInAir.begin(); iterator != objectsInAir.end(); )
    {
        const DynamicMapObject & mapObject = **iterator;
        moveToCalculatedPosition(mapObject, 270);
        if (!MapToolKit::isInAir(mapObject.getRect(), map))
        {
            iterator = objectsInAir.erase(iterator);
            continue;
        }
        iterator++;
    }

    if (objectsInAir.empty() && movements.empty())
    {
        momentsTimer.stop();
    }
}

void MapPhysics::moveToCalculatedPosition(const DynamicMapObject & mapObject, const qreal angle)
{
    DynamicMapObjectGeometry * requester = findGeometryBy(mapObject);

    if (requester != nullptr)
    {
        QRectF & requesterRect = requester->getRect();
        const QPointF requestedPosition = calculateNewPositionFor(requesterRect, angle);

        if (isNewPositionValid(*(requester->getObject()), requestedPosition))
        {
            const QPointF oldPosition = requesterRect.topLeft();
            requesterRect.moveTopLeft(requestedPosition);
            notifyAboutMove(requester, requesterRect, oldPosition);
        }
    }
#ifdef QT_DEBUG
    else
    {
        qDebug() << "requester of move() was not found for some reason";
    }
#endif
}

const QPointF MapPhysics::calculateNewPositionFor(const QRectF & rect, const qreal angle) const
{
    QLineF directionLine(0, 0, (speed / (1000 / momentsTimer.interval())), 0);
    directionLine.setAngle(angle);

    const qreal potentialHorDistance = directionLine.x2() - directionLine.x1();
    const qreal potentialVerDistance = directionLine.y2() - directionLine.y1();
    qreal horDistance = 0;
    qreal verDistanse = 0;
    if (MapToolKit::isRectInsideOfStairs(rect, map))
    {
        if (MapToolKit::hasWallBellow(rect, map))
        {
            horDistance = potentialHorDistance;
            if (MapToolKit::isRectInsideOfAir(rect, map))
            {
                verDistanse = 0;
            }
            else
            {
                verDistanse = potentialVerDistance;
            }
        }
        else
        {
            horDistance = 0;
            verDistanse = potentialVerDistance;
        }
    }
    else
    {
        horDistance = potentialHorDistance;
        verDistanse = potentialVerDistance > 0 ? potentialVerDistance : 0;
    }

    const QPointF initialPosition = rect.topLeft();

    return QPointF(initialPosition.x() + horDistance, initialPosition.y() + verDistanse);
}


DynamicMapObjectGeometry * MapPhysics::findGeometryBy(const DynamicMapObject & mapObject) const
{
    DynamicMapLayer & dynamicLayer = map.getDynamicLayer();

    for (auto iterator = dynamicLayer.begin(); iterator != dynamicLayer.end(); iterator++)
    {
        QSharedPointer<DynamicMapObjectGeometry> & object = *iterator;

        if (object->getObject() == &mapObject)
        {
            return object.data();
        }
    }

    return nullptr;
}

bool MapPhysics::isNewPositionValid(const DynamicMapObject & object, const QPointF & newPosition) const
{
    QRectF newRect(object.getRect());
    newRect.moveTopLeft(newPosition);
    return MapToolKit::isRectWithinMap(newRect, map) && !MapToolKit::isRectInsideOfWall(newRect, map);
}

void MapPhysics::notifyAboutMove(DynamicMapObjectGeometry * requester, QRectF & requesterRect, const QPointF oldPosition) const
{
    for (auto & listener : listeners)
    {
        listener->onObjectChangedPosition(*(requester->getObject()), oldPosition, requesterRect.topLeft());
    }
}
