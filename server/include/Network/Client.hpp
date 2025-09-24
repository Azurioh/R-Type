/*
** EPITECH PROJECT, 2025
** R-Type
** File description:
** Client.hpp
*/

#pragma once

#include <boost/asio.hpp>
#include <cstdint>
#include <memory>
#include <functional>
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
             * @struct Message
             * @brief Represents a message with a header and body.
             */
            struct Message {
                std::uint8_t header; /*!< The header of the message */
                std::vector<std::uint8_t> body; /*!> The body of the message */
            };

            /**
             * @brief Callback function type for handling disconnection events.
             */
            using DisconnectCallback = std::function<void(std::uint32_t)>;

            /**
             * @brief Callback function type for handling received data.
             */
            using DataCallback = std::function<void(std::uint32_t, const Message&)>;

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
             * @brief Start asynchronous read operation.
             */
            void StartRead();

            /**
             * @brief Handle completed read operation.
             *
             * @param error The error code from the read operation.
             * @param bytes Number of bytes read.
             */
            void HandleRead(const boost::system::error_code& error, std::size_t bytes);

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

            std::array<std::uint8_t, 1024> _readBuffer; /*!< Buffer for incoming data */
            std::vector<Message> _writeQueue; /*!< Queue for outgoing messages */
            std::mutex _writeQueueMutex; /*!< Mutex to protect the write queue */
            bool _writing; /*!< Flag to indicate if a write operation is in progress */

            DisconnectCallback _onDisconnect; /*!< Callback for disconnection events */
            DataCallback _onData; /*!< Callback for received data */
    };
}
