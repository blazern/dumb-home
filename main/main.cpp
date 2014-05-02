#include <QtGui/QGuiApplication>
#include <QQmlContext>
#include <QtQml>
#include <QQuickItem>
#include "cppsrc/qtquick2applicationviewer/qtquick2applicationviewer.h"
#include "cppsrc/PlayerActionsQmlReceiver.h"
#include "cppsrc/QmlMapInterface.h"
#include "cppsrc/map/DynamicMapObject.h"
#include "cppsrc/MapObjectQmlWrapper.h"

int main(int argc, char *argv[])
{
    qmlRegisterType<QmlMapInterface>("DumbHome", 1, 0, "QmlMapInterface");
    qmlRegisterType<MapObjectQmlWrapper>("DumbHome", 1, 0, "MapObjectQmlWrapper");

    QGuiApplication app(argc, argv);

    QtQuick2ApplicationViewer viewer;
    viewer.setMainQmlFile(QStringLiteral("qmlsrc/code-if-wanna-live/main.qml"));
    viewer.showExpanded();

    Map map(10, 10, 10);

    PlayerActionsQmlReceiver playerActionsQmlReceiver(map);
    viewer.rootContext()->setContextProperty("playerActionsReceiver", &playerActionsQmlReceiver);

    QmlMapInterface * const qmlMapInterface =
            viewer.rootObject()->findChild<QmlMapInterface*>("qmlMapInterface");

    if (qmlMapInterface != nullptr)
    {
        qmlMapInterface->setMap(map);
        map.addListener(*qmlMapInterface);
    }

    return app.exec();
}
