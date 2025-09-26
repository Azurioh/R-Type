/*
** EPITECH PROJECT, 2025
** R-Type
** File description:
** SFMAdapter
*/

#include "SFMLAdapter.hpp"
#include <vector>
#include <cstddef>
#include <map>

Subsystems::Render::SFMLAdapter::SFMLAdapter()
{
    _keyMap = {
        {sf::Keyboard::Key::A, HMI::Input::KeyCode::A},
        {sf::Keyboard::Key::B, HMI::Input::KeyCode::B},
        {sf::Keyboard::Key::C, HMI::Input::KeyCode::C},
        {sf::Keyboard::Key::D, HMI::Input::KeyCode::D},
        {sf::Keyboard::Key::E, HMI::Input::KeyCode::E},
        {sf::Keyboard::Key::F, HMI::Input::KeyCode::F},
        {sf::Keyboard::Key::G, HMI::Input::KeyCode::G},
        {sf::Keyboard::Key::H, HMI::Input::KeyCode::H},
        {sf::Keyboard::Key::I, HMI::Input::KeyCode::I},
        {sf::Keyboard::Key::J, HMI::Input::KeyCode::J},
        {sf::Keyboard::Key::K, HMI::Input::KeyCode::K},
        {sf::Keyboard::Key::L, HMI::Input::KeyCode::L},
        {sf::Keyboard::Key::M, HMI::Input::KeyCode::M},
        {sf::Keyboard::Key::N, HMI::Input::KeyCode::N},
        {sf::Keyboard::Key::O, HMI::Input::KeyCode::O},
        {sf::Keyboard::Key::P, HMI::Input::KeyCode::P},
        {sf::Keyboard::Key::Q, HMI::Input::KeyCode::Q},
        {sf::Keyboard::Key::R, HMI::Input::KeyCode::R},
        {sf::Keyboard::Key::S, HMI::Input::KeyCode::S},
        {sf::Keyboard::Key::T, HMI::Input::KeyCode::T},
        {sf::Keyboard::Key::U, HMI::Input::KeyCode::U},
        {sf::Keyboard::Key::V, HMI::Input::KeyCode::V},
        {sf::Keyboard::Key::W, HMI::Input::KeyCode::W},
        {sf::Keyboard::Key::X, HMI::Input::KeyCode::X},
        {sf::Keyboard::Key::Y, HMI::Input::KeyCode::Y},
        {sf::Keyboard::Key::Z, HMI::Input::KeyCode::Z},
        {sf::Keyboard::Key::Num0, HMI::Input::KeyCode::Num0},
        {sf::Keyboard::Key::Num1, HMI::Input::KeyCode::Num1},
        {sf::Keyboard::Key::Num2, HMI::Input::KeyCode::Num2},
        {sf::Keyboard::Key::Num3, HMI::Input::KeyCode::Num3},
        {sf::Keyboard::Key::Num4, HMI::Input::KeyCode::Num4},
        {sf::Keyboard::Key::Num5, HMI::Input::KeyCode::Num5},
        {sf::Keyboard::Key::Num6, HMI::Input::KeyCode::Num6},
        {sf::Keyboard::Key::Num7, HMI::Input::KeyCode::Num7},
        {sf::Keyboard::Key::Num8, HMI::Input::KeyCode::Num8},
        {sf::Keyboard::Key::Num9, HMI::Input::KeyCode::Num9},
        {sf::Keyboard::Key::Up, HMI::Input::KeyCode::Up},
        {sf::Keyboard::Key::Down, HMI::Input::KeyCode::Down},
        {sf::Keyboard::Key::Left, HMI::Input::KeyCode::Left},
        {sf::Keyboard::Key::Right, HMI::Input::KeyCode::Right},
        {sf::Keyboard::Key::Space, HMI::Input::KeyCode::Space},
        {sf::Keyboard::Key::Enter, HMI::Input::KeyCode::Enter},
        {sf::Keyboard::Key::Escape, HMI::Input::KeyCode::Escape},
        {sf::Keyboard::Key::Tab, HMI::Input::KeyCode::Tab},
        {sf::Keyboard::Key::LShift, HMI::Input::KeyCode::Shift},
        {sf::Keyboard::Key::RShift, HMI::Input::KeyCode::Shift},
        {sf::Keyboard::Key::LControl, HMI::Input::KeyCode::Ctrl},
        {sf::Keyboard::Key::RControl, HMI::Input::KeyCode::Ctrl},
        {sf::Keyboard::Key::LAlt, HMI::Input::KeyCode::Alt},
        {sf::Keyboard::Key::RAlt, HMI::Input::KeyCode::Alt},
        {sf::Keyboard::Key::Hyphen, HMI::Input::KeyCode::Minus},
        {sf::Keyboard::Key::Add, HMI::Input::KeyCode::Plus},
        {sf::Keyboard::Key::Subtract, HMI::Input::KeyCode::Minus},
        {sf::Keyboard::Key::Multiply, HMI::Input::KeyCode::Asterisk},
        {sf::Keyboard::Key::Divide, HMI::Input::KeyCode::Slash},
        {sf::Keyboard::Key::Period, HMI::Input::KeyCode::Dot},
        {sf::Keyboard::Key::Comma, HMI::Input::KeyCode::Comma},
        {sf::Keyboard::Key::Semicolon, HMI::Input::KeyCode::Semicolon},
        {sf::Keyboard::Key::Backslash, HMI::Input::KeyCode::Backslash},
        {sf::Keyboard::Key::Grave, HMI::Input::KeyCode::Backquote},
        {sf::Keyboard::Key::Backspace, HMI::Input::KeyCode::Backspace},
        {sf::Keyboard::Key::Delete, HMI::Input::KeyCode::Delete},
        {sf::Keyboard::Key::Insert, HMI::Input::KeyCode::Insert},
        {sf::Keyboard::Key::Home, HMI::Input::KeyCode::Home},
        {sf::Keyboard::Key::End, HMI::Input::KeyCode::End},
        {sf::Keyboard::Key::PageUp, HMI::Input::KeyCode::PageUp},
        {sf::Keyboard::Key::PageDown, HMI::Input::KeyCode::PageDown},
        {sf::Keyboard::Key::F1, HMI::Input::KeyCode::F1},
        {sf::Keyboard::Key::F2, HMI::Input::KeyCode::F2},
        {sf::Keyboard::Key::F3, HMI::Input::KeyCode::F3},
        {sf::Keyboard::Key::F4, HMI::Input::KeyCode::F4},
        {sf::Keyboard::Key::F5, HMI::Input::KeyCode::F5},
        {sf::Keyboard::Key::F6, HMI::Input::KeyCode::F6},
        {sf::Keyboard::Key::F7, HMI::Input::KeyCode::F7},
        {sf::Keyboard::Key::F8, HMI::Input::KeyCode::F8},
        {sf::Keyboard::Key::F9, HMI::Input::KeyCode::F9},
        {sf::Keyboard::Key::F10, HMI::Input::KeyCode::F10},
        {sf::Keyboard::Key::F11, HMI::Input::KeyCode::F11},
        {sf::Keyboard::Key::F12, HMI::Input::KeyCode::F12},
    };
    _mouseMap = {
        {sf::Mouse::Button::Left, HMI::Input::KeyCode::MouseLeft},
        {sf::Mouse::Button::Right, HMI::Input::KeyCode::MouseRight},
        {sf::Mouse::Button::Middle, HMI::Input::KeyCode::MouseMiddle},
        {sf::Mouse::Button::Extra1, HMI::Input::KeyCode::MouseX1},
        {sf::Mouse::Button::Extra2, HMI::Input::KeyCode::MouseX2},
    };
}


void Subsystems::Render::SFMLAdapter::AdaptInput(const std::any& input)
{
    sf::Event event = std::any_cast<sf::Event>(input);

    _inputType = HMI::Input::Type::UnknownType;
    _inputKey = HMI::Input::KeyCode::UnknownKey;
    _inputAction = HMI::Input::Action::UnknownAction;

    if (!isInputTypeValid(event)) {
        return;
    }

    if (isPressEvent(event)) {
        _inputAction = HMI::Input::Action::Pressed;
    } else if (isReleaseEvent(event)) {
        _inputAction = HMI::Input::Action::Released;
    }

    if (isKeyboardMouseEvent(event)) {
        adaptKeyboardMouseEvent(event);
    }
}

Subsystems::HMI::Input::Type Subsystems::Render::SFMLAdapter::GetType(void) const
{
    return _inputType;
}

std::size_t Subsystems::Render::SFMLAdapter::GetKey(void) const
{
    return _inputKey;
}

Subsystems::HMI::Input::Action Subsystems::Render::SFMLAdapter::GetAction(void) const
{
    return _inputAction;
}

void Subsystems::Render::SFMLAdapter::SetType(HMI::Input::Type type)
{
    _inputType = type;
}

void Subsystems::Render::SFMLAdapter::SetKey(std::size_t key)
{
    _inputKey = key;
}

void Subsystems::Render::SFMLAdapter::SetAction(HMI::Input::Action action)
{
    _inputAction = action;
}

bool Subsystems::Render::SFMLAdapter::isInputTypeValid(const sf::Event& event) const
{
    if (isKeyboardMouseEvent(event)) {
        return true;
    }
    return false;
}

bool Subsystems::Render::SFMLAdapter::isKeyboardMouseEvent(const sf::Event& event) const
{
    if (event.is<sf::Event::KeyPressed>()
        || event.is<sf::Event::KeyReleased>()
        || event.is<sf::Event::MouseButtonPressed>()
        || event.is<sf::Event::MouseButtonReleased>()) {
        return true;
    }
    return false;
}

bool Subsystems::Render::SFMLAdapter::isGamepadEvent(const sf::Event& event) const
{
    if (!sf::Joystick::isConnected(0)) {
        return false;
    }
    if (event.is<sf::Event::JoystickButtonPressed>()
        || event.is<sf::Event::JoystickMoved>()
        || event.is<sf::Event::JoystickButtonReleased>()
        || event.is<sf::Event::JoystickMoved>()) {
        return true;
    }
    return false;
}

bool Subsystems::Render::SFMLAdapter::isReleaseEvent(const sf::Event& event) const
{
    if (event.is<sf::Event::KeyReleased>()
        || event.is<sf::Event::MouseButtonReleased>()
        || event.is<sf::Event::JoystickButtonReleased>()
        || event.is<sf::Event::JoystickMoved>()) {
        return true;
    }
    return false;
}

bool Subsystems::Render::SFMLAdapter::isPressEvent(const sf::Event& event) const
{
    if (event.is<sf::Event::KeyPressed>()
        || event.is<sf::Event::MouseButtonPressed>()
        || event.is<sf::Event::JoystickButtonPressed>()
        || event.is<sf::Event::JoystickMoved>()) {
        return true;
    }
    return false;
}

void Subsystems::Render::SFMLAdapter::adaptKeyboardMouseEvent(const sf::Event& event)
{
    _inputType = HMI::Input::Type::KeyboardMouse;
    if (event.is<sf::Event::KeyPressed>() || event.is<sf::Event::KeyReleased>()) {
        auto keyPressedEvent = event.getIf<sf::Event::KeyPressed>();
        if (keyPressedEvent) {
            auto keyIt = _keyMap.find(keyPressedEvent->code);
            if (keyIt != _keyMap.end()) {
                _inputKey = keyIt->second;
            }
            return;
        }
        auto keyReleasedEvent = event.getIf<sf::Event::KeyReleased>();
        if (keyReleasedEvent) {
            auto keyIt = _keyMap.find(keyReleasedEvent->code);
            if (keyIt != _keyMap.end()) {
                _inputKey = keyIt->second;
            }
        }
    } else if (event.is<sf::Event::MouseButtonPressed>() || event.is<sf::Event::MouseButtonReleased>()) {
        auto mousePressedEvent = event.getIf<sf::Event::MouseButtonPressed>();
        if (mousePressedEvent) {
            auto mouseIt = _mouseMap.find(mousePressedEvent->button);
            if (mouseIt != _mouseMap.end()) {
                _inputKey = mouseIt->second;
            }
            return;
        }
        auto mouseReleasedEvent = event.getIf<sf::Event::MouseButtonReleased>();
        if (mouseReleasedEvent) {
            auto mouseIt = _mouseMap.find(mouseReleasedEvent->button);
            if (mouseIt != _mouseMap.end()) {
                _inputKey = mouseIt->second;
            }
        }
    }
}
