#include <iostream>
#include <fstream>
#include <sstream>
#include <chrono>

/*** OUTPUT ***

    House #: 665280
    2nd House #: 705600
    Time taken: 0.266s
 
 ***/

void P1(uint32_t input);
void P2(uint32_t input);
uint32_t divisorSum(uint32_t n);
uint32_t delivered(uint32_t n);

int main() {
    auto start = std::chrono::steady_clock::now();

    std::ifstream infile("input.txt");
    uint32_t input;
    infile >> input;

    P1(input);

    P2(input);

    auto end = std::chrono::steady_clock::now();
    std::cout << "Time taken: " 
		<< std::chrono::duration_cast<std::chrono::duration<double>>(end - start).count()
		<< "s" << std::endl;
}

void P1(uint32_t input) {

    uint32_t result = 0;

    uint32_t h = 0, step = 1;
    if (input > 1000) {
        step = 6;
    }

    while (h += step) {

        uint32_t presents = divisorSum(h);

        if (10 * presents >= input) {
            result = h;
            break;
        }
    }

    std::cout << "House #: " << result << std::endl;
}

void P2(uint32_t input) {

    uint32_t result = 0;

    uint32_t h = 0, step = 1;
    if (input > 2000) {
        step = 6;
    }

    while (h += step) {

        uint32_t presents = delivered(h);

        if (11 * presents >= input) {
            result = h;
            break;
        }
    }

    std::cout << "2nd House #: " << result << std::endl;
}

uint32_t divisorSum(uint32_t n) {

	uint32_t sum = (n != 1 ? 1 : 0) + n;

	uint32_t i = 0;
	for (i = 2; i*i < n; i++) {
		if (n%i == 0) {
			sum += i + n/i;
		}
	}

	if (i*i == n) {
		sum += i;
	}

	return sum;
}

uint32_t delivered(uint32_t n) {

    uint32_t sum = 0;

	uint32_t i = 0;
	for (i = 1; i <= 50 && i*i < n; i++) {

		if (n%i == 0) {
			if (n <= i*50) {
                sum += i;
            };

            sum += n/i;
		}
	}

	if (i*i == n && n <= i*50) {
		sum += i;
	}

	return sum;
}
