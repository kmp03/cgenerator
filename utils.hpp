#ifndef UTILS_HPP
#define UTILS_HPP

#include <string>
#include <map>

namespace utils
{
    std::map<char, std::string> parse_command_line(int argc, char *argv[]);
}

#endif // UTILS_HPP
