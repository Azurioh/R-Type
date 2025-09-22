/**
 * EPITECH PROJECT, 2025
 * R-Type
 * File description:
 * Window.cpp
 */

#include <SFML/Graphics.hpp>
#include "Subsystems/Render/Window.hpp"

Subsystems::Render::Window::Window(std::string windowName, unsigned int width, unsigned int height)
    : _windowName(windowName), _width(width), _height(height)
{
    _window = new sf::RenderWindow(sf::VideoMode({width, height}), windowName);
}

Subsystems::Render::Window::~Window()
{
    sf::RenderWindow *window = static_cast<sf::RenderWindow *>(_window);

    closeWindow();
    if (window) {
        delete window;
    }
}

unsigned int Subsystems::Render::Window::getWidth() const
{
    return _width;
}

unsigned int Subsystems::Render::Window::getHeight() const
{
    return _height;
}

std::string Subsystems::Render::Window::getWindowName() const
{
    return _windowName;
}

void *Subsystems::Render::Window::getWindow() const
{
    return _window;
}

bool Subsystems::Render::Window::isOpen() const
{
    return static_cast<sf::RenderWindow *>(_window)->isOpen();
}

void Subsystems::Render::Window::setWidth(unsigned int width)
{
    _width = width;
}

void Subsystems::Render::Window::setHeight(unsigned int height)
{
    _height = height;
}

void Subsystems::Render::Window::setWindowName(std::string windowName)
{
    _windowName = windowName;
}

void Subsystems::Render::Window::setWindow(void *window)
{
    _window = window;
}

void Subsystems::Render::Window::handleEvents()
{
    sf::RenderWindow *window = static_cast<sf::RenderWindow *>(_window);

    while (const std::optional event = window->pollEvent()) {
        if (event->is<sf::Event::Closed>()) {
            window->close();
        }
    }
}

void Subsystems::Render::Window::clearWindow(Color color)
{
    sf::RenderWindow *window = static_cast<sf::RenderWindow *>(_window);
    sf::Color sfColor = *static_cast<sf::Color *>(getColor(color));

    window->clear(sfColor);
}

void Subsystems::Render::Window::closeWindow()
{
    sf::RenderWindow *window = static_cast<sf::RenderWindow *>(_window);
    if (window->isOpen()) {
        window->close();
    }
}

void Subsystems::Render::Window::draw(const Sprite& sprite)
{
    sf::RenderWindow *window = static_cast<sf::RenderWindow *>(_window);
    sf::Sprite sfSprite = *static_cast<sf::Sprite *>(sprite.getSprite());

    window->draw(sfSprite);
}

void Subsystems::Render::Window::draw(const Text& text)
{
    sf::RenderWindow *window = static_cast<sf::RenderWindow *>(_window);
    sf::Text sfText = *static_cast<sf::Text *>(text.getText());

    window->draw(sfText);
}

void Subsystems::Render::Window::refreshWindow()
{
    sf::RenderWindow *window = static_cast<sf::RenderWindow *>(_window);

    window->close();

    window->create(sf::WindowHandle());
}

void Subsystems::Render::Window::displayWindow()
{
    sf::RenderWindow *window = static_cast<sf::RenderWindow *>(_window);
    window->display();
}

void *Subsystems::Render::Window::getColor(Color color) const
{
    switch (color) {
        case Color::WHITE_COLOR:
            return static_cast<void *>(new sf::Color(sf::Color::White));
        case Color::RED_COLOR:
            return static_cast<void *>(new sf::Color(sf::Color::Red));
        case Color::GREEN_COLOR:
            return static_cast<void *>(new sf::Color(sf::Color::Green));
        case Color::BLUE_COLOR  :
            return static_cast<void *>(new sf::Color(sf::Color::Blue));
        case Color::YELLOW_COLOR:
            return static_cast<void *>(new sf::Color(sf::Color::Yellow));
        case Color::MAGENTA_COLOR:
            return static_cast<void *>(new sf::Color(sf::Color::Magenta));
        default:
            return static_cast<void *>(new sf::Color(sf::Color::Black));
    }
}
