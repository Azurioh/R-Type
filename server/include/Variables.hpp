/*
** EPITECH PROJECT, 2025
** R-Type
** File description:
** Variables.hpp
*/

#pragma once

#include <cstdint>

constexpr std::uint32_t MAX_MESSAGE_SIZE = 1024 * 1024 * 50; /*!< Maximum size for TCP messages (50MB) */

constexpr std::uint8_t HEADER_SIZE = 6; /*!< Size of the message header (2 + 4 bytes) */
