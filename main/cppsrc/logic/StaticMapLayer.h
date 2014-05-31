#ifndef STATICMAPLAYER_H
#define STATICMAPLAYER_H

#include <QVector>
#include "StaticMapObject.h"

class StaticMapLayer
{
    Q_DISABLE_COPY(StaticMapLayer)
public:
    // throws std::invalid_argument if:
    // width (i.e. staticObjects.size()) == 0
    // height (i.e. staticObjects[i].size()) == 0
    // staticObjects[i].size() != staticObjects[j].size()
    // staticObjects[i][j] == nulptr
    // some stairs start not on wall
    // some stairs end without 2 walls on both sides
    // some stairs are on edge of map
    // some stairs end right beneath a wall
    explicit StaticMapLayer(const QVector<QVector<StaticMapObject*>> & staticObjects);
    ~StaticMapLayer();

    int getWidth() const;
    int getHeight() const;
    const StaticMapObject & get(const int x, const int y) const;
    StaticMapObject & get(const int x, const int y);

private:
    QVector<QVector<StaticMapObject*>> staticObjects;

private:
    void checkArguments(const QVector<QVector<StaticMapObject*>> & staticObjects) const;
    void checkSizes(const QVector<QVector<StaticMapObject*>> & staticObjects) const;
    void checkForNullptr(const QVector<QVector<StaticMapObject*>> & staticObjects) const;
    void checkStairs(const QVector<QVector<StaticMapObject*>> & staticObjects) const;
};

#endif // STATICMAPLAYER_H
