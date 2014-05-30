#include <QString>
#include <QtTest>

#include <QSharedPointer>
#include <stdexcept>
#include "../../main/cppsrc/json/JsonMapParser.h"
#include "../../main/cppsrc/logic/StaticMapObject.h"

class JsonMapParserTest : public QObject
{
    Q_OBJECT

public:
    JsonMapParserTest();

private:
    const JsonMapParser mapParser;
    const QString validMapJson;
    const QString invalidMapJson;
    const QString mapWithStairsJson;

private:
    bool isWall(const StaticMapObject & staticMapObject) const;
    bool isAir(const StaticMapObject & staticMapObject) const;
    bool isStairs(const StaticMapObject & staticMapObject) const;

private Q_SLOTS:
    void testValidMapExistence();
    void testValidMapSizes();
    void testValidStaticObjectSizes();
    void testValidMapStaticLayer();
    void testValidMapPlayer();
    void testIvalidMapWithPlayerInsideOfWallThrows();
    void testStairsParsing();
};

JsonMapParserTest::JsonMapParserTest() :
    mapParser(),
    //represents:
    // xxxx
    // xoox
    // xopx
    // xxxx
    validMapJson(R"({ )"
                 R"( "player": { )"
                 R"(        "x": 20, )"
                 R"(        "y": 19, )"
                 R"(        "width": 10, )"
                 R"(        "height": 11 )"
                 R"(    },)"
                 R"(    "staticObjectWidth": 9, )"
                 R"(    "staticObjectHeight": 10, )"
                 R"(    "staticLayerWidth": 4, )"
                 R"(    "staticLayerHeight": 4, )"
                 R"(    "rows": [ { )"
                 R"(        "y":0, )"
                 R"(        "cells": [ )"
                 R"(            { "x":0 }, )"
                 R"(            { "x":1 }, )"
                 R"(            { "x":2 }, )"
                 R"(            { "x":3 } )"
                 R"(        ] }, { )"
                 R"(        "y":1, )"
                 R"(        "cells": [ )"
                 R"(            { "x":0 }, )"
                 R"(            { "x":3 } )"
                 R"(        ] }, { )"
                 R"(        "y":2, )"
                 R"(        "cells": [ )"
                 R"(            { "x":0 }, )"
                 R"(            { "x":3 } )"
                 R"(        ] }, { )"
                 R"(        "y":3, )"
                 R"(        "cells": [ )"
                 R"(            { "x":0 }, )"
                 R"(            { "x":1 }, )"
                 R"(            { "x":2 }, )"
                 R"(            { "x":3 } )"
                 R"(        ] }    ] )"
                 R"(} )"),
    //represents:
    // xxxxx
    // xoox
    // xopx
    // xxxx
    invalidMapJson(R"({ )"
                   R"(    "player": { )"
                   R"(        "x": 20, )"
                   R"(        "y": 19, )"
                   R"(        "width": 10, )"
                   R"(        "height": 11 )"
                   R"(    },)"
                   R"(  "staticObjectWidth": 9, )"
                   R"(  "staticObjectHeight": 10, )"
                   R"(    "staticLayerWidth": 4, )"
                   R"(    "staticLayerHeight": 4, )"
                   R"(    "rows": [ { )"
                   R"(        "y":0, )"
                   R"(        "cells": [ )"
                   R"(            { "x":0 }, )"
                   R"(            { "x":1 }, )"
                   R"(            { "x":2 }, )"
                   R"(            { "x":3 }, )"
                   R"(            { "x":4 } )"
                   R"(        ] }, { )"
                   R"(        "y":1, )"
                   R"(        "cells": [ )"
                   R"(            { "x":0 }, )"
                   R"(            { "x":3 } )"
                   R"(        ] }, { )"
                   R"(        "y":2, )"
                   R"(        "cells": [ )"
                   R"(            { "x":0 }, )"
                   R"(            { "x":3 } )"
                   R"(        ] }, { )"
                   R"(        "y":3, )"
                   R"(        "cells": [ )"
                   R"(            { "x":0 }, )"
                   R"(            { "x":1 }, )"
                   R"(            { "x":2 }, )"
                   R"(            { "x":3 } )"
                   R"(        ] }    ] )"
                   R"(} )"),
    //represents:
    // ooo
    // xsx
    // oso
    // xxx
    mapWithStairsJson(R"({ )"
                      R"( "player": { )"
                      R"(        "x": 10, )"
                      R"(        "y": 10, )"
                      R"(        "width": 10, )"
                      R"(        "height": 10 )"
                      R"(    },)"
                      R"(    "staticObjectWidth": 10, )"
                      R"(    "staticObjectHeight": 10, )"
                      R"(    "staticLayerWidth": 3, )"
                      R"(    "staticLayerHeight": 4, )"
                      R"(    "rows": [ { )"
                      R"(        "y":1, )"
                      R"(        "cells": [ )"
                      R"(            { "x":0, "type": "wall" }, )"
                      R"(            { "x":1, "type": "stairs" }, )"
                      R"(            { "x":2, "type": "wall" } )"
                      R"(        ] }, { )"
                      R"(        "y":2, )"
                      R"(        "cells": [ )"
                      R"(            { "x":1, "type": "stairs" } )"
                      R"(        ] }, { )"
                      R"(        "y":3, )"
                      R"(        "cells": [ )"
                      R"(            { "x":0, "type": "wall" }, )"
                      R"(            { "x":1, "type": "wall" }, )"
                      R"(            { "x":2, "type": "wall" } )"
                      R"(        ] }    ] )"
                      R"(} )")
{
}

void JsonMapParserTest::testValidMapExistence()
{
    const QSharedPointer<const Map> validMap = QSharedPointer<const Map>(mapParser.parseFromString(validMapJson));
    QVERIFY(validMap != nullptr);
}

void JsonMapParserTest::testValidMapSizes()
{
    const QSharedPointer<const Map> validMap = QSharedPointer<const Map>(mapParser.parseFromString(validMapJson));
    const StaticMapLayer & staticLayer = validMap->getStaticLayer();

    const int expectedWidth = 4;
    const int expectedHeight = 4;

    QVERIFY(staticLayer.getWidth() == expectedWidth);
    QVERIFY(staticLayer.getHeight() == expectedHeight);
}

void JsonMapParserTest::testValidStaticObjectSizes()
{
    const QSharedPointer<const Map> validMap = QSharedPointer<const Map>(mapParser.parseFromString(validMapJson));

    QVERIFY(validMap->getStaticMapObjectWidth() == 9);
    QVERIFY(validMap->getStaticMapObjectHeight() == 10);
}

void JsonMapParserTest::testValidMapStaticLayer()
{
    const QSharedPointer<const Map> validMap = QSharedPointer<const Map>(mapParser.parseFromString(validMapJson));
    const StaticMapLayer & staticLayer = validMap->getStaticLayer();

    // line0
    QVERIFY(isWall(staticLayer.get(0, 0)));
    QVERIFY(isWall(staticLayer.get(1, 0)));
    QVERIFY(isWall(staticLayer.get(2, 0)));
    QVERIFY(isWall(staticLayer.get(3, 0)));

    // line1
    QVERIFY(isWall(staticLayer.get(0, 1)));
    QVERIFY(isAir(staticLayer.get(1, 1)));
    QVERIFY(isAir(staticLayer.get(2, 1)));
    QVERIFY(isWall(staticLayer.get(3, 1)));

    // line2
    QVERIFY(isWall(staticLayer.get(0, 2)));
    QVERIFY(isAir(staticLayer.get(1, 2)));
    QVERIFY(isAir(staticLayer.get(2, 2)));
    QVERIFY(isWall(staticLayer.get(3, 2)));

    // line3
    QVERIFY(isWall(staticLayer.get(0, 3)));
    QVERIFY(isWall(staticLayer.get(1, 3)));
    QVERIFY(isWall(staticLayer.get(2, 3)));
    QVERIFY(isWall(staticLayer.get(3, 3)));
}

bool JsonMapParserTest::isWall(const StaticMapObject & staticMapObject) const
{
    return staticMapObject.getType() == StaticMapObject::Type::WALL;
}

bool JsonMapParserTest::isAir(const StaticMapObject & staticMapObject) const
{
    return staticMapObject.getType() == StaticMapObject::Type::AIR;
}

void JsonMapParserTest::testValidMapPlayer()
{
    const QSharedPointer<const Map> validMap = QSharedPointer<const Map>(mapParser.parseFromString(validMapJson));
    const DynamicMapLayer & dynamicLayer = validMap->getDynamicLayer();

    const QRectF & playerRect = dynamicLayer.getPlayer().getRect();

    QVERIFY(playerRect.x() == 20);
    QVERIFY(playerRect.y() == 19);
    QVERIFY(playerRect.width() == 10);
    QVERIFY(playerRect.height() == 11);
}

void JsonMapParserTest::testIvalidMapWithPlayerInsideOfWallThrows()
{
    bool exceptionThrown = false;

    try
    {
        const QSharedPointer<const Map> invalidValidMap =
                QSharedPointer<const Map>(mapParser.parseFromString(invalidMapJson));
    }
    catch (const std::invalid_argument &)
    {
        exceptionThrown = true;
    }

    QVERIFY(exceptionThrown);
}

void JsonMapParserTest::testStairsParsing()
{
    const QSharedPointer<const Map> mapWithStairs = QSharedPointer<const Map>(mapParser.parseFromString(mapWithStairsJson));
    const StaticMapLayer & staticLayer = mapWithStairs->getStaticLayer();

    QVERIFY(isStairs(staticLayer.get(1, 1)));
    QVERIFY(isStairs(staticLayer.get(1, 2)));
}

bool JsonMapParserTest::isStairs(const StaticMapObject & staticMapObject) const
{
    return staticMapObject.getType() == StaticMapObject::Type::STAIRS;
}

QTEST_MAIN(JsonMapParserTest)

#include "tst_JsonMapParserTest.moc"
