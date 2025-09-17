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
            // void setX(float x);
            // void setY(float y);
            // void setZ(float z);
            // void setWidth(float width);
            // void setHeight(float height);
            // void setRotation(float rotation);
            // void setScale(float scale);
            // void setAngle(float angle);
            // void setOriginX(float originX);
            // void setOriginY(float originY);
            // void setOriginZ(float originZ);

        private:
            Texture *_texture;
            void *_sprite;
            void *_color;
            // float _x;
            // float _y;
            // float _z;
            // float _width;
            // float _height;
            // float _rotation;
            // float _scale;
    };
}
