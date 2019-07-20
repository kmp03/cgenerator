#ifndef UTILS_HPP
#define UTILS_HPP

#include <string>
#include <map>
#include <iostream>
#include <pqxx/pqxx>

namespace utils {
std::map<char, std::string> parse_command_line(int argc, char *argv[]);
void print_query(pqxx::result res, std::ostream &os = std::cout);
} // namespace utils

#endif // UTILS_HPP
