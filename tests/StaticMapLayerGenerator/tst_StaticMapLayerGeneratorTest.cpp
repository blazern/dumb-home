#include <QString>
#include <QtTest>

#include "../../main/cppsrc/logic/StaticMapLayer.h"
#include "../../main/cppsrc/gen/StaticMapLayerGenerator.h"

class StaticMapLayerGeneratorTest : public QObject
{
    Q_OBJECT

public:
    StaticMapLayerGeneratorTest();

private:
    int getStoreysCount(const StaticMapLayer & staticLayer) const;

private Q_SLOTS:
    void testGeneratedLayerHasCorrectSize();
    void testSidesTopBottomAreWalls();
    void testStoreysCountIsCorrect();
};

StaticMapLayerGeneratorTest::StaticMapLayerGeneratorTest()
{
}

void StaticMapLayerGeneratorTest::testGeneratedLayerHasCorrectSize()
{
    const int width = 10;
    const int height = 20;
    StaticMapLayerGenerator generator(width, height);
    StaticMapLayer * staticLayer = generator.generate();

    QVERIFY(staticLayer->getWidth() == width);
    QVERIFY(staticLayer->getHeight() == height);

    delete staticLayer;
}

void StaticMapLayerGeneratorTest::testSidesTopBottomAreWalls()
{
    const int width = 10;
    const int height = 20;
    StaticMapLayerGenerator generator(width, height);
    StaticMapLayer * staticLayer = generator.generate();

    const int top = 0;
    const int bottom = staticLayer->getHeight() - 1;
    for (int x = 0; x < staticLayer->getWidth(); x++)
    {
        QVERIFY(staticLayer->get(x, top).getType() == StaticMapObject::Type::WALL);
        QVERIFY(staticLayer->get(x, bottom).getType() == StaticMapObject::Type::WALL);
    }

    const int left = 0;
    const int right = staticLayer->getWidth() - 1;
    for (int y = 0; y < staticLayer->getHeight(); y++)
    {
        QVERIFY(staticLayer->get(left, y).getType() == StaticMapObject::Type::WALL);
        QVERIFY(staticLayer->get(right, y).getType() == StaticMapObject::Type::WALL);
    }

    delete staticLayer;
}

void StaticMapLayerGeneratorTest::testStoreysCountIsCorrect()
{
    const int width = 10;
    const int height = 50;
    const int storeysCount = 5;
    StaticMapLayerGenerator generator(width, height, storeysCount);
    StaticMapLayer * staticLayer = generator.generate();

    const int actualStoreysCount = getStoreysCount(*staticLayer);

    QVERIFY(storeysCount == actualStoreysCount);
    delete staticLayer;
}

int StaticMapLayerGeneratorTest::getStoreysCount(const StaticMapLayer & staticLayer) const
{
    int storeysCount = 1;
    for (int y = 1; y < staticLayer.getHeight() - 1; y++)
    {
        bool isStoreysBottom = true;
        for (int x = 0; x < staticLayer.getWidth(); x++)
        {
            if (staticLayer.get(x, y).getType() != StaticMapObject::Type::WALL
                && staticLayer.get(x, y).getType() != StaticMapObject::Type::STAIRS)
            {
                isStoreysBottom = false;
                break;
            }
        }
        if (isStoreysBottom)
        {
            storeysCount++;
        }
    }

    return storeysCount;
}

QTEST_MAIN(StaticMapLayerGeneratorTest)

#include "tst_StaticMapLayerGeneratorTest.moc"
