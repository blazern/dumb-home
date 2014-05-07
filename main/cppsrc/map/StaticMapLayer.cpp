#include "StaticMapLayer.h"
#include "StaticMapObjectImpl.h"

StaticMapLayer::StaticMapLayer(const QVector<QVector<QSharedPointer<StaticMapObject>>> & staticObjects) :
    staticObjects(staticObjects)
{
}

StaticMapLayer::StaticMapLayer(const int width, const int height) :
    staticObjects()
{
    for (int widthIndex = 0; widthIndex < width; widthIndex++)
    {
        staticObjects.append(QVector<QSharedPointer<StaticMapObject>>());
        for (int heightIndex = 0; heightIndex < height; heightIndex++)
        {
            if (widthIndex == 0 || heightIndex == 0 || widthIndex == width - 1 || heightIndex == height - 1 || widthIndex == height - heightIndex)
            {
                staticObjects[widthIndex].append(
                            QSharedPointer<StaticMapObject>(new StaticMapObjectImpl()));
            }
            else
            {
                staticObjects[widthIndex].append(QSharedPointer<StaticMapObject>(nullptr));
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

const StaticMapObject * StaticMapLayer::get(const int x, const int y) const
{
    return staticObjects[x][y].data();
}

StaticMapObject *StaticMapLayer::get(const int x, const int y)
{
    return staticObjects[x][y].data();
}
