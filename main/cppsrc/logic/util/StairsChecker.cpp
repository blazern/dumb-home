#include "StairsChecker.h"

StairsChecker::StairsChecker()
{
}

StairsChecker::StairsStatus StairsChecker::getStatusForStairsIn(const QVector<QVector<StaticMapObject*>> & staticObjects)
{
    const int width = staticObjects.size();
    const int height = staticObjects[0].size();

    for (int x = 0; x < width; x++)
    {
        for (int y = 0; y < height; y++)
        {
            const StaticMapObject * const object = staticObjects[x][y];
            if (object->getType() == StaticMapObject::Type::STAIRS)
            {
                if (x == 0 || y == 0 || x == width - 1 || y == height - 1)
                {
                    return StairsChecker::StairsStatus::PART_IS_ON_EDGE;
                }

                if (isTopOfStairs(x, y, staticObjects))
                {
                    if (!areWallsOrStairsOnSides(x, y, staticObjects))
                    {
                        return StairsChecker::StairsStatus::END_IN_AIR;
                    }
                    if (isWallAbove(x, y, staticObjects))
                    {
                        return StairsChecker::StairsStatus::ENDS_BENEATH_WALL;
                    }
                }

                if (isBottomOfStairs(x, y, staticObjects)
                    && !isWallBeneath(x, y, staticObjects))
                {
                    return StairsChecker::StairsStatus::STARTS_NOT_ON_WALL;
                }
            }
        }
    }

    return StairsChecker::StairsStatus::VALID;
}

bool StairsChecker::isTopOfStairs(const int x, const int y, const QVector<QVector<StaticMapObject*>> & staticObjects)
{
    if (staticObjects[x][y]->getType() == StaticMapObject::Type::STAIRS)
    {
        if (staticObjects[x][y - 1]->getType() != StaticMapObject::Type::STAIRS
            && staticObjects[x][y + 1]->getType() == StaticMapObject::Type::STAIRS)
        {
            return true;
        }
    }

    return false;
}

bool StairsChecker::areWallsOrStairsOnSides(const int x, const int y, const QVector<QVector<StaticMapObject *>> & staticObjects)
{
    const StaticMapObject::Type leftType = staticObjects[x - 1][y]->getType();
    const StaticMapObject::Type rightType = staticObjects[x + 1][y]->getType();

    return  (leftType == StaticMapObject::Type::WALL || leftType == StaticMapObject::Type::STAIRS)
            && (rightType == StaticMapObject::Type::WALL || rightType == StaticMapObject::Type::STAIRS);
}

bool StairsChecker::isBottomOfStairs(const int x, const int y, const QVector<QVector<StaticMapObject *> > & staticObjects)
{
    if (staticObjects[x][y]->getType() == StaticMapObject::Type::STAIRS)
    {
        if (staticObjects[x][y - 1]->getType() == StaticMapObject::Type::STAIRS
            && staticObjects[x][y + 1]->getType() != StaticMapObject::Type::STAIRS)
        {
            return true;
        }
    }

    return false;
}

bool StairsChecker::isWallBeneath(const int x, const int y, const QVector<QVector<StaticMapObject *> > & staticObjects)
{
    return staticObjects[x][y + 1]->getType() == StaticMapObject::Type::WALL;
}

bool StairsChecker::isWallAbove(const int x, const int y, const QVector<QVector<StaticMapObject *> > & staticObjects)
{
    return staticObjects[x][y - 1]->getType() == StaticMapObject::Type::WALL;
}

