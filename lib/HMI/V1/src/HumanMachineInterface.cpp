/**
 * EPITECH PROJECT, 2025
 * R-Type
 * File description:
 * HumanMachineInterface.cpp
 */

 #include <optional>
 #include "Subsystems/HMI/HumanMachineInterface.hpp"

void Subsystems::HMI::HumanMachineInterface::handleInput(const Input& input)
{
    std::optional<std::string> action = _inputMapper.getAction(input);
    if (action) {
        _actions.push_back(*action);
    }
}

std::vector<std::string> Subsystems::HMI::HumanMachineInterface::pollActions()
{
    return _actions;
}

void Subsystems::HMI::HumanMachineInterface::clearActions()
{
    _actions.clear();
}

Subsystems::HMI::InputMapper& Subsystems::HMI::HumanMachineInterface::getInputMapper()
{
    return _inputMapper;
}
