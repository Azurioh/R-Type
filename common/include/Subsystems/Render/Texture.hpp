/**
 * EPITECH PROJECT, 2025
 * R-Type
 * File description:
 * Texture
 */

#pragma once

#include <string>

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
             * @brief Destroys the texture.
             */
            ~Texture();

            /**
             * @brief Gets the image path.
             *
             * @return The image path.
             */
            std::string getImagePath() const;

            /**
             * @brief Gets the texture.
             *
             * @return The texture.
             */
            void *getTexture() const;

            /**
             * @brief Sets the image path.
             *
             * @param imagePath The image path.
             */
            void setTexture(std::string imagePath);

            /**
             * @brief Sets the texture.
             *
             * @param texture The texture.
             */
            void setTexture(void *texture);

            /**
             * @brief Deletes the texture.
             */
            void deleteTexture();

        private:
            std::string _imagePath; /*!> The image path. */
            void *_texture; /*!> The texture. */
    };
}
