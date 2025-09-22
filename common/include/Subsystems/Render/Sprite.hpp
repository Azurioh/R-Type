/**
 * EPITECH PROJECT, 2025
 * R-Type
 * File description:
 * Sprite
 */

#pragma once

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
            Sprite(Texture *texture);

            /**
             * @brief Destroys the sprite.
             */
            ~Sprite();

            /**
             * @brief Gets the texture of the sprite.
             *
             * @return The texture of the sprite.
             */
            Texture *getTexture() const;

            /**
             * @brief Gets the sprite.
             *
             * @return The sprite.
             */
            void *getSprite() const;

            /**
             * @brief Sets the texture of the sprite.
             *
             * @param texture The texture of the sprite.
             */
            void setTexture(Texture *texture);

            /**
             * @brief Sets the sprite of the sprite.
             *
             * @param sprite The sprite of the sprite.
             */
            void setSprite(void *sprite);

            /**
             * @brief Sets the color of the sprite.
             *
             * @param color The color of the sprite.
             */
            void setColor(void *color);

        private:
            Texture *_texture; /*!> The texture of the sprite. */
            void *_sprite; /*!> The sprite. */
            void *_color; /*!> The color of the sprite. */
    };
}
