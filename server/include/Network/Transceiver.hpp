/*
** EPITECH PROJECT, 2025
** R-Type
** File description:
** Transceiver.hpp
*/

#pragma once

#include "Network/Client.hpp"

#include <boost/asio.hpp>
#include <unordered_map>
#include <cstdint>
#include <memory>
#include <thread>
#include <atomic>
#include <mutex>

/**
 * @namespace Network
 * @brief Contains networking-related classes and functions.
 */
namespace Network
{
    /**
     * @class Transceiver
     * @brief Server that manages client connections using Asio.
     */
    class Transceiver
    {
        public:
            /**
             * @brief Constructor for Transceiver.
             *
             * @param port The port number to listen on.
             */
            Transceiver(std::uint16_t port);

            /**
             * @brief Destructor for Transceiver.
             */
            ~Transceiver();

            /**
             * @brief Start the server and begin accepting connections.
             */
            void Start();

            /**
             * @brief Stop the server and disconnect all clients.
             */
            void Stop();

            /**
             * @brief Check if the server is running.
             *
             * @return true if the server is running, false otherwise.
             */
            bool IsRunning() const;

            /**
             * @brief Get the number of connected clients.
             *
             * @return The number of connected clients.
             */
            std::size_t GetClientCount() const;

            /**
             * @brief Send data to a specific client.
             *
             * @param clientId The ID of the client to send data to.
             * @param message The message to send.
             * @return True if the client was found and data was sent, false otherwise.
             */
            bool SendToClient(std::uint32_t clientId, const Client::Message& message);

            /**
             * @brief Broadcast data to all connected clients.
             *
             * @param message The message to broadcast.
             */
            void BroadcastToAll(const Client::Message& message);

        private:
            /**
             * @brief Start accepting new connections asynchronously.
             */
            void StartAccept();

            /**
             * @brief Handle a new client connection.
             *
             * @param socket The socket for the new connection.
             * @param error The error code from the accept operation.
             */
            void HandleAccept(std::shared_ptr<boost::asio::ip::tcp::socket> socket, const boost::system::error_code& error);

            /**
             * @brief Handle client disconnection.
             *
             * @param clientId The identifier of the client that disconnected.
             */
            void HandleClientDisconnect(std::uint32_t clientId);

            /**
             * @brief Handle data received from a client.
             *
             * @param clientId The identifier of the client that sent the data.
             * @param message The received message.
             */
            void HandleClientData(std::uint32_t clientId, const Client::Message& message);

            /**
             * @brief Generate a unique client identifier.
             *
             * @return A unique client identifier.
             */
            std::uint32_t GenerateClientId();

            std::thread _thread; /*!< Thread for running the IO context */
            boost::asio::io_context _context; /*!< The IO context */
            boost::asio::ip::tcp::acceptor _acceptor; /*!< The acceptor for incoming connections */

            std::unordered_map<std::uint32_t, std::shared_ptr<Client>> _clients; /*!< Map of connected clients */
            mutable std::mutex _clientsMutex; /*!< Mutex to protect the clients map */
            std::atomic<bool> _running; /*!< Flag indicating if the server is running */
            std::atomic<std::uint32_t> _nextId; /*!< Counter for generating unique client identifiers */
            std::uint16_t _port; /*!< The port number the server listens on */
    };
}
