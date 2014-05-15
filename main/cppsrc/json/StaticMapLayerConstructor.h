#ifndef STATICMAPLAYERCONSTRUCTOR_H
#define STATICMAPLAYERCONSTRUCTOR_H

#include <QVector>
#include "../logic/StaticMapLayer.h"

class StaticMapLayerConstructor
{
public:
    StaticMapLayerConstructor(const int width, const int height);

    void markCell(const int x, const int y); // throws std::invalid_argument if position is out of bounds

    StaticMapLayer * construct() const;

private:
    QVector<QVector<bool>> grid;
};

#endif // STATICMAPLAYERCONSTRUCTOR_H
