#include <iostream>
#include <ios>
#include <iomanip>

// temporary
#include <unordered_map>
#include <map>

#include <pqxx/pqxx>
#include <vector>

#include "database.hpp"
#include "utils.hpp"
#include "config.hpp"

int main(int argc, char *argv[]) {
    auto mp{utils::parse_command_line(argc, argv)};
    config cfg(mp.at('c'));
    database db(cfg);
    // std::string qr{"SELECT datname FROM pg_database WHERE datistemplate = false;"};
    // std::string qr2{"select * from actor;"};

    auto vec{db.get_table_names()};
    for (const auto &name : vec) {
        std::cout << name << std::endl;
    }

    // database db{"dbname=mikhail user=postgres host=localhost"};
}
