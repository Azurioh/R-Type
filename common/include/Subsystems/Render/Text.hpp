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
            std::string GetTextStr() const;

            /**
             * @brief Gets the font path.
             *
             * @return The font path.
             */
            std::string GetFontPath() const;

            /**
             * @brief Gets the font.
             *
             * @return The font.
             */
            void *GetFont() const;

            /**
             * @brief Gets the text.
             *
             * @return The text.
             */
            void *GetText() const;

            /**
             * @brief Gets the character size.
             *
             * @return The character size.
             */
            unsigned int GetCharacterSize() const;

            /**
             * @brief Sets the text string.
             *
             * @param textStr The text string.
             */
            void SetTextStr(std::string textStr);

            /**
             * @brief Sets the font path.
             *
             * @param fontPath The font path.
             */
            void SetFontPath(std::string fontPath);

            /**
             * @brief Sets the font.
             *
             * @param font The font.
             */
            void SetFont(void *font);

            /**
             * @brief Sets the text.
             *
             * @param text The text.
             */
            void SetText(void *text);

            /**
             * @brief Sets the character size.
             *
             * @param characterSize The character size.
             */
            void SetCharacterSize(unsigned int characterSize);

            /**
             * @brief Refreshes the text.
             */
            void RefreshText();

        private:
            std::string _textStr; /*!> The text string. */
            std::string _fontPath; /*!> The font path. */
            void *_font; /*!> The font. */
            void *_text; /*!> The text. */
            unsigned int _characterSize; /*!> The character size. */
    };
}
