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

std::uint32_t Network::Client::GetId() const
{
    return _id;
}

void Network::Client::StartAsync(DisconnectCallback onDisconnect, DataCallback onData)
{
    _onDisconnect = onDisconnect;
    _onData = onData;

    StartRead();
}

void Network::Client::StartRead()
{
    if (IsConnected()) {
        auto self = shared_from_this();

        _socket->async_read_some(boost::asio::buffer(_readBuffer), [this, self](const boost::system::error_code& ec, std::size_t bytes) {
            HandleRead(ec, bytes);
        });
    }
}

void Network::Client::HandleRead(const boost::system::error_code& ec, std::size_t bytes)
{
    if (!ec && bytes > 0) {
        std::vector<std::uint8_t> data(_readBuffer.begin(), _readBuffer.begin() + bytes);

        if (data.size() >= 1) {
            Message message = {
                .header = data[0],
                .body = {}
            };

            if (data.size() > 1) {
                message.body.assign(data.begin() + 1, data.end());
            }

            if (_onData) {
                _onData(_id, message);
            }
        }

        StartRead();
    } else {
        if (ec != boost::asio::error::operation_aborted && ec != boost::asio::error::eof && ec != boost::asio::error::connection_reset) {
            Miscellaneous::Utils::Log(std::format("Client {} read error: {}", _id, ec.message()), Miscellaneous::Utils::LogLevel::Warning);
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

                std::vector<std::uint8_t> serializedData = {};

                serializedData.push_back(message.header);
                serializedData.insert(serializedData.end(), message.body.begin(), message.body.end());

                boost::asio::async_write(*_socket, boost::asio::buffer(serializedData), [this, self](const boost::system::error_code& ec, std::size_t bytes) {
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

            std::vector<std::uint8_t> serializedData = {};

            serializedData.push_back(nextMessage.header);
            serializedData.insert(serializedData.end(), nextMessage.body.begin(), nextMessage.body.end());

            boost::asio::async_write(*_socket, boost::asio::buffer(serializedData), [this, self](const boost::system::error_code& ec, std::size_t bytes) {
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
