/**
 * EPITECH PROJECT, 2025
 * R-Type
 * File description:
 * Image
 */

#pragma once

#include "Subsystems/Render/Texture.hpp"
#include <any>
#include <string>

namespace Subsystems::Render {
    /**
     * @class Image
     *
     * @brief A class that represents an image.
     */
    class Image {
        public:
            /**
             * @brief Constructs an image with the specified image path.
             *
             * @param imagePath The path of the image.
             */
            Image(std::string imagePath);

            /**
             * @brief Gets the image.
             *
             * @return The image.
             */
            std::any& GetImage();

            /**
             * @brief Sets the image path.
             *
             * @param imagePath The path of the image.
             */
            void SetImage(std::string imagePath);

            /**
             * @brief Sets the image.
             *
             * @param image The image.
             */
            void SetImage(std::any& image);

        private:
            std::any _image; /*!> The image. */
    };
}
