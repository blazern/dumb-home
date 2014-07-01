#ifndef QMLMAPINTERFACE_H
#define QMLMAPINTERFACE_H

#include <QObject>
#include <QSharedPointer>
#include "logic/MapPhysicsListener.h"
#include "logic/Map.h"
#include "MapObjectQmlWrapper.h"

class QmlMapInterface : public QObject, public MapPhysicsListener
{
    Q_OBJECT
    Q_DISABLE_COPY(QmlMapInterface)
public:
    explicit QmlMapInterface(QObject * parent = 0);

    void setMap(const Map & map);

    Q_INVOKABLE bool isMapSetUp() const;
    Q_INVOKABLE unsigned int getPlayerId() const;
    Q_INVOKABLE MapObjectQmlWrapper * getObjectById(const unsigned int id);

    Q_INVOKABLE int getObjectsCount() const;
    Q_INVOKABLE MapObjectQmlWrapper * getObject(const int index);
    Q_INVOKABLE int getStaticObjectsCount() const;
    Q_INVOKABLE MapObjectQmlWrapper * getStaticObject(const int index);
    Q_INVOKABLE int getDynamicObjectsCount() const;
    Q_INVOKABLE MapObjectQmlWrapper * getDynamicObject(const int index);

    virtual void onObjectChangedPosition(
            const DynamicMapObject & object,
            const QPointF & oldPosition,
            const QPointF & newPosition) final override;

signals:
    void objectChangedPosition(
            const unsigned int id,
            const qreal oldX,
            const qreal oldY,
            const qreal newX,
            const qreal newY) const;
    void mapSetUp() const;

private:
    const Map * map;
    unsigned int playerId;
    QVector<QSharedPointer<MapObjectQmlWrapper>> staticMapObjects;
    QVector<QSharedPointer<MapObjectQmlWrapper>> dynamicMapObjects;

    void refillMapObjects();
    void refillStaticMapObjects();
    void refillDynamicMapObjects();
};

#endif // QMLMAPINTERFACE_H
