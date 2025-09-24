/*
** EPITECH PROJECT, 2025
** R-Type
** File description:
** Transceiver.cpp
*/

#include "Network/Transceiver.hpp"
#include "Miscellaneous/Utils.hpp"
#include "Exception/Generic.hpp"

#include <format>

Network::Transceiver::Transceiver(std::uint16_t port) : _acceptor(_context, boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(), port)), _nextId(1), _isRunning(false), _port(port) {}

Network::Transceiver::~Transceiver()
{
    Stop();
}

void Network::Transceiver::Start()
{
    if (_isRunning.load()) {
        Miscellaneous::Utils::Log("Transceiver is already running", Miscellaneous::Utils::LogLevel::Warning);
    } else {
        _isRunning.store(true);

        try {
            StartAccept();

            _thread = std::thread([this]() {
                try {
                    _context.run();
                } catch (const std::exception& ex) {
                    Miscellaneous::Utils::Log(std::format("IO context error: {}", ex.what()), Miscellaneous::Utils::LogLevel::Error);
                }
            });

            Miscellaneous::Utils::Log(std::format("Server started on port {}", _port), Miscellaneous::Utils::LogLevel::Informational);
        } catch (const std::exception& ex) {
            _isRunning.store(false);
            throw new Exception::Generic(std::format("Failed to start server: {}", ex.what()));
        }
    }

}

void Network::Transceiver::Stop()
{
    if (_isRunning.load()) {
        _isRunning.store(false);

        try {
            if (_acceptor.is_open()) {
                _acceptor.close();
            }

            {
                std::lock_guard<std::mutex> lock(_clientsMutex);
                for (auto& [id, client] : _clients) {
                    if (client) {
                        client->Disconnect();
                    }
                }
                _clients.clear();
            }

            _context.stop();

            if (_thread.joinable()) {
                _thread.join();
            }

            _context.restart();

            Miscellaneous::Utils::Log("Server stopped", Miscellaneous::Utils::LogLevel::Informational);
        } catch (const std::exception& ex) {
            throw new Exception::Generic(std::format("Failed to stop server: {}", ex.what()));
        }
    }
}

bool Network::Transceiver::IsRunning() const
{
    return _isRunning.load();
}

std::size_t Network::Transceiver::GetClientCount() const
{
    std::lock_guard<std::mutex> lock(_clientsMutex);
    return _clients.size();
}

bool Network::Transceiver::SendToClient(std::uint32_t id, const Client::Message& message)
{
    std::lock_guard<std::mutex> lock(_clientsMutex);
    auto it = _clients.find(id);
    if (it != _clients.end() && it->second && it->second->IsConnected()) {
        it->second->SendAsync(message);
        return true;
    }
    return false;
}

void Network::Transceiver::BroadcastToAll(const Client::Message& message)
{
    std::lock_guard<std::mutex> lock(_clientsMutex);
    for (const auto& [id, client] : _clients) {
        if (client && client->IsConnected()) {
            client->SendAsync(message);
        }
    }
}

void Network::Transceiver::StartAccept()
{
    auto socket = std::make_shared<boost::asio::ip::tcp::socket>(_context);

    _acceptor.async_accept(*socket, [this, socket](const boost::system::error_code& ec) {
        HandleAccept(socket, ec);
    });
}

void Network::Transceiver::HandleAccept(std::shared_ptr<boost::asio::ip::tcp::socket> socket, const boost::system::error_code& ec)
{
    if (!ec && _isRunning.load()) {
        try {
            std::uint32_t id = GenerateClientId();
            auto client = std::make_shared<Client>(id, socket);

            {
                std::lock_guard<std::mutex> lock(_clientsMutex);
                _clients[id] = client;
            }

            client->StartAsync([this](std::uint32_t id) {
                HandleClientDisconnect(id);
            }, [this](std::uint32_t id, const Client::Message& message) {
                HandleClientData(id, message);
            });
        } catch (const std::exception& e) {
            Miscellaneous::Utils::Log(std::format("Error handling new connection: {}", e.what()), Miscellaneous::Utils::LogLevel::Error);
        }
    } else if (ec) {
        if (ec != boost::asio::error::operation_aborted) {
            Miscellaneous::Utils::Log(std::format("Accept error: {}", ec.message()), Miscellaneous::Utils::LogLevel::Error);
        }
    }

    if (_isRunning.load()) {
        StartAccept();
    }
}

void Network::Transceiver::HandleClientDisconnect(std::uint32_t id)
{
    std::lock_guard<std::mutex> lock(_clientsMutex);

    auto it = _clients.find(id);
    if (it != _clients.end()) {
        it->second->Disconnect();
        _clients.erase(it);
    }
}

void Network::Transceiver::HandleClientData(std::uint32_t id, const Client::Message& message)
{
    Miscellaneous::Utils::Log(std::format("Received message from client {}: {}", id, message.ToHexString()), Miscellaneous::Utils::LogLevel::Informational);

    std::lock_guard<std::mutex> lock(_clientsMutex);
    auto it = _clients.find(id);
    if (it != _clients.end() && it->second) {
        it->second->SendAsync(message);
    }
}

std::uint32_t Network::Transceiver::GenerateClientId()
{
    return _nextId.fetch_add(1);
}
