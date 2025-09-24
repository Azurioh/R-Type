/**
 * EPITECH PROJECT, 2025
 * R-Type
 * File description:
 * HumanMachineInterface.cpp
 */

 #include <optional>
 #include "Subsystems/HMI/HumanMachineInterface.hpp"

void Subsystems::HMI::HumanMachineInterface::HandleInput(const Input& input)
{
    std::optional<std::string> action = _inputMapper.GetAction(input);
    if (action) {
        _actions.push_back(*action);
    }
}

std::vector<std::string> Subsystems::HMI::HumanMachineInterface::PollActions()
{
    return _actions;
}

void Subsystems::HMI::HumanMachineInterface::ClearActions()
{
    _actions.clear();
}

Subsystems::HMI::InputMapper& Subsystems::HMI::HumanMachineInterface::GetInputMapper()
{
    return _inputMapper;
}
