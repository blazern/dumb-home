#ifndef MAP_H
#define MAP_H

#include <QPair>
#include <QPointF>
#include <QVector>
#include <QPoint>
#include <QSharedPointer>
#include "Mover.h"
#include "MapListener.h"
#include "StaticMapLayer.h"
#include "DynamicMapLayer.h"

class Map : public Mover
{
    Q_DISABLE_COPY(Map)
public:
    explicit Map(const int width, const int height, const qreal staticMapObjectSize);

    const StaticMapLayer & getStaticLayer() const;
    qreal getStaticMapObjectWidth() const;
    qreal getStaticMapObjectHeight() const;
    const QRectF getRectOfStaticObjectWith(const int horPos, const int verPos) const;

    const DynamicMapLayer & getDynamicLayer() const;
    DynamicMapLayer & getDynamicLayer();

    void addListener(MapListener & listener);
    void removeListener(MapListener & listener);

protected:
    virtual void move(const DynamicMapObject & mapObject, const qreal toX, const qreal toY) final override;

private:
    StaticMapLayer staticLayer;
    const qreal staticMapObjectWidth;
    const qreal staticMapObjectHeight;

    DynamicMapLayer dynamicLayer;

    QVector<MapListener*> listeners;

private:
    bool isNewPositionValid(const QRectF & rect, const qreal x, const qreal y) const;
    bool isRectangleWithNewPositionValid(const QRectF & rect, const qreal x, const qreal y) const;
};

#endif // MAP_H
