#include "utils.hpp"

//#include <unistd.h> // linus specified
#include <getopt.h>

#include <iostream>

std::map<char, std::string> utils::parse_command_line(int argc, char * argv[])
{
    std::map<char, std::string> response;

    const char* short_options = "c";

    int flag_config {};
    const struct option long_options[] = {
            {"config", required_argument, &flag_config,'c'},
            {nullptr, 0, nullptr,0}
        };
    int rez;
    int option_index = -1; // if equals -1 -> short option
    while ((rez=getopt_long(argc,argv,short_options,
            long_options,&option_index))!=-1){

            /*

            */
            switch(rez){
                case 'c':
                {
                    response.insert(std::make_pair<char, std::string>('c', std::string(optarg)));
                    break;
                }
                case '?': default: {
                    std::cout << "found unknown option\n" << std::endl;
                    break;
                };
            };
        };


    return response;
}
