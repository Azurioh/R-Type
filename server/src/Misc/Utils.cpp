/*
** EPITECH PROJECT, 2025
** R-Type
** File description:
** Utils.cpp
*/

#include "Exception/Generic.hpp"
#include "Misc/Utils.hpp"

#include <iostream>
#include <iomanip>
#include <sstream>
#include <format>

const std::string Misc::Utils::GetTextOption(char **begin, char **end, const std::string& name)
{
    char **itr = std::find(begin, end, name);

    if (itr != end && ++itr != end) {
        return *itr;
    }
    throw Exception::Generic(std::format("Missing argument for option '{}'.", name));
}

void Misc::Utils::Log(const std::string& message, const LogLevel level)
{
    auto currentTimePoint = std::chrono::system_clock::now();
    auto timeT = std::chrono::system_clock::to_time_t(currentTimePoint);
    auto localTimeInfo = std::localtime(&timeT);

    switch (level) {
        case Informational:
            std::cerr << "\r[" << std::put_time(localTimeInfo, "%Y-%m-%d %H:%M:%S") << "] \033[0;32m>\033[0;0m " << message << std::endl;
            break;
        case Warning:
            std::cout << "\r[" << std::put_time(localTimeInfo, "%Y-%m-%d %H:%M:%S") << "] \033[0;33m>\033[0;0m " << message << std::endl;
            break;
        case Error:
            std::cout << "\r[" << std::put_time(localTimeInfo, "%Y-%m-%d %H:%M:%S") << "] \033[0;31m>\033[0;0m " << message << std::endl;
            break;
        default:
            break;
    }
}

std::string Misc::Utils::BytesToHex(const std::vector<std::uint8_t>& data)
{
    std::stringstream ss = {};

    ss << std::hex << std::uppercase;
    for (size_t i = 0; i < data.size(); i++) {
        if (i > 0) {
            ss << " ";
        }
        ss << std::setfill('0') << std::setw(2) << static_cast<std::int32_t>(data[i]);
    }

    return ss.str();
}
