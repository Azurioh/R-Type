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
    class Sprite {
        public:
            Sprite(Texture *texture);
            ~Sprite();

            Texture *getTexture() const;
            void *getSprite() const;

            void setTexture(Texture *texture);
            void setSprite(void *sprite);
            void setColor(void *color);

        private:
            Texture *_texture;
            void *_sprite;
            void *_color;
    };
}
