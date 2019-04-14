#include <iostream>
#include <fstream>
#include <sstream>
#include <chrono>
#include <vector>
#include <regex>

/*** OUTPUT ***

    Score: 222870
    Limit score: 117936
    Time taken: 0.008s
 
 ***/

struct Ingredient {
    // std::string name;
    int32_t capacity;
    int32_t durability;
    int32_t flavor;
    int32_t texture;
    int32_t calories;
};

void P1(std::istream& input);
void P2(std::istream& input);
std::vector<Ingredient> parse(std::istream& input);
Ingredient addmul(const Ingredient& a, const Ingredient& b, const int32_t n);
int32_t combine(Ingredient mix, int32_t spoons, size_t index, std::vector<Ingredient>& v, int32_t limit = 0);

int main() {
    auto start = std::chrono::steady_clock::now();

    std::istringstream test1(R"(Butterscotch: capacity -1, durability -2, flavor 6, texture 3, calories 8
Cinnamon: capacity 2, durability 3, flavor -2, texture -1, calories 3)"); // p1: 62842880, p2: 57600000

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

    auto ingredients = parse(input);

    // auto mix = Ingredient{"Mix", 0, 0, 0, 0, 0};

    int32_t result = combine(Ingredient{}, 100, 0, ingredients);

    std::cout << "Score: " << result << std::endl;
}

void P2(std::istream& input) {

    auto ingredients = parse(input);

    int32_t result = combine(Ingredient{}, 100, 0, ingredients, 500);

    std::cout << "Limit score: " << result << std::endl;
}

std::vector<Ingredient> parse(std::istream& input) {

    std::vector<Ingredient> ingredients;

    std::regex re("^(\\w+?): capacity (-?\\d+?), durability (-?\\d+?), flavor (-?\\d+?), texture (-?\\d+?), calories (-?\\d+?)");
    std::smatch matches;

    std::string line;
    while (std::getline(input, line)) {

        if (!std::regex_search(line, matches, re)) {
            std::cout << "Failed on: " << line << std::endl;
            continue;
        }

        Ingredient ing{};

        // ing.name = matches[1].str();
        ing.capacity = std::stoi(matches[2].str());
        ing.durability = std::stoi(matches[3].str());
        ing.flavor = std::stoi(matches[4].str());
        ing.texture = std::stoi(matches[5].str());
        ing.calories = std::stoi(matches[6].str());

        ingredients.push_back(ing);
    }

    return ingredients;
}

Ingredient addmul(const Ingredient& a, const Ingredient& b, const int32_t n) {

    return Ingredient{
        // a.name + b.name,
        a.capacity + b.capacity * n,
        a.durability + b.durability * n,
        a.flavor + b.flavor * n,
        a.texture + b.texture * n,
        a.calories + b.calories * n,
    };
}

int32_t combine(Ingredient mix, int32_t spoons, size_t index, std::vector<Ingredient>& v, int32_t limit /* = 0 */) {

    if (index == v.size()-1) {
        mix = addmul(mix, v[index], spoons);

        if (limit > 0 && mix.calories != limit) {
            return 0;
        }

        if (mix.capacity <= 0 || mix.durability <= 0 || mix.flavor <= 0 || mix.texture <= 0) {
            return 0;
        }

        return mix.capacity * mix.durability * mix.flavor * mix.texture;
    }

    int32_t result = 0;

    for (int32_t i = 0; i <= spoons; i++) {
        result = std::max(result, combine(addmul(mix, v[index], i), spoons-i, index+1, v, limit));
    }

    return result;
}
