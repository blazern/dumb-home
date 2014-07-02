#include <QString>
#include <QtTest>
#include <QCoreApplication>
#include <stdexcept>

#include "../../main/cppsrc/logic/StaticMapObject.h"
#include "../../main/cppsrc/gen/RoomGenerator.h"

class RoomGeneratorTest : public QObject
{
    Q_OBJECT

public:
    RoomGeneratorTest();

private:
    QVector<QVector<StaticMapObject *> > createEmptyStaticObjects(const int right, const int bottom) const;
    bool doesContainOnlyAir(const QVector<QVector<StaticMapObject *> > & staticObjects) const;

private Q_SLOTS:
    void testEmptyRoomGeneratorGeneratesAir();
    void testTooSmallWidthThrows();
    void testTooSmallHeightThrows();
};

RoomGeneratorTest::RoomGeneratorTest()
{
}

void RoomGeneratorTest::testEmptyRoomGeneratorGeneratesAir()
{
    const int left = 0;
    const int top = 0;
    const int right = 5;
    const int bottom = 5;
    RoomGenerator roomGenerator(left, top, right, bottom);

    QVector<QVector<StaticMapObject *> > staticObjects = createEmptyStaticObjects(right, bottom);

    roomGenerator.generate(staticObjects);

    QVERIFY(doesContainOnlyAir(staticObjects));
}

QVector<QVector<StaticMapObject *> > RoomGeneratorTest::createEmptyStaticObjects(const int right, const int bottom) const
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

bool RoomGeneratorTest::doesContainOnlyAir(const QVector<QVector<StaticMapObject *> > & staticObjects) const
{
    for (int x = 0; x < staticObjects.size(); x++)
    {
        for (int y = 0; y < staticObjects[x].size(); y++)
        {
            if (staticObjects[x][y] == nullptr
                || staticObjects[x][y]->getType() != StaticMapObject::Type::AIR)
            {
                return false;
            }
        }
    }
    return true;
}

void RoomGeneratorTest::testTooSmallWidthThrows()
{
    const int left = 0;
    const int top = 0;
    const int right = 2;
    const int bottom = 5;

    bool thrown = false;
    try
    {
        RoomGenerator roomGenerator(left, top, right, bottom);
    }
    catch (const std::invalid_argument & e)
    {
        thrown = true;
    }
    QVERIFY(thrown);
}

void RoomGeneratorTest::testTooSmallHeightThrows()
{
    const int left = 0;
    const int top = 0;
    const int right = 5;
    const int bottom = 1;

    bool thrown = false;
    try
    {
        RoomGenerator roomGenerator(left, top, right, bottom);
    }
    catch (const std::invalid_argument & e)
    {
        thrown = true;
    }
    QVERIFY(thrown);
}

QTEST_MAIN(RoomGeneratorTest)

#include "tst_RoomGeneratorTest.moc"
