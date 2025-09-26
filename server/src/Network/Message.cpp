/*
** EPITECH PROJECT, 2025
** R-Type
** File description:
** Message.cpp
*/

#include "Exception/Generic.hpp"
#include "Network/Message.hpp"

#include <cstring>

Network::Message::Message(const std::uint16_t id, const std::vector<std::uint8_t>& content) : _id(id), _content(content) {}

Network::Message::Message(const std::vector<std::uint8_t>& raw)
{
    if (raw.size() < 6) {
        throw Exception::Generic("Raw data too short to contain a valid message");
    }

    std::uint16_t id = 0;
    std::uint32_t length = 0;

    std::memcpy(&id, raw.data(), 2);
    std::memcpy(&length, raw.data() + 2, 4);

    std::vector<std::uint8_t> content(raw.begin() + 6, raw.end());

    _id = id;
    _content = std::move(content);
}

std::uint16_t Network::Message::GetId() const
{
    return _id;
}

const std::vector<std::uint8_t>& Network::Message::GetContent() const
{
    return _content;
}

std::vector<std::uint8_t> Network::Message::Serialize() const
{
    std::vector<uint8_t> buffer(6 + _content.size());
    std::uint32_t length = _content.size();

    std::memcpy(buffer.data(), &_id, 2);
    std::memcpy(buffer.data() + 2, &length, 4);

    if (!_content.empty()) {
        std::memcpy(buffer.data() + 6, _content.data(), length);
    }
    return buffer;
}
