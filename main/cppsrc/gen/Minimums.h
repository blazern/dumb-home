#ifndef MAPMINIMUM_H
#define MAPMINIMUM_H

class Minimums
{
public:
    Minimums() = delete;

    static const int ROOM_WIDTH = 4;
    static const int ROOM_HEIGHT = 3;
    static const int MAP_WIDTH = ROOM_WIDTH + 2;
    static const int MAP_HEIGHT = ROOM_HEIGHT + 2;
    static const int STOREY_HEIGHT = ROOM_HEIGHT + 1;

    static const int STAIRS_WIDTH = 2;
};

#endif // MAPMINIMUM_H
