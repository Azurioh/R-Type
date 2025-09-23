/*
** EPITECH PROJECT, 2025
** R-Type
** File description:
** Asio.hpp
*/

#pragma once

#include <boost/asio.hpp>

/**
 * @namespace Wrapper
 * @brief A namespace for the wrapper of the project.
 */
namespace Wrapper
{
    /**
     * @class Asio
     * @brief A wrapper for Asio functionalities using UDP protocol.
     */
    class Asio
    {
        public:
            using IoContext = boost::asio::io_context; /*!> Type alias for io_context */

            using Endpoint = boost::asio::ip::udp::endpoint; /*!> Type alias for endpoint */

            using Socket = boost::asio::ip::udp::socket; /*!> Type alias for socket */

            /**
             * @brief Create and return a socket bound to the specified port.
             *
             * @param context The context to associate with the socket.
             * @param port The port number to bind the socket to.
             * @return Socket The created and bound socket.
             */
            static Socket CreateSocket(IoContext& context, const std::uint16_t port);
    };
}
