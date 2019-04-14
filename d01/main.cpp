#include <iostream>
#include <fstream>
#include <chrono>

/*** OUTPUT ***

    Floor: 280
    Position: 1797
    Time taken: 0.001s
 
 ***/

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
    
    char ch;
    while (input >> ch) {
        result += (ch == '(' ? 1 : -1);
    }

    std::cout << "Floor: " << result << std::endl;
}

void P2(std::istream& input) {

    int32_t level = 0;
    int32_t position = 0;
    
    char ch;
    while (level >= 0 && input >> ch) {
        position++;
        level += (ch == '(' ? 1 : -1);
    }

    std::cout << "Position: " << position << std::endl;
}
