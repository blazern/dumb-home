#include "MapToolKit.h"

#include "Wall.h"

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
    const int leftCell = getLeftIndexOf(rect, map);
    const int rightCell = getRightIndexOf(rect, map);
    const int bottomRow = getBottomIndexOf(rect, map);

    const int bellowRow = bottomRow + 1;
    const StaticMapLayer & staticLayer = map.getStaticLayer();

    bool hasWallBelow = false;

    for (int horIndex = leftCell; horIndex <= rightCell; horIndex++)
    {
        const Wall * const wall = dynamic_cast<const Wall *>(&staticLayer.get(horIndex, bellowRow));

        if (wall != nullptr)
        {
            hasWallBelow = true;

            const qreal wallTop = bellowRow * map.getStaticMapObjectHeight();
            if (wallTop > rect.bottom())
            {
                return true;
            }
        }
    }

    return !hasWallBelow;
}

bool MapToolKit::isRectWithinMap(const QRectF & rect, const Map & map)
{
    const StaticMapLayer & staticLayer = map.getStaticLayer();

    return 0 <= rect.left()
            && 0 <= rect.top()
            && rect.right() <= staticLayer.getWidth() * map.getStaticMapObjectWidth()
            && rect.bottom() <= staticLayer.getHeight() * map.getStaticMapObjectHeight();
}

bool MapToolKit::isRectInsideOfWall(const QRectF & rect, const Map & map)
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
            if (dynamic_cast<const Wall *>(&staticLayer.get(hor, ver)) != nullptr)
            {
                return true;
            }
        }
    }
    return false;
}
