#include "Player.h"

Player::Player(const QRectF & rect, Mover & mover) :
    Player(rect, &mover)
{
}

Player::Player(const QRectF & rect) :
    Player(rect, nullptr)
{
}

Player::Player(const QRectF & rect, Mover * mover) :
    DynamicMapObject(),
    rect(rect),
    mover(mover)
{
}

void Player::setMover(Mover & mover)
{
    this->mover = &mover;
}

void Player::moveTo(const Player::MovementDirection direction)
{
    if (mover != nullptr)
    {
        switch (direction)
        {
        case MovementDirection::UP:
            mover->move(*this, 270);
            break;
        case MovementDirection::RIGHT:
            mover->move(*this, 0);
            break;
        case MovementDirection::DOWN:
            mover->move(*this, 90);
            break;
        case MovementDirection::LEFT:
            mover->move(*this, 180);
            break;
        }
    }
}

void Player::stopMovement()
{
    if (mover != nullptr)
    {
        mover->stop(*this);
    }
}

const QRectF & Player::getRect() const
{
    return rect;
}

