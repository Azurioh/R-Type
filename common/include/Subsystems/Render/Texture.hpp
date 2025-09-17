/**
 * EPITECH PROJECT, 2025
 * R-Type
 * File description:
 * Texture
 */

#pragma once

#include <string>

namespace Subsystems::Render {
    class Texture {
        public:
            Texture(std::string imagePath);
            ~Texture();

            std::string getImagePath() const;
            void *getTexture() const;

            void setImagePath(std::string imagePath);
            void setTexture(void *texture);

        private:
            std::string _imagePath;
            void *_texture;
    };
}
