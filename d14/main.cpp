#include <iostream>
#include <fstream>
#include <sstream>
#include <chrono>
#include <vector>
#include <regex>

/*** OUTPUT ***

    Distance: 2655
    Points: 1059
    Time taken: 0.002s
 
 ***/

struct Reindeer {
    uint32_t speed;
    uint32_t stamina;
    uint32_t rest;
    uint32_t distance;
    uint32_t score;
};

void P1(std::istream& input, uint32_t race);
void P2(std::istream& input, uint32_t race);
uint32_t traveled(uint32_t speed, uint32_t stamina, uint32_t rest, uint32_t after);

int main() {
    auto start = std::chrono::steady_clock::now();

    std::istringstream test1(R"(Comet can fly 14 km/s for 10 seconds, but then must rest for 127 seconds.
Dancer can fly 16 km/s for 11 seconds, but then must rest for 162 seconds.)"); // p1: 1120, p2: 689

    std::ifstream infile("input.txt");

    // P1(test1, 1000);
    P1(infile, 2503);

    infile.clear();
    infile.seekg(0);
    // P2(test1, 1000);
    P2(infile, 2503);

    auto end = std::chrono::steady_clock::now();
    std::cout << "Time taken: " 
		<< std::chrono::duration_cast<std::chrono::duration<double>>(end - start).count()
		<< "s" << std::endl;
}

void P1(std::istream& input, uint32_t race) {

    uint32_t result = 0;

    std::regex re("(\\w+?) can fly (\\d+?) km/s for (\\d+?) seconds, but then must rest for (\\d+?) seconds.");
    std::smatch matches;

    std::string line;
    while (std::getline(input, line)) {

        if (!std::regex_search(line, matches, re)) {
            std::cout << "Failed on: " << line << std::endl;
            continue;
        }

        // std::string deer = matches[1].str();
        uint32_t speed = std::stoi(matches[2].str());
        uint32_t stamina = std::stoi(matches[3].str());
        uint32_t rest = std::stoi(matches[4].str());

        uint32_t distance = traveled(speed, stamina, rest, race);

        result = std::max(result, distance);
    }

    std::cout << "Distance: " << result << std::endl;
}

void P2(std::istream& input, uint32_t race) {

    std::vector<Reindeer> deers;

    std::regex re("^(\\w+?) can fly (\\d+?) km/s for (\\d+?) seconds, but then must rest for (\\d+?) seconds.");
    std::smatch matches;

    std::string line;
    while (std::getline(input, line)) {

        if (!std::regex_search(line, matches, re)) {
            std::cout << "Failed on: " << line << std::endl;
            continue;
        }

        // std::string deer = matches[1].str();
        uint32_t speed = std::stoi(matches[2].str());
        uint32_t stamina = std::stoi(matches[3].str());
        uint32_t rest = std::stoi(matches[4].str());

        deers.push_back(Reindeer{speed, stamina, rest, 0, 0});
    }

    for (uint32_t i = 1; i <= race; i++) {

        uint32_t distance = 0;

        for (size_t j = 0; j < deers.size(); j++) {
            deers[j].distance = traveled(deers[j].speed, deers[j].stamina, deers[j].rest, i);
            distance = std::max(distance, deers[j].distance);
        }

        for (size_t j = 0; j < deers.size(); j++) {
            if (deers[j].distance == distance) {
                deers[j].score++;
            }
        }
    }

    uint32_t result = 0;

    for (const auto& d : deers) {
        result = std::max(result, d.score);
    }

    std::cout << "Points: " << result << std::endl;
}

uint32_t traveled(uint32_t speed, uint32_t stamina, uint32_t rest, uint32_t after) {

    uint32_t periods = after / (stamina + rest);
    uint32_t rem = after % (stamina + rest);
    uint32_t dist = periods * (speed * stamina);
    dist += std::min(rem, stamina) * speed;

    return dist;
}
