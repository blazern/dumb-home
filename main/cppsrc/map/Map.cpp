#include "Map.h"
#include "StaticMapObjectImpl.h"
#include <math.h>

Map::Map(const int width, const int height, const qreal staticMapObjectSize) :
    staticMapObjectWidth(staticMapObjectSize),
    staticMapObjectHeight(staticMapObjectSize),
    playerRect(
        (2) * staticMapObjectSize,
        (2) * staticMapObjectSize,
        staticMapObjectSize * 2,
        staticMapObjectSize * 2),
    player(playerRect, *this),
    staticObjects(),
    listeners()
{
    for (int widthIndex = 0; widthIndex < width; widthIndex++)
    {
        staticObjects.append(QVector<QSharedPointer<StaticMapObject>>());
        for (int heightIndex = 0; heightIndex < height; heightIndex++)
        {
            if (widthIndex == 0 || heightIndex == 0 || widthIndex == width - 1 || heightIndex == height - 1 || widthIndex == height - heightIndex)
            {
                staticObjects[widthIndex].append(
                            QSharedPointer<StaticMapObject>(new StaticMapObjectImpl(QPoint(widthIndex, heightIndex))));
            }
            else
            {
                staticObjects[widthIndex].append(QSharedPointer<StaticMapObject>(nullptr));
            }
        }
    }
}

const DynamicMapObject & Map::getDynamicObject(const int index) const
{
    if (index == 0)
    {
        return player;
    }
    else
    {
        abort();
    }
}

int Map::getDynamicObjectsCount() const
{
    return 1;
}

const Player & Map::getPlayer() const
{
    return player;
}

Player & Map::getPlayer()
{
    return player;
}

const StaticMapObject * Map::getStaticObjectAt(const int x, const int y) const
{
    return staticObjects[x][y].data();
}

qreal Map::getStaticMapObjectWidth() const
{
    return staticMapObjectWidth;
}

qreal Map::getStaticMapObjectHeight() const
{
    return staticMapObjectHeight;
}

int Map::getMapWidth() const
{
    return staticObjects.size();
}

int Map::getMapHeight() const
{
    return staticObjects[0].size();
}

void Map::addListener(MapListener & listener)
{
    listeners.append(&listener);
}

void Map::removeListener(MapListener & listener)
{
    for (auto iterator = listeners.begin(); iterator != listeners.end(); )
    {
        if (*iterator == &listener)
        {
            iterator = listeners.erase(iterator);
            continue;
        }
        iterator++;
    }
}

void Map::move(const DynamicMapObject & mapObject, const qreal toX, const qreal toY)
{
    if (&mapObject == &player)
    {
        if (isNewPositionValid(playerRect, toX, toY))
        {
            const qreal oldWidth = playerRect.width();
            const qreal oldHeight = playerRect.height();
            playerRect.setX(toX);
            playerRect.setWidth(oldWidth);
            playerRect.setY(toY);
            playerRect.setHeight(oldHeight);
            for (auto & listener : listeners)
            {
                listener->onObjectChangedPosition(player, playerRect.topLeft());
            }
        }
    }
}

bool Map::isNewPositionValid(const QRectF & rect, const qreal x, const qreal y) const
{
    if (isRectangleWithNewPositionValid(rect, x, y))
    {
        // static objects represent a grid, therefore it is easy to check
        // if there is any static object underneath the rect
        const int left = floor(x / staticMapObjectWidth);
        const int right = floor((x - 1 + rect.width()) / staticMapObjectWidth);
        const int top = floor(y / staticMapObjectHeight);
        const int bottom = floor((y - 1 + rect.height()) / staticMapObjectHeight);

        for (int hor = left; hor <= right; hor++)
        {
            for (int ver = top; ver <= bottom; ver++)
            {
                if (!staticObjects[hor][ver].isNull())
                {
                    return false;
                }
            }
        }
        return true;
    }
    else
    {
        return false;
    }
}

bool Map::isRectangleWithNewPositionValid(const QRectF & rect, const qreal x, const qreal y) const
{
    return 0 <= x
            && 0 <= y
            && x + rect.width() <= getMapWidth() * staticMapObjectWidth
            && y + rect.height() <= getMapHeight() * staticMapObjectHeight;
}
