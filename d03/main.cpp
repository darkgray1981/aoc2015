#include <iostream>
#include <fstream>
#include <sstream>
#include <chrono>
#include <unordered_map>
#include <unordered_set>

/*** OUTPUT ***

    Total: 2565
    2nd Total: 2639
    Time taken: 0.003s
 
 ***/

struct hash_pair { 
    template <class T1, class T2> 
    size_t operator()(const std::pair<T1, T2>& p) const
    { 
        auto hash1 = std::hash<T1>{}(p.first); 
        auto hash2 = std::hash<T2>{}(p.second); 
        return hash1 ^ hash2; 
    } 
};

using Pos = std::pair<int32_t, int32_t>;

void P1(std::istream& input);
void P2(std::istream& input);

int main() {
    auto start = std::chrono::steady_clock::now();

    std::istringstream test1(R"(>)"); // 2
    std::istringstream test2(R"(^>v<)"); // 4
    std::istringstream test3(R"(^v^v^v^v^v)"); // 2

    std::ifstream infile("input.txt");

    // P1(test1);
    // P1(test2);
    // P1(test3);
    P1(infile);

    infile.clear();
    infile.seekg(0);
    // P2(test1);
    // P2(test2);
    // P2(test3);
    P2(infile);

    auto end = std::chrono::steady_clock::now();
    std::cout << "Time taken: " 
		<< std::chrono::duration_cast<std::chrono::duration<double>>(end - start).count()
		<< "s" << std::endl;
}

void P1(std::istream& input) {

    std::unordered_set<Pos, hash_pair> set;
    
    char dir;
    Pos current(0, 0);

    set.insert(current);
    uint32_t result = 1;

    while (input >> dir) {

        switch (dir) {
            case '^':
                current.second--;
                break;
            case '>':
                current.first++;
                break;
            case 'v':
                current.second++;
                break;
            case '<':
                current.first--;
                break;
        }

        if (set.insert(current).second) {
            result++;
        }
    }

    std::cout << "Total: " << result << std::endl;
}

void P2(std::istream& input) {

    std::unordered_map<Pos, bool, hash_pair> map;
    
    char dir;
    Pos current[] = { Pos(0, 0), Pos(0, 0) };

    uint8_t who = 0;
    map[current[who]] = true;
    uint32_t result = 1;

    while (input >> dir) {

        switch (dir) {
            case '^':
                current[who].second--;
                break;
            case '>':
                current[who].first++;
                break;
            case 'v':
                current[who].second++;
                break;
            case '<':
                current[who].first--;
                break;
        }

        if (!map[current[who]]) {
            map[current[who]] = true;
            result++;
        }

        who = 1 - who;
    }

    std::cout << "2nd Total: " << result << std::endl;
}
