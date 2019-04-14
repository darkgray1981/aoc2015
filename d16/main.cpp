#include <iostream>
#include <fstream>
#include <sstream>
#include <chrono>
#include <unordered_map>

/*** OUTPUT ***

    Sue #: 40
    Real Sue #: 241
    Time taken: 0.001s
 
 ***/

std::unordered_map<std::string, int32_t> map = {
    { "children", 3 },
    { "cats", 7 },
    { "samoyeds", 2 },
    { "pomeranians", 3 },
    { "akitas", 0 },
    { "vizslas", 0 },
    { "goldfish", 5 },
    { "trees", 3 },
    { "cars", 2 },
    { "perfumes", 1 },
};

void P1(std::istream& input);
void P2(std::istream& input);

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

    int32_t result = 0;

    std::string line;
    while (std::getline(input, line)) {

        std::istringstream ss(line);

        bool match = true;
        int32_t sueNum = -1;

        std::string key, value;
        while (ss >> key >> value) {

            if (key == "Sue") {
                sueNum = std::stoi(value);
                continue;
            }

            key.pop_back(); // remove ending ':'

            if (map[key] != std::stoi(value)) {
                match = false;
                break;
            }
        }

        if (match) {
            result = sueNum;
            break;
        }
    }

    std::cout << "Sue #: " << result << std::endl;
}

void P2(std::istream& input) {

    int32_t result = 0;

    std::string line;
    while (std::getline(input, line)) {

        std::istringstream ss(line);

        bool match = true;
        int32_t sueNum = -1;

        std::string key, value;
        while (match && (ss >> key >> value)) {

            if (key == "Sue") {
                sueNum = std::stoi(value);
                continue;
            }

            key.pop_back(); // remove ending ':'

            int32_t num = std::stoi(value);

            if (key == "cats" || key == "trees") {
                match = (num > map[key]);
            } else if (key == "pomeranians" || key == "goldfish") {
                match = (num < map[key]);
            } else {
                match = (num == map[key]);
            }
        }

        if (match) {
            result = sueNum;
            break;
        }
    }

    std::cout << "Real Sue #: " << result << std::endl;
}
