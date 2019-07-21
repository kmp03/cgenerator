#include <iostream>
#include <ios>
#include <iomanip>

// temporary
#include <unordered_map>

#include <pqxx/pqxx>

#include "database.hpp"
#include "utils.hpp"
#include "config.hpp"

int main(int argc, char *argv[]) {
    std::string name = "config.cfg";
    config cfg;
    try {
        cfg.reset(name);
    } catch (...) {
        std::cout << "bad config";
        return 1;
    }

    auto table = cfg.get();
    for (auto section : table) {
        std::cout << section.first << std::endl;
        for (auto key_value : section.second) {
            std::cout << key_value.first << "=" << key_value.second << std::endl;
        }
        std::cout << std::endl;
    }
}
