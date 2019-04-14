#include <iostream>
#include <fstream>
#include <sstream>
#include <chrono>
#include <vector>

/*** OUTPUT ***

    Lights: 543903
    2nd Lights: 14687245
    Time taken: 0.044s
 
 ***/

const size_t DIM = 1000;

void P1(std::istream& input);
void P2(std::istream& input);

int main() {
    auto start = std::chrono::steady_clock::now();

    std::istringstream test1(R"(turn on 0,0 through 999,999
toggle 0,0 through 999,0
turn off 499,499 through 500,500)"); // p1: 998996

    std::istringstream test2(R"(turn on 0,0 through 0,0
toggle 0,0 through 999,999)"); // p2: 2000001

    std::ifstream infile("input.txt");

    // P1(test1);
    P1(infile);

    infile.clear();
    infile.seekg(0);
    // P2(test1);
    // P2(test2);
    P2(infile);

    auto end = std::chrono::steady_clock::now();
    std::cout << "Time taken: " 
		<< std::chrono::duration_cast<std::chrono::duration<double>>(end - start).count()
		<< "s" << std::endl;
}

void P1(std::istream& input) {

    bool grid[DIM][DIM] = {};

    std::string line;
    while (std::getline(input, line)) {

        std::istringstream ss(line);

        std::string action;
        ss >> action;
        if (action != "toggle") {
            ss >> action;
        }

        size_t xa, xb, ya, yb;
        std::string dumps;
        char dumpc;
        ss >> xa >> dumpc >> ya >> dumps >> xb >> dumpc >> yb;

        if (action == "toggle") {
            for (size_t y = ya; y <= yb; y++) {
                for (size_t x = xa; x <= xb; x++) {
                    grid[y][x] = !grid[y][x];
                }
            }
        } else {
            bool state = (action == "on");

            for (size_t y = ya; y <= yb; y++) {
                for (size_t x = xa; x <= xb; x++) {
                    grid[y][x] = state;
                }
            }
        }
    }

    uint32_t on = 0;

    for (size_t y = 0; y < DIM; y++) {
        for (size_t x = 0; x < DIM; x++) {
            if (grid[y][x]) {
                on++;
            }
        }
    }

    std::cout << "Lights: " << on << std::endl;
}

void P2(std::istream& input) {

    auto grid = std::vector<std::vector<uint32_t>>(DIM, std::vector<uint32_t>(DIM));

    std::string line;
    while (std::getline(input, line)) {

        std::istringstream ss(line);

        std::string action;
        ss >> action;
        if (action != "toggle") {
            ss >> action;
        }

        size_t xa, xb, ya, yb;
        std::string dumps;
        char dumpc;
        ss >> xa >> dumpc >> ya >> dumps >> xb >> dumpc >> yb;

        int32_t change = -1;
        if (action == "toggle") {
            change = 2;
        } else if (action == "on") {
            change = 1;
        }

        for (size_t y = ya; y <= yb; y++) {
            for (size_t x = xa; x <= xb; x++) {
                if (!(change == -1 && grid[y][x] == 0)) {
                    grid[y][x] += change;
                }
            }
        }
    }

    uint32_t brightness = 0;

    for (size_t y = 0; y < DIM; y++) {
        for (size_t x = 0; x < DIM; x++) {
            brightness += grid[y][x];
        }
    }

    std::cout << "2nd Lights: " << brightness << std::endl;
}
