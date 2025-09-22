/**
 * EPITECH PROJECT, 2025
 * R-Type
 * File description:
 * Image
 */

#pragma once

#include "Subsystems/Render/Texture.hpp"
#include <string>

namespace Subsystems::Render {
    class Image {
        public:
            Image(std::string imagePath);
            ~Image();

            void *getImage() const;

            void setImage(std::string imagePath);
            void setImage(void *image);
            void deleteImage();

        private:
            void *_image;
    };
}
