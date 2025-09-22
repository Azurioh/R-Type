/*
** EPITECH PROJECT, 2025
** R-Type
** File description:
** Window
*/

#pragma once

#include <string>
#include "Subsystems/Render/Sprite.hpp"
#include "Subsystems/Render/Text.hpp"

namespace Subsystems::Render {
    /**
     * @class Window
     *
     * @brief A class that represents a window.
     */
    class Window {
        public:
            /**
             * @enum Color
             *
             * @brief The color of the window.
             */
            enum Color {
                BLACK_COLOR = 0,
                WHITE_COLOR = 1,
                RED_COLOR = 2,
                GREEN_COLOR = 3,
                BLUE_COLOR = 4,
                YELLOW_COLOR = 5,
                MAGENTA_COLOR = 6,
            };

            /**
             * @brief Constructs a window with the specified window name, width and height.
             *
             * @param windowName The name of the window.
             * @param width The width of the window.
             * @param height The height of the window.
             */
            Window(std::string windowName, unsigned int width, unsigned int height);

            /**
             * @brief Destroys the window.
             */
            ~Window();

            /**
             * @brief Gets the width of the window.
             *
             * @return The width of the window.
             */
            unsigned int getWidth() const;

            /**
             * @brief Gets the height of the window.
             *
             * @return The height of the window.
             */
            unsigned int getHeight() const;

            /**
             * @brief Gets the name of the window.
             *
             * @return The name of the window.
             */
            std::string getWindowName() const;

            /**
             * @brief Gets the window.
             *
             * @return The window.
             */
            void *getWindow() const;

            /**
             * @brief Checks if the window is open.
             *
             * @return True if the window is open, false otherwise.
             */
            bool isOpen() const;

            /**
             * @brief Sets the width of the window.
             *
             * @param width The width of the window.
             */
            void setWidth(unsigned int width);

            /**
             * @brief Sets the height of the window.
             *
             * @param height The height of the window.
             */
            void setHeight(unsigned int height);

            /**
             * @brief Sets the name of the window.
             *
             * @param windowName The name of the window.
             */
            void setWindowName(std::string windowName);

            /**
             * @brief Sets the window.
             *
             * @param window The window.
             */
            void setWindow(void *window);

            /**
             * @brief Handles the events of the window.
             */
            void handleEvents(void);

            /**
             * @brief Clears the window.
             */
            void clearWindow(Color color);

            /**
             * @brief Closes the window.
             */
            void closeWindow(void);

            /**
             * @brief Draws the sprite.
             */
            void draw(const Sprite& sprite);

            /**
             * @brief Draws the text.
             */
            void draw(const Text& text);

            /**
             * @brief Displays the window.
             */
            void displayWindow(void);

        private:
            /**
             * @brief Refreshes the window.
             */
            void refreshWindow(void);

            /**
             * @brief Gets the color.
             *
             * @param color The color.
             * @return The color.
             */
            void *getColor(Color color) const;

            unsigned int _width; /*!> The width of the window. */
            unsigned int _height; /*!> The height of the window. */
            std::string _windowName; /*!> The name of the window. */
            void *_window; /*!> The window. */
    };
}
