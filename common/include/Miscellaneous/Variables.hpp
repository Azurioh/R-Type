/**
 * EPITECH PROJECT, 2025
 * R-Type
 * File description:
 * Variables.hpp
 */

#pragma once

#include <cstdint>

namespace RType {
    /*!> The size of a pagination. */
    constexpr std::uint8_t PAGINATION_SIZE = 5;

    /*!> Get the index of a pagination. */
    constexpr std::uint8_t PAGINATION_IDX(std::uint8_t value) {
        return value / PAGINATION_SIZE;
    }

    /*!> Get the index in a pagination. */
    constexpr std::uint8_t IDX_IN_PAGINATION(std::uint8_t value) {
        return value % PAGINATION_SIZE;
    }
}
