/*
** EPITECH PROJECT, 2025
** R-Type
** File description:
** Asio.cpp
*/

#include "Wrapper/Asio.hpp"

Wrapper::Asio::Socket Wrapper::Asio::CreateSocket(IoContext& context, const std::uint16_t port)
{
    Socket socket(context, Endpoint(boost::asio::ip::udp::v4(), port));
    return socket;
}
