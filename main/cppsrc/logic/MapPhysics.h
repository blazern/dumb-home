#ifndef MAPPHYSICS_H
#define MAPPHYSICS_H

#include <QVector>
#include <vector>
#include <QTimer>
#include "Mover.h"
#include "Map.h"
#include "MapPhysicsListener.h"
#include "Movement.h"

class MapPhysics : public Mover, public QObject
{
    Q_DISABLE_COPY(MapPhysics)
public:
    explicit MapPhysics(Map & map, QObject * parent = 0);
    void start();

    void setSpeed(const qreal speed);
    qreal getSpeed() const;

    virtual void move(const DynamicMapObject & mapObject, const qreal angle) final override;
    virtual void stop(const DynamicMapObject & mapObject) final override;

    int getTimeBetweenMoments() const;

    void addListener(MapPhysicsListener & listener);
    void removeListener(MapPhysicsListener & listener);

private slots:
    void onMomentsTimerTimeout();

private:
    Map & map;
    QTimer momentsTimer;
    qreal speed; /// per second

    static constexpr int timeBetweenMoments = 10;

    QVector<const Movement*> movements;
    QVector<const DynamicMapObject*> objectsInAir;

    QVector<MapPhysicsListener*> listeners;

private:
    const QPointF calculateNewPositionFor(const QRectF & rect, const qreal angle) const;
    void moveToCalculatedPosition(const DynamicMapObject & mapObject, const qreal angle);
    DynamicMapObjectGeometry * findGeometryBy(const DynamicMapObject& mapObject) const;
    bool isNewPositionValid(const DynamicMapObject & object, const QPointF & newPosition) const;
    void notifyAboutMove(DynamicMapObjectGeometry * requester, QRectF & requesterRect, const QPointF oldPosition) const;
};

#endif // MAPPHYSICS_H
