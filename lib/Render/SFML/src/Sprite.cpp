/**
 * EPITECH PROJECT, 2025
 * R-Type
 * File description:
 * Sprite.cpp
 */

#include "Subsystems/Render/Sprite.hpp"
#include "Subsystems/Render/Texture.hpp"
#include <SFML/Graphics.hpp>

Subsystems::Render::Sprite::Sprite(Texture *texture)
{
    sf::Texture *sfTexture = static_cast<sf::Texture *>(texture->GetTexture());

    _sprite = new sf::Sprite(*sfTexture);
}

Subsystems::Render::Sprite::~Sprite()
{
    DeleteSprite();
}

void *Subsystems::Render::Sprite::GetSprite() const
{
    return _sprite;
}

void Subsystems::Render::Sprite::SetSprite(void *sprite)
{
    DeleteSprite();
    _sprite = sprite;
}

void Subsystems::Render::Sprite::SetTexture(Texture *texture)
{
    sf::Texture *sfTexture = static_cast<sf::Texture *>(texture->GetTexture());

    DeleteSprite();
    _sprite = new sf::Sprite(*sfTexture);
}

void Subsystems::Render::Sprite::DeleteSprite()
{
    if (_sprite) {
        sf::Sprite *sfSprite = static_cast<sf::Sprite *>(_sprite);
        delete sfSprite;
        _sprite = nullptr;
    }
}
