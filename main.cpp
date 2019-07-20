#include <iostream>
#include <ios>
#include <iomanip>

// temporary
#include <thread>
#include <mutex>
#include <map>

#include <pqxx/pqxx>

#include "database.hpp"
#include "utils.hpp"

int main(int argc, char *argv[]) {
    auto table{utils::parse_command_line(argc, argv)};

    for (auto _pair : table) {
        std::cout << "option: " << _pair.first << ", value: " << _pair.second << std::endl;
    }
}
