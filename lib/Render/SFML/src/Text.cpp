/**
 * EPITECH PROJECT, 2025
 * R-Type
 * File description:
 * Text.cpp
 */

#include "Subsystems/Render/Text.hpp"
#include <SFML/Graphics.hpp>

Subsystems::Render::Text::Text(std::string textStr, std::string fontPath, unsigned int characterSize): _textStr(textStr), _fontPath(fontPath)
{
    sf::Font *sfFont = new sf::Font(fontPath);

    _font = sfFont;
    _text = new sf::Text(*sfFont, textStr, characterSize);
}

Subsystems::Render::Text::~Text()
{
    if (_font) {
        sf::Font *sfFont = static_cast<sf::Font *>(_font);
        delete sfFont;
        _font = nullptr;
    }
    if (_text) {
        sf::Text *sfText = static_cast<sf::Text *>(_text);
        delete sfText;
        _text = nullptr;
    }
}

std::string Subsystems::Render::Text::getTextStr() const
{
    return _textStr;
}

std::string Subsystems::Render::Text::getFontPath() const
{
    return _fontPath;
}

void *Subsystems::Render::Text::getFont() const
{
    return _font;
}

void *Subsystems::Render::Text::getText() const
{
    return _text;
}

unsigned int Subsystems::Render::Text::getCharacterSize() const
{
    return _characterSize;
}

void Subsystems::Render::Text::setTextStr(std::string textStr)
{
    _textStr = textStr;
    _text = new sf::Text(*static_cast<sf::Font *>(_font), _textStr, _characterSize);

    refreshText();
}

void Subsystems::Render::Text::setFontPath(std::string fontPath)
{
    _fontPath = fontPath;
    _font = new sf::Font(fontPath);
    _text = new sf::Text(*static_cast<sf::Font *>(_font), _textStr, _characterSize);

    refreshText();
}

void Subsystems::Render::Text::setFont(void *font)
{
    _font = font;
    _text = new sf::Text(*static_cast<sf::Font *>(font), _textStr, _characterSize);

    refreshText();
}

void Subsystems::Render::Text::setText(void *text)
{
    _text = text;

    refreshText();
}

void Subsystems::Render::Text::setCharacterSize(unsigned int characterSize)
{
    _characterSize = characterSize;
    _text = new sf::Text(*static_cast<sf::Font *>(_font), _textStr, _characterSize);

    refreshText();
}

void Subsystems::Render::Text::refreshText()
{
    sf::Font *sfFont = static_cast<sf::Font *>(_font);
    sf::Text *sfText = static_cast<sf::Text *>(_text);

    delete sfText;
    delete sfFont;

    _font = new sf::Font(_fontPath);
    _text = new sf::Text(*static_cast<sf::Font *>(_font), _textStr, _characterSize);
}
