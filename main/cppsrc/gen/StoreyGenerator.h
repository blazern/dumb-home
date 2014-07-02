#ifndef STOREYGENERATOR_H
#define STOREYGENERATOR_H

#include <QVector>
#include <QSharedPointer>
#include "../logic/StaticMapObject.h"
#include "RoomGenerator.h"


/// Reusing instances of the class is not recommended - they will produce always almost same storeys as they produced before.
class StoreyGenerator
{
    StoreyGenerator(const StoreyGenerator & other) = delete;
    StoreyGenerator & operator=(const StoreyGenerator & other) = delete;

public:
    // throws std::invalid_argument if height is smaller than MIN_HEIGHT
    explicit StoreyGenerator(const int top,
                             const int bottom,
                             const int mapWidth,
                             StoreyGenerator * const aboveStoreyGenerator = nullptr);
    // throws std::invalid_argument if height is smaller than MIN_HEIGHT
    explicit StoreyGenerator(const int top,
                             const int bottom,
                             const int mapWidth,
                             const int roomsCount,
                             StoreyGenerator * const aboveStoreyGenerator = nullptr);
    ~StoreyGenerator();

    // throws std::invalid_argument if bottom or mapWidth is not applicable for staticObjects, if mapWidths are different
    void generate(QVector<QVector<StaticMapObject *> > & staticObjects);

private:
    int setStairsFromBellow(const QVector<int> & forbiddenPositions);

    void freeResources();
    QVector<int> getRoomsDividers(const int mapWidth, const int roomsCount) const;
    QVector<QSharedPointer<RoomGenerator>> getRoomsGenerators(const int mapWidth, const QVector<int> & roomsDividers) const;
    void checkArguments(const int top, const int bottom, const StoreyGenerator * const aboveStoreyGenerator, const int mapWidth) const;
    void setUpStairsWith(StoreyGenerator & aboveStoreyGenerator);
    void checkGenerateArguments(QVector<QVector<StaticMapObject *> > & staticObjects) const;
    void generateRoomsDividers(QVector<QVector<StaticMapObject *> > & staticObjects) const;
    void generateStairs(QVector<QVector<StaticMapObject *> > & staticObjects) const;
    void replaceNullptrsWithWalls(QVector<QVector<StaticMapObject *> > & staticObjects) const;
    QVector<int> getForbiddenPositions() const;

    static const int DEFAULT_AVERAGE_ROOM_WIDTH = 6;

    const int top;
    const int bottom;
    const int mapWidth;
    const int roomsCount;
    StoreyGenerator * const aboveStoreyGenerator;
    const QVector<int> roomsDividers;
    QVector<QSharedPointer<RoomGenerator>> roomsGenerators;

    const int * stairsToAboveX;
    const int * stairsFromBellowX;
};

#endif // STOREYGENERATOR_H
