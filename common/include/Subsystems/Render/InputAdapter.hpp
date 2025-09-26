/*
** EPITECH PROJECT, 2025
** R-Type
** File description:
** InputAdapter
*/

#pragma once

#include "Subsystems/HMI/Input.hpp"
#include <any>

namespace Subsystems::Render {
    /**
     * @class InputAdapter
     *
     * @brief A class that represents an input adapter.
     */
    class InputAdapter {
        public:
            virtual void AdaptInput(const std::any& input) = 0;

            virtual HMI::Input::Type GetType(void) const = 0;
            virtual std::size_t GetKey(void) const = 0;
            virtual HMI::Input::Action GetAction(void) const = 0;

            virtual void SetType(HMI::Input::Type type) = 0;
            virtual void SetKey(std::size_t key) = 0;
            virtual void SetAction(HMI::Input::Action action) = 0;
    };
}
