#ifndef DUNGEON_H
#ifndef DUNGEON_H
#define DUNGEON_H

#include "room.h"
#include <vector>

class Dungeon
{
public:
    Dungeon();
    const std::vector<Room>& getRooms() const;

private:
    std::vector<Room> rooms;
};

#endif