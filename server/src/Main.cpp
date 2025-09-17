/*
** EPITECH PROJECT, 2025
** R-Type
** File description:
** Main.cpp
*/

#include "Miscellaneous/Utils.hpp"
#include "Exception/Generic.hpp"
#include "Transciever.hpp"

#include <exception>
#include <iostream>

/**
 * @brief Run the transciever with the specified port.
 *
 * @param port The port number to connect to.
 */
static void Run(const std::uint16_t port) {
    auto& transciever = Transciever::GetInstance();

    transciever.Initialize(port);
    transciever.Deinitialize();
}

/**
 * @brief Retrieve command-line arguments and start the application.
 *
 * @return Exit status code.
 */
int main(int argc, char **argv) {
    try {
        if (argc != 3) {
            throw Exception::Generic("You must provide the port number.");
        }

        const std::string portTextValue = Miscellaneous::Utils::GetTextOption(argv, argv + argc, "-p");
        const std::uint16_t portValue = static_cast<std::uint16_t>(std::stoi(portTextValue));

        Run(portValue);
    } catch (const Exception::Generic& ex) {
        std::cerr << ex << std::endl;
        return 1;
    } catch (const std::exception& ex) {
        std::cerr << ex.what() << std::endl;
        return 1;
    } catch (...) {
        std::cerr << "Unknown error occurred." << std::endl;
        return 1;
    }
    return 0;
}
