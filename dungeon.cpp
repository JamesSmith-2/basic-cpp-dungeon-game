#include "dungeon.h"

Dungeon::Dungeon()
{
	rooms.emplace_back(RoomType::Entry, "The Threshold",
		"A rusted gate groans open. Cold air carries the smell of rain and old stone.");
	rooms.emplace_back(RoomType::SmallCombat, "The Collapsed Gallery",
		"Broken statues line a gallery where something small and hungry watches from the rubble.");
	rooms.emplace_back(RoomType::MediumCombat, "The Flooded Archive",
		"Half-submerged shelves form narrow paths through a chamber humming with hostile magic.");
	rooms.emplace_back(RoomType::Rest, "The Lantern Shrine",
		"A blue lantern burns beside a dry camp and a locked chest. The dungeon is quiet here.");
	rooms.emplace_back(RoomType::Boss, "The Warden's Vault",
		"A stone throne rises from a ring of runes. The dungeon warden stands and draws its blade.");
}

const std::vector<Room>& Dungeon::getRooms() const { return rooms; }
