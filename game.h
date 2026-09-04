#ifndef GAME_H
#ifndef GAME_H
#define GAME_H

#include "adventurer.h"
#include "dungeon.h"
#include <random>

class Game
{
public:
    Game();
    void run();

private:
    Adventurer chooseAdventurer();
    void showRoom(const Room& room) const;
    void exploreRoom(const Room& room, Adventurer& player);
    void combat(Adventurer& player, const std::string& enemy, int health, int attack);
    bool promptYesNo(const std::string& prompt) const;
    int readChoice(int minimum, int maximum) const;
    void printStatus(const Adventurer& player) const;

    Dungeon dungeon;
    std::mt19937 generator;
};

#endif