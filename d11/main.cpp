#include <iostream>
#include <fstream>
#include <chrono>

/*** OUTPUT ***

    Password: vzbxxyzz
    2nd Password: vzcaabcc
    Time taken: 0.013s
 
 ***/

void P1(const std::string& input);
void P2(const std::string& input);
std::string generate(const std::string& input, uint32_t count);
std::string prepare(const std::string& input);
void twist(std::string& s);
bool isAscending(const std::string& s);
bool isPaired(const std::string& s);
bool isPairedDistinct(const std::string& s);

int main() {
    auto start = std::chrono::steady_clock::now();

    const std::string test1 = "abcdefgh"; // p1: abcdffaa
    const std::string test2 = "ghijklmn"; // p1: ghjaabcc

    std::ifstream infile("input.txt");
    std::string input;
    infile >> input;

    // P1(test1);
    // P1(test2);
    P1(input);

    P2(input);

    auto end = std::chrono::steady_clock::now();
    std::cout << "Time taken: " 
		<< std::chrono::duration_cast<std::chrono::duration<double>>(end - start).count()
		<< "s" << std::endl;
}

void P1(const std::string& input) {
    std::cout << "Password: " << generate(input, 1) << std::endl;
}

void P2(const std::string& input) {
    std::cout << "2nd Password: " << generate(input, 2) << std::endl;
}

std::string generate(const std::string& input, uint32_t count) {

    std::string result = prepare(input);

    do {
        twist(result);
    } while (!isPaired(result) || !isAscending(result) || --count > 0);

    return result;
}

std::string prepare(const std::string& input) {

    std::string s = input;

    size_t i = 0;
    for ( ; i < s.length(); i++) {
        if (s[i] == 'i' || s[i] == 'o' || s[i] == 'l') {
            s[i]++;
            break;
        }
    }

    while (++i < s.length()) {
        s[i] = 'a';
    }

    return s;
}

void twist(std::string& s) {

    for (int32_t i = s.length()-1; i >= 0; i--) {

        if (s[i] == 'z') {
            s[i] = 'a';
            continue;
        }

        s[i]++;

        if (s[i] == 'i' || s[i] == 'o' || s[i] == 'l') {
            s[i]++;
        }

        break;
    }

}

bool isPaired(const std::string& s) {

    bool pair = false;

    for (size_t i = 1; i < s.length(); i++) {
        if (s[i] == s[i-1]) {
            if (pair) {
                return true;
            }

            pair = true;
            i++;
        }
    }

    return false;
}

bool isAscending(const std::string& s) {

    for (size_t i = 2; i < s.length(); i++) {
        if (s[i] == s[i-1]+1 && s[i] == s[i-2]+2) {
            return true;
        }
    }

    return false;
}

bool isPairedDistinct(const std::string& s) {

    char pair = -1;

    for (size_t i = 1; i < s.length(); i++) {
        if (s[i] == s[i-1]) {
            if (pair == -1) {
                pair = s[i];
            } else if (pair != s[i]) {
                return true;
            }

            i++;
        }
    }

    return false;
}
