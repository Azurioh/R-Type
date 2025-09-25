/*
** EPITECH PROJECT, 2025
** R-Type
** File description:
** Window
*/

#pragma once

#include <any>
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
            unsigned int GetWidth() const;

            /**
             * @brief Gets the height of the window.
             *
             * @return The height of the window.
             */
            unsigned int GetHeight() const;

            /**
             * @brief Gets the name of the window.
             *
             * @return The name of the window.
             */
            std::string GetWindowName() const;

            /**
             * @brief Gets the window.
             *
             * @return The window.
             */
            std::any& GetWindow();

            /**
             * @brief Checks if the window is open.
             *
             * @return True if the window is open, false otherwise.
             */
            bool IsOpen() const;

            /**
             * @brief Sets the width of the window.
             *
             * @param width The width of the window.
             */
            void SetWidth(unsigned int width);

            /**
             * @brief Sets the height of the window.
             *
             * @param height The height of the window.
             */
            void SetHeight(unsigned int height);

            /**
             * @brief Sets the name of the window.
             *
             * @param windowName The name of the window.
             */
            void SetWindowName(std::string windowName);

            /**
             * @brief Sets the window.
             *
             * @param window The window.
             */
            void SetWindow(std::any& window);

            /**
             * @brief Handles the events of the window.
             */
            void HandleEvents(void);

            /**
             * @brief Clears the window.
             */
            void ClearWindow(Color color);

            /**
             * @brief Closes the window.
             */
            void CloseWindow(void);

            /**
             * @brief Draws the sprite.
             */
            void Draw(Sprite& sprite);

            /**
             * @brief Draws the text.
             */
            void Draw(Text& text);

            /**
             * @brief Displays the window.
             */
            void DisplayWindow(void);

        private:
            /**
             * @brief Gets the color.
             *
             * @param color The color.
             * @return The color.
             */
            std::any GetColor(Color color);

            unsigned int _width; /*!> The width of the window. */
            unsigned int _height; /*!> The height of the window. */
            std::string _windowName; /*!> The name of the window. */
            std::any _window; /*!> The window. */
    };
}
