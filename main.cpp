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

void print_query(pqxx::result res, std::ostream & os = std::cout)
{
    const size_t width {20};

    // shows the names of columns
    for (size_t i {0}; i < res.begin().size(); ++i)
    {
        if (! res.begin()[static_cast<int>(i)].is_null())
            os << std::setw(width) << res.begin()[static_cast<int>(i)].name() << " | ";
        else
            os << std::setw(width) << "Null" << " | ";
    }
    os << std::endl;

    // prints data
    for (auto iter {res.begin()}; iter != res.end(); ++iter)
    {
        for (size_t col {0}; col < iter[static_cast<int>(col)].size(); ++col)
        {
            if (! iter[static_cast<int>(col)].is_null())
                os << std::setw(width) << iter[static_cast<int>(col)].as<std::string>() << " | ";
            else
                os << std::setw(width) << "Null" << " | ";
        }
        os << std::endl;
    }

}


int main(int argc, char *argv[])
{
    auto table  {utils::parse_command_line(argc, argv)};
    for (auto _pair : table)
    {
        std::cout << "option: "  << _pair.first << ", value: " << _pair.second << std::endl;
    }
}
