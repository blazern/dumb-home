#include "StaticMapObjectImpl.h"

StaticMapObjectImpl::StaticMapObjectImpl(const QPoint & position) :
    position(position)
{
}

const QPoint & StaticMapObjectImpl::getPosition() const
{
    return position;
}
