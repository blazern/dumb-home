#include "StaticMapLayer.h"
#include <stdexcept>
#include "StaticMapObject.h"
#include "util/StairsChecker.h"

#ifdef QT_DEBUG
#include <QDebug>
#endif

StaticMapLayer::~StaticMapLayer()
{
    freeResources();
}

void StaticMapLayer::freeResources()
{
    for (auto horIterator = staticObjects.begin(); horIterator != staticObjects.end(); horIterator++)
    {
        for (auto verIterator = horIterator->begin(); verIterator != horIterator->end(); verIterator++)
        {
            delete *verIterator;
        }
    }
}

StaticMapLayer::StaticMapLayer(const QVector<QVector<StaticMapObject*>> & staticObjects) :
    staticObjects(staticObjects)
{
    try
    {
        checkArguments(staticObjects);
    }
    catch(...)
    {
        freeResources();
        throw;
    }
}

void StaticMapLayer::checkArguments(const QVector<QVector<StaticMapObject*>> & staticObjects) const
{
    checkSizes(staticObjects);
    checkForNullptr(staticObjects);
    checkStairs(staticObjects);
}

void StaticMapLayer::checkSizes(const QVector<QVector<StaticMapObject*>>& staticObjects) const
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
}

void StaticMapLayer::checkForNullptr(const QVector<QVector<StaticMapObject*>> & staticObjects) const
{
    for (int x = 0; x < staticObjects.size(); x++)
    {
        for (int y = 0; y < staticObjects[x].size(); y++)
        {
            if (staticObjects[x][y] == nullptr)
            {
                throw std::invalid_argument("all elements of staticObjects must not be nullptr");
            }
        }
    }
}

void StaticMapLayer::checkStairs(const QVector<QVector<StaticMapObject*>> & staticObjects) const
{
    switch (StairsChecker::getStatusForStairsIn(staticObjects))
    {
    case StairsChecker::StairsStatus::VALID:
        break;
    case StairsChecker::StairsStatus::END_IN_AIR:
        throw std::invalid_argument("some stairs end in air");
        break;
    case StairsChecker::StairsStatus::PART_IS_ON_EDGE:
        throw std::invalid_argument("some stairs are on an edge of the map");
        break;
    case StairsChecker::StairsStatus::STARTS_NOT_ON_WALL:
        throw std::invalid_argument("some stairs start not on a wall");
        break;
    case StairsChecker::StairsStatus::ENDS_BENEATH_WALL:
        throw std::invalid_argument("some end right beneath a wall");
        break;
#ifdef QT_DEBUG
    default:
        qDebug() << "received an unknown instance of StairsChecker::StairsStatus";
#endif
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
