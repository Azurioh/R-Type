/**
 * EPITECH PROJECT, 2025
 * R-Type
 * File description:
 * Sprite.cpp
 */

#include "Subsystems/Render/Sprite.hpp"
#include "Subsystems/Render/Texture.hpp"
#include <SFML/Graphics.hpp>
#include <memory>
#include <iostream>

Subsystems::Render::Sprite::Sprite(Texture& texture)
{
    std::shared_ptr<sf::Texture> sfTexture = std::any_cast<std::shared_ptr<sf::Texture>>(texture.GetTexture());

    _sprite = std::make_shared<sf::Sprite>(*sfTexture);
}

std::any& Subsystems::Render::Sprite::GetSprite()
{
    return _sprite;
}

void Subsystems::Render::Sprite::SetSprite(std::any& sprite)
{
    _sprite = sprite;
}

void Subsystems::Render::Sprite::SetTexture(Texture& texture)
{
    auto sfTexture = std::any_cast<std::shared_ptr<sf::Texture>>(texture.GetTexture());

    _sprite = std::make_shared<sf::Sprite>(*sfTexture);
}
