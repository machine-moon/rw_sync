#ifndef CONFIG_HPP
#define CONFIG_HPP

#include <cstdlib>
#include <optional>
#include <sstream>
#include <stdexcept>
#include <string>

class Config {
public:
    template<typename T>
    static std::optional<T> get_env(const std::string &var);
};

template<typename T>
std::optional<T> Config::get_env(const std::string &var) {
    const char *val = std::getenv(var.c_str());
    if (val == nullptr) {
        return std::nullopt;
    } else {
        std::stringstream ss(val);
        T result;
        ss >> result;
        if (ss.fail()) {
            throw std::runtime_error("Failed to convert environment variable to the requested type");
        }
        return result;
    }
}

#endif // CONFIG_HPP
