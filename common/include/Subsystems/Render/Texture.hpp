/**
 * EPITECH PROJECT, 2025
 * R-Type
 * File description:
 * Texture
 */

#pragma once

#include <string>
#include <any>

namespace Subsystems::Render {
    /**
     * @class Texture
     *
     * @brief A class that represents a texture.
     */
    class Texture {
        public:
            /**
             * @brief Constructs a texture with the specified image path.
             *
             * @param imagePath The path of the image.
             */
            Texture(std::string imagePath);

            /**
             * @brief Gets the image path.
             *
             * @return The image path.
             */
            std::string GetImagePath() const;

            /**
             * @brief Gets the texture.
             *
             * @return The texture.
             */
            std::any& GetTexture();

            /**
             * @brief Sets the image path.
             *
             * @param imagePath The image path.
             */
            void SetTexture(std::string imagePath);

            /**
             * @brief Sets the texture.
             *
             * @param texture The texture.
             */
            void SetTexture(std::any& texture);

        private:
            std::string _imagePath; /*!> The image path. */
            std::any _texture; /*!> The texture. */
    };
}
