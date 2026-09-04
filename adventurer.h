#ifndef ADVENTURER_H
#define ADVENTURER_H

#include <string>

class Adventurer
{
public:
    Adventurer(const std::string& name, const std::string& role, int maxHealth,
               int attack, int defense, int potions);

    const std::string& getName() const;
    const std::string& getRole() const;
    int getHealth() const;
    int getMaxHealth() const;
    int getAttack() const;
    int getDefense() const;
    int getPotions() const;
    bool isAlive() const;
    void takeDamage(int damage);
    void heal(int amount);
    bool usePotion();

private:
    std::string name;
    std::string role;
    int health;
    int maxHealth;
    int attack;
    int defense;
    int potions;
};

#endif