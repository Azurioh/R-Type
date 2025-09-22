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
    sf::Texture *sfTexture = static_cast<sf::Texture *>(texture->getTexture());

    _sprite = new sf::Sprite(*sfTexture);
}

Subsystems::Render::Sprite::~Sprite()
{
    deleteSprite();
}

void *Subsystems::Render::Sprite::getSprite() const
{
    return _sprite;
}

void Subsystems::Render::Sprite::setSprite(void *sprite)
{
    deleteSprite();
    _sprite = sprite;
}

void Subsystems::Render::Sprite::setTexture(Texture *texture)
{
    sf::Texture *sfTexture = static_cast<sf::Texture *>(texture->getTexture());

    deleteSprite();
    _sprite = new sf::Sprite(*sfTexture);
}

void Subsystems::Render::Sprite::deleteSprite()
{
    if (_sprite) {
        sf::Sprite *sfSprite = static_cast<sf::Sprite *>(_sprite);
        delete sfSprite;
        _sprite = nullptr;
    }
}
