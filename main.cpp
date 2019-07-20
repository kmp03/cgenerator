#include <iostream>
#include <ios>
#include <iomanip>


// temporary
#include <thread>
#include <mutex>

#include <pqxx/pqxx>

#include "database.hpp"

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

void print_square(char ch)
{
    std::this_thread::sleep_for(std::chrono::milliseconds(30)); // kind of complex work
    const size_t size {10};
    for (size_t i {}; i < size; ++i)
    {
        for (size_t j {}; j < size; ++j)
        {
            std::cout << ch;
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(30)); // kind of complex work
}

struct s
{
    s()
    {
        std::cout << "ctor\n";
    }
    ~s()
    {
        std::cout << "dtor\n";
    }
};

void foo()
{
    try {
        s a;
        throw 12;
    } catch (...) {

        throw;
    }
}

int main(int, char *argv[])
{
    foo();

}
