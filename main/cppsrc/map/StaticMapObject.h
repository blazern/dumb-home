#ifndef STATICMAPOBJECT_H
#define STATICMAPOBJECT_H

#include <QPoint>

class StaticMapObject
{
public:
    virtual const QPoint & getPosition() const = 0;
    virtual ~StaticMapObject(){}
};

#endif // STATICMAPOBJECT_H
