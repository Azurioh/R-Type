/**
 * EPITECH PROJECT, 2025
 * R-Type
 * File description:
 * Texture.cpp
 */

#include "Subsystems/Render/Texture.hpp"
#include "Subsystems/Render/Image.hpp"
#include <SFML/Graphics.hpp>

Subsystems::Render::Texture::Texture(std::string imagePath)
{
    _texture = new sf::Texture(imagePath);
}

Subsystems::Render::Texture::~Texture()
{
    deleteTexture();
}

std::string Subsystems::Render::Texture::getImagePath() const
{
    return _imagePath;
}

void *Subsystems::Render::Texture::getTexture() const
{
    return _texture;
}

void Subsystems::Render::Texture::setTexture(std::string imagePath)
{
    deleteTexture();
    _texture = new sf::Texture(imagePath);
}

void Subsystems::Render::Texture::setTexture(void *texture)
{
    deleteTexture();
    _texture = texture;
}

void Subsystems::Render::Texture::deleteTexture()
{
    if (_texture) {
        sf::Texture *sfTexture = static_cast<sf::Texture *>(_texture);
        delete sfTexture;
        _texture = nullptr;
    }
}
