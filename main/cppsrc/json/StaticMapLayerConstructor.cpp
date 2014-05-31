#include "StaticMapLayerConstructor.h"
#include <stdexcept>

StaticMapLayerConstructor::StaticMapLayerConstructor(const int width, const int height) :
    grid()
{
    for (int horIndex = 0; horIndex < width; horIndex++)
    {
        grid.append(QVector<StaticMapObject::Type>());
        for (int verIndex = 0; verIndex < height; verIndex++)
        {
            grid[horIndex].append(StaticMapObject::Type::AIR);
        }
    }
}

void StaticMapLayerConstructor::markCell(const int x, const int y, const StaticMapObject::Type type)
{
    const int width = grid.size();
    const int height = grid[0].size();

    if (x < 0 || width <= x
        || y < 0 || height <= y)
    {
        throw std::invalid_argument("static object is out of bounds");
    }

    grid[x][y] = type;
}

StaticMapLayer * StaticMapLayerConstructor::construct() const
{
    QVector<QVector<StaticMapObject*>> staticObjects;

    for (int horIndex = 0; horIndex < grid.size(); horIndex++)
    {
        staticObjects.append(QVector<StaticMapObject*>());
        for (int verIndex = 0; verIndex < grid[0].size(); verIndex++)
        {
            staticObjects[horIndex].append(new StaticMapObject(grid[horIndex][verIndex]));
        }
    }

    return new StaticMapLayer(staticObjects);
}
