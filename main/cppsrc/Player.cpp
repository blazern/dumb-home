#include "Player.h"

Player::Player(const QPointF & position, Mover & mover, QObject * parent) :
    QObject(parent),
    position(position),
    mover(mover),
    movementDirection(Player::MovementDirection::UP),
    movementTimer()
{
    movementTimer.setSingleShot(false);
    movementTimer.setInterval(timerInterval);
    connect(&movementTimer, &QTimer::timeout,
            this, &Player::onMovementTimerTimeout);
}

void Player::moveTo(const Player::MovementDirection direction)
{
    if (this->movementDirection == direction && movementTimer.isActive())
    {
        return;
    }

    this->movementDirection = direction;
    movementTimer.start();
}

void Player::stopMovement()
{
    movementTimer.stop();
}

const QPointF & Player::getPosition() const
{
    return position;
}

void Player::onMovementTimerTimeout()
{
    const qreal distanse = (qreal) timerInterval / (speed * 1000);

    qreal resultPosition;

    switch (movementDirection)
    {
    case MovementDirection::UP:
        resultPosition = position.y() + distanse;
        mover.move(*this, QPointF(position.x(), resultPosition));
        break;
    case MovementDirection::RIGHT:
        resultPosition = position.x() + distanse;
        mover.move(*this, QPointF(resultPosition, position.y()));
        break;
    case MovementDirection::DOWN:
        resultPosition = position.y() - distanse;
        mover.move(*this, QPointF(position.x(), resultPosition));
        break;
    case MovementDirection::LEFT:
        resultPosition = position.x() - distanse;
        mover.move(*this, QPointF(resultPosition, position.y()));
        break;
    }
}
