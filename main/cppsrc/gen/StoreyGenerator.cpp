#include "StoreyGenerator.h"

#include <stdexcept>
#include <QSharedPointer>
#include <math.h>
#include "RoomGenerator.h"
#include "../util/LineDivider.h"
#include "Minimums.h"

#ifdef QT_DEBUG
#include <QDebug>
const int LOOP_LIMIT = 100000;
#endif

StoreyGenerator::~StoreyGenerator()
{
    freeResources();
}

void StoreyGenerator::freeResources()
{
    delete stairsToAboveX;
    delete stairsFromBellowX;
}

StoreyGenerator::StoreyGenerator(const int top,
                                 const int bottom,
                                 const int mapWidth,
                                 StoreyGenerator * const aboveStoreyGenerator) :
    StoreyGenerator(top, bottom, mapWidth, (mapWidth - 2) / (DEFAULT_AVERAGE_ROOM_WIDTH + 1), aboveStoreyGenerator)
{
}

StoreyGenerator::StoreyGenerator(const int top,
                                 const int bottom,
                                 const int mapWidth,
                                 const int roomsCount,
                                 StoreyGenerator * const aboveStoreyGenerator) :
    top(top),
    bottom(bottom),
    mapWidth(mapWidth),
    roomsCount(roomsCount),
    aboveStoreyGenerator(aboveStoreyGenerator),
    roomsDividers(getRoomsDividers(mapWidth, roomsCount)),
    roomsGenerators(getRoomsGenerators(mapWidth, roomsDividers)),
    stairsToAboveX(nullptr),
    stairsFromBellowX(nullptr)
{
    try
    {
        checkArguments(top, bottom, aboveStoreyGenerator, mapWidth);
    }
    catch(...)
    {
        freeResources();
        throw;
    }

    if (aboveStoreyGenerator != nullptr)
    {
        setUpStairsWith(*aboveStoreyGenerator);
    }
}

QVector<int> StoreyGenerator::getRoomsDividers(const int mapWidth, const int roomsCount) const
{
    return LineDivider::getDividers(0, mapWidth, roomsCount, Minimums::ROOM_WIDTH + 2);
}

QVector<QSharedPointer<RoomGenerator>> StoreyGenerator::getRoomsGenerators(const int mapWidth, const QVector<int> & roomsDividers) const
{
    QVector<QSharedPointer<RoomGenerator>> roomGenerators;

    for (int dividerIndex = 0; dividerIndex <= roomsDividers.size(); dividerIndex++)
    {
        const int left = dividerIndex == 0 ? 1 : roomsDividers[dividerIndex - 1] + 1;
        const int right = dividerIndex == roomsDividers.size() ? mapWidth - 2 : roomsDividers[dividerIndex] - 1;
        roomGenerators.append(QSharedPointer<RoomGenerator>(new RoomGenerator(left, top, right, bottom - 1)));
    }

    return roomGenerators;
}

void StoreyGenerator::checkArguments(const int top, const int bottom, const StoreyGenerator * const aboveStoreyGenerator, const int mapWidth) const
{
    if (bottom <= top)
    {
        throw std::invalid_argument("received storey's bottom is equal to or above of received storey's top");
    }
    if ((bottom - top) + 1 < Minimums::STOREY_HEIGHT)
    {
        throw std::invalid_argument("received storey's height is smaller than minimum");
    }
    if (aboveStoreyGenerator != nullptr && top <= aboveStoreyGenerator->bottom)
    {
        throw std::invalid_argument("received aboveStoreyGenerator is not above of this");
    }
    if (aboveStoreyGenerator != nullptr && mapWidth != aboveStoreyGenerator->mapWidth)
    {
        throw std::invalid_argument("received aboveStoreyGenerator has different mapWidth");
    }
}

void StoreyGenerator::setUpStairsWith(StoreyGenerator & aboveStoreyGenerator)
{
    stairsToAboveX = new int(aboveStoreyGenerator.setStairsFromBellow(getForbiddenPositions()));
}

QVector<int> StoreyGenerator::getForbiddenPositions() const
{
    QVector<int> forbiddentPositions;

    forbiddentPositions.append(0);
    forbiddentPositions.append(mapWidth - 1);

    if (stairsToAboveX != nullptr)
    {
        for (int locationIndex = 0; locationIndex < Minimums::STAIRS_WIDTH; locationIndex++)
        {
            forbiddentPositions.append(*stairsToAboveX + locationIndex);
        }
    }

    if (stairsFromBellowX != nullptr)
    {
        for (int locationIndex = 0; locationIndex < Minimums::STAIRS_WIDTH; locationIndex++)
        {
            forbiddentPositions.append(*stairsFromBellowX + locationIndex);
        }
    }

    for (const auto & roomDivider : roomsDividers)
    {
        forbiddentPositions.append(roomDivider);
    }

    return forbiddentPositions;
}

int StoreyGenerator::setStairsFromBellow(const QVector<int> & forbiddenPositions)
{
    const QVector<int> myForbiddenPositions = getForbiddenPositions();

#ifdef QT_DEBUG
    int loopIndex = 0;
#endif

    while (true)
    {
        const int potentialBellowStairsLocation = qrand() % mapWidth;
        bool potentialFromBellowStairsAreGood = true;

        for (int locationIndex = 0; locationIndex < Minimums::STAIRS_WIDTH; locationIndex++)
        {
            const int currentPotentialBellowStairsLocation = potentialBellowStairsLocation + locationIndex;
            if (forbiddenPositions.contains(currentPotentialBellowStairsLocation)
                || myForbiddenPositions.contains(currentPotentialBellowStairsLocation))
            {
                potentialFromBellowStairsAreGood = false;
                break;
            }
        }

        if (potentialFromBellowStairsAreGood)
        {
            delete stairsFromBellowX;
            stairsFromBellowX = new int(potentialBellowStairsLocation);
            return *stairsFromBellowX;
        }

#ifdef QT_DEBUG
        loopIndex++;
        if (loopIndex == LOOP_LIMIT)
        {
            qDebug() << "looks like for some reason a loop for finding good stairs position has gone infinite";
        }
#endif
    }
}

void StoreyGenerator::generate(QVector<QVector<StaticMapObject *>> & staticObjects)
{
    checkGenerateArguments(staticObjects);

    for (auto & roomGenerator : roomsGenerators)
    {
        roomGenerator->generate(staticObjects);
    }

    generateRoomsDividers(staticObjects);
    generateStairs(staticObjects);
    replaceNullptrsWithWalls(staticObjects);
}

void StoreyGenerator::checkGenerateArguments(QVector<QVector<StaticMapObject *>> & staticObjects) const
{
    if (mapWidth != staticObjects.size())
    {
        throw std::invalid_argument("received staticObject's width does not equal to given mapWidth");
    }
    for (int x = 0; x < staticObjects.size(); x++)
    {
        if (staticObjects[x].size() <= bottom)
        {
            throw std::invalid_argument("received staticObject's height does match the given bottom at one of x");
        }
    }
}

void StoreyGenerator::generateRoomsDividers(QVector<QVector<StaticMapObject *>>& staticObjects) const
{
    for (auto & roomDivider : roomsDividers)
    {
        for (int y = bottom - 1; y >= bottom - 2; y--)
        {
#ifdef QT_DEBUG
            if (staticObjects[roomDivider][y] != nullptr)
            {
                qDebug() << "StoreyGenerator: staticObjects[" << roomDivider << "][" << y << "] expected to be nullptr but it's not";
            }
#endif
            delete staticObjects[roomDivider][y];
            staticObjects[roomDivider][y] = new StaticMapObject(StaticMapObject::Type::AIR);
        }
    }
}

void StoreyGenerator::generateStairs(QVector<QVector<StaticMapObject *>> & staticObjects) const
{
    if (stairsToAboveX != nullptr)
    {
        for (int positionIndex = 0; positionIndex < Minimums::STAIRS_WIDTH; positionIndex++)
        {
            const int x = *stairsToAboveX + positionIndex;
            for (int y = bottom - 1; y >= top; y--)
            {
                delete staticObjects[x][y];
                staticObjects[x][y] = new StaticMapObject(StaticMapObject::Type::STAIRS);
            }
        }
    }

    if (stairsFromBellowX != nullptr)
    {
        for (int positionIndex = 0; positionIndex < Minimums::STAIRS_WIDTH; positionIndex++)
        {
            const int x = *stairsFromBellowX + positionIndex;
            delete staticObjects[x][bottom];
            staticObjects[x][bottom] = new StaticMapObject(StaticMapObject::Type::STAIRS);
        }
    }
}

void StoreyGenerator::replaceNullptrsWithWalls(QVector<QVector<StaticMapObject *>> & staticObjects) const
{
    for (int x = 0; x < staticObjects.size(); x++)
    {
        for (int y = top; y <= bottom; y++)
        {
            if (staticObjects[x][y] == nullptr)
            {
                staticObjects[x][y] = new StaticMapObject(StaticMapObject::Type::WALL);
            }
        }
    }
}
