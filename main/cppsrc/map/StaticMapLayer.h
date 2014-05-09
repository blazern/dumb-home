#ifndef STATICMAPLAYER_H
#define STATICMAPLAYER_H

#include <QSharedPointer>
#include <QVector>
#include "StaticMapObject.h"

class StaticMapLayer
{
    Q_DISABLE_COPY(StaticMapLayer)
public:
    explicit StaticMapLayer(const QVector<QVector<QSharedPointer<StaticMapObject>>> & staticObjects);

    int getWidth() const;
    int getHeight() const;
    const StaticMapObject * get(const int x, const int y) const;
    StaticMapObject * get(const int x, const int y);

private:
    QVector<QVector<QSharedPointer<StaticMapObject>>> staticObjects;
};

#endif // STATICMAPLAYER_H
