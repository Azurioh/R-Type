/**
 * EPITECH PROJECT, 2025
 * R-Type
 * File description:
 * Entity
 */

#pragma once

#include <string>
#include <cstddef>

namespace Engine {
    class Entity {
        public:
            Entity(std::string name);

        private:
            std::size_t _id;
            std::string _name;
    };
}
