#include "QmlMapInterface.h"

#include "logic/StaticMapObject.h"

#ifdef QT_DEBUG
#include <QDebug>
#endif

QmlMapInterface::QmlMapInterface(QObject * parent) :
    QObject(parent),
    MapPhysicsListener(),
    map(nullptr),
    playerId(0),
    staticMapObjects(),
    dynamicMapObjects()
{
}

void QmlMapInterface::setMap(const Map & map)
{
    this->map = &map;

    refillMapObjects();

    emit mapSetUp();
}

void QmlMapInterface::refillMapObjects()
{
    playerId = 0;
    staticMapObjects.clear();
    refillStaticMapObjects();
    dynamicMapObjects.clear();
    refillDynamicMapObjects();
}

void QmlMapInterface::refillStaticMapObjects()
{
    const int mapWidth = map->getStaticLayer().getWidth();
    const int mapHeight = map->getStaticLayer().getHeight();
    const StaticMapLayer & staticMapLayer = map->getStaticLayer();

    for (int widthIndex = 0; widthIndex < mapWidth; widthIndex++)
    {
        for (int heightIndex = 0; heightIndex < mapHeight; heightIndex++)
        {
            const StaticMapObject & mapObject =
                    staticMapLayer.get(widthIndex, heightIndex);
            const StaticMapObject::Type type = mapObject.getType();

            if (type != StaticMapObject::Type::AIR)
            {
                QColor color;

                switch (type)
                {
                case StaticMapObject::Type::WALL:
                    color = QColor("red");
                    break;
                case StaticMapObject::Type::STAIRS:
                    color = QColor("purple");
                    break;
                default:
#ifdef QT_DEBUG
                    qDebug() << "an unknown type of StaticMapObject is received!";
#endif
                    color = QColor("black");
                    break;
                }

                staticMapObjects.append(QSharedPointer<MapObjectQmlWrapper>(
                                      new MapObjectQmlWrapper(
                                          mapObject,
                                          map->getRectOfStaticObjectWith(widthIndex, heightIndex),
                                          color,
                                          this)));
            }
        }
    }
}

void QmlMapInterface::refillDynamicMapObjects()
{
    const DynamicMapLayer & dynamicMapLayer = map->getDynamicLayer();

    for (auto iterator = dynamicMapLayer.constBegin(); iterator != dynamicMapLayer.constEnd(); iterator++)
    {
        const QSharedPointer<DynamicMapObjectGeometry> & mapObjectGeometry = *iterator;

        const DynamicMapObject & mapObject = *mapObjectGeometry->getObject();
        dynamicMapObjects.append(QSharedPointer<MapObjectQmlWrapper>(new MapObjectQmlWrapper(mapObject, this)));

        if (&mapObject == &(dynamicMapLayer.getPlayer()))
        {
            playerId = dynamicMapObjects.last()->getId();
        }
    }
}

bool QmlMapInterface::isMapSetUp() const
{
    return map != nullptr;
}

unsigned int QmlMapInterface::getPlayerId() const
{
    return playerId;
}

MapObjectQmlWrapper * QmlMapInterface::getObjectById(const unsigned int id)
{
    for (int index = 0; index < getObjectsCount(); index++)
    {
        MapObjectQmlWrapper * currentObject = getObject(index);
        if (currentObject->getId() == id)
        {
            return currentObject;
        }
    }
    return nullptr;
}

int QmlMapInterface::getObjectsCount() const
{
    return staticMapObjects.size() + dynamicMapObjects.size();
}

MapObjectQmlWrapper * QmlMapInterface::getObject(const int index)
{
    if (index < staticMapObjects.size())
    {
        return staticMapObjects[index].data();
    }
    else
    {
        return dynamicMapObjects[index - staticMapObjects.size()].data();
    }
}

int QmlMapInterface::getStaticObjectsCount() const
{
    return staticMapObjects.size();
}

MapObjectQmlWrapper * QmlMapInterface::getStaticObject(const int index)
{
    return staticMapObjects[index].data();
}

int QmlMapInterface::getDynamicObjectsCount() const
{
    return dynamicMapObjects.size();
}

MapObjectQmlWrapper * QmlMapInterface::getDynamicObject(const int index)
{
    return dynamicMapObjects[index].data();
}

void QmlMapInterface::onObjectChangedPosition(const DynamicMapObject & object, const QPointF & oldPosition, const QPointF & newPosition)
{
    unsigned int id = 0;
    for (auto iterator = dynamicMapObjects.begin(); iterator != dynamicMapObjects.end(); iterator++)
    {
        const MapObjectQmlWrapper & mapObjectQmlWrapper = **iterator;
        if (mapObjectQmlWrapper.isMadeFor(object))
        {
            id = mapObjectQmlWrapper.getId();
            break;
        }
    }

#ifdef QT_DEBUG
    if (id == 0)
    {
        qDebug() << "id was not found for some reason!";
    }
#endif

    emit objectChangedPosition(id, oldPosition.x(), oldPosition.y(), newPosition.x(), newPosition.y());
}
