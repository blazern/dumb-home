#ifndef PLAYERACTIONSQMLRECEIVER_H
#define PLAYERACTIONSQMLRECEIVER_H

#include <QObject>
#include "map/Map.h"

class PlayerActionsQmlReceiver : public QObject
{
    Q_OBJECT
    Q_DISABLE_COPY(PlayerActionsQmlReceiver)
public:
    static const int UP = 0;
    static const int RIGHT = 1;
    static const int DOWN = 2;
    static const int LEFT = 3;

    explicit PlayerActionsQmlReceiver(Map & map, QObject * parent = 0);

public slots:
    void onMoveRequested(const int direction);
    void onMoveStopRequested();

private:
    Map & map;
};

#endif // PLAYERACTIONSQMLRECEIVER_H
