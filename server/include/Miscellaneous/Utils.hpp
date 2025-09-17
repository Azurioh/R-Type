/*
** EPITECH PROJECT, 2025
** R-Type
** File description:
** Utils.hpp
*/

#pragma once

#include <string>

namespace Miscellaneous
{
    /**
     * @class Utils
     * @brief This class provides different utility functions.
     */
    class Utils
    {
        public:
            /**
             * @enum LogLevel
             * @brief Represents the level of logging.
             */
            enum LogLevel {
                Informational, /*!> Informational log level */
                Error /*!> Error log level */
            };

            /**
             * @brief Get the value of an option from a list of arguments
             *
             * @param begin The beginning of the list of arguments
             * @param end The end of the list of arguments
             * @param name The name of the option to search for
             * @return The value of the option, or an empty string if not found
             */
            static const std::string GetTextOption(char **begin, char **end, const std::string& name);

            /**
             * @brief Log an informational message with a timestamp
             *
             * @param message The informational message to log
             * @param level The level of the log message (default is informational)
             */
            static void Log(const std::string& message, const LogLevel level = Informational);
    };
}
