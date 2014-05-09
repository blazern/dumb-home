#include "StaticMapLayer.h"
#include "StaticMapObjectImpl.h"

StaticMapLayer::StaticMapLayer(const QVector<QVector<QSharedPointer<StaticMapObject>>> & staticObjects) :
    staticObjects(staticObjects)
{
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
