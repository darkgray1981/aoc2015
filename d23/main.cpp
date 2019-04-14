#include <iostream>
#include <fstream>
#include <sstream>
#include <chrono>
#include <vector>

/*** OUTPUT ***

    Reg b: 184
    a=1 Reg b: 231
    Time taken: 0.001s
 
 ***/

struct Operation {
    std::string name;
    uint8_t reg;
    int32_t val;
};

void P1(std::istream& input);
void P2(std::istream& input);
uint32_t run(std::istream& input, uint32_t initial = 0);

int main() {
    auto start = std::chrono::steady_clock::now();

    std::istringstream test1(R"(inc a
jio a, +2
tpl a
inc a)");

    std::ifstream infile("input.txt");

    // P1(test1);
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
    std::cout << "Reg b: " << run(input) << std::endl;
}

void P2(std::istream& input) {
    std::cout << "a=1 Reg b: " << run(input, 1) << std::endl;
}

uint32_t run(std::istream& input, uint32_t initial /* = 0 */) {

    std::vector<Operation> program;

    std::string line;
    while (std::getline(input, line)) {

        std::istringstream ss(line);

        std::string op, para, parb;
        ss >> op >> para;

        if (op == "hlf" || op == "tpl" || op == "inc") {
            program.push_back(Operation{op, (para == "b"), 0});
        } else if (op == "jmp") {
            program.push_back(Operation{op, 0, std::stoi(para)});
        } else {
            ss >> parb;
            program.push_back(Operation{op, (para == "b,"), std::stoi(parb)});
        }
    }

    uint32_t regs[] = { initial, 0 };

    for (size_t i = 0; i < program.size(); i++) {

        auto op = &program[i];

        if (op->name == "hlf") {
            regs[op->reg] /= 2;
        } else if (op->name == "tpl") {
            regs[op->reg] *= 3;
        } else if (op->name == "inc") {
            regs[op->reg]++;
        } else if (op->name == "jmp") {
            i += op->val - 1;
        } else if (op->name == "jie") {
            if (regs[op->reg] % 2 == 0) {
                i += op->val - 1;
            }
        } else if (op->name == "jio") {
            if (regs[op->reg] == 1) {
                i += op->val - 1;
            }
        }

    }

    return regs[1];
}
