#include <iostream>
#include <fstream>
#include <sstream>
#include <chrono>
#include <regex>

/*** OUTPUT ***

    Code: 9132360 for 2981,3075
    Time taken: 0.207s
 
 ***/

void P1(std::istream& input);
std::pair<uint32_t, uint32_t> parse(std::istream& input);
uint32_t coord2num(uint32_t row, uint32_t col);
uint64_t getnum(std::pair<uint32_t, uint32_t> target);

int main() {
    auto start = std::chrono::steady_clock::now();

    std::istringstream test1(R"(To continue, please consult the code grid in the manual.  Enter the code at row 3, column 2.)"); // p1: 8057251

    std::ifstream infile("input.txt");

    // P1(test1);
    P1(infile);

    auto end = std::chrono::steady_clock::now();
    std::cout << "Time taken: " 
		<< std::chrono::duration_cast<std::chrono::duration<double>>(end - start).count()
		<< "s" << std::endl;
}

void P1(std::istream& input) {

    auto target = parse(input);

    std::cout << "Code: " << getnum(target) << " for " << target.first << "," << target.second << std::endl;
}

std::pair<uint32_t, uint32_t> parse(std::istream& input) {

    std::regex re("row (\\d+), column (\\d+).$");
    std::smatch matches;

    std::string line;
    std::getline(input, line);

    if (!std::regex_search(line, matches, re)) {
        std::cout << "Failed on: " << line << std::endl;
        exit(1);
    }

    uint32_t row = std::stoi(matches[1].str());
    uint32_t column = std::stoi(matches[2].str());

    return std::make_pair(row, column);
}

uint64_t getnum(std::pair<uint32_t, uint32_t> target) {

    uint64_t value = 20151125;
    uint64_t mul = 252533;
    uint64_t div = 33554393;

    uint32_t loops = coord2num(target.first, target.second);

    while (--loops) {
        value = (value * mul) % div;
    }

    return value;
}

uint32_t coord2num(uint32_t row, uint32_t col) {

    return (col+row - 1) * (col+row - 2) / 2 + col;

    // return (col*(col+1) + (row-1)*(row-2)) / 2 + col*(row-1);

    // uint32_t result = 0;

    // for (uint32_t i = 1; i <= col; i++) {
    //     result += i;
    // }

    // for (uint32_t i = 0; i < row-1; i++) {
    //     result += col + i;
    // }

    // return result;
}
