#include <iostream>
#include <fstream>
#include <sstream>
#include <chrono>
#include <unordered_map>
#include <vector>
#include <algorithm>

/*** OUTPUT ***

    Total: 255
    2nd Total: 55
    Time taken: 0.009s
 
 ***/

void P1(std::istream& input);
void P2(std::istream& input);

int main() {
    auto start = std::chrono::steady_clock::now();

    std::istringstream test1(R"(ugknbfddgicrmopn aaa jchzalrnumimnmhp haegwjzuvuyypxyu dvszwmarrgswjxmb)"); // p1: 2
    std::istringstream test2(R"(qjhvhtzxzqqjkmpb xxyxx uurcxstgmygtbstg ieodomkazucvgmuy)"); // p2: 2

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

    bool vowels[32] = {};
    for (const auto& v : {'a', 'e', 'i', 'o', 'u'}) {
        vowels[v - 'a'] = true;
    }

    std::vector<std::string> forbidden = { "ab", "cd", "pq", "xy" };

    uint32_t result = 0;

    std::string s;
    while (input >> s) {

        uint32_t vowelCount = (vowels[s[0]-'a'] ? 1 : 0);
        bool hasDouble = false;
        bool hasForbidden = false;

        for (size_t i = 1; !hasForbidden && i < s.length(); i++) {
            vowelCount += (vowels[s[i]-'a'] ? 1 : 0);
            hasDouble = hasDouble || s[i-1] == s[i];

            if (std::find(forbidden.begin(), forbidden.end(), s.substr(i-1, 2)) != forbidden.end()) {
                hasForbidden = true;
            }
        }

        if (vowelCount >= 3 && hasDouble && !hasForbidden) {
            result++;
        }
    }

    std::cout << "Total: " << result << std::endl;
}

void P2(std::istream& input) {

    uint32_t result = 0;

    std::string s;
    while (input >> s) {

        std::unordered_map<std::string, uint32_t> map;

        bool hasPair = false;
        bool hasRepeat = false;

        for (size_t i = 1; i < s.length(); i++) {
            auto pair = s.substr(i-1, 2);

            if (map.find(pair) != map.end()) {
                hasPair = (i - map[pair] > 1);
            } else {
                map[pair] = i;
            }

            hasRepeat = hasRepeat || (i >= 2 && s[i-2] == s[i]);
        }

        if (hasPair && hasRepeat) {
            result++;
        }
    }

    std::cout << "2nd Total: " << result << std::endl;
}
