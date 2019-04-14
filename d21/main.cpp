#include <iostream>
#include <fstream>
#include <sstream>
#include <chrono>
#include <vector>
#include <cmath>
#include <limits>

/*** OUTPUT ***

    Least: 78
    Most: 148
    Time taken: 0.001s
 
 ***/

struct Unit {
    std::string name;
    int32_t hp;
    int32_t damage;
    int32_t armor;
};

struct Item {
    std::string name;
    int32_t cost;
    int32_t damage;
    int32_t armor;
};

std::vector<Item> weapons = {
    Item{ "Dagger", 8, 4, 0 },
    Item{ "Shortsword", 10, 5, 0 },
    Item{ "Warhammer", 25, 6, 0 },
    Item{ "Longsword", 40, 7, 0 },
    Item{ "Greataxe", 74, 8, 0 },
};

std::vector<Item> armor = {
    Item{ "Leather", 13, 0, 1 },
    Item{ "Chainmail", 31, 0, 2 },
    Item{ "Splintmail", 53, 0, 3 },
    Item{ "Bandedmail", 75, 0, 4 },
    Item{ "Platemail", 102, 0, 5 },
};

std::vector<Item> rings = {
    Item{ "Damage +1", 25, 1, 0 },
    Item{ "Damage +2", 50, 2, 0 },
    Item{ "Damage +3", 100, 3, 0 },
    Item{ "Defense +1", 20, 0, 1 },
    Item{ "Defense +2", 40, 0, 2 },
    Item{ "Defense +3", 80, 0, 3 },
};

void P1(std::istream& input);
void P2(std::istream& input);
void equip(Unit& unit, const Item& item);
void unequip(Unit& unit, const Item& item);
bool playerWins(const Unit& player, const Unit& boss);
bool playerWinsSimulation(Unit& player, Unit& boss);

int main() {
    auto start = std::chrono::steady_clock::now();

    std::ifstream infile("input.txt");

    // std::cout.setstate(std::ios::failbit);

    // P1(test2);
    P1(infile);

    infile.clear();
    infile.seekg(0);
    // P2(test2);
    P2(infile);

    // std::cout.clear();

    auto end = std::chrono::steady_clock::now();
    std::cout << "Time taken: " 
		<< std::chrono::duration_cast<std::chrono::duration<double>>(end - start).count()
		<< "s" << std::endl;
}

void P1(std::istream& input) {

    Unit player = { "player", 100, 0, 0 };
    Unit boss = { "boss", 0, 0, 0 };

    std::string stat;
    uint32_t value;
    while (input >> stat) {

        if (stat == "Hit") {
            input >> stat >> value;
            boss.hp = value;
        } else if (stat == "Damage:") {
            input >> value;
            boss.damage = value;
        } else if (stat == "Armor:") {
            input >> value;
            boss.armor = value;
        } else {
            std::cout << "Failed to read input: " << stat << std::endl;
            exit(1);
        }
    }

    int32_t result = std::numeric_limits<int32_t>::max();

    for (const auto& w : weapons) {

        Unit& p = player;
        const Unit& b = boss;

        int32_t cost = w.cost;
        equip(p, w);

        // Just weapon
        if (playerWins(p, b)) {
            result = std::min(result, cost);
        }

        for (const auto& a : armor) {
            
            cost += a.cost;
            equip(p, a);

            // Weapon + Armor
            if (playerWins(p, b)) {
                result = std::min(result, cost);
            }

            for (size_t i = 0; i < rings.size(); i++) {
                cost += rings[i].cost;
                equip(p, rings[i]);

                // Weapon + Armor + 1 ring
                if (playerWins(p, b)) {
                    result = std::min(result, cost);
                }

                for (size_t j = i+1; j < rings.size(); j++) {
                    cost += rings[j].cost;
                    equip(p, rings[j]);

                    // Weapon + Armor + 2 rings
                    if (playerWins(p, b)) {
                        result = std::min(result, cost);
                    }

                    cost -= rings[j].cost;
                    unequip(p, rings[j]);
                }

                cost -= rings[i].cost;
                unequip(p, rings[i]);
            }

            cost -= a.cost;
            unequip(p, a);
        }

        for (size_t i = 0; i < rings.size(); i++) {
            cost += rings[i].cost;
            equip(p, rings[i]);

            // Weapon + 1 ring
            if (playerWins(p, b)) {
                result = std::min(result, cost);
            }

            for (size_t j = i+1; j < rings.size(); j++) {
                cost += rings[j].cost;
                equip(p, rings[j]);

                // Weapon + 2 rings
                if (playerWins(p, b)) {
                    result = std::min(result, cost);
                }

                cost -= rings[j].cost;
                unequip(p, rings[j]);
            }

            cost -= rings[i].cost;
            unequip(p, rings[i]);
        }

        // Remove weapon here
        cost -= w.cost;
        unequip(p, w);
    }

    std::cout << "Least: " << result << std::endl;
}

void P2(std::istream& input) {

    Unit player = { "player", 100, 0, 0 };
    Unit boss = { "boss", 0, 0, 0 };

    std::string stat;
    uint32_t value;
    while (input >> stat) {

        if (stat == "Hit") {
            input >> stat >> value;
            boss.hp = value;
        } else if (stat == "Damage:") {
            input >> value;
            boss.damage = value;
        } else if (stat == "Armor:") {
            input >> value;
            boss.armor = value;
        } else {
            std::cout << "Failed to read input: " << stat << std::endl;
            exit(1);
        }
    }

    int32_t result = 0;

    for (const auto& w : weapons) {

        Unit& p = player;
        const Unit& b = boss;

        int32_t cost = w.cost;
        equip(p, w);

        // Just weapon
        if (!playerWins(p, b)) {
            result = std::max(result, cost);
        }

        for (const auto& a : armor) {
            
            cost += a.cost;
            equip(p, a);

            // Weapon + Armor
            if (!playerWins(p, b)) {
                result = std::max(result, cost);
            }

            for (size_t i = 0; i < rings.size(); i++) {
                cost += rings[i].cost;
                equip(p, rings[i]);

                // Weapon + Armor + 1 ring
                if (!playerWins(p, b)) {
                    result = std::max(result, cost);
                }

                for (size_t j = i+1; j < rings.size(); j++) {
                    cost += rings[j].cost;
                    equip(p, rings[j]);

                    // Weapon + Armor + 2 rings
                    if (!playerWins(p, b)) {
                        result = std::max(result, cost);
                    }

                    cost -= rings[j].cost;
                    unequip(p, rings[j]);
                }

                cost -= rings[i].cost;
                unequip(p, rings[i]);
            }

            cost -= a.cost;
            unequip(p, a);
        }

        for (size_t i = 0; i < rings.size(); i++) {
            cost += rings[i].cost;
            equip(p, rings[i]);

            // Weapon + 1 ring
            if (!playerWins(p, b)) {
                result = std::max(result, cost);
            }

            for (size_t j = i+1; j < rings.size(); j++) {
                cost += rings[j].cost;
                equip(p, rings[j]);

                // Weapon + 2 rings
                if (!playerWins(p, b)) {
                    result = std::max(result, cost);
                }

                cost -= rings[j].cost;
                unequip(p, rings[j]);
            }

            cost -= rings[i].cost;
            unequip(p, rings[i]);
        }

        // Remove weapon here
        cost -= w.cost;
        unequip(p, w);
    }

    std::cout << "Most: " << result << std::endl;
}

void equip(Unit& unit, const Item& item) {
    unit.damage += item.damage;
    unit.armor += item.armor;
}

void unequip(Unit& unit, const Item& item) {
    unit.damage -= item.damage;
    unit.armor -= item.armor;
}

bool playerWins(const Unit& player, const Unit& boss) {

    int32_t pturns = std::ceil(1.0 * boss.hp / std::max(1, player.damage - boss.armor));
    int32_t bturns = std::ceil(1.0 * player.hp / std::max(1, boss.damage - player.armor));

    return (pturns <= bturns);
}

bool playerWinsSimulation(Unit& player, Unit& boss) {

    Unit units[] = { player, boss };

    uint8_t active = 0;

    while (true) {
        auto attacker = &units[active];
        auto victim = &units[1-active];

        int32_t dealt = std::max(1, attacker->damage - victim->armor);
        victim->hp = std::max(0, victim->hp - dealt);

        std::cout << "The " << attacker->name << " deals " << dealt << " damage; the "
                  << victim->name << " goes down to " << victim->hp << " hit points->" << std::endl;

        if (victim->hp <= 0) {
            break;
        }
        active = 1 - active;
    }

    return units[1].hp <= 0;
}
