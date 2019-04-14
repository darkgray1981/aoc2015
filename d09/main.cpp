#include <iostream>
#include <fstream>
#include <sstream>
#include <chrono>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <limits>

/*** OUTPUT ***

    Shortest: 251
    Longest: 898
    Time taken: 0.113s
 
 ***/

using Pair = std::pair<std::string, uint32_t>;

void P1(std::istream& input);
void P2(std::istream& input);
uint32_t shortest(const std::string& from, std::unordered_map<std::string, std::vector<Pair>>& map, std::unordered_set<std::string>& used);
uint32_t longest(const std::string& from, std::unordered_map<std::string, std::vector<Pair>>& map, std::unordered_set<std::string>& used);

int main() {
    auto start = std::chrono::steady_clock::now();

    std::istringstream test1(R"(London to Dublin = 464
London to Belfast = 518
Dublin to Belfast = 141)"); // p1: 605, p2: 982

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

    std::unordered_map<std::string, std::vector<Pair>> map;
    std::unordered_set<std::string> used;

    std::string line;
    while (std::getline(input, line)) {

        std::istringstream ss(line);

        std::string from, dumps, to;
        uint32_t distance;

        ss >> from >> dumps >> to >> dumps >> distance;

        map[from].push_back(Pair(to, distance));
        map[to].push_back(Pair(from, distance));
    }

    uint32_t result = std::numeric_limits<int>::max();

    for (const auto& p : map) {
        result = std::min(result, shortest(p.first, map, used));
    }

    std::cout << "Shortest: " << result << std::endl;
}

void P2(std::istream& input) {

    std::unordered_map<std::string, std::vector<Pair>> map;
    std::unordered_set<std::string> used;

    std::string line;
    while (std::getline(input, line)) {

        std::istringstream ss(line);

        std::string from, dumps, to;
        uint32_t distance;

        ss >> from >> dumps >> to >> dumps >> distance;

        map[from].push_back(Pair(to, distance));
        map[to].push_back(Pair(from, distance));
    }

    uint32_t result = 0;

    for (const auto& p : map) {
        result = std::max(result, longest(p.first, map, used));
    }

    std::cout << "Longest: " << result << std::endl;
}

uint32_t shortest(const std::string& from, std::unordered_map<std::string, std::vector<Pair>>& map, std::unordered_set<std::string>& used) {

    uint32_t min = std::numeric_limits<int>::max();

    used.insert(from);

    bool last = true;

    for (const auto& p : map[from]) {
        if (used.find(p.first) != used.end()) {
            continue;
        }

        min = std::min(min, p.second + shortest(p.first, map, used));
        last = false;
    }

    used.erase(from);

    return (last ? 0 : min);
}

uint32_t longest(const std::string& from, std::unordered_map<std::string, std::vector<Pair>>& map, std::unordered_set<std::string>& used) {

    uint32_t max = 0;

    used.insert(from);

    for (const auto& p : map[from]) {
        if (used.find(p.first) != used.end()) {
            continue;
        }

        max = std::max(max, p.second + longest(p.first, map, used));
    }

    used.erase(from);

    return max;
}
