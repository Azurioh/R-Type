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
            /**
             * @brief Constructs an SFMLAdapter.
             */
            SFMLAdapter();

            /**
             * @brief Adapts the input received from the SFML event.
             */
            void AdaptInput(const std::any& input);

            /**
             * @brief Gets the adapted input data.
             *
             * @return A tuple containing the input type, key, and action.
             */
            HMI::Input::Type GetType(void) const;

            /**
             * @brief Gets the adapted input key.
             *
             * @return The input key.
             */
            std::size_t GetKey(void) const;

            /**
             * @brief Gets the adapted input action.
             *
             * @return The input action.
             */
            HMI::Input::Action GetAction(void) const;

            /**
             * @brief Sets the input type.
             *
             * @param type The input type to set.
             */
            void SetType(HMI::Input::Type type);

            /**
             * @brief Sets the input key.
             *
             * @param key The input key to set.
             */
            void SetKey(std::size_t key);

            /**
             * @brief Sets the input action.
             *
             * @param action The input action to set.
             */
            void SetAction(HMI::Input::Action action);

        private:
            /**
             * @brief Checks if the input type is valid.
             *
             * @param event The SFML event to check.
             * @return true if the input type is valid, false otherwise.
             */
            bool isInputTypeValid(const sf::Event& event) const;

            /**
             * @brief Checks if the event is a keyboard mouse event.
             *
             * @param event The SFML event to check.
             * @return true if the event is a keyboard mouse event, false otherwise.
             */
            bool isKeyboardMouseEvent(const sf::Event& event) const;

            /**
             * @brief Checks if the event is a gamepad event.
             *
             * @param event The SFML event to check.
             * @return true if the event is a gamepad event, false otherwise.
             */
            bool isGamepadEvent(const sf::Event& event) const;

            /**
             * @brief Checks if the event is a release event.
             *
             * @param event The SFML event to check.
             * @return true if the event is a release event, false otherwise.
             */
            bool isReleaseEvent(const sf::Event& event) const;

            /**
             * @brief Checks if the event is a press event.
             *
             * @param event The SFML event to check.
             * @return true if the event is a press event, false otherwise.
             */
            bool isPressEvent(const sf::Event& event) const;

            /**
             * @brief Adapts the keyboard mouse event.
             *
             * @param event The SFML event to adapt.
             */
            void adaptKeyboardMouseEvent(const sf::Event& event);

            /**
             * @brief Checks if the event is a gamepad event.
             *
             * @param event The SFML event to check.
             * @return true if the event is a gamepad event, false otherwise.
             */
            bool isGamepadEvent(const sf::Event& event) const;

            /**
             * @brief Checks if the event is a release event.
             *
             * @param event The SFML event to check.
             * @return true if the event is a release event, false otherwise.
             */
            bool isReleaseEvent(const sf::Event& event) const;

            /**
             * @brief Checks if the event is a press event.
             *
             * @param event The SFML event to check.
             * @return true if the event is a press event, false otherwise.
             */
            bool isPressEvent(const sf::Event& event) const;

            std::map<sf::Keyboard::Key, HMI::Input::KeyCode> _keyMap;
            std::map<sf::Mouse::Button, HMI::Input::KeyCode> _mouseMap;
            HMI::Input::Type _inputType;
            std::size_t _inputKey;
            HMI::Input::Action _inputAction;
    };
}
