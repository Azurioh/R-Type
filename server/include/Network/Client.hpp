/*
** EPITECH PROJECT, 2025
** R-Type
** File description:
** Client.hpp
*/

#pragma once

#include "Network/Message.hpp"
#include "Variables.hpp"

#include <boost/asio.hpp>
#include <functional>
#include <cstdint>
#include <memory>
#include <vector>
#include <array>
#include <mutex>

/**
 * @namespace Network
 * @brief Contains networking-related classes and functions.
 */
namespace Network
{
    /**
     * @class Client
     * @brief Represents a network client with asynchronous communication capabilities.
     */
    class Client : public std::enable_shared_from_this<Client>
    {
        public:
            /**
             * @brief Callback function type for handling disconnection events.
             */
            using DisconnectCallback = std::function<void(std::uint32_t)>;

            /**
             * @brief Callback function type for handling received data.
             */
            using DataCallback = std::function<void(std::uint32_t, const std::vector<std::uint8_t>&)>;

            /**
             * @brief Create a new client.
             *
             * @param id The unique identifier for the client.
             * @param socket A shared pointer to the socket associated with the client.
             */
            Client(std::uint32_t id, std::shared_ptr<boost::asio::ip::tcp::socket> socket);

            /**
             * @brief Get the unique identifier of the client.
             *
             * @return The client's unique identifier.
             */
            std::uint32_t GetId() const;

            /**
             * @brief Start asynchronous operations for this client.
             *
             * @param onDisconnect Callback function to call when client disconnects.
             * @param onData Callback function to call when data is received.
             */
            void StartAsync(DisconnectCallback onDisconnect, DataCallback onData);

            /**
             * @brief Send data to the client asynchronously.
             *
             * @param message The message to send.
             */
            void SendAsync(const Message& message);

            /**
             * @brief Disconnect the client by closing its socket.
             */
            void Disconnect();

            /**
             * @brief Check if the client is connected.
             *
             * @return True if the client is connected, false otherwise.
             */
            bool IsConnected() const;

        private:
            /**
             * @brief Start asynchronous read operation for the message header.
             */
            void StartReadHeader();

            /**
             * @brief Handle completed header read operation.
             *
             * @param error The error code from the read operation.
             * @param bytes Number of bytes read.
             */
            void HandleReadHeader(const boost::system::error_code& error, std::size_t bytes);

            /**
             * @brief Start asynchronous read operation for the message content.
             */
            void StartReadContent();

            /**
             * @brief Handle completed content read operation.
             *
             * @param error The error code from the read operation.
             * @param bytes Number of bytes read.
             */
            void HandleReadContent(const boost::system::error_code& error, std::size_t bytes);

            /**
             * @brief Handle completed write operation.
             *
             * @param error The error code from the write operation.
             * @param bytes Number of bytes written.
             */
            void HandleWrite(const boost::system::error_code& error, std::size_t bytes);

            std::shared_ptr<boost::asio::ip::tcp::socket> _socket; /*!< The socket associated with the client */
            boost::asio::ip::udp::endpoint _endpoint; /*!< The endpoint associated with the client */
            std::uint32_t _id; /*!< The unique identifier for the client */

            std::array<std::uint8_t, HEADER_SIZE> _headerBuffer; /*!< Buffer for incoming header data */
            std::vector<std::uint8_t> _contentBuffer; /*!< Buffer for incoming content data */
            std::uint32_t _currentLength; /*!< Current message content length being processed */
            std::uint16_t _currentId; /*!< Current message ID being processed */

            std::deque<Message> _writeQueue; /*!< Queue for outgoing messages */
            std::mutex _writeQueueMutex; /*!< Mutex to protect the write queue */
            bool _writing; /*!< Flag to indicate if a write operation is in progress */

            DisconnectCallback _onDisconnect; /*!< Callback for disconnection events */
            DataCallback _onData; /*!< Callback for received data */
    };
}
