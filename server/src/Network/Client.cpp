/*
** EPITECH PROJECT, 2025
** R-Type
** File description:
** Client.cpp
*/

#include "Miscellaneous/Utils.hpp"
#include "Network/Client.hpp"

Network::Client::Client(std::uint32_t id, std::shared_ptr<boost::asio::ip::tcp::socket> socket) : _socket(socket), _id(id), _writing(false)
{
    Miscellaneous::Utils::Log(std::format("Client {} connected from {}:{}.", _id, _socket->remote_endpoint().address().to_string(), _socket->remote_endpoint().port()), Miscellaneous::Utils::LogLevel::Informational);
}

std::string Network::Client::Message::ToHexString() const
{
    std::vector<std::uint8_t> message = {};
    std::uint32_t length = static_cast<std::uint32_t>(content.size());

    message.resize(6 + content.size());

    std::memcpy(message.data(), &id, 2);
    std::memcpy(message.data() + 2, &length, 4);
    std::memcpy(message.data() + 6, content.data(), content.size());

    return Miscellaneous::Utils::BytesToHex(message);
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
        auto self = shared_from_this();

        boost::asio::async_read(*_socket, boost::asio::buffer(_headerBuffer), [this, self](const boost::system::error_code& ec, std::size_t bytes) {
            HandleReadHeader(ec, bytes);
        });
    }
}

void Network::Client::HandleReadHeader(const boost::system::error_code& ec, std::size_t bytes)
{
    if (!ec && bytes == HEADER_SIZE) {
        std::memcpy(&_currentId, _headerBuffer.data(), 2);
        std::memcpy(&_currentLength, _headerBuffer.data() + 2, 4);

        if (_currentLength > 0 && _currentLength <= MAX_MESSAGE_SIZE) {
            _contentBuffer.resize(_currentLength);
            StartReadContent();
        } else if (!_currentLength) {
            Message message = {
                .id = _currentId,
                .content = {}
            };

            if (_onData) {
                _onData(_id, message);
            }

            StartReadHeader();
        } else {
            Miscellaneous::Utils::Log(std::format("Client {} sent invalid content length: {}", _id, _currentLength), Miscellaneous::Utils::LogLevel::Warning);
            if (_onDisconnect) {
                _onDisconnect(_id);
            }
        }
    } else {
        if (ec != boost::asio::error::operation_aborted && ec != boost::asio::error::eof && ec != boost::asio::error::connection_reset) {
            Miscellaneous::Utils::Log(std::format("Client {} header read error: {}", _id, ec.message()), Miscellaneous::Utils::LogLevel::Warning);
        }

        if (_onDisconnect) {
            _onDisconnect(_id);
        }
    }
}

void Network::Client::StartReadContent()
{
    if (IsConnected()) {
        auto self = shared_from_this();

        boost::asio::async_read(*_socket, boost::asio::buffer(_contentBuffer), [this, self](const boost::system::error_code& ec, std::size_t bytes) {
            HandleReadContent(ec, bytes);
        });
    }
}

void Network::Client::HandleReadContent(const boost::system::error_code& ec, std::size_t bytes)
{
    if (!ec && bytes == _currentLength) {
        Message message = {
            .id = _currentId,
            .content = _contentBuffer
        };

        if (_onData) {
            _onData(_id, message);
        }

        StartReadHeader();
    } else {
        if (ec != boost::asio::error::operation_aborted && ec != boost::asio::error::eof && ec != boost::asio::error::connection_reset) {
            Miscellaneous::Utils::Log(std::format("Client {} content read error: {}", _id, ec.message()), Miscellaneous::Utils::LogLevel::Warning);
        }

        if (_onDisconnect) {
            _onDisconnect(_id);
        }
    }
}

void Network::Client::SendAsync(const Message& message)
{
    if (IsConnected()) {
        auto self = shared_from_this();

        boost::asio::post(_socket->get_executor(), [this, self, message]() {
            bool queueFull = false;
            bool wasEmpty = false;

            {
                std::lock_guard<std::mutex> lock(_writeQueueMutex);
                if (_writeQueue.size() >= 100) {
                    queueFull = true;
                    Miscellaneous::Utils::Log(std::format("Client {} write queue full, dropping message", _id), Miscellaneous::Utils::LogLevel::Warning);
                } else {
                    wasEmpty = _writeQueue.empty();
                    _writeQueue.push_back(message);
                }
            }

            if (!queueFull && wasEmpty && !_writing) {
                _writing = true;

                std::vector<std::uint8_t> serialized = {};
                std::uint32_t length = static_cast<std::uint32_t>(message.content.size());

                serialized.resize(6 + message.content.size());

                std::memcpy(serialized.data(), &message.id, 2);
                std::memcpy(serialized.data() + 2, &length, 4);
                std::memcpy(serialized.data() + 6, message.content.data(), message.content.size());

                boost::asio::async_write(*_socket, boost::asio::buffer(serialized), [this, self](const boost::system::error_code& ec, std::size_t bytes) {
                    HandleWrite(ec, bytes);
                });
            }
        });
    }
}

void Network::Client::HandleWrite(const boost::system::error_code& ec, std::size_t)
{
    if (!ec) {
        Message nextMessage = {};
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
            auto self = shared_from_this();

            std::vector<std::uint8_t> serialized = {};
            std::uint32_t length = static_cast<std::uint32_t>(nextMessage.content.size());

            serialized.resize(6 + nextMessage.content.size());

            std::memcpy(serialized.data(), &nextMessage.id, 2);
            std::memcpy(serialized.data() + 2, &length, 4);
            std::memcpy(serialized.data() + 6, nextMessage.content.data(), nextMessage.content.size());

            boost::asio::async_write(*_socket, boost::asio::buffer(serialized), [this, self](const boost::system::error_code& ec, std::size_t bytes) {
                HandleWrite(ec, bytes);
            });
        } else {
            _writing = false;
        }
    } else {
        _writing = false;
        Miscellaneous::Utils::Log(std::format("Client {} write error: {}", _id, ec.message()), Miscellaneous::Utils::LogLevel::Error);

        if (_onDisconnect) {
            _onDisconnect(_id);
        }
    }
}

void Network::Client::Disconnect()
{
    if (_socket && _socket->is_open()) {
        boost::system::error_code ec = {};

        _socket->close(ec);
        if (ec) {
            Miscellaneous::Utils::Log(std::format("Error closing socket for client {}: {}", _id, ec.message()), Miscellaneous::Utils::LogLevel::Error);
        } else {
            Miscellaneous::Utils::Log(std::format("Client {} disconnected successfully.", _id), Miscellaneous::Utils::LogLevel::Informational);
        }
    }
}

bool Network::Client::IsConnected() const
{
    return _socket && _socket->is_open();
}
