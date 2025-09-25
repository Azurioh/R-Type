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
    _texture = std::make_shared<sf::Texture>(imagePath);
}

std::string Subsystems::Render::Texture::GetImagePath() const
{
    return _imagePath;
}

std::any& Subsystems::Render::Texture::GetTexture()
{
    return _texture;
}

void Subsystems::Render::Texture::SetTexture(std::string imagePath)
{
    _texture = std::make_shared<sf::Texture>(imagePath);
}

void Subsystems::Render::Texture::SetTexture(std::any& texture)
{
    _texture = texture;
}
