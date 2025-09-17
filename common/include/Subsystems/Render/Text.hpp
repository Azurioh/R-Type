/**
 * EPITECH PROJECT, 2025
 * R-Type
 * File description:
 * Text
 */

#pragma once

#include <string>

namespace Subsystems::Render {
    class Text {
        public:
            Text(std::string textStr, std::string fontPath);
            ~Text();

            std::string getTextStr() const;
            std::string getFontPath() const;
            void *getFont() const;
            void *getText() const;

            void setTextStr(std::string textStr);
            void setFontPath(std::string fontPath);
            void setFont(void *font);
            void setText(void *text);
        private:
            std::string _textStr;
            std::string _fontPath;
            void *_font;
            void *_text;
    };
}
