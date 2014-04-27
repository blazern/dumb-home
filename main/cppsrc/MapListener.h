#ifndef MAPLISTENER_H
#define MAPLISTENER_H

#include <QPointF>

class MapListener
{
public:
    virtual void onPlayerChangedPosition(const QPointF & position) = 0;
};

#endif // MAPLISTENER_H
