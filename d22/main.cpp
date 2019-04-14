#include <iostream>
#include <fstream>
#include <sstream>
#include <chrono>
#include <unordered_map>
#include <queue>
#include <vector>
#include <limits>

/*** OUTPUT ***

    Least: 1269
    Least (Hard): 1309
    Time taken: 1.127s
 
 ***/

struct Unit {
    int32_t hp;
    int32_t mp;
    int32_t damage;
    int32_t armor;
};

struct State {
    State() : player{}, boss{}, mana{} {}
    Unit player;
    Unit boss;
    uint32_t mana;
    std::unordered_map<std::string, int32_t> effects;
};

struct Spell {
    std::string name;
    int32_t cost;
    int32_t damage;
    int32_t heal;
    int32_t armor;
    int32_t dot;
    int32_t recharge;
    int32_t duration;
};

const int32_t SHIELD_BUFF = 7;
const int32_t POISON_DOT = 3;
const int32_t RECHARGE_BOOST = 101;

std::unordered_map<std::string, Spell> spells = {
    { "Magic Missile", Spell{"Magic Missile", 53, 4, 0, 0, 0, 0, 0} },
    { "Drain", Spell{"Drain", 73, 2, 2, 0, 0, 0, 0} },
    { "Shield", Spell{"Shield", 113, 0, 0, SHIELD_BUFF, 0, 0, 6} },
    { "Poison", Spell{"Poison", 173, 0, 0, 0, POISON_DOT, 0, 6} },
    { "Recharge", Spell{"Recharge", 229, 0, 0, 0, 0, RECHARGE_BOOST, 5} },
};

class Comparison {
    public:
    bool operator() (const State& a, const State& b) const {
        return a.mana > b.mana;
    }
};

void P1(std::istream& input);
void P2(std::istream& input);
void applyEffects(State& state);
uint32_t play(State& state, bool hard = false);
bool combat(State& state, const Spell& spell);
void applyEffects(State& state);

int main() {
    auto start = std::chrono::steady_clock::now();

    std::istringstream test1(R"(Hit Points: 55
Damage: 8)"); // p1: 953, p2: 1289

    std::istringstream test2(R"(Hit Points: 71
Damage: 10)"); // p1: 1824, p2: 1937

    std::istringstream test3(R"(Hit Points: 51
Damage: 9)"); // p1: 900, p2: 1216

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

    Unit player = { 50, 500, 0, 0 };
    Unit boss = { 0, 0, 0, 0 };

    std::string stat;
    uint32_t value;
    while (input >> stat) {

        if (stat == "Hit") {
            input >> stat >> value;
            boss.hp = value;
        } else if (stat == "Damage:") {
            input >> value;
            boss.damage = value;
        } else {
            std::cout << "Failed to read input: " << stat << std::endl;
            exit(1);
        }
    }

    State state;
    state.player = player;
    state.boss = boss;

    uint32_t result = play(state);

    std::cout << "Least: " << result << std::endl;
}

void P2(std::istream& input) {

    Unit player = { 50, 500, 0, 0 };
    Unit boss = { 0, 0, 0, 0 };

    std::string stat;
    uint32_t value;
    while (input >> stat) {

        if (stat == "Hit") {
            input >> stat >> value;
            boss.hp = value;
        } else if (stat == "Damage:") {
            input >> value;
            boss.damage = value;
        } else {
            std::cout << "Failed to read input: " << stat << std::endl;
            exit(1);
        }
    }

    State state;
    state.player = player;
    state.boss = boss;

    uint32_t result = play(state, true);

    std::cout << "Least (Hard): " << result << std::endl;
}

uint32_t play(State& state, bool hard /* = false */) {

    uint32_t result = std::numeric_limits<uint32_t>::max();

    std::priority_queue<State, std::vector<State>, Comparison> pq;
    pq.push(state);

    while (!pq.empty()) {

        auto s = pq.top();
        pq.pop();

        if (s.boss.hp <= 0) {
            result = s.mana;
            break;
        }

        if (hard && --s.player.hp <= 0) {
            continue;
        }

        applyEffects(s);
        if (s.boss.hp <= 0) {
            result = s.mana;
            break;
        }

        for (const auto& kv : spells) {

            auto after = s;
            if (combat(after, kv.second) && after.mana < result) {
                if (after.boss.hp <= 0) {
                    result = std::min(result, after.mana);
                }

                pq.push(std::move(after));
            }
        }
    }

    return result;
}

bool combat(State& state, const Spell& spell) {

    // Player's turn
    if (state.player.mp < spell.cost || (spell.duration > 0 && state.effects[spell.name] > 0)) {
        return false;
    }

    state.player.mp -= spell.cost;
    state.mana += spell.cost;
    state.boss.hp -= spell.damage;
    state.player.hp += spell.heal;
    state.player.armor += spell.armor;
    if (spell.duration > 0) {
        state.effects[spell.name] = spell.duration;
    }

    if (state.boss.hp <= 0) {
        return true;
    }

    // Boss's turn
    applyEffects(state);

    if (state.boss.hp <= 0) {
        return true;
    }

    state.player.hp -= std::max(1, state.boss.damage - state.player.armor);

    return (state.player.hp > 0);
}

void applyEffects(State& state) {

    for (auto it = state.effects.begin(); it != state.effects.end(); ) {

        if (it->first == "Shield" && it->second == 1) {
            state.player.armor -= SHIELD_BUFF;
        } else if (it->first == "Poison" && it->second > 0) {
            state.boss.hp -= POISON_DOT;
        } else if (it->first == "Recharge" && it->second > 0) {
            state.player.mp += RECHARGE_BOOST;
        }

        if (it->second <= 1) {
            it = state.effects.erase(it);
        } else {
            it->second--;
            it++;
        }
    }
}
