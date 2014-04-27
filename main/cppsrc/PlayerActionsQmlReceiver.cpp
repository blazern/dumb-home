#include "PlayerActionsQmlReceiver.h"

PlayerActionsQmlReceiver::PlayerActionsQmlReceiver(Map & map, QObject * parent) :
    QObject(parent),
    map(map)
{
}

void PlayerActionsQmlReceiver::onMoveRequested(const int direction)
{
    Player & player = map.getPlayer();

    switch (direction)
    {
    case UP:
        player.moveTo(Player::MovementDirection::UP);
        break;
    case RIGHT:
        player.moveTo(Player::MovementDirection::RIGHT);
        break;
    case DOWN:
        player.moveTo(Player::MovementDirection::DOWN);
        break;
    case LEFT:
        player.moveTo(Player::MovementDirection::LEFT);
        break;
    }
}

void PlayerActionsQmlReceiver::onMoveStopRequested()
{
    map.getPlayer().stopMovement();
}
