#include "game.h"
#include <algorithm>
#include <chrono>
#include <iostream>
#include <limits>

Game::Game()
	: generator(static_cast<unsigned int>(
		  std::chrono::steady_clock::now().time_since_epoch().count()))
{
}

int Game::readChoice(int minimum, int maximum) const
{
	int choice;
	while (true)
	{
		std::cout << "> ";
		if (std::cin >> choice && choice >= minimum && choice <= maximum)
		{
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			return choice;
		}
		std::cout << "Choose a number from " << minimum << " to " << maximum << ".\n";
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	}
}

bool Game::promptYesNo(const std::string& prompt) const
{
	std::cout << prompt << " (1 yes, 2 no)\n";
	return readChoice(1, 2) == 1;
}

Adventurer Game::chooseAdventurer()
{
	std::cout << "Choose your adventurer:\n"
			  << "1. Fighter  - 32 health, strong attacks, 2 potions\n"
			  << "2. Wizard   - 22 health, devastating attacks, 3 potions\n"
			  << "3. Priest   - 27 health, steady attacks, 4 potions\n"
			  << "4. Performer - 25 health, balanced attacks, 3 potions\n";
	int choice = readChoice(1, 4);
	std::string role;
	int health;
	int attack;
	int defense;
	int potions;
	if (choice == 1) { role = "Fighter"; health = 32; attack = 9; defense = 4; potions = 2; }
	else if (choice == 2) { role = "Wizard"; health = 22; attack = 13; defense = 1; potions = 3; }
	else if (choice == 3) { role = "Priest"; health = 27; attack = 8; defense = 3; potions = 4; }
	else { role = "Performer"; health = 25; attack = 10; defense = 2; potions = 3; }

	std::string name;
	std::cout << "What is your name?\n> ";
	std::getline(std::cin, name);
	if (name.empty()) name = "Nameless Adventurer";
	return Adventurer(name, role, health, attack, defense, potions);
}

void Game::printStatus(const Adventurer& player) const
{
	std::cout << player.getName() << " the " << player.getRole()
			  << " | HP " << player.getHealth() << "/" << player.getMaxHealth()
			  << " | Potions " << player.getPotions() << "\n";
}

void Game::showRoom(const Room& room) const
{
	std::cout << "\n== " << room.getTitle() << " ==\n" << room.getDescription() << "\n";
}

void Game::combat(Adventurer& player, const std::string& enemy, int enemyHealth, int enemyAttack)
{
	std::uniform_int_distribution<int> variance(-2, 2);
	std::cout << "\n" << enemy << " attacks!\n";
	while (player.isAlive() && enemyHealth > 0)
	{
		printStatus(player);
		std::cout << enemy << " HP: " << enemyHealth << "\n"
				  << "1. Strike\n2. Drink a potion\n3. Inspect\n";
		int choice = readChoice(1, 3);
		if (choice == 1)
		{
			int damage = std::max(1, player.getAttack() + variance(generator));
			enemyHealth -= damage;
			std::cout << "You deal " << damage << " damage.\n";
		}
		else if (choice == 2)
		{
			if (!player.usePotion())
				std::cout << "You have no potions left.\n";
			else
				std::cout << "Warm light restores your strength.\n";
		}
		else
		{
			std::cout << enemy << " is dangerous, but its next attack is telegraphed.\n";
			continue;
		}
		if (enemyHealth > 0)
		{
			int damage = std::max(1, enemyAttack + variance(generator) - player.getDefense());
			player.takeDamage(damage);
			std::cout << enemy << " deals " << damage << " damage.\n";
		}
	}
	if (player.isAlive()) std::cout << enemy << " falls. The way forward is clear.\n";
}

void Game::exploreRoom(const Room& room, Adventurer& player)
{
	showRoom(room);
	if (room.getType() == RoomType::Entry)
	{
		std::cout << "A bronze plaque reads: 'Only those who keep moving leave.'\n";
	}
	else if (room.getType() == RoomType::SmallCombat)
	{
		if (promptYesNo("Search the fallen wardrobe?"))
		{
			player.heal(5);
			std::cout << "You find a healing herb and recover 5 HP.\n";
		}
		combat(player, "a tunnel rat", 18, 7);
	}
	else if (room.getType() == RoomType::MediumCombat)
	{
		if (promptYesNo("Read the glowing archive page?"))
			std::cout << "The page whispers a warning: the warden hates fire.\n";
		combat(player, "a drowned sentinel", 30, 9);
	}
	else if (room.getType() == RoomType::Rest)
	{
		player.heal(player.getMaxHealth());
		std::cout << "You rest beside the lantern and recover completely.\n";
		if (promptYesNo("Open the shrine chest?"))
			std::cout << "Inside is a charm that hardens your resolve.\n";
	}
	else
	{
		combat(player, "the dungeon warden", 45, 11);
	}
}

void Game::run()
{
	std::cout << "================================\n"
			  << "       THE LAST LANTERN         \n"
			  << "================================\n"
			  << "A five-room dungeon adventure\n\n";
	Adventurer player = chooseAdventurer();
	std::cout << "\n" << player.getName() << ", your lantern flickers to life.\n";
	const std::vector<Room>& rooms = dungeon.getRooms();
	exploreRoom(rooms[0], player);

	std::vector<int> middleRooms = {1, 2, 3};
	std::shuffle(middleRooms.begin(), middleRooms.end(), generator);
	for (int roomIndex : middleRooms)
	{
		if (!player.isAlive()) break;
		exploreRoom(rooms[roomIndex], player);
	}
	if (player.isAlive()) exploreRoom(rooms[4], player);
	if (player.isAlive())
		std::cout << "\nThe vault opens onto dawn. You saved the valley. Victory!\n";
	else
		std::cout << "\nYour lantern goes dark in the deep. The dungeon endures.\n";
}
