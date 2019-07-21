#ifndef CONFIG_HPP
#define CONFIG_HPP

#include <unordered_map>

class config {
public:
    typedef std::unordered_map<std::string, std::unordered_map<std::string, std::string>> table_type;
    config();
    config(const std::string &);
    void reset(const std::string &);
    table_type get() const;

protected:
private:
    table_type m_data{};
    std::string m_name;

    void init();
};

#endif // CONFIG_HPP
