#ifndef MAP_H
#define MAP_H

#include <QPair>
#include <QPointF>
#include <QPoint>
#include <QSharedPointer>
#include "StaticMapLayer.h"
#include "DynamicMapLayer.h"

class Map
{
    Q_DISABLE_COPY(Map)
public:
    // throws std::invalid_argument if:
    // one of the layers is nullptr
    // one of the sizes <= 0
    explicit Map(StaticMapLayer * const staticLayer,
                 DynamicMapLayer * const dynamicLayer,
                 const qreal staticObjectWidth,
                 const qreal staticObjectHeight);
    virtual ~Map();

    const StaticMapLayer & getStaticLayer() const;
    StaticMapLayer & getStaticLayer();
    qreal getStaticMapObjectWidth() const;
    qreal getStaticMapObjectHeight() const;
    const QRectF getRectOfStaticObjectWith(const int horPos, const int verPos) const;

    const DynamicMapLayer & getDynamicLayer() const;
    DynamicMapLayer & getDynamicLayer();

private:
    void freeResources();

    StaticMapLayer * const staticLayer;
    const qreal staticMapObjectWidth;
    const qreal staticMapObjectHeight;

    DynamicMapLayer * const dynamicLayer;
};

#endif // MAP_H
