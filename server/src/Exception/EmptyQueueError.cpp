/*
** EPITECH PROJECT, 2025
** R-Type
** File description:
** EmptyErrorQueue.cpp
*/

#include "Exception/EmptyQueueError.hpp"
#include <iostream>

Exception::EmptyQueueError::EmptyQueueError(const std::string& name, const std::source_location &where) : Generic(FormatError(name), where) {}

const std::string Exception::EmptyQueueError::FormatError(const std::string& name) const
{
    return std::format("Attempted to receive from the empty queue: {}", name);
}
