/**
 * EPITECH PROJECT, 2025
 * R-Type
 * File description:
 * Text
 */

#pragma once

#include <string>

namespace Subsystems::Render {
    /**
     * @class Text
     *
     * @brief A class that represents a text.
     */
    class Text {
        public:
            /**
             * @brief Constructs a text with the specified text string and font path.
             *
             * @param textStr The text string.
             * @param fontPath The font path.
             * @param characterSize The character size.
             */
            Text(std::string textStr, std::string fontPath, unsigned int characterSize = 32);

            /**
             * @brief Destroys the text.
             */
            ~Text();

            /**
             * @brief Gets the text string.
             *
             * @return The text string.
             */
            std::string getTextStr() const;

            /**
             * @brief Gets the font path.
             *
             * @return The font path.
             */
            std::string getFontPath() const;

            /**
             * @brief Gets the font.
             *
             * @return The font.
             */
            void *getFont() const;

            /**
             * @brief Gets the text.
             *
             * @return The text.
             */
            void *getText() const;

            /**
             * @brief Gets the character size.
             *
             * @return The character size.
             */
            unsigned int getCharacterSize() const;

            /**
             * @brief Sets the text string.
             *
             * @param textStr The text string.
             */
            void setTextStr(std::string textStr);

            /**
             * @brief Sets the font path.
             *
             * @param fontPath The font path.
             */
            void setFontPath(std::string fontPath);

            /**
             * @brief Sets the font.
             *
             * @param font The font.
             */
            void setFont(void *font);

            /**
             * @brief Sets the text.
             *
             * @param text The text.
             */
            void setText(void *text);

            /**
             * @brief Sets the character size.
             *
             * @param characterSize The character size.
             */
            void setCharacterSize(unsigned int characterSize);

            /**
             * @brief Refreshes the text.
             */
            void refreshText();

        private:
            std::string _textStr; /*!> The text string. */
            std::string _fontPath; /*!> The font path. */
            void *_font; /*!> The font. */
            void *_text; /*!> The text. */
            unsigned int _characterSize; /*!> The character size. */
    };
}
