#include "MapToolKit.h"

#include "StaticMapObject.h"

MapToolKit::MapToolKit()
{
}

int MapToolKit::getTopIndexOf(const QRectF & rect, const Map & map)
{
    return floor(rect.top() / map.getStaticMapObjectHeight());
}

int MapToolKit::getRightIndexOf(const QRectF & rect, const Map & map)
{
    return floor((rect.right() - 1) / map.getStaticMapObjectWidth());
}

int MapToolKit::getBottomIndexOf(const QRectF & rect, const Map & map)
{
    return floor((rect.bottom() - 1) / map.getStaticMapObjectHeight());
}

int MapToolKit::getLeftIndexOf(const QRectF & rect, const Map & map)
{
    return floor(rect.left() / map.getStaticMapObjectWidth());
}

bool MapToolKit::isInAir(const QRectF & rect, const Map & map)
{
    return !(hasObjectBelow(StaticMapObject::Type::WALL, rect, map)
            || hasObjectBelow(StaticMapObject::Type::STAIRS, rect, map)
            || isRectInsideOf(StaticMapObject::Type::WALL, rect, map)
            || isRectInsideOf(StaticMapObject::Type::STAIRS, rect, map));
}

bool MapToolKit::hasObjectBelow(const StaticMapObject::Type type, const QRectF & rect, const Map & map)
{
    const int leftCell = getLeftIndexOf(rect, map);
    const int rightCell = getRightIndexOf(rect, map);
    const int bottomRow = getBottomIndexOf(rect, map);

    const int bellowRow = bottomRow + 1;
    const StaticMapLayer & staticLayer = map.getStaticLayer();

    bool hasObjectBelow = false;

    for (int horIndex = leftCell; horIndex <= rightCell; horIndex++)
    {
        const StaticMapObject & mapObject = staticLayer.get(horIndex, bellowRow);
        if (mapObject.getType() == type)
        {
            hasObjectBelow = true;

            const qreal wallTop = bellowRow * map.getStaticMapObjectHeight();
            if (wallTop > rect.bottom())
            {
                return false;
            }
        }
    }

    return hasObjectBelow;
}

bool MapToolKit::isRectWithinMap(const QRectF & rect, const Map & map)
{
    const StaticMapLayer & staticLayer = map.getStaticLayer();

    return 0 <= rect.left()
            && 0 <= rect.top()
            && rect.right() <= staticLayer.getWidth() * map.getStaticMapObjectWidth()
            && rect.bottom() <= staticLayer.getHeight() * map.getStaticMapObjectHeight();
}

bool MapToolKit::hasWallBellow(const QRectF & rect, const Map & map)
{
    return hasObjectBelow(StaticMapObject::Type::WALL, rect, map);
}

bool MapToolKit::isRectInsideOfWall(const QRectF & rect, const Map & map)
{
    return isRectInsideOf(StaticMapObject::Type::WALL, rect, map);
}

bool MapToolKit::isRectInsideOfStairs(const QRectF & rect, const Map & map)
{
    return isRectInsideOf(StaticMapObject::Type::STAIRS, rect, map);
}

bool MapToolKit::isRectInsideOfAir(const QRectF & rect, const Map & map)
{
    return isRectInsideOf(StaticMapObject::Type::AIR, rect, map);
}

bool MapToolKit::isRectInsideOf(const StaticMapObject::Type type, const QRectF & rect, const Map & map)
{
    const StaticMapLayer & staticLayer = map.getStaticLayer();

    // static objects represent a grid, therefore it is easy to check
    // if there is any static object underneath the rect
    const int left = MapToolKit::getLeftIndexOf(rect, map);
    const int right = MapToolKit::getRightIndexOf(rect, map);
    const int top = MapToolKit::getTopIndexOf(rect, map);
    const int bottom = MapToolKit::getBottomIndexOf(rect, map);

    for (int hor = left; hor <= right; hor++)
    {
        for (int ver = top; ver <= bottom; ver++)
        {
            const StaticMapObject & mapObject = staticLayer.get(hor, ver);
            if (mapObject.getType() == type)
            {
                return true;
            }
        }
    }
    return false;
}
