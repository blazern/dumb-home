#ifndef STATICMAPOBJECT_H
#define STATICMAPOBJECT_H

#include <QPoint>

class StaticMapObject
{
    friend class QVector<StaticMapObject>;
public:
    virtual ~StaticMapObject(){}

protected:
    explicit StaticMapObject(){}
};

#endif // STATICMAPOBJECT_H
