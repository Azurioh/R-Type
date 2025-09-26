/*
** EPITECH PROJECT, 2025
** R-Type
** File description:
** Message.hpp
*/

#pragma once

#include <cstdint>
#include <vector>

/**
 * @namespace Network
 * @brief Contains networking-related classes and functions.
 */
namespace Network
{
    /**
     * @class Message
     * @brief Represents a network message with an identifier and content.
     */
    class Message
    {
        public:
            /**
             * @brief Construct a new message.
             *
             * @param id The message identifier.
             * @param content The message content as a vector of bytes.
             */
            Message(const std::uint16_t id, const std::vector<std::uint8_t>& content);

            /**
             * @brief Construct a new message from raw data.
             *
             * @param raw The raw byte vector containing the serialized message (header + content).
             */
            Message(const std::vector<std::uint8_t>& raw);

            /**
             * @brief Get the message identifier.
             *
             * @return The message identifier.
             */
            std::uint16_t GetId() const;

            /**
             * @brief Get the message content.
             *
             * @return The message content as a vector of bytes.
             */
            const std::vector<std::uint8_t>& GetContent() const;

            /**
             * @brief Serialize the message into a byte vector, including header and content.
             *
             * @return A vector of bytes representing the serialized message.
             */
            std::vector<std::uint8_t> Serialize() const;

        private:
            std::uint16_t _id; /*!< The message identifier */
            std::vector<std::uint8_t> _content; /*!< The message content */
    };
}
