#include <iostream>
#include <fstream>
#include <sstream>
#include <chrono>
#include <iomanip>
#include <openssl/md5.h> // add -lcrypto at the end when compiling

/*** OUTPUT ***

    Number: 254575
    Number: 1038736
    Time taken: 2.542s
 
 ***/

void P1(const std::string& input);
void P2(const std::string& input);
std::string md5string(const std::string& in);

int main() {
    auto start = std::chrono::steady_clock::now();

    // P1("abcdef"); // p1: 609043
    // P1("pqrstuv"); // p1: 1048970

    std::ifstream infile("input.txt");
    std::string input;
    infile >> input;

    P1(input);

    P2(input);

    auto end = std::chrono::steady_clock::now();
    std::cout << "Time taken: " 
        << std::chrono::duration_cast<std::chrono::duration<double>>(end - start).count()
        << "s" << std::endl;
}

void P1(const std::string& input) {

    uint32_t result = 0;

    for (uint32_t i = 1; ; i++) {
        auto md5 = md5string(input + std::to_string(i));
        if (md5.compare(0, 5, "00000") == 0) {
            result = i;
            break;
        }
    }

    std::cout << "Number: " << result << std::endl;
}

void P2(const std::string& input) {

    uint32_t result = 0;

    for (uint32_t i = 1; ; i++) {
        auto md5 = md5string(input + std::to_string(i));
        if (md5.compare(0, 6, "000000") == 0) {
            result = i;
            break;
        }
    }

    std::cout << "Number: " << result << std::endl;
}

std::string md5string(const std::string& in) {

    unsigned char result[MD5_DIGEST_LENGTH];
    MD5((unsigned char*)in.data(), in.length(), result);

    std::ostringstream ss;
    ss << std::hex << std::setfill('0');
    for (auto c : result) {
        ss << std::setw(2) << (int32_t)c;
    }

    return ss.str();
}
