#ifndef STATICMAPLAYERGENERATOR_H
#define STATICMAPLAYERGENERATOR_H

#include <QVector>
#include <QSharedPointer>
#include "../logic/StaticMapLayer.h"
#include "StoreyGenerator.h"


class StaticMapLayerGenerator
{
    StaticMapLayerGenerator(const StaticMapLayerGenerator & other) = delete;
    StaticMapLayerGenerator & operator=(const StaticMapLayerGenerator & other) = delete;

public:
    // throws std::invalid_argument if (width < Minimums::MAP_WIDTH || height < Minimums::MAP_HEIGHT)
    explicit StaticMapLayerGenerator(const int width, const int height);
    // throws std::invalid_argument if (width < Minimums::MAP_WIDTH || height < Minimums::MAP_HEIGHT)
    explicit StaticMapLayerGenerator(const int width, const int height, const int storeysCount);
    ~StaticMapLayerGenerator();

    StaticMapLayer * generate();

private:
    void freeResources();
    void checkArguments(const int height, const int width) const;
    void invalidateStoreysCount(const int mapWidth);
    QVector<QVector<StaticMapObject *>> getEmptyStaticMapLayer(const int width, const int height) const;
    QVector<int> getStoreysBottoms(const int mapHeight, const int storeysCount) const;
    QVector<QSharedPointer<StoreyGenerator>> getStoreysGenerators(const int mapWidth, const int mapHeight, const int storeysCount) const;
    void replaceNullptrsWithWalls(QVector<QVector<StaticMapObject *>> & staticObjects) const;
    void free(QVector<QVector<StaticMapObject *>> & staticObjects) const;

    const int width;
    const int height;
    const int * storeysCount;
};

#endif // STATICMAPLAYERGENERATOR_H
