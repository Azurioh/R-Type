/*
** EPITECH PROJECT, 2025
** R-Type
** File description:
** EmptyQueueError.hpp
*/

#pragma once

#include "Exception/Generic.hpp"

namespace Exception
{
    /**
     * @class EmptyQueueError
     * @brief Exception thrown when attempting to receive a message from an empty queue.
     */
    class EmptyQueueError : public Generic
    {
        public:
            /**
             * @brief Create an error indicating an attempt to receive from an empty queue.
             *
             * @param where The location where the exception was thrown (default: current location).
             */
            EmptyQueueError(const std::string& name, const std::source_location &where = std::source_location::current());

        private:
            /**
             * @brief Format the error message with the provided name.
             *
             * @param name The name to include in the error message.
             * @return The formatted error message.
             */
            const std::string FormatError(const std::string& name) const;
    };
}
