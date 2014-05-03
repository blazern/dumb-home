#include "QmlMapInterface.h"

#ifdef QT_DEBUG
#include <QDebug>
#endif

QmlMapInterface::QmlMapInterface(QObject * parent) :
    QObject(parent),
    MapListener(),
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

    for (int widthIndex = 0; widthIndex < map->getMapWidth(); widthIndex++)
    {
        for (int heightIndex = 0; heightIndex < map->getMapHeight(); heightIndex++)
        {
            const StaticMapObject * const mapObject =
                    map->getStaticObjectAt(widthIndex, heightIndex);

            if (mapObject != nullptr)
            {
                mapObjects.append(QSharedPointer<MapObjectQmlWrapper>(
                                      new MapObjectQmlWrapper(
                                          *mapObject,
                                          map->getStaticMapObjectWidth(),
                                          map->getStaticMapObjectHeight(),
                                          this)));
            }
        }
    }

    for (int index = 0; index < map->getDynamicObjectsCount(); index++)
    {
        const DynamicMapObject & mapObject = map->getDynamicObject(index);
        mapObjects.append(QSharedPointer<MapObjectQmlWrapper>(new MapObjectQmlWrapper(mapObject, this)));

        if (&mapObject == &(map->getPlayer()))
        {
            playerId = mapObjects.last()->getId();
        }
    }
}

int QmlMapInterface::getWidth() const
{
    return map != nullptr ? map->getMapWidth() : 0;
}

int QmlMapInterface::getHeight() const
{
    return map != nullptr ? map->getMapHeight() : 0;
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

void QmlMapInterface::onObjectChangedPosition(const DynamicMapObject & object, const QPointF & position)
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

    emit objectChangedPosition(id, position.x(), position.y());
}
