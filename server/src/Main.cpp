/*
** EPITECH PROJECT, 2025
** R-Type
** File description:
** Main.cpp
*/

#include "Miscellaneous/Utils.hpp"
#include "Network/Transceiver.hpp"
#include "Exception/Generic.hpp"

#include <exception>
#include <iostream>
#include <csignal>
#include <thread>
#include <chrono>
#include <atomic>

/**
 * @brief Atomic boolean to control the running state of the application.
 */
std::atomic<bool> isRunning(true);

/**
 * @brief Signal handler to gracefully stop the application.
 *
 * @param signal The signal number received.
 */
static void SignalHandler(std::int32_t signal) {
    switch (signal) {
        case SIGINT:
            isRunning = false;
            break;
        default:
            break;
    }
}

/**
 * @brief Run the transciever with the specified port.
 *
 * @param port The port number to connect to.
 */
static void Run(const std::uint16_t port) {
    Network::Transceiver server(port);

    server.Start();

    while (isRunning.load()) {
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }

    server.Stop();
}

/**
 * @brief Retrieve command-line arguments and start the application.
 *
 * @return Exit status code.
 */
std::int32_t main(std::int32_t argc, char **argv) {
    try {
        if (argc != 3) {
            throw Exception::Generic("You must provide the port number.");
        }

        const std::string portTextValue = Miscellaneous::Utils::GetTextOption(argv, argv + argc, "-p");
        const std::uint16_t portValue = static_cast<std::uint16_t>(std::stoi(portTextValue));

        std::signal(SIGINT, SignalHandler);

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
