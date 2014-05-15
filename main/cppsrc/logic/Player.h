#ifndef PLAYER_H
#define PLAYER_H

#include <QObject>
#include <QTimer>
#include <QRectF>
#include "DynamicMapObject.h"
#include "Mover.h"

class Player : public QObject, public DynamicMapObject
{
    Q_OBJECT
    Q_DISABLE_COPY(Player)
public:
    enum class MovementDirection { UP, RIGHT, DOWN, LEFT };

    explicit Player(const QRectF & rect, Mover & mover, QObject * parent = 0);
    explicit Player(const QRectF & rect, QObject * parent = 0);

    void setMover(Mover & mover);

    void moveTo(const MovementDirection direction);
    void stopMovement();
    virtual const QRectF & getRect() const final override;

private slots:
    void onMovementTimerTimeout();

private:
    static constexpr float speed = 100.0f; // number per second
    static constexpr int timerInterval = 10;

    const QRectF & rect;
    Mover * mover;
    MovementDirection movementDirection;
    QTimer movementTimer;

private:
    explicit Player(const QRectF & rect, Mover * mover, QObject * parent);
};

#endif // PLAYER_H
