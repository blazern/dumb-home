#include <QtGui/QGuiApplication>
#include <QQmlContext>
#include <QtQml>
#include <QQuickItem>
#include <QUrl>
#include <QDir>
#include "cppsrc/qtquick2applicationviewer/qtquick2applicationviewer.h"
#include "cppsrc/PlayerActionsQmlReceiver.h"
#include "cppsrc/QmlMapInterface.h"
#include "cppsrc/map/DynamicMapObject.h"
#include "cppsrc/MapObjectQmlWrapper.h"
#include "cppsrc/json/JsonMapParser.h"

#ifdef QT_DEBUG
#include <QDebug>
#endif

int main(int argc, char *argv[])
{
    qmlRegisterType<QmlMapInterface>("DumbHome", 1, 0, "QmlMapInterface");
    qmlRegisterType<MapObjectQmlWrapper>("DumbHome", 1, 0, "MapObjectQmlWrapper");

    QGuiApplication app(argc, argv);

    QtQuick2ApplicationViewer viewer;
    viewer.setMainQmlFile(QStringLiteral("qmlsrc/code-if-wanna-live/main.qml"));
    viewer.showExpanded();

    const JsonMapParser mapParser;

    const QUrl defaultUrl(QUrl::fromLocalFile(QString() + "resources" + QDir::separator() + "map.json"));

    QSharedPointer<Map> map;

    try
    {
        map.reset(mapParser.parse(defaultUrl));
    }
    catch (std::invalid_argument & exception)
    {
        qDebug() << exception.what();
        return -1;
    }

    PlayerActionsQmlReceiver playerActionsQmlReceiver(*map);
    viewer.rootContext()->setContextProperty("playerActionsReceiver", &playerActionsQmlReceiver);

    QmlMapInterface * const qmlMapInterface =
            viewer.rootObject()->findChild<QmlMapInterface*>("qmlMapInterface");

    if (qmlMapInterface != nullptr)
    {
        qmlMapInterface->setMap(*map);
        map->addListener(*qmlMapInterface);
    }

    return app.exec();
}
