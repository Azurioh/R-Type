/*
** EPITECH PROJECT, 2025
** R-Type
** File description:
** Transciever.cpp
*/

#include "Exception/EmptyQueueError.hpp"
#include "Miscellaneous/Utils.hpp"
#include "Transciever.hpp"

void Transciever::Initialize(const std::uint16_t port)
{
    if (_initialized) {
        throw Exception::Generic("Failed to initialize the already initialized transciever.");
    }

    _initialized = true;

    Miscellaneous::Utils::Log(std::format("Transciever initialized on port {}", port), Miscellaneous::Utils::Informational);
}

void Transciever::Deinitialize()
{
    if (!_initialized) {
        throw Exception::Generic("Failed to deinitialize the uninitialized transciever.");
    }

    _initialized = false;

    Miscellaneous::Utils::Log("Transciever deinitialized", Miscellaneous::Utils::Informational);
}

std::size_t Transciever::QueueKeyHash::operator()(const QueueKey& key) const
{
    return std::hash<std::uint32_t>()(key.first) ^ std::hash<std::uint32_t>()(static_cast<std::uint32_t>(key.second));
}

std::queue<Transciever::Message>& Transciever::GetQueue(const Direction direction, const std::uint32_t id, const bool explosion)
{
    QueueKey key = std::make_pair(id, direction);

    if (_messages.find(key) != _messages.end()) {
        return _messages.at(key);
    }
    if (explosion) {
        throw Exception::EmptyQueueError(std::format("{} — {}", direction != Incoming ? "Outgoing" : "Incoming", id));
    }
    return _messages[key];
}

Transciever::Message Transciever::ReceiveMessage(const std::uint32_t id)
{
    std::queue<Message>& queue = GetQueue(Incoming, id, true);
    Message message = queue.front();

    queue.pop();
    return message;
}

void Transciever::SendMessage(const std::uint32_t id, const std::uint8_t header, const std::vector<std::uint8_t>& body)
{
    std::queue<Message>& queue = GetQueue(Outgoing, id);
    Message message = {header, body};

    queue.push(message);
}
