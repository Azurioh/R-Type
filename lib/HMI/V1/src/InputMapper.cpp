/**
 * EPITECH PROJECT, 2025
 * R-Type
 * File description:
 * InputMapper.cpp
 */

#include <algorithm>
#include "Subsystems/HMI/InputMapper.hpp"

void Subsystems::HMI::InputMapper::Bind(Input input, std::string action)
{
    _inputMap[input] = action;
}

std::optional<std::string> Subsystems::HMI::InputMapper::GetAction(const Input& input)
{
    auto it = _inputMap.find(input);
    if (it != _inputMap.end()) {
        return it->second;
    }
    return std::nullopt;
}
