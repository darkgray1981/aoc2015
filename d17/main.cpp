#include <iostream>
#include <fstream>
#include <sstream>
#include <chrono>
#include <vector>

/*** OUTPUT ***

    Combinations: 1304
    Min combinations: 18
    Time taken: 0.002s
 
 ***/

void P1(std::istream& input, uint32_t target);
void P2(std::istream& input, uint32_t target);
uint32_t ways(int32_t target, size_t index, std::vector<uint32_t>& containers);
void waysUsed(int32_t target, size_t index, std::vector<uint32_t>& containers, size_t used, std::vector<uint32_t>& results);

int main() {
    auto start = std::chrono::steady_clock::now();

    std::istringstream test1(R"(20 15 10 5 5)"); // p1: 4, p2: 3

    std::ifstream infile("input.txt");

    // std::cout.setstate(std::ios_base::failbit);

    // P1(test1, 25);
    P1(infile, 150);

    infile.clear();
    infile.seekg(0);
    // P2(test1, 25);
    P2(infile, 150);

    // std::cout.clear();

    auto end = std::chrono::steady_clock::now();
    std::cout << "Time taken: " 
		<< std::chrono::duration_cast<std::chrono::duration<double>>(end - start).count()
		<< "s" << std::endl;
}

void P1(std::istream& input, uint32_t target) {

    std::vector<uint32_t> containers;

    uint32_t n;
    while (input >> n) {
        containers.push_back(n);
    }

    uint32_t result = ways(target, 0, containers);

    std::cout << "Combinations: " << result << std::endl;
}

void P2(std::istream& input, uint32_t target) {

    std::vector<uint32_t> containers;

    uint32_t n;
    while (input >> n) {
        containers.push_back(n);
    }

    std::vector<uint32_t> results(containers.size());

    waysUsed(target, 0, containers, 0, results);

    uint32_t result = 0;
    for (size_t i = 0; i < results.size(); i++) {
        if (results[i] > 0) {
            result = results[i];
            break;
        }
    }

    std::cout << "Min combinations: " << result << std::endl;
}

uint32_t ways(int32_t target, size_t index, std::vector<uint32_t>& containers) {

    if (target <= 0 || index >= containers.size()) {
        return (target == 0) ? 1 : 0;
    }

    uint32_t result = 0;

    result += ways(target - containers[index], index+1, containers);
    result += ways(target, index+1, containers);

    return result;
}

void waysUsed(int32_t target, size_t index, std::vector<uint32_t>& containers, size_t used, std::vector<uint32_t>& results) {

    if (target <= 0 || index >= containers.size()) {
        if (target == 0) {
            results[used]++;
        }
        return;
    }

    waysUsed(target - containers[index], index+1, containers, used+1, results);
    waysUsed(target, index+1, containers, used, results);
}
