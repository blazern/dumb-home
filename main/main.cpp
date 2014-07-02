#include <QtGui/QGuiApplication>
#include <QQmlContext>
#include <QtQml>
#include <QQuickItem>
#include <QUrl>
#include <QDir>
#include <QTime>
#include <QStringList>
#include "cppsrc/qtquick2applicationviewer/qtquick2applicationviewer.h"
#include "cppsrc/PlayerActionsQmlReceiver.h"
#include "cppsrc/QmlMapInterface.h"
#include "cppsrc/logic/DynamicMapObject.h"
#include "cppsrc/MapObjectQmlWrapper.h"
#include "cppsrc/json/JsonMapParser.h"
#include "cppsrc/logic/MapPhysics.h"
#include "cppsrc/logic/World.h"
#include "cppsrc/gen/StaticMapLayerGenerator.h"

#ifdef QT_DEBUG
#include <QDebug>
#endif

Map * createMap()
{
    const QStringList arguments = QGuiApplication::arguments();
    bool shouldReadMapFromFile = false;

    if (arguments.size() > 1 && arguments[1] == "--from_file")
    {
        shouldReadMapFromFile = true;
    }

    try
    {
        if (shouldReadMapFromFile)
        {
            const JsonMapParser mapParser;
            return mapParser.parseFromFile(":/map.json");
        }
        else
        {
            StaticMapLayerGenerator generator(30, 20);
            StaticMapLayer * staticLayer = generator.generate();
            DynamicMapLayer * dynamicLayer = new DynamicMapLayer(QRectF(20, 20, 10, 10));
            return new Map(staticLayer, dynamicLayer, 10, 10);
        }
    }
    catch (std::invalid_argument & exception)
    {
        qDebug() << "Application is going to crash because of an unhandled Map parsing exception: " << exception.what();
        throw;
    }
}

int main(int argc, char * argv[])
{
    qsrand(QTime::currentTime().msec());

    qmlRegisterType<QmlMapInterface>("DumbHome", 1, 0, "QmlMapInterface");
    qmlRegisterType<MapObjectQmlWrapper>("DumbHome", 1, 0, "MapObjectQmlWrapper");

    QGuiApplication app(argc, argv);

    QtQuick2ApplicationViewer viewer;
    viewer.setMainQmlFile(QStringLiteral("qmlsrc/code-if-wanna-live/main.qml"));
    viewer.showExpanded();

    Map * const map = createMap();
    World world(map, new MapPhysics(*map));

    PlayerActionsQmlReceiver playerActionsQmlReceiver(world.getMap());
    viewer.rootContext()->setContextProperty("playerActionsReceiver", &playerActionsQmlReceiver);

    QmlMapInterface * const qmlMapInterface =
            viewer.rootObject()->findChild<QmlMapInterface*>("qmlMapInterface");

    if (qmlMapInterface != nullptr)
    {
        qmlMapInterface->setMap(world.getMap());
        world.getMapPhysics().addListener(*qmlMapInterface);
    }

    return app.exec();
}
