#include "StaticMapLayer.h"
#include <stdexcept>
#include "Wall.h"

StaticMapLayer::StaticMapLayer(const QVector<QVector<StaticMapObject*>> & staticObjects) :
    staticObjects(staticObjects)
{
    checkArguments(staticObjects);
}

StaticMapLayer::~StaticMapLayer()
{
    for (auto horIterator = staticObjects.begin(); horIterator != staticObjects.end(); horIterator++)
    {
        for (auto verIterator = horIterator->begin(); verIterator != horIterator->end(); verIterator++)
        {
            delete *verIterator;
        }
    }
}

void StaticMapLayer::checkArguments(const QVector<QVector<StaticMapObject*>> & staticObjects) const
{
    if (staticObjects.size() == 0)
    {
        throw std::invalid_argument("StaticMapLayer's width must be greater than 0");
    }

    const int height = staticObjects[0].size();

    if (height == 0)
    {
        throw std::invalid_argument("StaticMapLayer's height must be greater than 0");
    }

    for (auto iterator = staticObjects.begin(); iterator != staticObjects.end(); iterator++)
    {
        if (iterator->size() != height)
        {
            throw std::invalid_argument("StaticMapLayer's height must not differ from row to row");
        }
    }

    for (auto horIterator = staticObjects.begin(); horIterator != staticObjects.end(); horIterator++)
    {
        for (auto verIterator = horIterator->begin(); verIterator != horIterator->end(); verIterator++)
        {
            if (*verIterator == nullptr)
            {
                throw std::invalid_argument("all elements of staticObjects must not be nullptr");
            }
        }
    }
}

int StaticMapLayer::getWidth() const
{
    return staticObjects.size();
}

int StaticMapLayer::getHeight() const
{
    return staticObjects.size() > 0 ? staticObjects[0].size() : 0;
}

const StaticMapObject & StaticMapLayer::get(const int x, const int y) const
{
    return *staticObjects[x][y];
}

StaticMapObject & StaticMapLayer::get(const int x, const int y)
{
    return *staticObjects[x][y];
}
