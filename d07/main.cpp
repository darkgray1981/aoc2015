#include <iostream>
#include <fstream>
#include <sstream>
#include <chrono>
#include <unordered_map>
#include <algorithm>

/*** OUTPUT ***

    Signal: 16076
    2nd Signal: 2797
    Time taken: 0.004s
 
 ***/

void P1(std::istream& input);
void P2(std::istream& input);
void parse(std::istream& input, std::unordered_map<std::string, std::string>& map);
uint16_t execute(const std::string& wire, std::unordered_map<std::string, std::string>& map, std::unordered_map<std::string, uint16_t>& cache);

int main() {
    auto start = std::chrono::steady_clock::now();

    std::ifstream infile("input.txt");

    P1(infile);

    infile.clear();
    infile.seekg(0);
    P2(infile);

    auto end = std::chrono::steady_clock::now();
    std::cout << "Time taken: " 
        << std::chrono::duration_cast<std::chrono::duration<double>>(end - start).count()
        << "s" << std::endl;
}

void P1(std::istream& input) {

    std::unordered_map<std::string, std::string> map;
    std::unordered_map<std::string, uint16_t> cache;

    parse(input, map);

    std::cout << "Signal: " << execute("a", map, cache) << std::endl;
}

void P2(std::istream& input) {

    std::unordered_map<std::string, std::string> map;
    std::unordered_map<std::string, uint16_t> cache;

    parse(input, map);

    auto first = execute("a", map, cache);
    cache.clear();
    map["b"] = std::to_string(first);

    std::cout << "2nd Signal: " << execute("a", map, cache) << std::endl;
}

void parse(std::istream& input, std::unordered_map<std::string, std::string>& map) {

    std::string line;
    while (std::getline(input, line)) {

        auto delim = line.find(" -> ");

        auto gate = line.substr(0, delim);
        auto wire = line.substr(delim+4);

        // Strip pesky \r line endings
        wire.erase(remove_if(wire.begin(), wire.end(), isspace), wire.end());

        map[wire] = gate;
    }
}

uint16_t execute(const std::string& wire, std::unordered_map<std::string, std::string>& map, std::unordered_map<std::string, uint16_t>& cache) {

    if (cache.count(wire) != 0) {
        return cache[wire];
    }

    if (map.count(wire) == 0) {
        return std::stoi(wire);
    }

    std::string gate = map[wire];

    uint16_t result = 0;

    std::istringstream ss(gate);
    std::string lstr, rstr, op;
    uint16_t lval, rval;

    auto spaces = std::count(gate.begin(), gate.end(), ' ');

    if (spaces == 2) {
        ss >> lstr >> op >> rstr;
        lval = execute(lstr, map, cache);
        rval = execute(rstr, map, cache);

        if (op == "AND") {
            result = lval & rval;
        } else if (op == "OR") {
            result = lval | rval;
        } else if (op == "LSHIFT") {
            result = lval << rval;
        } else if (op == "RSHIFT") {
            result = lval >> rval;
        }

    } else if (spaces == 1) {
        ss >> op >> rstr;
        rval = execute(rstr, map, cache);
        result = ~rval;
    } else {
        ss >> lstr;
        lval = execute(lstr, map, cache);
        result = lval;
    }

    cache[wire] = result;

    return result;
}
