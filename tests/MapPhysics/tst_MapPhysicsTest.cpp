#include <QString>
#include <QtTest>

#include <QSharedPointer>
#include "../../main/cppsrc/json/JsonMapParser.h"
#include "../../main/cppsrc/logic/MapPhysics.h"

class MapPhysicsTest : public QObject
{
    Q_OBJECT

public:
    MapPhysicsTest();

private:
    bool differenceIsCloseTo(const qreal value1, const qreal value2, const int to);
    bool differenceIsCloseTo(const qreal value1, const qreal value2, const int to, const double error);

private Q_SLOTS:
    void playerMovesToTheRight();
    void playerMovesToTheLeft();
    void playerCantMoveUpByAir();
    void moveTo45DegreesIsShorterThanTo0Digrees();
    void playerFalls();
    void playerCantMoveWhileFalls();
    void speedIsCorrect();

private:
    const JsonMapParser mapParser;
    const QString jsonMapWithRestingPlayer;
    const QSharedPointer<Map> mapWithRestingPlayer;
    MapPhysics mapPhysicsOfMapWithRestingPlayer;
    const QString jsonMapWithFallingPlayer;
    const QString longJsonMap;
    const QString jsonMapWithObstacles;
};

MapPhysicsTest::MapPhysicsTest() :
    mapParser(),
    //represents:
    // ooo
    // opo
    // xxx
    jsonMapWithRestingPlayer(
        R"({ )"
        R"( "player": { )"
        R"(        "x": 10, )"
        R"(        "y": 10, )"
        R"(        "width": 10, )"
        R"(        "height": 10 )"
        R"(    },)"
        R"(    "staticObjectWidth": 10, )"
        R"(    "staticObjectHeight": 10, )"
        R"(    "staticLayerWidth": 3, )"
        R"(    "staticLayerHeight": 3, )"
        R"(    "rows": [ { )"
        R"(        "y":2, )"
        R"(        "cells": [ )"
        R"(            { "x":0 }, )"
        R"(            { "x":1 }, )"
        R"(            { "x":2 } )"
        R"(        ] }    ] )"
        R"(} )"),
    mapWithRestingPlayer(mapParser.parseFromString(jsonMapWithRestingPlayer)),
    mapPhysicsOfMapWithRestingPlayer(*mapWithRestingPlayer),
    //represents:
    // opo
    // ooo
    // xxx
    jsonMapWithFallingPlayer(
        R"({ )"
        R"( "player": { )"
        R"(        "x": 10, )"
        R"(        "y": 0, )"
        R"(        "width": 10, )"
        R"(        "height": 10 )"
        R"(    },)"
        R"(    "staticObjectWidth": 10, )"
        R"(    "staticObjectHeight": 10, )"
        R"(    "staticLayerWidth": 3, )"
        R"(    "staticLayerHeight": 3, )"
        R"(    "rows": [ { )"
        R"(        "y":2, )"
        R"(        "cells": [ )"
        R"(            { "x":0 }, )"
        R"(            { "x":1 }, )"
        R"(            { "x":2 } )"
        R"(        ] }    ] )"
        R"(} )"),
    //represents:
    // opoooooo
    // xxxxxxxx
    longJsonMap(
        R"({ )"
        R"( "player": { )"
        R"(        "x": 10, )"
        R"(        "y": 0, )"
        R"(        "width": 10, )"
        R"(        "height": 10 )"
        R"(    },)"
        R"(    "staticObjectWidth": 10, )"
        R"(    "staticObjectHeight": 10, )"
        R"(    "staticLayerWidth": 8, )"
        R"(    "staticLayerHeight": 2, )"
        R"(    "rows": [ { )"
        R"(        "y":1, )"
        R"(        "cells": [ )"
        R"(            { "x":0 }, )"
        R"(            { "x":1 }, )"
        R"(            { "x":2 }, )"
        R"(            { "x":3 }, )"
        R"(            { "x":4 }, )"
        R"(            { "x":5 }, )"
        R"(            { "x":6 }, )"
        R"(            { "x":7 } )"
        R"(        ] }    ] )"
        R"(} )"),
    //represents:
    // opoxoxo
    // xxxxxxx
    jsonMapWithObstacles(
        R"({ )"
        R"( "player": { )"
        R"(        "x": 10, )"
        R"(        "y": 0, )"
        R"(        "width": 10, )"
        R"(        "height": 10 )"
        R"(    },)"
        R"(    "staticObjectWidth": 10, )"
        R"(    "staticObjectHeight": 10, )"
        R"(    "staticLayerWidth": 87, )"
        R"(    "staticLayerHeight": 2, )"
        R"(    "rows": [ { )"
        R"(        "y":1, )"
        R"(        "cells": [ )"
        R"(            { "x":0 }, )"
        R"(            { "x":1 }, )"
        R"(            { "x":2 }, )"
        R"(            { "x":3 }, )"
        R"(            { "x":4 }, )"
        R"(            { "x":5 }, )"
        R"(            { "x":6 }, )"
        R"(            { "x":7 } )"
        R"(        ] }, { )"
        R"(        "y":1, )"
        R"(        "cells": [ )"
        R"(            { "x":3 }, )"
        R"(            { "x":5 } )"
        R"(        ] }    ] )"
        R"(} )")
{
}

void MapPhysicsTest::playerMovesToTheRight()
{
    Player & player = mapWithRestingPlayer->getDynamicLayer().getPlayer();
    const QPointF initialPosition = player.getRect().topLeft();

    mapPhysicsOfMapWithRestingPlayer.move(player, 0);

    QTest::qWait(mapPhysicsOfMapWithRestingPlayer.getTimeBetweenMoments() * 2);

    mapPhysicsOfMapWithRestingPlayer.stop(player);

    const QPointF finalPosition = player.getRect().topLeft();

    QVERIFY(initialPosition.x() < finalPosition.x());
}

void MapPhysicsTest::playerMovesToTheLeft()
{
    Player & player = mapWithRestingPlayer->getDynamicLayer().getPlayer();
    const QPointF initialPosition = player.getRect().topLeft();

    mapPhysicsOfMapWithRestingPlayer.move(player, 180);

    QTest::qWait(mapPhysicsOfMapWithRestingPlayer.getTimeBetweenMoments() * 2);

    mapPhysicsOfMapWithRestingPlayer.stop(player);

    const QPointF finalPosition = player.getRect().topLeft();

    QVERIFY(finalPosition.x() < initialPosition.x());
}

void MapPhysicsTest::playerCantMoveUpByAir()
{
    Player & player = mapWithRestingPlayer->getDynamicLayer().getPlayer();
    const QPointF initialPosition = player.getRect().topLeft();

    mapPhysicsOfMapWithRestingPlayer.move(player, 270);

    const QPointF finalPosition = player.getRect().topLeft();

    QVERIFY(finalPosition == initialPosition);
}

void MapPhysicsTest::moveTo45DegreesIsShorterThanTo0Digrees()
{
    Player & player = mapWithRestingPlayer->getDynamicLayer().getPlayer();
    const QPointF initialPosition = player.getRect().topLeft();

    mapPhysicsOfMapWithRestingPlayer.move(player, 0);
    QTest::qWait(mapPhysicsOfMapWithRestingPlayer.getTimeBetweenMoments() * 4);
    mapPhysicsOfMapWithRestingPlayer.stop(player);
    const QPointF to0DegreesMovePosition = player.getRect().topLeft();

    mapPhysicsOfMapWithRestingPlayer.move(player, 45);
    QTest::qWait(mapPhysicsOfMapWithRestingPlayer.getTimeBetweenMoments() * 4);
    mapPhysicsOfMapWithRestingPlayer.stop(player);
    const QPointF to45DegreesMovePosition = player.getRect().topLeft();

    const qreal to0DigreesDistance = to0DegreesMovePosition.x() - initialPosition.x();
    const qreal to45DigreesDistance = to45DegreesMovePosition.x() - to0DegreesMovePosition.x();

    QVERIFY(to0DigreesDistance != 0);
    QVERIFY(to45DigreesDistance != 0);

    QVERIFY(to45DigreesDistance < to0DigreesDistance);
}

void MapPhysicsTest::playerFalls()
{
    QSharedPointer<Map> map(mapParser.parseFromString(jsonMapWithFallingPlayer));
    MapPhysics mapPhysics(*map);

    Player & player = map->getDynamicLayer().getPlayer();
    const QPointF initialPosition = player.getRect().topLeft();

    QTest::qWait(mapPhysics.getTimeBetweenMoments() * 2);

    const QPointF finalPosition = player.getRect().topLeft();

    QVERIFY(initialPosition.y() < finalPosition.y());
}

void MapPhysicsTest::playerCantMoveWhileFalls()
{
    QSharedPointer<Map> map(mapParser.parseFromString(jsonMapWithFallingPlayer));
    MapPhysics mapPhysics(*map);

    Player & player = map->getDynamicLayer().getPlayer();
    const QPointF initialPosition = player.getRect().topLeft();

    mapPhysics.move(player, 0);

    QTest::qWait(mapPhysics.getTimeBetweenMoments() * 2);

    const QPointF finalPosition = player.getRect().topLeft();

    QVERIFY(initialPosition.x() == finalPosition.x());
}

void MapPhysicsTest::speedIsCorrect()
{
    QSharedPointer<Map> map(mapParser.parseFromString(longJsonMap));
    MapPhysics mapPhysics(*map);

    mapPhysics.setSpeed(mapPhysics.getSpeed() * 2); // per second

    Player & player = map->getDynamicLayer().getPlayer();
    const QPointF initialPosition = player.getRect().topLeft();

    mapPhysics.move(player, 0);

    const int timeToWait = 100; // 1/10 of a second
    QTest::qWait(timeToWait);

    mapPhysics.stop(player);

    const QPointF finalPosition = player.getRect().topLeft();

    QVERIFY(differenceIsCloseTo(initialPosition.y(), finalPosition.y(), 0));
    const qreal allowedError = mapPhysics.getSpeed() / timeToWait;
    QVERIFY(differenceIsCloseTo(initialPosition.x(),
                                finalPosition.x(),
                                mapPhysics.getSpeed() / (1000 / timeToWait),
                                allowedError));
}

bool MapPhysicsTest::differenceIsCloseTo(const qreal value1, const qreal value2, const int to)
{
    return differenceIsCloseTo(value1, value2, to, 0.00001);
}

bool MapPhysicsTest::differenceIsCloseTo(const qreal value1, const qreal value2, const int to, const double error)
{
    return fabs(fabs(value1 - value2) - to) <= error;
}

QTEST_MAIN(MapPhysicsTest)

#include "tst_MapPhysicsTest.moc"
