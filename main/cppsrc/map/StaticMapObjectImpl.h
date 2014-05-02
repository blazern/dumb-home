#ifndef STATICMAPOBJECTIMPL_H
#define STATICMAPOBJECTIMPL_H

#include <QPoint>
#include "StaticMapObject.h"

class StaticMapObjectImpl : public StaticMapObject
{
public:
    StaticMapObjectImpl(const QPoint & position);

    virtual const QPoint & getPosition() const final override;

private:
    const QPoint position;
};

#endif // STATICMAPOBJECTIMPL_H
