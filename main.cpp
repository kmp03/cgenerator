#include <iostream>
#include <ios>
#include <iomanip>

#include <pqxx/pqxx>

#include "database.hpp"

void print_query(pqxx::result res, std::ostream & os = std::cout)
{
    size_t num_of_rows = res.size();
    size_t num_of_cols = res.begin()[0].size();
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

int main(int, char *argv[])
{
  database db {"dbname=mikhail user=postgres" };
  if (db.is_open())
  {
      const char query[]  {
                            R"(SELECT * FROM actor)"
                          };
      auto res = db.query(query);
      print_query(res);

  }
  else
  {
      std::cout << "ERROR" << std::endl;
  }
}
