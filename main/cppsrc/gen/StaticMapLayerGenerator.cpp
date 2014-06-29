#include "StaticMapLayerGenerator.h"

#include <stdexcept>
#include "math.h"
#include "../logic/StaticMapObject.h"
#include "../util/LineDivider.h"
#include "StoreyGenerator.h"
#include "Minimums.h"

#ifdef QT_DEBUG
#include <QDebug>
#endif

StaticMapLayerGenerator::StaticMapLayerGenerator(const int width, const int height) :
    width(width),
    height(height),
    storeysCount(nullptr)
{
    try
    {
        checkArguments(height, width);
    }
    catch(...)
    {
        freeResources();
        throw;
    }
}

void StaticMapLayerGenerator::checkArguments(const int height, const int width) const
{
    if (width < Minimums::MAP_WIDTH)
    {
        throw std::invalid_argument("received map's width is smaller than the minimum");
    }
    if (height < Minimums::MAP_HEIGHT)
    {
        throw std::invalid_argument("received map's height is smaller than the minimum");
    }
}

void StaticMapLayerGenerator::freeResources()
{
    delete storeysCount;
}

StaticMapLayerGenerator::StaticMapLayerGenerator(const int width, const int height, const int storeysCount) :
    width(width),
    height(height),
    storeysCount(new int(storeysCount))
{
    try
    {
        checkArguments(height, width);
    }
    catch(...)
    {
        freeResources();
        throw;
    }
}

StaticMapLayerGenerator::~StaticMapLayerGenerator()
{
    freeResources();
}

StaticMapLayer * StaticMapLayerGenerator::generate()
{
    invalidateStoreysCount(height);
    QVector<QVector<StaticMapObject *>> staticObjects = getEmptyStaticMapLayer(width, height);

    QVector<QSharedPointer<StoreyGenerator>> storeysGenerators = getStoreysGenerators(width, height, *storeysCount);
    for (auto & storeyGenerator : storeysGenerators)
    {
        try
        {
            storeyGenerator->generate(staticObjects);
        }
        catch(...)
        {
            free(staticObjects);
        }
    }

    replaceNullptrsWithWalls(staticObjects);
    return new StaticMapLayer(staticObjects);
}

void StaticMapLayerGenerator::invalidateStoreysCount(const int mapHeight)
{
    const int availableForStoreysGenerationMapHeight = mapHeight - 1;
    if (storeysCount == nullptr)
    {
        storeysCount = new int(floor(availableForStoreysGenerationMapHeight / (Minimums::STOREY_HEIGHT + 1)));
    }
}

QVector<QVector<StaticMapObject*>> StaticMapLayerGenerator::getEmptyStaticMapLayer(const int width, const int height) const
{
    QVector<QVector<StaticMapObject*>> staticObjects;
    for (int x = 0; x < width; x++)
    {
        staticObjects.append(QVector<StaticMapObject*>());
        for (int y = 0; y < height; y++)
        {
            staticObjects[x].append(nullptr);
        }
    }
    return staticObjects;
}

QVector<int> StaticMapLayerGenerator::getStoreysBottoms(const int mapHeight, const int storeysCount) const
{
    QVector<int> storeysBottoms = LineDivider::getDividers(0, mapHeight, storeysCount, Minimums::STOREY_HEIGHT + 1);
    storeysBottoms.append(mapHeight - 1);
    return storeysBottoms;
}

QVector<QSharedPointer<StoreyGenerator> > StaticMapLayerGenerator::getStoreysGenerators(
        const int mapWidth,
        const int mapHeight,
        const int storeysCount) const
{
    const QVector<int> storeysBottoms = getStoreysBottoms(mapHeight, storeysCount);

    QVector<QSharedPointer<StoreyGenerator>> storeysGenerators;

    int nextTop = 1;
    for (int bottomIndex = 0; bottomIndex < storeysBottoms.size(); bottomIndex++)
    {
        const int bottom = storeysBottoms[bottomIndex];
        if (bottomIndex == 0)
        {
            storeysGenerators.append(QSharedPointer<StoreyGenerator>(new StoreyGenerator(nextTop, bottom, mapWidth)));
        }
        else
        {
            storeysGenerators.append(QSharedPointer<StoreyGenerator>(
                                         new StoreyGenerator(nextTop, bottom, mapWidth, storeysGenerators[bottomIndex - 1].data())));
        }
        nextTop = bottom + 1;
    }

    return storeysGenerators;
}

void StaticMapLayerGenerator::replaceNullptrsWithWalls(QVector<QVector<StaticMapObject *>> & staticObjects) const
{
    for (int x = 0; x < staticObjects.size(); x++)
    {
        for (int y = 0; y < staticObjects[x].size(); y++)
        {
            if (staticObjects[x][y] == nullptr)
            {
                staticObjects[x][y] = new StaticMapObject(StaticMapObject::Type::WALL);
            }
        }
    }
}

void StaticMapLayerGenerator::free(QVector<QVector<StaticMapObject *>> & staticObjects) const
{
    for (int x = 0; x < staticObjects.size(); x++)
    {
        for (int y = 0; y < staticObjects[x].size(); y++)
        {
            delete staticObjects[x][y];
        }
    }
}
