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
            ~Image();

            /**
             * @brief Gets the image.
             *
             * @return The image.
             */
            void *GetImage() const;

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
            void SetImage(void *image);

            /**
             * @brief Deletes the image.
             */
            void DeleteImage();

        private:
            void *_image; /*!> The image. */
    };
}
