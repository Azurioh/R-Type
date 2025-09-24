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
    DeleteTexture();
}

std::string Subsystems::Render::Texture::GetImagePath() const
{
    return _imagePath;
}

void *Subsystems::Render::Texture::GetTexture() const
{
    return _texture;
}

void Subsystems::Render::Texture::SetTexture(std::string imagePath)
{
    DeleteTexture();
    _texture = new sf::Texture(imagePath);
}

void Subsystems::Render::Texture::SetTexture(void *texture)
{
    DeleteTexture();
    _texture = texture;
}

void Subsystems::Render::Texture::DeleteTexture()
{
    if (_texture) {
        sf::Texture *sfTexture = static_cast<sf::Texture *>(_texture);
        delete sfTexture;
        _texture = nullptr;
    }
}
