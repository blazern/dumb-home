#ifndef MAPTOOLKIT_H
#define MAPTOOLKIT_H

#include <QRectF>
#include "Map.h"

class MapToolKit
{
    Q_DISABLE_COPY(MapToolKit)
public:
    static int getTopIndexOf(const QRectF & rect, const Map & map);
    static int getRightIndexOf(const QRectF & rect, const Map & map);
    static int getBottomIndexOf(const QRectF & rect, const Map & map);
    static int getLeftIndexOf(const QRectF & rect, const Map & map);

    static bool isInAir(const QRectF & rect, const Map & map);
    static bool isRectWithinMap(const QRectF & rect, const Map & map);
    static bool isRectInsideOfWall(const QRectF & rect, const Map & map);
    static bool isRectInsideOfStairs(const QRectF & rect, const Map & map);
    static bool isRectInsideOfAir(const QRectF & rect, const Map & map);
    static bool hasWallBellow(const QRectF & rect, const Map & map);

private:
    explicit MapToolKit();
    static bool isRectInsideOf(const StaticMapObject::Type type, const QRectF & rect, const Map & map);
    static bool hasObjectBelow(const StaticMapObject::Type type, const QRectF & rect, const Map & map);
};

#endif // MAPTOOLKIT_H
