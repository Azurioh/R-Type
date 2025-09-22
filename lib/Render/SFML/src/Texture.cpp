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

Subsystems::Render::Texture::Texture(const Image& image)
{
    sf::Image *sfImage = static_cast<sf::Image *>(image.getImage());
    _texture = new sf::Texture(*sfImage);
}

Subsystems::Render::Texture::~Texture()
{
    deleteTexture();
}

void *Subsystems::Render::Texture::getTexture()
{
    return _texture;
}

void Subsystems::Render::Texture::setTexture(std::string imagePath)
{
    deleteTexture();
    _texture = new sf::Texture(imagePath);
}

void Subsystems::Render::Texture::setTexture(const Image& image)
{
    deleteTexture();
    _texture = new sf::Texture(*static_cast<sf::Image *>(image.getImage()));
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
