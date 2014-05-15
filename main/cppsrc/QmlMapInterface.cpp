#include "QmlMapInterface.h"

#include "logic/Wall.h"

#ifdef QT_DEBUG
#include <QDebug>
#endif

QmlMapInterface::QmlMapInterface(QObject * parent) :
    QObject(parent),
    MapPhysicsListener(),
    map(nullptr),
    playerId(0),
    mapObjects()
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
    mapObjects.clear();

    const int mapWidth = map->getStaticLayer().getWidth();
    const int mapHeight = map->getStaticLayer().getHeight();
    const StaticMapLayer & staticMapLayer = map->getStaticLayer();

    for (int widthIndex = 0; widthIndex < mapWidth; widthIndex++)
    {
        for (int heightIndex = 0; heightIndex < mapHeight; heightIndex++)
        {
            const StaticMapObject & mapObject =
                    staticMapLayer.get(widthIndex, heightIndex);

            if (dynamic_cast<const Wall*>(&mapObject) != nullptr)
            {
                mapObjects.append(QSharedPointer<MapObjectQmlWrapper>(
                                      new MapObjectQmlWrapper(
                                          mapObject,
                                          map->getRectOfStaticObjectWith(widthIndex, heightIndex),
                                          this)));
            }
        }
    }

    const DynamicMapLayer & dynamicMapLayer = map->getDynamicLayer();

    for (auto iterator = dynamicMapLayer.constBegin(); iterator != dynamicMapLayer.constEnd(); iterator++)
    {
        const QSharedPointer<DynamicMapObjectGeometry> & mapObjectGeometry = *iterator;

        const DynamicMapObject & mapObject = *mapObjectGeometry->getObject();
        mapObjects.append(QSharedPointer<MapObjectQmlWrapper>(new MapObjectQmlWrapper(mapObject, this)));

        if (&mapObject == &(dynamicMapLayer.getPlayer()))
        {
            playerId = mapObjects.last()->getId();
        }
    }
}

int QmlMapInterface::getWidth() const
{
    return map != nullptr ? map->getStaticLayer().getWidth() : 0;
}

int QmlMapInterface::getHeight() const
{
    return map != nullptr ? map->getStaticLayer().getHeight() : 0;
}

bool QmlMapInterface::isMapSetUp() const
{
    return map != nullptr;
}

int QmlMapInterface::getObjectsCount() const
{
    return mapObjects.size();
}

MapObjectQmlWrapper * QmlMapInterface::getMapObject(const int index)
{
    return mapObjects[index].data();
}

unsigned int QmlMapInterface::getPlayerId() const
{
    return playerId;
}

void QmlMapInterface::onObjectChangedPosition(const DynamicMapObject & object, const QPointF & oldPosition, const QPointF & newPosition)
{
    unsigned int id = 0;
    for (auto iterator = mapObjects.begin(); iterator != mapObjects.end(); iterator++)
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
