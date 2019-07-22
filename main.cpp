#include <iostream>
#include <ios>
#include <iomanip>

// temporary
#include <unordered_map>
#include <map>

#include <pqxx/pqxx>

#include "database.hpp"
#include "utils.hpp"
#include "config.hpp"

int main(int argc, char *argv[]) {
    auto mp{utils::parse_command_line(argc, argv)};
    config cfg(mp.at('c'));
    database db(cfg);
    // database db{"dbname=mikhail user=postgres host=localhost"};
}
