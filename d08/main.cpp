#include <iostream>
#include <fstream>
#include <sstream>
#include <chrono>

/*** OUTPUT ***

    Difference: 1350 (6195-4845)
    2nd Difference: 2085 (8280-6195)
    Time taken: 0.001s
 
 ***/

void P1(std::istream& input);
void P2(std::istream& input);

int main() {
    auto start = std::chrono::steady_clock::now();

    std::istringstream test1(R"(""
"abc"
"aaa\"aaa"
"\x27")"); // p1: 12, p2: 19

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

    uint32_t literalCount = 0;
    uint32_t memoryCount = 0;

    std::string line;
    while (std::getline(input, line)) {

        literalCount += line.length();

        for (size_t i = 0; i < line.length(); i++) {
            if (line[i] == '"') {
                continue;
            }

            if (line[i] == '\\') {
                if (line[i+1] == 'x') {
                    i += 3;
                } else {
                    i++;
                }
            }

            memoryCount++;
        }
    }

    std::cout << "Difference: " << literalCount - memoryCount << " (" << literalCount << "-" << memoryCount << ")" << std::endl;
}

void P2(std::istream& input) {

    uint32_t originalCount = 0;
    uint32_t encodedCount = 0;

    std::string line;
    while (std::getline(input, line)) {

        originalCount += line.length();
        encodedCount += 2; // surrounding ""

        for (size_t i = 0; i < line.length(); i++) {
            if (line[i] == '"' || line[i] == '\\') {
                encodedCount++;
            }

            encodedCount++;
        }
    }

    std::cout << "2nd Difference: " << encodedCount - originalCount << " (" << encodedCount << "-" << originalCount << ")" << std::endl;
}
