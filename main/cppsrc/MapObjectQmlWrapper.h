#ifndef MAPOBJECTQMLWRAPPER_H
#define MAPOBJECTQMLWRAPPER_H

#include <QObject>
#include <QColor>
#include "map/DynamicMapObject.h"
#include "map/StaticMapObject.h"


class MapObjectQmlWrapper : public QObject
{
    Q_OBJECT
    Q_DISABLE_COPY(MapObjectQmlWrapper)
public:
    Q_PROPERTY(unsigned int id READ getId CONSTANT FINAL)
    Q_PROPERTY(QColor color READ getColor CONSTANT FINAL)
    Q_PROPERTY(qreal x READ getX FINAL)
    Q_PROPERTY(qreal y READ getY FINAL)
    Q_PROPERTY(qreal width READ getWidth FINAL)
    Q_PROPERTY(qreal height READ getHeight FINAL)

    explicit MapObjectQmlWrapper(QObject * parent = 0); // required by QML
    explicit MapObjectQmlWrapper(const DynamicMapObject & dynamicMapObject, QObject * parent = 0);
    explicit MapObjectQmlWrapper(const StaticMapObject & staticMapObject,
                                 const qreal width,
                                 const qreal height,
                                 QObject * parent = 0);

    unsigned int getId() const;
    const QColor & getColor() const;
    qreal getX() const;
    qreal getY() const;
    qreal getWidth() const;
    qreal getHeight() const;

    bool isMadeFor(const DynamicMapObject & mapObject) const;

private:
    static unsigned int nextId;

private:
    const unsigned int id;
    const QColor color;
    const DynamicMapObject * const dynamicMapObject;
    const StaticMapObject * const staticMapObject;
    const qreal width;
    const qreal height;
};

#endif // MAPOBJECTQMLWRAPPER_H
