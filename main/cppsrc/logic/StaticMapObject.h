#ifndef STATICMAPOBJECT_H
#define STATICMAPOBJECT_H

#include <QPoint>

class StaticMapObject
{
public:
    enum class Type { AIR, WALL, STAIRS };

    explicit StaticMapObject(const Type type) : type(type) {}
    Type getType() const { return type; }

private:
    const Type type;
};

#endif // STATICMAPOBJECT_H
