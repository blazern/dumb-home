#include <QString>
#include <QtTest>

#include <QSharedPointer>
#include <stdexcept>
#include "../../main/cppsrc/json/JsonMapParser.h"
#include "../../main/cppsrc/map/Wall.h"
#include "../../main/cppsrc/map/Air.h"

class JsonMapParserTest : public QObject
{
    Q_OBJECT

public:
    JsonMapParserTest();

private:
    const JsonMapParser mapParser;
    const QString validMapJson;
    const QString invalidMapJson;

private:
    bool isWall(const StaticMapObject & staticMapObject) const;
    bool isAir(const StaticMapObject & staticMapObject) const;

private Q_SLOTS:
    void testValidMapExistence();
    void testValidMapSizes();
    void testValidStaticObjectSizes();
    void testValidMapStaticLayer();
    void testValidMapPlayer();
    void testIvalidMapWithPlayerInsideOfWallThrows();
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
                   R"(} )")
{
}

void JsonMapParserTest::testValidMapExistence()
{
    const QSharedPointer<const Map> validMap = QSharedPointer<const Map>(mapParser.parseJson(validMapJson));
    QVERIFY(validMap != nullptr);
}

void JsonMapParserTest::testValidMapSizes()
{
    const QSharedPointer<const Map> validMap = QSharedPointer<const Map>(mapParser.parseJson(validMapJson));
    const StaticMapLayer & staticLayer = validMap->getStaticLayer();

    const int expectedWidth = 4;
    const int expectedHeight = 4;

    QVERIFY(staticLayer.getWidth() == expectedWidth);
    QVERIFY(staticLayer.getHeight() == expectedHeight);
}

void JsonMapParserTest::testValidStaticObjectSizes()
{
    const QSharedPointer<const Map> validMap = QSharedPointer<const Map>(mapParser.parseJson(validMapJson));

    QVERIFY(validMap->getStaticMapObjectWidth() == 9);
    QVERIFY(validMap->getStaticMapObjectHeight() == 10);
}

void JsonMapParserTest::testValidMapStaticLayer()
{
    const QSharedPointer<const Map> validMap = QSharedPointer<const Map>(mapParser.parseJson(validMapJson));
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
    return dynamic_cast<const Wall*>(&staticMapObject) != nullptr;
}

bool JsonMapParserTest::isAir(const StaticMapObject & staticMapObject) const
{
    return dynamic_cast<const Air*>(&staticMapObject) != nullptr;
}

void JsonMapParserTest::testValidMapPlayer()
{
    const QSharedPointer<const Map> validMap = QSharedPointer<const Map>(mapParser.parseJson(validMapJson));
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
                QSharedPointer<const Map>(mapParser.parseJson(invalidMapJson));
    }
    catch (const std::invalid_argument &)
    {
        exceptionThrown = true;
    }

    QVERIFY(exceptionThrown);
}

QTEST_MAIN(JsonMapParserTest)

#include "tst_JsonMapParserTest.moc"
