/*
** EPITECH PROJECT, 2025
** R-Type
** File description:
** Transciever.hpp
*/

#pragma once

#include "Miscellaneous/Singleton.hpp"

#include <unordered_map>
#include <iostream>
#include <cstdint>
#include <vector>
#include <string>
#include <queue>

/**
 * @class Transciever
 * @brief This class is responsible for sending and receiving messages.
 */
class Transciever : public Miscellaneous::Singleton<Transciever>
{
    public:
        /**
         * @struct Message
         * @brief Represents a message with a header and body.
         */
        struct Message {
            std::uint8_t header; /*!> The header of the message */
            std::vector<std::uint8_t> body; /*!> The body of the message */
        };

        /**
         * @enum Direction
         * @brief Represents the direction of the message.
         */
        enum Direction {
            Incoming, /*!> The message is incoming */
            Outgoing /*!> The message is outgoing */
        };

        /**
         * @brief Constructs the transciever with the specified port.
         *
         * @param port The port number to connect to.
         */
        void Initialize(const std::uint16_t port);

        /**
         * @brief Deinitializes the transciever.
         */
        void Deinitialize();

        /**
         * @brief Pop and receive the message from the queue.
         *
         * @param id The identifier associated with the message.
         * @return The received message.
         */
        Message ReceiveMessage(const std::uint32_t id);

        /**
         * @brief Add and send the message to the queue.
         *
         * @param id The identifier associated with the message.
         * @param header The header of the message.
         * @param body The body of the message.
         */
        void SendMessage(const std::uint32_t id, const std::uint8_t header, const std::vector<std::uint8_t>& body);

    private:
        friend class Miscellaneous::Singleton<Transciever>; /*!> Allow the singleton to access the private constructor and destructor */

        /**
         * @brief Key type for the message queue map.
         */
        using QueueKey = std::pair<std::uint32_t, Direction>;

        /**
         * @struct QueueKeyHash
         * @brief Structure holding the hash function for the queue key.
         */
        struct QueueKeyHash {
            /**
             * @brief Hash function for the queue key.
             *
             * @param key The queue key to hash.
             * @return The computed hash value.
             */
            std::size_t operator()(const QueueKey& key) const;
        };

        /**
         * @brief Set the constructor private to prevent instantiation of the class.
         */
        Transciever() = default;

        /**
         * @brief Set the destructor private to prevent deletion of the class.
         */
        ~Transciever() = default;

        /**
         * @brief Get the message queue for the specified identifier
         *
         * @param direction The direction of the message.
         * @param id The identifier associated with the message.
         * @param explosion If true, throw an error if the queue does not exist.
         * @return A reference to the message queue.
         */
        std::queue<Message>& GetQueue(const Direction direction, const std::uint32_t id, const bool explosion = false);

        std::unordered_map<QueueKey, std::queue<Message>, QueueKeyHash> _messages; /*!> The queue with the identifier and the direction as key */
        bool _initialized; /*!> Indicates if the transciever has been initialized */
};
