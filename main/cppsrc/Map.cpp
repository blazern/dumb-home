#include "Map.h"

Map::Map(const int width, const int height) :
    width(width),
    height(height),
    playerPosition(width / 2, height / 2),
    player(playerPosition, *this),
    listeners()
{
}

Player & Map::getPlayer()
{
    return player;
}

const Player & Map::getPlayer() const
{
    return player;
}

int Map::getWidth() const
{
    return width;
}

int Map::getHeight() const
{
    return height;
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

void Map::move(const MapObject & mapObject, const QPointF & destination)
{
    if (&mapObject == &player)
    {
        if (isLocationWithinMap(destination))
        {
            playerPosition = destination;
            for (auto & listener : listeners)
            {
                listener->onPlayerChangedPosition(playerPosition);
            }
        }
    }
}

bool Map::isLocationWithinMap(const QPointF & location) const
{
    if (0 <= location.x() && 0 <= location.y()
        && location.x() <= width && location.y() <= height)
    {
        return true;
    }
    else
    {
        return false;
    }
}
