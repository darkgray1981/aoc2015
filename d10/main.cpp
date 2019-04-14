#include <iostream>
#include <fstream>
#include <sstream>
#include <chrono>

/*** OUTPUT ***

    Length (40x): 329356
    Length (50x): 4666278
    Time taken: 0.154s
 
 ***/

void P12(const std::string& input, uint32_t loops);

int main() {
    auto start = std::chrono::steady_clock::now();

    std::ifstream infile("input.txt");
    std::string input;
    infile >> input;

    P12(input, 40);

    P12(input, 50);

    auto end = std::chrono::steady_clock::now();
    std::cout << "Time taken: " 
		<< std::chrono::duration_cast<std::chrono::duration<double>>(end - start).count()
		<< "s" << std::endl;
}

void P12(const std::string& input, uint32_t loops) {

    std::string result = input;

    for (uint32_t n = 0; n < loops; n++) {

        std::string next;
        next.reserve(2*result.length());

        char digit = result[0];
        uint32_t count = 1;

        for (size_t i = 1; i < result.length(); i++) {
            if (result[i] != digit) {
                // next += std::to_string(count);
                next += '0' + count;
                next += digit;
                digit = result[i];
                count = 0;
            }

            count++;
        }

        // next += std::to_string(count);
        next += '0' + count;
        next += digit;

        result = std::move(next);
    }

    std::cout << "Length (" << loops << "x): " << result.length() << std::endl;
}
