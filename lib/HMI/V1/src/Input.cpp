/**
 * EPITECH PROJECT, 2025
 * R-Type
 * File description:
 * Input.cpp
 */

#include "Subsystems/HMI/Input.hpp"

Subsystems::HMI::Input::Input(Type type, KeyCode key, Action action)
    : _type(type), _key(key), _action(action)
{
}

Subsystems::HMI::Input::Input(Type type, GamepadCode gamepad, Action action)
    : _type(type), _key(gamepad), _action(action)
{
}

Subsystems::HMI::Input::Type Subsystems::HMI::Input::GetType() const
{
    return _type;
}

std::size_t Subsystems::HMI::Input::GetKey() const
{
    return _key;
}

Subsystems::HMI::Input::Action Subsystems::HMI::Input::GetAction() const
{
    return _action;
}

void Subsystems::HMI::Input::SetType(Type type)
{
    _type = type;
}

void Subsystems::HMI::Input::SetKey(KeyCode key)
{
    _key = key;
}

void Subsystems::HMI::Input::SetKey(GamepadCode gamepad)
{
    _key = gamepad;
}

void Subsystems::HMI::Input::SetAction(Action action)
{
    _action = action;
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

std::ostream& operator<<(std::ostream& os, const Subsystems::HMI::Input& input)
{
    os << "Type: " << static_cast<int>(input.GetType())
       << ", Key: " << input.GetKey()
       << ", Action: " << static_cast<int>(input.GetAction());
    return os;
}
