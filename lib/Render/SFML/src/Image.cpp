/**
 * EPITECH PROJECT, 2025
 * R-Type
 * File description:
 * Image.cpp
 */

#include "Subsystems/Render/Image.hpp"
#include "Subsystems/Render/Texture.hpp"
#include <SFML/Graphics.hpp>
#include <memory>

Subsystems::Render::Image::Image(std::string imagePath)
{
    _image = std::make_shared<sf::Image>(imagePath);
}

std::any& Subsystems::Render::Image::GetImage()
{
    return _image;
}

void Subsystems::Render::Image::SetImage(std::string imagePath)
{
    _image = std::make_shared<sf::Image>(imagePath);
}

void Subsystems::Render::Image::SetImage(std::any& image)
{
    _image = image;
}
