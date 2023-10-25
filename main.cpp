#include <iostream>
#include <fstream>
#include <sstream>
#include <unordered_map>
#include <cstdlib>
#include <cstring>

std::unordered_map<std::string, std::string> fill_map(const std::string &filepath) {
    std::fstream fs(filepath, std::ios::in);

    if (!fs) {
        std::cerr << "File " << "'" << filepath << "' not found!\n";
        std::exit(1);
    }

    std::unordered_map<std::string, std::string> m{};

    std::string line;
    while (std::getline(fs, line)) {
        std::stringstream ss(line);
        std::string p0, p1;

        std::getline(ss, p0, ',');
        std::getline(ss, p1, ',');

        m.insert(std::pair<std::string, std::string>(p0, p1));
    }

    fs.close();

    return m;
}

int game_loop(std::unordered_map<std::string, std::string> &capitals_map) {
    int strikes = 0, score = 0;
    while (strikes < 3) {
        auto it = capitals_map.begin();
        std::advance(it, rand() % capitals_map.size());
        size_t idx = rand() % capitals_map.size();
        std::cout << "the capital of " << it->first << " is:  ";

        std::string answer;
        std::getline(std::cin, answer);

        if (std::strcmp(answer.c_str(), it->second.c_str()) == 0) {
            std::cout << "correct!" << std::endl;
            score += 1;
            continue;
        }

        std::cout << "wrong, the capital of " << it->first << " is " << it->second << "!" << std::endl;
        strikes += 1;

        capitals_map.erase(it);
    }

    std::cout << "Game over! Your score: " << score << std::endl;

    return 0;
}

int main(int argc, char **argv) {
    srand(time(nullptr));

    const std::string &filepath = "../capitals.csv";
    std::unordered_map<std::string, std::string> capitals_map = fill_map(filepath);

    game_loop(capitals_map);

    return 0;
}
