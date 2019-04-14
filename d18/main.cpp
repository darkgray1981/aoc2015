#include <iostream>
#include <fstream>
#include <sstream>
#include <chrono>
#include <vector>

/*** OUTPUT ***

    Lights: 768
    Broken lights: 781
    Time taken: 0.027s
 
 ***/

void P1(std::istream& input, uint32_t steps);
void P2(std::istream& input, uint32_t steps);
void printgrid(std::vector<std::vector<bool>>& grid);

int main() {
    auto start = std::chrono::steady_clock::now();

    std::istringstream test1(R"(.#.#.#
...##.
#....#
..#...
#.#..#
####..)"); // p1: 4 -> 4, p2: 5 -> 17

    std::ifstream infile("input.txt");

    // P1(test1, 4);
    P1(infile, 100);

    infile.clear();
    infile.seekg(0);
    // P2(test1, 5);
    P2(infile, 100);

    auto end = std::chrono::steady_clock::now();
    std::cout << "Time taken: " 
		<< std::chrono::duration_cast<std::chrono::duration<double>>(end - start).count()
		<< "s" << std::endl;
}

void P1(std::istream& input, uint32_t steps) {

    std::vector<std::vector<bool>> grid;
    int32_t dim = 0;

    std::string line;
    while (std::getline(input, line)) {

        // Strip pesky \r line endings
        if (line.length() > 0 && line[line.length()-1] == '\r') {
            line.pop_back();
        }

        if (dim == 0) {
            dim = line.length() + 2; // Pad outer grid edges
        }

        std::vector<bool> row(dim);

        for (size_t i = 0; i < line.length(); i++) {
            row[i+1] = (line[i] == '#');
        }

        grid.push_back(row);
    }

    // Pad outer grid edges to avoid going out of bounds
    grid.insert(grid.begin(), std::vector<bool>(dim));
    grid.push_back(std::vector<bool>(dim));

    std::vector<std::vector<bool>> next = grid;

    // printgrid(grid);

    for (uint32_t i = 0; i < steps; i++) {
        for (int32_t y = 1; y < dim-1; y++) {
            for (int32_t x = 1; x < dim-1; x++) {

                uint32_t on = grid[y-1][x-1] + grid[y-1][x] + grid[y-1][x+1];
                on += grid[y][x-1] + grid[y][x+1];
                on += grid[y+1][x-1] + grid[y+1][x] + grid[y+1][x+1];

                if (grid[y][x] && (on != 2 && on != 3)) {
                    next[y][x] = false;
                } else if (!grid[y][x] && on == 3) {
                    next[y][x] = true;
                } else {
                    next[y][x] = grid[y][x];
                }
            }
        }

        swap(grid, next);

        // printgrid(grid);
    }

    uint32_t brightness = 0;

    for (size_t y = 0; y < grid.size(); y++) {
        for (size_t x = 0; x < grid[y].size(); x++) {
            if (grid[y][x]) {
                brightness++;
            }
        }
    }

    std::cout << "Lights: " << brightness << std::endl;
}

void P2(std::istream& input, uint32_t steps) {

    std::vector<std::vector<bool>> grid;
    int32_t dim = 0;

    std::string line;
    while (std::getline(input, line)) {

        // Strip pesky \r line endings
        if (line.length() > 0 && line[line.length()-1] == '\r') {
            line.pop_back();
        }

        if (dim == 0) {
            dim = line.length() + 2; // Pad outer grid edges
        }

        std::vector<bool> row(dim);

        for (size_t i = 0; i < line.length(); i++) {
            row[i+1] = (line[i] == '#');
        }

        grid.push_back(row);
    }

    // Pad outer grid edges to avoid going out of bounds
    grid.insert(grid.begin(), std::vector<bool>(dim));
    grid.push_back(std::vector<bool>(dim));

    grid[1][1] = true;
    grid[1][dim-2] = true;
    grid[dim-2][1] = true;
    grid[dim-2][dim-2] = true;

    std::vector<std::vector<bool>> next = grid;

    // printgrid(grid);

    for (uint32_t i = 0; i < steps; i++) {
        for (int32_t y = 1; y < dim-1; y++) {
            for (int32_t x = 1; x < dim-1; x++) {

                uint32_t on = grid[y-1][x-1] + grid[y-1][x] + grid[y-1][x+1];
                on += grid[y][x-1] + grid[y][x+1];
                on += grid[y+1][x-1] + grid[y+1][x] + grid[y+1][x+1];

                if (grid[y][x] && (on != 2 && on != 3)) {
                    next[y][x] = false;
                } else if (!grid[y][x] && on == 3) {
                    next[y][x] = true;
                } else {
                    next[y][x] = grid[y][x];
                }
            }
        }

        next[1][1] = true;
        next[1][dim-2] = true;
        next[dim-2][1] = true;
        next[dim-2][dim-2] = true;

        swap(grid, next);

        // printgrid(grid);
    }

    uint32_t brightness = 0;

    for (size_t y = 0; y < grid.size(); y++) {
        for (size_t x = 0; x < grid[y].size(); x++) {
            if (grid[y][x]) {
                brightness++;
            }
        }
    }

    std::cout << "Broken lights: " << brightness << std::endl;
}

void printgrid(std::vector<std::vector<bool>>& grid) {
    for (size_t y = 0; y < grid.size(); y++) {
        for (size_t x = 0; x < grid[y].size(); x++) {
            std::cout << (grid[y][x] ? '#' : '.');
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}
