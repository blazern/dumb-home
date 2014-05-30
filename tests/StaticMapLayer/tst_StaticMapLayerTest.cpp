#include <QString>
#include <QtTest>
#include <QCoreApplication>

#include <stdexcept>
#include <QVector>
#include "../../main/cppsrc/logic/StaticMapLayer.h"

class StaticMapLayerTest : public QObject
{
    Q_OBJECT

public:
    StaticMapLayerTest();

private:
    bool isExceptionThrownDuringConstructionWith(QVector<QVector<StaticMapObject*>> objects);

private Q_SLOTS:
    void constructorThrowsIfStairsEndInAirOnBothSides();
    void constructorThrowsIfStairsEndHasWallOnlyOn1Side();
    void constructorDoesntThrowIfStairsEndIsNotInAir();
    void stairsMustNotBeOnEdgeOfMap();
    void stairsMustStartOnWall();
    void stairsMustEndBeneathAir();
};

StaticMapLayerTest::StaticMapLayerTest()
{
}

void StaticMapLayerTest::constructorThrowsIfStairsEndInAirOnBothSides()
{
    QVector<QVector<StaticMapObject*>> objects;

    objects.append(QVector<StaticMapObject*>());
    objects[0].append(new StaticMapObject(StaticMapObject::Type::AIR));
    objects[0].append(new StaticMapObject(StaticMapObject::Type::AIR));
    objects[0].append(new StaticMapObject(StaticMapObject::Type::AIR));
    objects[0].append(new StaticMapObject(StaticMapObject::Type::WALL));

    objects.append(QVector<StaticMapObject*>());
    objects[1].append(new StaticMapObject(StaticMapObject::Type::AIR));
    objects[1].append(new StaticMapObject(StaticMapObject::Type::STAIRS));
    objects[1].append(new StaticMapObject(StaticMapObject::Type::STAIRS));
    objects[1].append(new StaticMapObject(StaticMapObject::Type::WALL));

    objects.append(QVector<StaticMapObject*>());
    objects[2].append(new StaticMapObject(StaticMapObject::Type::AIR));
    objects[2].append(new StaticMapObject(StaticMapObject::Type::AIR));
    objects[2].append(new StaticMapObject(StaticMapObject::Type::AIR));
    objects[2].append(new StaticMapObject(StaticMapObject::Type::WALL));

    const bool exceptionThrown = isExceptionThrownDuringConstructionWith(objects);

    QVERIFY(exceptionThrown);
}

bool StaticMapLayerTest::isExceptionThrownDuringConstructionWith(QVector<QVector<StaticMapObject *> > objects)
{
    try
    {
        StaticMapLayer staticLayer(objects);
    }
    catch (std::invalid_argument &)
    {
        return true;
    }
    return false;
}

void StaticMapLayerTest::constructorThrowsIfStairsEndHasWallOnlyOn1Side()
{
    QVector<QVector<StaticMapObject*>> objects;

    objects.append(QVector<StaticMapObject*>());
    objects[0].append(new StaticMapObject(StaticMapObject::Type::AIR));
    objects[0].append(new StaticMapObject(StaticMapObject::Type::AIR));
    objects[0].append(new StaticMapObject(StaticMapObject::Type::AIR));
    objects[0].append(new StaticMapObject(StaticMapObject::Type::WALL));

    objects.append(QVector<StaticMapObject*>());
    objects[1].append(new StaticMapObject(StaticMapObject::Type::AIR));
    objects[1].append(new StaticMapObject(StaticMapObject::Type::STAIRS));
    objects[1].append(new StaticMapObject(StaticMapObject::Type::STAIRS));
    objects[1].append(new StaticMapObject(StaticMapObject::Type::WALL));

    objects.append(QVector<StaticMapObject*>());
    objects[2].append(new StaticMapObject(StaticMapObject::Type::AIR));
    objects[2].append(new StaticMapObject(StaticMapObject::Type::WALL));
    objects[2].append(new StaticMapObject(StaticMapObject::Type::AIR));
    objects[2].append(new StaticMapObject(StaticMapObject::Type::WALL));

    const bool exceptionThrown = isExceptionThrownDuringConstructionWith(objects);

    QVERIFY(exceptionThrown);
}

void StaticMapLayerTest::constructorDoesntThrowIfStairsEndIsNotInAir()
{
    QVector<QVector<StaticMapObject*>> objects;

    objects.append(QVector<StaticMapObject*>());
    objects[0].append(new StaticMapObject(StaticMapObject::Type::AIR));
    objects[0].append(new StaticMapObject(StaticMapObject::Type::WALL));
    objects[0].append(new StaticMapObject(StaticMapObject::Type::AIR));
    objects[0].append(new StaticMapObject(StaticMapObject::Type::WALL));

    objects.append(QVector<StaticMapObject*>());
    objects[1].append(new StaticMapObject(StaticMapObject::Type::AIR));
    objects[1].append(new StaticMapObject(StaticMapObject::Type::STAIRS));
    objects[1].append(new StaticMapObject(StaticMapObject::Type::STAIRS));
    objects[1].append(new StaticMapObject(StaticMapObject::Type::WALL));

    objects.append(QVector<StaticMapObject*>());
    objects[2].append(new StaticMapObject(StaticMapObject::Type::AIR));
    objects[2].append(new StaticMapObject(StaticMapObject::Type::WALL));
    objects[2].append(new StaticMapObject(StaticMapObject::Type::AIR));
    objects[2].append(new StaticMapObject(StaticMapObject::Type::WALL));

    const bool exceptionThrown = isExceptionThrownDuringConstructionWith(objects);

    QVERIFY(!exceptionThrown);
}

void StaticMapLayerTest::stairsMustNotBeOnEdgeOfMap()
{
    QVector<QVector<StaticMapObject*>> objects;

    objects.append(QVector<StaticMapObject*>());
    objects[0].append(new StaticMapObject(StaticMapObject::Type::AIR));
    objects[0].append(new StaticMapObject(StaticMapObject::Type::WALL));
    objects[0].append(new StaticMapObject(StaticMapObject::Type::AIR));
    objects[0].append(new StaticMapObject(StaticMapObject::Type::WALL));

    objects.append(QVector<StaticMapObject*>());
    objects[1].append(new StaticMapObject(StaticMapObject::Type::AIR));
    objects[1].append(new StaticMapObject(StaticMapObject::Type::STAIRS));
    objects[1].append(new StaticMapObject(StaticMapObject::Type::STAIRS));
    objects[1].append(new StaticMapObject(StaticMapObject::Type::WALL));

    const bool exceptionThrown = isExceptionThrownDuringConstructionWith(objects);

    QVERIFY(exceptionThrown);
}

void StaticMapLayerTest::stairsMustStartOnWall()
{
    QVector<QVector<StaticMapObject*>> objects;

    objects.append(QVector<StaticMapObject*>());
    objects[0].append(new StaticMapObject(StaticMapObject::Type::AIR));
    objects[0].append(new StaticMapObject(StaticMapObject::Type::WALL));
    objects[0].append(new StaticMapObject(StaticMapObject::Type::AIR));
    objects[0].append(new StaticMapObject(StaticMapObject::Type::WALL));

    objects.append(QVector<StaticMapObject*>());
    objects[1].append(new StaticMapObject(StaticMapObject::Type::AIR));
    objects[1].append(new StaticMapObject(StaticMapObject::Type::STAIRS));
    objects[1].append(new StaticMapObject(StaticMapObject::Type::STAIRS));
    objects[1].append(new StaticMapObject(StaticMapObject::Type::AIR));

    objects.append(QVector<StaticMapObject*>());
    objects[2].append(new StaticMapObject(StaticMapObject::Type::AIR));
    objects[2].append(new StaticMapObject(StaticMapObject::Type::WALL));
    objects[2].append(new StaticMapObject(StaticMapObject::Type::AIR));
    objects[2].append(new StaticMapObject(StaticMapObject::Type::WALL));

    const bool exceptionThrown = isExceptionThrownDuringConstructionWith(objects);

    QVERIFY(exceptionThrown);
}

void StaticMapLayerTest::stairsMustEndBeneathAir()
{
    QVector<QVector<StaticMapObject*>> objects;

    objects.append(QVector<StaticMapObject*>());
    objects[0].append(new StaticMapObject(StaticMapObject::Type::AIR));
    objects[0].append(new StaticMapObject(StaticMapObject::Type::WALL));
    objects[0].append(new StaticMapObject(StaticMapObject::Type::AIR));
    objects[0].append(new StaticMapObject(StaticMapObject::Type::WALL));

    objects.append(QVector<StaticMapObject*>());
    objects[1].append(new StaticMapObject(StaticMapObject::Type::WALL));
    objects[1].append(new StaticMapObject(StaticMapObject::Type::STAIRS));
    objects[1].append(new StaticMapObject(StaticMapObject::Type::STAIRS));
    objects[1].append(new StaticMapObject(StaticMapObject::Type::WALL));

    objects.append(QVector<StaticMapObject*>());
    objects[2].append(new StaticMapObject(StaticMapObject::Type::AIR));
    objects[2].append(new StaticMapObject(StaticMapObject::Type::WALL));
    objects[2].append(new StaticMapObject(StaticMapObject::Type::AIR));
    objects[2].append(new StaticMapObject(StaticMapObject::Type::WALL));

    const bool exceptionThrown = isExceptionThrownDuringConstructionWith(objects);

    QVERIFY(exceptionThrown);
}

QTEST_MAIN(StaticMapLayerTest)

#include "tst_StaticMapLayerTest.moc"
