#ifndef PLAYER_H
#define PLAYER_H

#include <QObject>
#include <QPointF>
#include <QTimer>
#include "MapObject.h"
#include "Mover.h"

class Player : public QObject, public MapObject
{
    Q_OBJECT
public:
    enum class MovementDirection { UP, RIGHT, DOWN, LEFT };

    explicit Player(const QPointF & position, Mover & mover, QObject * parent = 0);

    void moveTo(const MovementDirection direction);
    void stopMovement();
    virtual const QPointF & getPosition() const final override;

private slots:
    void onMovementTimerTimeout();

private:
    static constexpr float speed = 0.1f; // 'speed' blocks per second // TODO: wrong, fix speeding agorithm
    static constexpr int timerInterval = 10;

    const QPointF & position;
    Mover & mover;
    MovementDirection movementDirection;
    QTimer movementTimer;
};

#endif // PLAYER_H
