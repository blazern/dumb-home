#ifndef QMLMAPINTERFACE_H
#define QMLMAPINTERFACE_H

#include <QObject>
#include "MapListener.h"
#include "Map.h"

class QmlMapInterface : public QObject, public MapListener
{
    Q_OBJECT
    Q_DISABLE_COPY(QmlMapInterface)
public:
    explicit QmlMapInterface(QObject * parent = 0);

    void setMap(const Map & map);

    Q_INVOKABLE float getPlayerPositionX() const;
    Q_INVOKABLE float getPlayerPositionY() const;
    Q_INVOKABLE int getWidth() const;
    Q_INVOKABLE int getHeight() const;
    Q_INVOKABLE bool isMapSetUp() const;

    virtual void onPlayerChangedPosition(const QPointF & position) final override;

signals:
    void playerChangePosition(const qreal x, const qreal y) const;
    void mapSetUp() const;

private:
    const Map * map;
};

#endif // QMLMAPINTERFACE_H
