#include "QmlMapInterface.h"

QmlMapInterface::QmlMapInterface(QObject * parent) :
    QObject(parent),
    MapListener(),
    map(nullptr)
{
}

void QmlMapInterface::setMap(const Map & map)
{
    this->map = &map;
    emit mapSetUp();
}

float QmlMapInterface::getPlayerPositionX() const
{
    return map != nullptr ? map->getPlayer().getPosition().x() : 0;
}

float QmlMapInterface::getPlayerPositionY() const
{
    return map != nullptr ? map->getPlayer().getPosition().y() : 0;
}

int QmlMapInterface::getWidth() const
{
    return map != nullptr ? map->getWidth() : 0;
}

int QmlMapInterface::getHeight() const
{
    return map != nullptr ? map->getHeight() : 0;
}

bool QmlMapInterface::isMapSetUp() const
{
    return map != nullptr;
}

void QmlMapInterface::onPlayerChangedPosition(const QPointF & position)
{
    emit playerChangePosition(position.x(), position.y());
}
