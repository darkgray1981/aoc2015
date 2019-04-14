#include <iostream>
#include <fstream>
#include <sstream>
#include <chrono>

/*** OUTPUT ***

    Sum: 119433
    Non-Red Sum: 68466
    Time taken: 0.006s
 
 ***/

void P1(std::istream& input);
void P2(std::istream& input);
int32_t sum(std::istream& input);

int main() {
    auto start = std::chrono::steady_clock::now();

    std::istringstream test1(R"([1,{"c":"red","b":2},3])"); // p1: 6, p2: 4
    std::istringstream test2(R"({"d":"red","e":[1,2,3,4],"f":5})"); // p1: 15, p2: 0
    std::istringstream test3(R"([1,"red",5])"); // p1: 6, p2: 6
    std::istringstream test4(R"([1,{"z":100,"a":{"a":[3]},"c":"red","b":2},3])"); // p1: 109, p2: 4

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
    std::cout << "Sum: " << sum(input) << std::endl;
}

void P2(std::istream& input) {

    std::stringstream ss;
    ss << input.rdbuf();
    std::string s = ss.str();

    size_t pos = 0;
    while ((pos = s.find(":\"red\"", pos)) != std::string::npos) {

        int32_t begin = pos;
        size_t end = pos;

        int32_t depth = 1;
        while (depth > 0 && --begin >= 0) {
            if (s[begin] == '}') {
                depth++;
            } else if (s[begin] == '{') {
                depth--;
            }
        }

        depth = 1;
        while (depth > 0 && ++end < s.length()) {
            if (s[end] == '{') {
                depth++;
            } else if (s[end] == '}') {
                depth--;
            }
        }

        s.erase(begin+1, end-begin-1);
        pos = begin;
    }

    ss.clear();
    ss.str(s);

    std::cout << "Non-Red Sum: " << sum(ss) << std::endl;
}

int32_t sum(std::istream& input) {

    int32_t result = 0;

    char c, pc = '\0';
    while (input >> c) {

        if (c < '0' || c > '9') {
            pc = c;
            continue;
        }

        input.unget();

        int32_t number;
        input >> number;

        if (pc == '-') {
            number *= -1;
        }

        result += number;
    }

    return result;
}
