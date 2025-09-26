/**
 * EPITECH PROJECT, 2025
 * R-Type
 * File description:
 * Input
 */

#pragma once

#include <cstddef>
#include <iostream>

namespace Subsystems::HMI {
    /**
     * @class Input
     * @brief The input class.
     */
    class Input {
        public:
            /**
             * @enum Type
             * @brief The type of input.
             */
            enum Type {
                UnknownType = 0,
                KeyboardMouse = 1,
                Gamepad,
            };

            /**
             * @enum KeyCode
             * @brief The key code.
             */
            enum KeyCode {
                UnknownKey = 0,
                A, B, C, D, E, F, G, H, I, J, K, L, M,
                N, O, P, Q, R, S, T, U, V, W, X, Y, Z,
                Num0, Num1, Num2, Num3, Num4, Num5, Num6, Num7, Num8, Num9,
                Up, Down, Left, Right,
                Space, Enter, Escape, Tab, Shift, Ctrl, Alt,
                Underscore, Plus, Minus, Asterisk, Slash,
                Dot, Comma, Semicolon, Colon, Quote,
                Backslash, Pipe, Backquote,
                Backspace, Delete, Insert, Home, End, PageUp, PageDown,
                F1, F2, F3, F4, F5, F6, F7, F8, F9, F10, F11, F12,
                MouseLeft, MouseRight, MouseMiddle, MouseX1, MouseX2,
            };

            /**
             * @enum GamepadCode
             * @brief The gamepad code.
             */
            enum GamepadCode {
                GamepadUnknown = 0,
                GamepadButtonA = 1, GamepadButtonB, GamepadButtonX, GamepadButtonY,
                GamepadButtonLB, GamepadButtonRB, GamepadButtonLT, GamepadButtonRT,
                GamepadButtonLS, GamepadButtonRS, GamepadButtonStart, GamepadButtonSelect,
                GamepadButtonUp, GamepadButtonDown, GamepadButtonLeft, GamepadButtonRight,
                GamepadButtonHome, GamepadButtonBack, GamepadButtonMenu, GamepadButtonView,
                GamepadLSUp, GamepadLSDown, GamepadLSLeft, GamepadLSRight,
                GamepadRSUp, GamepadRSDown, GamepadRSLeft, GamepadRSRight,
            };

            enum Action {
                Pressed,
                Released,
                UnknownAction,
            };

            /**
             * @brief Constructs an input with the specified type and key.
             *
             * @param type The type of input.
             * @param key The key code.
             */
            Input(Type type, KeyCode key, Action action);

            /**
             * @brief Constructs an input with the specified type and gamepad.
             *
             * @param type The type of input.
             * @param gamepad The gamepad code.
             */
            Input(Type type, GamepadCode gamepad, Action action);

            /**
             * @brief Gets the type of input.
             *
             * @return The type of input.
             */
            Type GetType() const;

            /**
             * @brief Gets the key code.
             *
             * @return The key code.
             */
            std::size_t GetKey() const;

            /**
             * @brief Gets the action.
             *
             * @return The action.
             */
            Action GetAction() const;

            /**
             * @brief Sets the type of input.
             *
             * @param type The type of input.
             */
            void SetType(Type type);

            /**
             * @brief Sets the key code.
             *
             * @param key The key code.
             */
            void SetKey(KeyCode key);

            /**
             * @brief Sets the gamepad code.
             *
             * @param gamepad The gamepad code.
             */
            void SetKey(GamepadCode gamepad);

            /**
             * @brief Sets the action.
             *
             * @param action The action.
             */
            void SetAction(Action action);

            /**
             * @brief Checks if the input is equal to the other input.
             *
             * @param other The other input.
             * @return True if the input is equal to the other input, false otherwise.
             */
            bool operator==(const Input& other) const;

            /**
             * @brief Checks if the input is less than the other input.
             *
             * @param other The other input.
             * @return True if the input is less than the other input, false otherwise.
             */
            bool operator<(const Input& other) const;

            friend std::ostream& operator<<(std::ostream& os, const Input& input);

        private:
            Type _type; /*!> The type of input. */
            std::size_t _key; /*!> The key code. */
            Action _action; /*!> The action of the input. */
    };
}
