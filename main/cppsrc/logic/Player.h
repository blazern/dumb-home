#ifndef PLAYER_H
#define PLAYER_H

#include <QRectF>
#include "DynamicMapObject.h"
#include "Mover.h"

class Player : public DynamicMapObject
{
    Q_DISABLE_COPY(Player)
public:
    enum class MovementDirection { UP, RIGHT, DOWN, LEFT };

    explicit Player(const QRectF & rect, Mover & mover);
    explicit Player(const QRectF & rect);

    void setMover(Mover & mover);

    void moveTo(const MovementDirection direction);
    void stopMovement();
    virtual const QRectF & getRect() const final override;

private:
    const QRectF & rect;
    Mover * mover;

private:
    explicit Player(const QRectF & rect, Mover * mover);
};

#endif // PLAYER_H
