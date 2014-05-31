#ifndef MAPOBJECTQMLWRAPPER_H
#define MAPOBJECTQMLWRAPPER_H

#include <QObject>
#include <QColor>
#include "logic/DynamicMapObject.h"
#include "logic/StaticMapObject.h"


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
                                 const QRectF & rect,
                                 const QColor & color,
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
    const qreal staticObjectX;
    const qreal staticObjectY;
};

#endif // MAPOBJECTQMLWRAPPER_H
