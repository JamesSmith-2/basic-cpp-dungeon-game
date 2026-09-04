#ifndef ROOM_H
#ifndef ROOM_H
#define ROOM_H

#include <string>

enum class RoomType { Entry, SmallCombat, MediumCombat, Rest, Boss };

class Room
{
public:
    Room(RoomType type, const std::string& title, const std::string& description);
    RoomType getType() const;
    const std::string& getTitle() const;
    const std::string& getDescription() const;

private:
    RoomType type;
    std::string title;
    std::string description;
};

#endif