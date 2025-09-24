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

std::string Subsystems::Render::Text::GetTextStr() const
{
    return _textStr;
}

std::string Subsystems::Render::Text::GetFontPath() const
{
    return _fontPath;
}

void *Subsystems::Render::Text::GetFont() const
{
    return _font;
}

void *Subsystems::Render::Text::GetText() const
{
    return _text;
}

unsigned int Subsystems::Render::Text::GetCharacterSize() const
{
    return _characterSize;
}

void Subsystems::Render::Text::SetTextStr(std::string textStr)
{
    _textStr = textStr;
    _text = new sf::Text(*static_cast<sf::Font *>(_font), _textStr, _characterSize);

    RefreshText();
}

void Subsystems::Render::Text::SetFontPath(std::string fontPath)
{
    _fontPath = fontPath;
    _font = new sf::Font(fontPath);
    _text = new sf::Text(*static_cast<sf::Font *>(_font), _textStr, _characterSize);

    RefreshText();
}

void Subsystems::Render::Text::SetFont(void *font)
{
    _font = font;
    _text = new sf::Text(*static_cast<sf::Font *>(font), _textStr, _characterSize);

    RefreshText();
}

void Subsystems::Render::Text::SetText(void *text)
{
    _text = text;

    RefreshText();
}

void Subsystems::Render::Text::SetCharacterSize(unsigned int characterSize)
{
    _characterSize = characterSize;
    _text = new sf::Text(*static_cast<sf::Font *>(_font), _textStr, _characterSize);

    RefreshText();
}

void Subsystems::Render::Text::RefreshText()
{
    sf::Font *sfFont = static_cast<sf::Font *>(_font);
    sf::Text *sfText = static_cast<sf::Text *>(_text);

    delete sfText;
    delete sfFont;

    _font = new sf::Font(_fontPath);
    _text = new sf::Text(*static_cast<sf::Font *>(_font), _textStr, _characterSize);
}
