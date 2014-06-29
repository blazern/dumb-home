#include "Map.h"
#include <stdexcept>


Map::Map(StaticMapLayer * const staticLayer,
         DynamicMapLayer * const dynamicLayer,
         const qreal staticObjectWidth,
         const qreal staticObjectHeight) :
    staticLayer(staticLayer),
    staticMapObjectWidth(staticObjectWidth),
    staticMapObjectHeight(staticObjectHeight),
    dynamicLayer(dynamicLayer)
{
    if (staticLayer == nullptr || dynamicLayer == nullptr)
    {
        freeResources();
        throw new std::invalid_argument("layers must not be nullptr");
    }
    else if (staticMapObjectWidth <= 0 || staticObjectHeight <= 0)
    {
        freeResources();
        throw new std::invalid_argument("static map object size is invalid");
    }
}

void Map::freeResources()
{
    delete staticLayer;
    delete dynamicLayer;
}

Map::~Map()
{
    freeResources();
}

const StaticMapLayer & Map::getStaticLayer() const
{
    return *staticLayer;
}

StaticMapLayer & Map::getStaticLayer()
{
    return *staticLayer;
}

qreal Map::getStaticMapObjectWidth() const
{
    return staticMapObjectWidth;
}

qreal Map::getStaticMapObjectHeight() const
{
    return staticMapObjectHeight;
}

const QRectF Map::getRectOfStaticObjectWith(const int horPos, const int verPos) const
{
    return QRectF(horPos * staticMapObjectWidth,
                  verPos * staticMapObjectHeight,
                  staticMapObjectWidth,
                  staticMapObjectHeight);
}

const DynamicMapLayer & Map::getDynamicLayer() const
{
    return *dynamicLayer;
}

DynamicMapLayer & Map::getDynamicLayer()
{
    return *dynamicLayer;
}
