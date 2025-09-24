/**
 * EPITECH PROJECT, 2025
 * R-Type
 * File description:
 * InputMapper
 */

#pragma once

#include <string>
#include <optional>
#include <map>
#include "Subsystems/HMI/Input.hpp"

namespace Subsystems::HMI {
    /**
     * @class InputMapper
     * @brief The input mapper class.
     */
    class InputMapper {
        public:
            /**
             * @brief Binds an input to an action.
             *
             * @param input The input.
             * @param action The action.
             */
            void bind(Input input, std::string action);

            /**
             * @brief Gets an action from an input.
             *
             * @param input The input.
             * @return The action.
             */
            std::optional<std::string> getAction(const Input& input);

        private:
            std::map<Input, std::string> _inputMap; /*!> The input map. */
    };
}
