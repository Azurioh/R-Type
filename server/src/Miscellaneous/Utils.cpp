/*
** EPITECH PROJECT, 2025
** R-Type
** File description:
** Utils.cpp
*/

#include "Miscellaneous/Utils.hpp"
#include "Exception/Generic.hpp"

#include <iostream>
#include <iomanip>
#include <format>

const std::string Miscellaneous::Utils::GetTextOption(char **begin, char **end, const std::string& name)
{
    char **itr = std::find(begin, end, name);

    if (itr != end && ++itr != end) {
        return *itr;
    }
    throw Exception::Generic(std::format("Missing argument for option '{}'.", name));
}

void Miscellaneous::Utils::Log(const std::string& message, const LogLevel level)
{
    auto currentTimePoint = std::chrono::system_clock::now();
    auto timeT = std::chrono::system_clock::to_time_t(currentTimePoint);
    auto localTimeInfo = std::localtime(&timeT);

    if (level != Error) {
        std::cout << "\r[" << std::put_time(localTimeInfo, "%Y-%m-%d %H:%M:%S") << "] \033[0;32m>\033[0;0m " << message << std::endl;
    } else {
        std::cerr << "\r[" << std::put_time(localTimeInfo, "%Y-%m-%d %H:%M:%S") << "] \033[0;31m>\033[0;0m " << message << std::endl;
    }
}
