#ifndef MAP_H
#define MAP_H

#include <QPair>
#include <QPointF>
#include <QVector>
#include "Mover.h"
#include "Player.h"
#include "MapListener.h"

class Map : public Mover
{
    Q_DISABLE_COPY(Map)
public:
    explicit Map(const int width, const int height);
    Player & getPlayer();
    const Player & getPlayer() const;

    int getWidth() const;
    int getHeight() const;

    void addListener(MapListener & listener);
    void removeListener(MapListener & listener);

protected:
    virtual void move(const MapObject & mapObject, const QPointF & destination) final override;

private:
    const int width;
    const int height;

    QPointF playerPosition;
    Player player;

    QVector<MapListener*> listeners;

private:
    bool isLocationWithinMap(const QPointF & location) const;
};

#endif // MAP_H
