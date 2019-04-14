#include <iostream>
#include <fstream>
#include <sstream>
#include <chrono>

/*** OUTPUT ***

    Total: 1588178
    Total: 3783758
    Time taken: 0.004s
 
 ***/

void P1(std::istream& input);
void P2(std::istream& input);

int main() {
    auto start = std::chrono::steady_clock::now();

    std::istringstream test1(R"(2x3x4
1x1x10)"); // p1: 101, p2: 48

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

    uint32_t result = 0;

    char dump;
    uint32_t l, w, h;

    while (input >> l >> dump >> w >> dump >> h) {

        uint32_t lw = l*w;
        uint32_t wh = w*h;
        uint32_t hl = h*l;

        uint32_t min = std::min(std::min(lw, wh), hl);

        result += 2 * (lw+wh+hl) + min;
    }

    std::cout << "Total: " << result << std::endl;
}

void P2(std::istream& input) {

    uint32_t result = 0;
    
    char dump;
    uint32_t l, w, h;

    while (input >> l >> dump >> w >> dump >> h) {

        uint32_t max = std::max(std::max(l, w), h);

        result += 2 * (l + w + h) - 2 * max + l*w*h;
    }

    std::cout << "Total: " << result << std::endl;
}
