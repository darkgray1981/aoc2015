#include <iostream>
#include <fstream>
#include <sstream>
#include <chrono>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <algorithm>
#include <stdexcept>
#include <cstdlib>

/*** OUTPUT ***

    Distinct: 518
    Steps: 200
    Time taken: 0.005s
 
 ***/

void P1(std::istream& input);
void P2(std::istream& input);
bool compare(const std::string& sa, const std::string &sb);
int32_t reduce(std::string molecule, int32_t depth, std::vector<std::string>& order, std::unordered_map<std::string, std::vector<std::string>>& map, std::unordered_set<std::string>& seen);

int main() {
    auto start = std::chrono::steady_clock::now();

    std::istringstream test1(R"(H => HO
H => OH
O => HH

HOHOHO)"); // p1: 7

    std::istringstream test2(R"(e => H
e => O
H => HO
H => OH
O => HH

HOHOHO)"); // p2: 6

    std::ifstream infile("input.txt");

    // P1(test1);
    P1(infile);

    infile.clear();
    infile.seekg(0);
    // P2(test2);
    P2(infile);

    auto end = std::chrono::steady_clock::now();
    std::cout << "Time taken: " 
		<< std::chrono::duration_cast<std::chrono::duration<double>>(end - start).count()
		<< "s" << std::endl;
}

void P1(std::istream& input) {

    std::unordered_map<std::string, std::vector<std::string>> map;

    std::string line, molecule;
    while (std::getline(input, line)) {

        // Strip pesky \r line endings
        if (line.length() > 0 && line[line.length()-1] == '\r') {
            line.pop_back();
        }

        if (line.length() == 0) {
            input >> molecule;
            continue;
        }

        std::istringstream ss(line);

        std::string key, z, value;
        ss >> key >> z >> value;
        map[key].push_back(value);
    }

    std::unordered_set<std::string> set;

    for (const auto& kv : map) {
        size_t pos = 0;
        while ((pos = molecule.find(kv.first, pos)) != std::string::npos) {
            for (const auto& rep : kv.second) {
                set.insert(molecule.substr(0, pos) + rep + molecule.substr(pos + kv.first.length()));
            }

            pos++;
        }
    }

    std::cout << "Distinct: " << set.size() << std::endl;
}

void P2(std::istream& input) {

    std::unordered_map<std::string, std::vector<std::string>> map;

    std::string line, molecule;
    while (std::getline(input, line)) {

        // Strip pesky \r line endings
        if (line.length() > 0 && line[line.length()-1] == '\r') {
            line.pop_back();
        }

        if (line.length() == 0) {
            input >> molecule;
            continue;
        }

        std::istringstream ss(line);

        std::string key, z, value;
        ss >> key >> z >> value;
        map[value].push_back(key);
    }

    std::vector<std::string> order;
    for (const auto& k : map) {
        order.push_back(k.first);
    }

    sort(order.begin(), order.end(), compare);

    std::srand(std::time(0));

    int32_t result = -1;
    do {
        std::unordered_set<std::string> set;

        result = reduce(molecule, 0, order, map, set);

        std::random_shuffle(order.begin(), order.end());
    } while (result == -1);

    std::cout << "Steps: " << result << std::endl;
}

bool compare(const std::string& sa, const std::string &sb) {
    if (sa.size() == sb.size()) {
        return sa > sb;
    }
    return sa.size() > sb.size();
}

int32_t reduce(std::string molecule, int32_t depth, std::vector<std::string>& order, std::unordered_map<std::string, std::vector<std::string>>& map, std::unordered_set<std::string>& seen) {

    if (molecule == "e") {
        return depth;
    }

    if (seen.find(molecule) != seen.end()) {
        return -1;
    }

    if (molecule.find("e") != std::string::npos) {
        return -1;
    }

    int32_t result = -1;

    for (const auto& k : order) {

        const auto& v = map[k];

        size_t pos = 0;
        while ((pos = molecule.find(k, pos)) != std::string::npos) {
            for (const auto& rep : v) {

                if (depth == 0) {
                    try {
                        result = reduce(molecule.substr(0, pos) + rep + molecule.substr(pos + k.length()), depth+1, order, map, seen);
                    } catch (std::logic_error& e) {
                        // std::cout << "Gave up, trying next..." << std::endl;
                        continue;
                    }
                } else {
                    result = reduce(molecule.substr(0, pos) + rep + molecule.substr(pos + k.length()), depth+1, order, map, seen);
                }

                if (result != -1) {
                    return result;
                }
            }

            pos++;
        }
    }

    if (seen.size() > 1000) {
        seen.clear();
        throw std::logic_error("Better try something else!");
    }

    seen.insert(molecule);

    return result;
}
