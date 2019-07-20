#include "utils.hpp"

#include <unistd.h> // linus specified

#include <iostream>

std::map<char, std::string> utils::parse_command_line(int argc, char * argv[])
{
    std::map<char, std::string> response;

    opterr=0; // uncomment to prohibit error message to stderr
    int rez=0;

    while ( (rez = getopt(argc,argv,"c")) != -1){
        switch (rez){
        case 'c':
        {
            try {
                std::string str(optarg);
            } catch (...) {
                std::cout << "bad\n" << optarg;
            }
            //std::string str(optarg);
            //response.insert(std::make_pair<char, std::string>(rez, optarg));
            break;
        }

        case '?':
        {
            std::cout << "Error. Option not found" << std::endl;
        }

        };
    };

    return response;
}
