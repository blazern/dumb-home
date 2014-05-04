#include "DynamicMapObjectGeometry.h"

DynamicMapObjectGeometry::~DynamicMapObjectGeometry()
{
    if (dynamicMapObject != nullptr)
    {
        delete dynamicMapObject;
    }
}

