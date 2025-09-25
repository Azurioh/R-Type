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
    RefreshText();
}

std::string Subsystems::Render::Text::GetTextStr() const
{
    return _textStr;
}

std::string Subsystems::Render::Text::GetFontPath() const
{
    return _fontPath;
}

std::any& Subsystems::Render::Text::GetFont()
{
    return _font;
}

std::any& Subsystems::Render::Text::GetText()
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

    RefreshText();
}

void Subsystems::Render::Text::SetFontPath(std::string fontPath)
{
    _fontPath = fontPath;

    RefreshText();
}

void Subsystems::Render::Text::SetFont(std::any& font)
{
    _font = font;

    RefreshText();
}

void Subsystems::Render::Text::SetText(std::any& text)
{
    _text = text;

    RefreshText();
}

void Subsystems::Render::Text::SetCharacterSize(unsigned int characterSize)
{
    _characterSize = characterSize;

    RefreshText();
}

void Subsystems::Render::Text::RefreshText()
{
    _font = std::make_shared<sf::Font>(_fontPath);
    std::shared_ptr<sf::Font> fontCasted = std::any_cast<std::shared_ptr<sf::Font>>(_font);
    const sf::Font fontConst = *fontCasted;
    _text = std::make_shared<sf::Text>(fontConst, _textStr, _characterSize);
}
