/*
** EPITECH PROJECT, 2025
** R-Type
** File description:
** Client.cpp
*/

#include "Exception/Generic.hpp"
#include "Network/Client.hpp"
#include "Misc/Utils.hpp"

#include <iostream>

Network::Client::Client(std::uint32_t id, std::shared_ptr<boost::asio::ip::tcp::socket> socket) : _socket(socket), _id(id), _writing(false)
{
    Misc::Utils::Log(std::format("Client {} connected from {}:{}", _id, _socket->remote_endpoint().address().to_string(), _socket->remote_endpoint().port()), Misc::Utils::LogLevel::Informational);
}

std::uint32_t Network::Client::GetId() const
{
    return _id;
}

void Network::Client::StartAsync(DisconnectCallback onDisconnect, DataCallback onData)
{
    _onDisconnect = onDisconnect;
    _onData = onData;

    StartReadHeader();
}

void Network::Client::StartReadHeader()
{
    if (IsConnected()) {
        boost::asio::async_read(*_socket, boost::asio::buffer(_headerBuffer), [this, self = shared_from_this()](const boost::system::error_code& ec, std::size_t bytes) {
            if (ec) {
                if (ec != boost::asio::error::operation_aborted && ec != boost::asio::error::eof && ec != boost::asio::error::connection_reset) {
                    Misc::Utils::Log(std::format("Client {} async read header error: {}", _id, ec.message()), Misc::Utils::LogLevel::Error);
                } else if (_onDisconnect) {
                    _onDisconnect(_id);
                }
            } else {
                HandleReadHeader(bytes);
            }
        });
    }
}

void Network::Client::HandleReadHeader(std::size_t bytes)
{
    try {
        if (bytes != HEADER_SIZE) {
            throw Exception::Generic(std::format("Client {} sent {} bytes for header, expected {}", _id, bytes, HEADER_SIZE));
        }

        std::memcpy(&_currentId, _headerBuffer.data(), 2);
        std::memcpy(&_currentLength, _headerBuffer.data() + 2, 4);

        if (_currentLength > MAX_MESSAGE_SIZE) {
            throw Exception::Generic(std::format("Client {} sent invalid content length: {}", _id, _currentLength));
        }

        if (_currentLength > 0) {
            _contentBuffer.resize(_currentLength);
            StartReadContent();
        } else {
            if (_onData) {
                std::vector<std::uint8_t> raw(_headerBuffer.begin(), _headerBuffer.end());
                _onData(_id, raw);
            }
            StartReadHeader();
        }
    } catch (const Exception::Generic& ex) {
        Misc::Utils::Log(ex.what(), Misc::Utils::LogLevel::Error);
    }
}

void Network::Client::StartReadContent()
{
    if (IsConnected()) {
        boost::asio::async_read(*_socket, boost::asio::buffer(_contentBuffer), [this, self = shared_from_this()](const boost::system::error_code& ec, std::size_t bytes) {
            if (ec) {
                if (ec != boost::asio::error::operation_aborted && ec != boost::asio::error::eof && ec != boost::asio::error::connection_reset) {
                    Misc::Utils::Log(std::format("Client {} async read content error: {}", _id, ec.message()), Misc::Utils::LogLevel::Error);
                } else if (_onDisconnect) {
                    _onDisconnect(_id);
                }
            } else {
                HandleReadContent(bytes);
            }
        });
    }
}

void Network::Client::HandleReadContent(std::size_t bytes)
{
    try {
        if (bytes != _currentLength) {
            throw Exception::Generic(std::format("Client {} sent {} bytes for content, expected {}", _id, bytes, _currentLength));
        }

        if (_onData) {
            std::vector<std::uint8_t> raw;

            raw.reserve(_headerBuffer.size() + _contentBuffer.size());
            raw.insert(raw.end(), _headerBuffer.begin(), _headerBuffer.end());
            raw.insert(raw.end(), _contentBuffer.begin(), _contentBuffer.end());
            _onData(_id, raw);
        }

        StartReadHeader();
    } catch (const Exception::Generic& ex) {
        Misc::Utils::Log(ex.what(), Misc::Utils::LogLevel::Error);
    }
}

void Network::Client::SendAsync(const Message& message)
{
    if (IsConnected()) {
        boost::asio::post(_socket->get_executor(), [this, self = shared_from_this(), message]() {
            bool queueFull = false;
            bool wasEmpty = false;

            {
                std::lock_guard<std::mutex> lock(_writeQueueMutex);
                if (_writeQueue.size() >= 100) {
                    queueFull = true;
                    Misc::Utils::Log(std::format("Client {} write queue full, dropping message", _id), Misc::Utils::LogLevel::Warning);
                } else {
                    wasEmpty = _writeQueue.empty();
                    _writeQueue.push_back(message);
                }
            }

            if (!queueFull && wasEmpty && !_writing) {
                _writing = true;

                std::vector<std::uint8_t> serialized = message.Serialize();

                Misc::Utils::Log(std::format("Sent message to client {}: {}", _id, Misc::Utils::BytesToHex(serialized)), Misc::Utils::LogLevel::Informational);
                boost::asio::async_write(*_socket, boost::asio::buffer(serialized), [this, self](const boost::system::error_code& ec, std::size_t bytes) {
                    if (ec) {
                        Misc::Utils::Log(std::format("Client {} write error: {}", _id, ec.message()), Misc::Utils::LogLevel::Error);
                        _writing = false;
                    } else {
                        HandleWrite(bytes);
                    }
                });
            }
        });
    }
}

void Network::Client::HandleWrite(std::size_t)
{
    Message nextMessage(0, {});
    bool hasNext = false;

    {
        std::lock_guard<std::mutex> lock(_writeQueueMutex);
        if (!_writeQueue.empty()) {
            _writeQueue.erase(_writeQueue.begin());
            if (!_writeQueue.empty()) {
                nextMessage = _writeQueue.front();
                hasNext = true;
            }
        }
    }

    if (hasNext) {
        std::vector<std::uint8_t> serialized = nextMessage.Serialize();

        Misc::Utils::Log(std::format("Sent message to client {}: {}", _id, Misc::Utils::BytesToHex(serialized)), Misc::Utils::LogLevel::Informational);
        boost::asio::async_write(*_socket, boost::asio::buffer(serialized), [this, self = shared_from_this()](const boost::system::error_code& ec, std::size_t bytes) {
            if (ec) {
                Misc::Utils::Log(std::format("Client {} write error: {}", _id, ec.message()), Misc::Utils::LogLevel::Error);
                _writing = false;
            } else {
                HandleWrite(bytes);
            }
        });
    } else {
        _writing = false;
    }
}

void Network::Client::Disconnect()
{
    auto socket = _socket;

    boost::asio::post(socket->get_executor(), [this, self = shared_from_this(), socket]() {
        if (socket->is_open()) {
            boost::system::error_code ec = {};

            socket->close(ec);
            if (ec) {
                Misc::Utils::Log(std::format("Error closing socket for client {}: {}", _id, ec.message()), Misc::Utils::LogLevel::Error);
            } else {
                Misc::Utils::Log(std::format("Client {} disconnected successfully.", _id), Misc::Utils::LogLevel::Informational);
            }
        }
    });
}

bool Network::Client::IsConnected() const
{
    return _socket && _socket->is_open();
}
