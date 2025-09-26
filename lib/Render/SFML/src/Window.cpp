/**
 * EPITECH PROJECT, 2025
 * R-Type
 * File description:
 * Window.cpp
 */

#include "Subsystems/Render/Window.hpp"
#include "SFMLAdapter.hpp"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <memory>
#include <tuple>

Subsystems::Render::Window::Window(std::string windowName, unsigned int width, unsigned int height)
    : _windowName(windowName), _width(width), _height(height)
{
    _window = std::make_shared<sf::RenderWindow>(sf::VideoMode({width, height}), windowName);
}

Subsystems::Render::Window::~Window()
{
    CloseWindow();
}

unsigned int Subsystems::Render::Window::GetWidth() const
{
    return _width;
}

unsigned int Subsystems::Render::Window::GetHeight() const
{
    return _height;
}

std::string Subsystems::Render::Window::GetWindowName() const
{
    return _windowName;
}

std::any& Subsystems::Render::Window::GetWindow()
{
    return _window;
}

bool Subsystems::Render::Window::IsOpen() const
{
    return std::any_cast<std::shared_ptr<sf::RenderWindow>>(_window)->isOpen();
}

void Subsystems::Render::Window::SetWidth(unsigned int width)
{
    _width = width;
}

void Subsystems::Render::Window::SetHeight(unsigned int height)
{
    _height = height;
}

void Subsystems::Render::Window::SetWindowName(std::string windowName)
{
    _windowName = windowName;
}

void Subsystems::Render::Window::SetWindow(std::any& window)
{
    _window = window;
}

std::vector<inputTuple> Subsystems::Render::Window::HandleEvents()
{
    std::shared_ptr<sf::RenderWindow> window = std::any_cast<std::shared_ptr<sf::RenderWindow>>(_window);
    SFMLAdapter adapter;
    std::vector<inputTuple> inputs;

    while (const std::optional event = window->pollEvent()) {
        if (event->is<sf::Event::Closed>()) {
            window->close();
        }
        adapter.AdaptInput(event.value());
        inputTuple inputData = std::make_tuple(adapter.GetType(), adapter.GetKey(), adapter.GetAction());
        if (std::get<0>(inputData) != HMI::Input::Type::UnknownType
            && std::get<1>(inputData) != HMI::Input::KeyCode::UnknownKey
            && std::get<2>(inputData) != HMI::Input::Action::UnknownAction) {
            inputs.push_back(inputData);
        }
    }
    return inputs;
}

void Subsystems::Render::Window::ClearWindow(Color color)
{
    std::shared_ptr<sf::RenderWindow> window = std::any_cast<std::shared_ptr<sf::RenderWindow>>(_window);
    sf::Color sfColor = std::any_cast<sf::Color>(GetColor(color));

    window->clear(sfColor);
}

void Subsystems::Render::Window::CloseWindow()
{
    std::shared_ptr<sf::RenderWindow> window = std::any_cast<std::shared_ptr<sf::RenderWindow>>(_window);
    if (window->isOpen()) {
        window->close();
    }
}

void Subsystems::Render::Window::Draw(Sprite& sprite)
{
    std::shared_ptr<sf::RenderWindow> window = std::any_cast<std::shared_ptr<sf::RenderWindow>>(_window);
    std::shared_ptr<sf::Sprite> sfSprite = std::any_cast<std::shared_ptr<sf::Sprite>>(sprite.GetSprite());

    window->draw(*sfSprite);
}

void Subsystems::Render::Window::Draw(Text& text)
{
    std::shared_ptr<sf::RenderWindow> window = std::any_cast<std::shared_ptr<sf::RenderWindow>>(_window);
    std::shared_ptr<sf::Text> sfText = std::any_cast<std::shared_ptr<sf::Text>>(text.GetText());

    window->draw(*sfText);
}

void Subsystems::Render::Window::DisplayWindow()
{
    std::shared_ptr<sf::RenderWindow> window = std::any_cast<std::shared_ptr<sf::RenderWindow>>(_window);
    window->display();
}

std::any Subsystems::Render::Window::GetColor(Color color)
{
    switch (color) {
        case Color::WHITE_COLOR:
            return sf::Color(sf::Color::White);
        case Color::RED_COLOR:
            return sf::Color(sf::Color::Red);
        case Color::GREEN_COLOR:
            return sf::Color(sf::Color::Green);
        case Color::BLUE_COLOR  :
            return sf::Color(sf::Color::Blue);
        case Color::YELLOW_COLOR:
            return sf::Color(sf::Color::Yellow);
        case Color::MAGENTA_COLOR:
            return sf::Color(sf::Color::Magenta);
        default:
            return sf::Color(sf::Color::Black);
    }
}
