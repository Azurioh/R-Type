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
    /**
     * @class Entity
     *
     * @brief A class that represents an entity.
     */
    class Entity {
        public:
            /**
             * @brief Constructs an entity with the specified name.
             *
             * @param name The name of the entity.
             */
            Entity(std::string name);

            /**
             * @brief Get the id of the entity.
             *
             * @return The id of the entity.
             */
            std::size_t GetId() const;

            /**
             * @brief Get the name of the entity.
             *
             * @return The name of the entity.
             */
            std::string GetName() const;

        private:
            std::size_t _id; /*!> The id of the entity. */
            std::string _name; /*!> The name of the entity. */
    };
}
