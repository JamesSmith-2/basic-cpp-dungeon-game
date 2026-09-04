#include "adventurer.h"

Adventurer::Adventurer(const std::string& name, const std::string& role,
					   int maxHealth, int attack, int defense, int potions)
	: name(name), role(role), health(maxHealth), maxHealth(maxHealth),
	  attack(attack), defense(defense), potions(potions)
{
}

const std::string& Adventurer::getName() const { return name; }
const std::string& Adventurer::getRole() const { return role; }
int Adventurer::getHealth() const { return health; }
int Adventurer::getMaxHealth() const { return maxHealth; }
int Adventurer::getAttack() const { return attack; }
int Adventurer::getDefense() const { return defense; }
int Adventurer::getPotions() const { return potions; }
bool Adventurer::isAlive() const { return health > 0; }

void Adventurer::takeDamage(int damage)
{
	health -= damage;
	if (health < 0) health = 0;
}

void Adventurer::heal(int amount)
{
	health += amount;
	if (health > maxHealth) health = maxHealth;
}

bool Adventurer::usePotion()
{
	if (potions == 0 || !isAlive()) return false;
	--potions;
	heal(12);
	return true;
}
