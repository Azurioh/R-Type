/**
 * EPITECH PROJECT, 2025
 * R-Type
 * File description:
 * Sprite
 */

#pragma once

#include <any>
#include <string>
#include "Subsystems/Render/Texture.hpp"

namespace Subsystems::Render {
    /**
     * @class Sprite
     *
     * @brief A class that represents a sprite.
     */
    class Sprite {
        public:
            /**
             * @brief Constructs a sprite with the specified texture.
             *
             * @param texture The texture of the sprite.
             */
            Sprite(Texture& texture);

            /**
             * @brief Gets the sprite.
             *
             * @return The sprite.
             */
            std::any& GetSprite();

            /**
             * @brief Sets the texture of the sprite.
             *
             * @param texture The texture of the sprite.
             */
            void SetTexture(Texture& texture);

            /**
             * @brief Sets the sprite of the sprite.
             *
             * @param sprite The sprite of the sprite.
             */
            void SetSprite(std::any& sprite);

        private:
            std::any _sprite; /*!> The sprite. */
    };
}
