#include <iostream>
#include <fstream>
#include <sstream>
#include <chrono>
#include <unordered_map>
#include <vector>
#include <algorithm>

/*** OUTPUT ***

    Optimal: 664
    Optimal me: 640
    Time taken: 0.456s
 
 ***/

void P1(std::istream& input);
void P2(std::istream& input);
std::unordered_map<std::string, std::unordered_map<std::string, int32_t>> parse(std::istream &input);
int32_t sumJoy(const std::vector<std::string>& names, std::unordered_map<std::string, std::unordered_map<std::string, int32_t>>& map);

int main() {
    auto start = std::chrono::steady_clock::now();

    std::istringstream test1(R"(Alice would gain 54 happiness units by sitting next to Bob.
Alice would lose 79 happiness units by sitting next to Carol.
Alice would lose 2 happiness units by sitting next to David.
Bob would gain 83 happiness units by sitting next to Alice.
Bob would lose 7 happiness units by sitting next to Carol.
Bob would lose 63 happiness units by sitting next to David.
Carol would lose 62 happiness units by sitting next to Alice.
Carol would gain 60 happiness units by sitting next to Bob.
Carol would gain 55 happiness units by sitting next to David.
David would gain 46 happiness units by sitting next to Alice.
David would lose 7 happiness units by sitting next to Bob.
David would gain 41 happiness units by sitting next to Carol.)"); // p1: 330

    std::ifstream infile("input.txt");

    // P1(test1);
    P1(infile);

    infile.clear();
    infile.seekg(0);
    // P2(test1);
    P2(infile);

    auto end = std::chrono::steady_clock::now();
    std::cout << "Time taken: " 
		<< std::chrono::duration_cast<std::chrono::duration<double>>(end - start).count()
		<< "s" << std::endl;
}

void P1(std::istream& input) {

    auto map = parse(input);

    std::vector<std::string> people;
    for (const auto& kv : map) {
        people.push_back(kv.first);
    }

    std::sort(people.begin(), people.end());

    int32_t result = 0;

    do {
        result = std::max(result, sumJoy(people, map));
    } while (std::next_permutation(people.begin(), people.end()));

    std::cout << "Optimal: " << result << std::endl;
}

void P2(std::istream& input) {

    auto map = parse(input);

    std::vector<std::string> people;
    for (const auto& kv : map) {
        people.push_back(kv.first);
    }

    people.push_back("<ME>");

    std::sort(people.begin(), people.end());

    int32_t result = 0;

    do {
        result = std::max(result, sumJoy(people, map));
    } while (std::next_permutation(people.begin(), people.end()));

    std::cout << "Optimal me: " << result << std::endl;
}

std::unordered_map<std::string, std::unordered_map<std::string, int32_t>> parse(std::istream &input) {

    std::unordered_map<std::string, std::unordered_map<std::string, int32_t>> map;

    std::string line;
    while (std::getline(input, line)) {

        std::istringstream ss(line);

        std::string person, neighbour, change, z;
        uint32_t happiness;
        ss >> person >> z >> change >> happiness >> z >> z >> z >> z >> z >> z >> neighbour;

        neighbour.pop_back(); // remove final period

        if (change == "lose") {
            happiness = -happiness;
        }

        map[person][neighbour] = happiness;
    }

    return map;
}

int32_t sumJoy(const std::vector<std::string>& names, std::unordered_map<std::string, std::unordered_map<std::string, int32_t>>& map) {

    int32_t result = 0;

    for (size_t i = 1; i < names.size(); i++) {
        result += map[names[i]][names[i-1]];
        result += map[names[i-1]][names[i]];
    }

    result += map[names[0]][names[names.size()-1]];
    result += map[names[names.size()-1]][names[0]];

    return result;
}
