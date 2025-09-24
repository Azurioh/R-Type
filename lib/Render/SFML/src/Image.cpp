/**
 * EPITECH PROJECT, 2025
 * R-Type
 * File description:
 * Image.cpp
 */

#include "Subsystems/Render/Image.hpp"
#include "Subsystems/Render/Texture.hpp"
#include <SFML/Graphics.hpp>

Subsystems::Render::Image::Image(std::string imagePath)
{
    _image = new sf::Image(imagePath);
}

Subsystems::Render::Image::~Image()
{
    DeleteImage();
}

void *Subsystems::Render::Image::GetImage() const
{
    return _image;
}

void Subsystems::Render::Image::SetImage(std::string imagePath)
{
    DeleteImage();
    _image = new sf::Image(imagePath);
}

void Subsystems::Render::Image::SetImage(void *image)
{
    DeleteImage();
    _image = image;
}

void Subsystems::Render::Image::DeleteImage()
{
    if (_image) {
        sf::Image *sfImage = static_cast<sf::Image *>(_image);
        delete sfImage;
        _image = nullptr;
    }
}
