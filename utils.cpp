#include "utils.hpp"

//#include <unistd.h> // linus specified
#include <getopt.h>

#include <iostream>
#include <ios>
#include <iomanip>

std::map<char, std::string>  utils::parse_command_line(int argc, char * argv[])
{
    std::map<char, std::string> response;

    const char* short_options = "c:";
    const struct option long_options[] =
    {
            {"config", required_argument, nullptr,'c'},
            {nullptr, 0, nullptr,0}
    };

    int rez;
    int option_index = -1; // if equals -1 -> short option
    while ((rez=getopt_long(argc,argv,short_options,
            long_options,&option_index))!=-1)
    {
            switch(rez){
                case 'c':
                {
                    response.insert(std::make_pair<char, std::string>('c', std::string(optarg)));
                    break;
                }
                case '?': default:
                {
                    std::cout << "found unknown option\n" << std::endl;
                    break;
                };
            };
        };
    return response;
}
void                         utils::print_query(pqxx::result res, std::ostream & os)
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

