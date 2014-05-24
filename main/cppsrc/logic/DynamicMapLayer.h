#ifndef DYNAMICMAPLAYER_H
#define DYNAMICMAPLAYER_H

#include <QRectF>
#include <QVector>
#include <QSharedPointer>
#include "DynamicMapObject.h"
#include "Player.h"
#include "DynamicMapObjectGeometry.h"
#include "Mover.h"

class DynamicMapLayer
{
    DynamicMapLayer(DynamicMapLayer & other) = delete;
    DynamicMapLayer & operator=(DynamicMapLayer & other) = delete;
public:
    explicit DynamicMapLayer(const QRectF & playerRect, Mover * mover = nullptr);

    const Player & getPlayer() const;
    Player & getPlayer();

    int getCount() const;

    typedef QVector<QSharedPointer<DynamicMapObjectGeometry>>::iterator iterator;
    iterator begin();
    iterator end();

    typedef QVector<QSharedPointer<DynamicMapObjectGeometry>>::const_iterator const_iterator;
    const_iterator constBegin() const;
    const_iterator constEnd() const;

private:
    QVector<QSharedPointer<DynamicMapObjectGeometry>> objects;
    Player * player;
};

#endif // DYNAMICMAPLAYER_H
