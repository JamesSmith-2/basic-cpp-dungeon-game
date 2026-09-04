#include "room.h"

Room::Room(RoomType type, const std::string& title, const std::string& description)
	: type(type), title(title), description(description)
{
}

RoomType Room::getType() const { return type; }
const std::string& Room::getTitle() const { return title; }
const std::string& Room::getDescription() const { return description; }
