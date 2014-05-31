#ifndef STAIRSCHECKER_H
#define STAIRSCHECKER_H

#include <QVector>
#include "../StaticMapObject.h"

class StairsChecker
{
    friend class StaticMapLayer;
protected:
    enum class StairsStatus { VALID, END_IN_AIR, PART_IS_ON_EDGE, STARTS_NOT_ON_WALL, ENDS_BENEATH_WALL };
    static StairsStatus getStatusForStairsIn(const QVector<QVector<StaticMapObject*>> & staticObjects);

private:
    explicit StairsChecker();
    static bool isTopOfStairs(const int x, const int y, const QVector<QVector<StaticMapObject*>> & staticObjects);
    static bool areWallsOrStairsOnSides(const int x, const int y, const QVector<QVector<StaticMapObject*>> & staticObjects);
    static bool isBottomOfStairs(const int x, const int y, const QVector<QVector<StaticMapObject*>> & staticObjects);
    static bool isWallBeneath(const int x, const int y, const QVector<QVector<StaticMapObject*>> & staticObjects);
    static bool isWallAbove(const int x, const int y, const QVector<QVector<StaticMapObject*>> & staticObjects);
};

#endif // STAIRSCHECKER_H
