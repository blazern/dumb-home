#include "RoomGenerator.h"

#include <stdexcept>
#include <QString>
#include "Minimums.h"

RoomGenerator::RoomGenerator(const int left, const int top, const int right, const int bottom) :
    left(left),
    top(top),
    right(right),
    bottom(bottom)
{
    const int width = (right - left) + 1;
    if (width < Minimums::ROOM_WIDTH)
    {
        throw std::invalid_argument("received room width is smaller than the minimum");
    }
    const int height = (bottom - top) + 1;
    if (height < Minimums::ROOM_HEIGHT)
    {
        throw std::invalid_argument("received room height is smaller than the minimum");
    }
}

void RoomGenerator::generate(QVector<QVector<StaticMapObject *>> & staticObjects) const
{
    checkGenerateArguments(staticObjects);

    for (int x = left; x <= right; x++)
    {
        for (int y = top; y <= bottom; y++)
        {
            delete staticObjects[x][y];
            staticObjects[x][y] = new StaticMapObject(StaticMapObject::Type::AIR);
        }
    }
}

void RoomGenerator::checkGenerateArguments(QVector<QVector<StaticMapObject *>> & staticObjects) const
{
    if (staticObjects.size() <= right)
    {
        throw std::invalid_argument("received staticObject's width does not match the given room's right");
    }
    for (int x = 0; x < staticObjects.size(); x++)
    {
        if (staticObjects[x].size() <= bottom)
        {
            throw std::invalid_argument("received staticObjects's height does not match the given room's bottom on one of x");
        }
    }
}
