#include <QString>
#include <QtTest>
#include <QCoreApplication>
#include <stdexcept>
#include <QVector>
#include <QPoint>

#include "../../main/cppsrc/logic/StaticMapObject.h"
#include "../../main/cppsrc/gen/StoreyGenerator.h"

class StoreyGeneratorTest : public QObject
{
    Q_OBJECT

public:
    StoreyGeneratorTest();

private:
    QVector<QVector<StaticMapObject *> > createEmptyStaticObjects(const int right, const int bottom) const;
    bool doesContainNullptr(const QVector<QVector<StaticMapObject *> > & staticObjects) const;
    bool doesLineHasOnlyWallAndStairs(const int y, const QVector<QVector<StaticMapObject *> > & staticObjects) const;
    int getRoomsCount(const QVector<QVector<StaticMapObject *> > & staticObjects, const int top, const int bottom) const;
    bool hasWallsOnSides(const QVector<QVector<StaticMapObject *> > & staticObjects) const;
    bool hasSingleStairsWhichAreCorrect(const QVector<QVector<StaticMapObject *> > & staticObjects) const;
    QVector<QPoint> getStairsWithTopLeftAtPositionToVector(const int leftX,
                                                           const int topY,
                                                           const QVector<QVector<StaticMapObject *> > & staticObjects) const;

private Q_SLOTS:
    void testContainsNoNullptr();
    void testBottomHasOnlyWallAndStairs();
    void testRoomsCountIsCorrect_data();
    void testRoomsCountIsCorrect();
    void testStoreyHasWallsOnSides();
};

StoreyGeneratorTest::StoreyGeneratorTest()
{
}

void StoreyGeneratorTest::testContainsNoNullptr()
{
    const int top = 0;
    const int bottom = 5;
    const int right = 10;
    StoreyGenerator storeyGenerator(top, bottom, right + 1);
    QVector<QVector<StaticMapObject *> > staticObjects = createEmptyStaticObjects(right, bottom);

    storeyGenerator.generate(staticObjects);

    QVERIFY(!doesContainNullptr(staticObjects));
}

QVector<QVector<StaticMapObject *> > StoreyGeneratorTest::createEmptyStaticObjects(const int right, const int bottom) const
{
    QVector<QVector<StaticMapObject *> > staticObjects;
    for (int x = 0; x <= right; x++)
    {
        staticObjects.append(QVector<StaticMapObject *>());
        for (int y = 0; y <= bottom; y++)
        {
            staticObjects[x].append(nullptr);
        }
    }

    return staticObjects;
}

bool StoreyGeneratorTest::doesContainNullptr(const QVector<QVector<StaticMapObject *> > & staticObjects) const
{
    for (int x = 0; x < staticObjects.size(); x++)
    {
        for (int y = 0; y < staticObjects[x].size(); y++)
        {
            if (staticObjects[x][y] == nullptr)
            {
                return true;
            }
        }
    }
    return false;
}

void StoreyGeneratorTest::testBottomHasOnlyWallAndStairs()
{
    const int top = 0;
    const int bottom = 5;
    const int right = 10;
    StoreyGenerator storeyGenerator(top, bottom, right + 1);
    QVector<QVector<StaticMapObject *> > staticObjects = createEmptyStaticObjects(right, bottom);

    storeyGenerator.generate(staticObjects);

    QVERIFY(doesLineHasOnlyWallAndStairs(bottom, staticObjects));
}

bool StoreyGeneratorTest::doesLineHasOnlyWallAndStairs(const int y, const QVector<QVector<StaticMapObject *> > & staticObjects) const
{
    for (int x = 0; x < staticObjects.size(); x++)
    {
        if (staticObjects[x][y]->getType() != StaticMapObject::Type::STAIRS
            && staticObjects[x][y]->getType() != StaticMapObject::Type::WALL)
        {
            return false;
        }
    }
    return true;
}

void StoreyGeneratorTest::testRoomsCountIsCorrect_data()
{
    QTest::addColumn<int>("roomsCount");
    QTest::addColumn<int>("right");

    QTest::newRow("roomsCount: 5, right: 30") << 5 << 30;
    QTest::newRow("roomsCount: 2, right: 30") << 2 << 30;
    QTest::newRow("roomsCount: 5, right: 30") << 5 << 30;
    QTest::newRow("roomsCount: 50, right: 300") << 50 << 300;
    QTest::newRow("roomsCount: 1, right: 6") << 1 << 6;
    QTest::newRow("roomsCount: 1, right: 30") << 1 << 30;
}

void StoreyGeneratorTest::testRoomsCountIsCorrect()
{
    QFETCH(int, roomsCount);
    QFETCH(int, right);

    const int top = 0;
    const int bottom = 5;
    StoreyGenerator storeyGenerator(top, bottom, right + 1, roomsCount);
    QVector<QVector<StaticMapObject *> > staticObjects = createEmptyStaticObjects(right, bottom);

    storeyGenerator.generate(staticObjects);

    const int actualRoomsCount = getRoomsCount(staticObjects, top, bottom);

    QVERIFY(roomsCount == actualRoomsCount);
}

int StoreyGeneratorTest::getRoomsCount(const QVector<QVector<StaticMapObject *> > & staticObjects, const int top, const int bottom) const
{
    int roomsCount = 1;
    for (int x = 1; x < staticObjects.size() - 1; x++)
    {
        if (staticObjects[x][bottom - 1]->getType() != StaticMapObject::Type::AIR
            && staticObjects[x][bottom - 2]->getType() != StaticMapObject::Type::AIR)
        {
            continue;
        }

        for (int y = bottom - 3; y >= top; y--)
        {
            if (staticObjects[x][y]->getType() != StaticMapObject::Type::WALL)
            {
                break;
            }
            if (y == top)
            {
                roomsCount++;
            }
        }
    }
    return roomsCount;
}

void StoreyGeneratorTest::testStoreyHasWallsOnSides()
{
    const int top = 0;
    const int bottom = 5;
    const int right = 10;
    StoreyGenerator storeyGenerator(top, bottom, right + 1);
    QVector<QVector<StaticMapObject *> > staticObjects = createEmptyStaticObjects(right, bottom);

    storeyGenerator.generate(staticObjects);

    QVERIFY(hasWallsOnSides(staticObjects));
}

bool StoreyGeneratorTest::hasWallsOnSides(const QVector<QVector<StaticMapObject *> > & staticObjects) const
{
    for (int y = 0; y < staticObjects[0].size(); y++)
    {
        if (staticObjects[0][y]->getType() != StaticMapObject::Type::WALL)
        {
            return false;
        }
    }
    for (int y = 0; y < staticObjects[staticObjects.size() - 1].size(); y++)
    {
        if (staticObjects[staticObjects.size() - 1][y]->getType() != StaticMapObject::Type::WALL)
        {
            return false;
        }
    }

    return true;
}

QTEST_MAIN(StoreyGeneratorTest)

#include "tst_StoreyGeneratorTest.moc"
