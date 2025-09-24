/**
 * EPITECH PROJECT, 2025
 * R-Type
 * File description:
 * Input.cpp
 */

#include "Subsystems/HMI/Input.hpp"

Subsystems::HMI::Input::Input(Type type, KeyCode key)
    : _type(type), _key(key)
{
}

Subsystems::HMI::Input::Input(Type type, GamepadCode gamepad)
    : _type(type), _key(gamepad)
{
}

Subsystems::HMI::Input::Type Subsystems::HMI::Input::getType() const
{
    return _type;
}

std::size_t Subsystems::HMI::Input::getKey() const
{
    return _key;
}

void Subsystems::HMI::Input::setType(Type type)
{
    _type = type;
}

void Subsystems::HMI::Input::setKey(KeyCode key)
{
    _key = key;
}

bool Subsystems::HMI::Input::operator==(const Input& other) const
{
    return _type == other._type && _key == other._key;
}

bool Subsystems::HMI::Input::operator<(const Input& other) const
{
    if (_type != other._type) {
        return _type < other._type;
    }
    return _key < other._key;
}
