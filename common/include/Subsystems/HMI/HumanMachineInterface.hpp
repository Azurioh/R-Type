/**
 * EPITECH PROJECT, 2025
 * R-Type
 * File description:
 * HumanMachineInterface
 */

#pragma once

#include <vector>
#include <string>
#include "Subsystems/HMI/InputMapper.hpp"

namespace Subsystems::HMI {
    /**
     * @class HumanMachineInterface
     * @brief The Human Machine Interface class.
     */
    class HumanMachineInterface {
        public:
            /**
             * @brief Handles the input.
             *
             * @param input The input.
             */
            void handleInput(const Input& input);

            /**
             * @brief Polls the actions.
             *
             * @return The actions.
             */
            std::vector<std::string> pollActions();

            /**
             * @brief Clears the actions.
             */
            void clearActions();

            /**
             * @brief Gets the input mapper.
             *
             * @return The input mapper.
             */
            InputMapper& getInputMapper();

        private:
            InputMapper _inputMapper; /*!> The input mapper. */
            std::vector<std::string> _actions; /*!> The actions. */
    };
}
