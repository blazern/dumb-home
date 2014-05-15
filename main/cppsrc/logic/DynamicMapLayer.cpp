#include "DynamicMapLayer.h"

#ifdef QT_DEBUG
#include <QDebug>
#endif


DynamicMapLayer::DynamicMapLayer(const QRectF & playerRect, Mover * mover) :
    objects(),
    player(nullptr)
{
    auto initializer = [this, &mover](const QRectF & rect)->DynamicMapObject*
    {
        if (mover != nullptr)
        {
            this->player = new Player(rect, *mover);
        }
        else
        {
            this->player = new Player(rect);
        }
        return this->player;
    };

    objects.append(QSharedPointer<DynamicMapObjectGeometry>(
                       new DynamicMapObjectGeometry(
                           playerRect,
                           initializer)));
}

int DynamicMapLayer::getCount() const
{
    return objects.size();
}

DynamicMapLayer::iterator DynamicMapLayer::begin()
{
    return objects.begin();
}

DynamicMapLayer::iterator DynamicMapLayer::end()
{
    return objects.end();
}

DynamicMapLayer::const_iterator DynamicMapLayer::constBegin() const
{
    return objects.constBegin();
}

DynamicMapLayer::const_iterator DynamicMapLayer::constEnd() const
{
    return objects.constEnd();
}

const Player & DynamicMapLayer::getPlayer() const
{
    return *player;
}

Player & DynamicMapLayer::getPlayer()
{
    return *player;
}
