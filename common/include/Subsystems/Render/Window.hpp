/*
** EPITECH PROJECT, 2025
** R-Type
** File description:
** Window
*/

#pragma once

#include <string>
#include "Subsystems/Render/Sprite.hpp"

namespace Subsystems::Render {
    class Window {
        public:
            enum Color {
                BLACK = 0,
                WHITE = 1,
                RED = 2,
                GREEN = 3,
                BLUE = 4,
                YELLOW = 5,
                MAGENTA = 6,
            };

            Window(std::string windowName, unsigned int width, unsigned int height);
            ~Window();

            unsigned int getWidth() const;
            unsigned int getHeight() const;
            std::string getWindowName() const;
            void *getWindow() const;
            bool isOpen() const;

            void setWidth(unsigned int width);
            void setHeight(unsigned int height);
            void setWindowName(std::string windowName);
            void setWindow(void *window);

            void handleEvents(void);
            void clearWindow(Color color);
            void closeWindow(void);
            void drawItem(Render::Sprite *sprite);
            void displayWindow(void);

        private:
            void refreshWindow(void);
            const void *getColor(Color color) const;

            unsigned int _width;
            unsigned int _height;
            std::string _windowName;
            void *_window;
    };
}
