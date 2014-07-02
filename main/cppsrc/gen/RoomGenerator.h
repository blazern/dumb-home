#ifndef ROOMGENERATOR_H
#define ROOMGENERATOR_H

#include <QVector>
#include "../logic/StaticMapObject.h"


class RoomGenerator
{
    RoomGenerator(const RoomGenerator & other) = delete;
    RoomGenerator & operator=(const RoomGenerator & other) = delete;

public:
    explicit RoomGenerator(const int left, const int top, const int right, const int bottom);

    // throws std::invalid_argument if right and/or bottom do not fit staticObjects
    void generate(QVector<QVector<StaticMapObject *>> & staticObjects) const;

    int getLeft() const { return left; }
    int getTop() const { return top; }
    int getRight() const { return right; }
    int getBottom() const { return bottom; }

private:
    void checkGenerateArguments(QVector<QVector<StaticMapObject *>> & staticObjects) const;

private:
    const int left;
    const int top;
    const int right;
    const int bottom;
};

#endif // ROOMGENERATOR_H
