#ifndef MAPPHYSICS_H
#define MAPPHYSICS_H

#include <QVector>
#include "Mover.h"
#include "Map.h"
#include "MapPhysicsListener.h"

class MapPhysics : public Mover
{
    Q_DISABLE_COPY(MapPhysics)
public:
    explicit MapPhysics(Map & map);

    virtual void move(const DynamicMapObject & mapObject, const qreal toX, const qreal toY) final override;

    void addListener(MapPhysicsListener & listener);
    void removeListener(MapPhysicsListener & listener);

private:
    Map & map;
    QVector<MapPhysicsListener*> listeners;

private:
    bool isNewPositionValid(const QRectF & rect, const qreal x, const qreal y) const;
    bool isNewPositionWithinMap(const QRectF & rect, const qreal x, const qreal y) const;
};

#endif // MAPPHYSICS_H
