#ifndef MAP_H
#define MAP_H

#include <QPair>
#include <QPointF>
#include <QVector>
#include <QPoint>
#include <QSharedPointer>
#include "Mover.h"
#include "Player.h"
#include "MapListener.h"
#include "StaticMapObject.h"

class Map : public Mover
{
    Q_DISABLE_COPY(Map)
public:
    explicit Map(const int width, const int height, const qreal staticMapObjectSize);

    const DynamicMapObject & getDynamicObject(const int index) const;
    int getDynamicObjectsCount() const;
    const Player & getPlayer() const;
    Player & getPlayer();

    const StaticMapObject * getStaticObjectAt(const int x, const int y) const;
    qreal getStaticMapObjectWidth() const;
    qreal getStaticMapObjectHeight() const;

    int getMapWidth() const;
    int getMapHeight() const;

    void addListener(MapListener & listener);
    void removeListener(MapListener & listener);

protected:
    virtual void move(const DynamicMapObject & mapObject, const qreal toX, const qreal toY) final override;

private:
    const qreal staticMapObjectWidth;
    const qreal staticMapObjectHeight;

    QRectF playerRect;
    Player player;

    QVector<QVector<QSharedPointer<StaticMapObject>>> staticObjects;

    QVector<MapListener*> listeners;

private:
    bool isNewPositionValid(const QRectF & rect, const qreal x, const qreal y) const;
    bool isRectangleWithNewPositionValid(const QRectF & rect, const qreal x, const qreal y) const;
};

#endif // MAP_H
