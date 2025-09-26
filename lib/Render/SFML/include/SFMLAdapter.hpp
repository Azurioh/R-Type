/*
** EPITECH PROJECT, 2025
** R-Type
** File description:
** SFMLAdapter
*/

#pragma once

#include "Subsystems/Render/InputAdapter.hpp"
#include <SFML/Window/Event.hpp>
#include <any>
#include <map>

namespace Subsystems::Render {
    /**
     * @class InputAdapter
     *
     * @brief A class that represents an input adapter.
     */
    class SFMLAdapter : public InputAdapter {
        public:
            SFMLAdapter();
            void AdaptInput(const std::any& input);

            HMI::Input::Type GetType(void) const;
            std::size_t GetKey(void) const;
            HMI::Input::Action GetAction(void) const;

            void SetType(HMI::Input::Type type);
            void SetKey(std::size_t key);
            void SetAction(HMI::Input::Action action);

        private:
            bool isInputTypeValid(const sf::Event& event) const;
            bool isKeyboardMouseEvent(const sf::Event& event) const;
            bool isGamepadEvent(const sf::Event& event) const;
            bool isReleaseEvent(const sf::Event& event) const;
            bool isPressEvent(const sf::Event& event) const;
            void adaptKeyboardMouseEvent(const sf::Event& event);

            std::map<sf::Keyboard::Key, HMI::Input::KeyCode> _keyMap;
            std::map<sf::Mouse::Button, HMI::Input::KeyCode> _mouseMap;

            HMI::Input::Type _inputType;
            std::size_t _inputKey;
            HMI::Input::Action _inputAction;
    };
}
