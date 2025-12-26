#include "WordCloud.h"
#include <cstdlib>
#include <SFML/Graphics.hpp>
#include <Windows.h>

std::string ConvertCP1251ToUTF8(const std::string& str)
{
    int len = MultiByteToWideChar(1251, 0, str.c_str(), -1, NULL, 0);
    wchar_t* wstr = new wchar_t[len];
    MultiByteToWideChar(1251, 0, str.c_str(), -1, wstr, len);

    len = WideCharToMultiByte(CP_UTF8, 0, wstr, -1, NULL, 0, 0, 0);
    char* utf8 = new char[len];
    WideCharToMultiByte(CP_UTF8, 0, wstr, -1, utf8, len, 0, 0);

    std::string result(utf8);
    delete[] wstr;
    delete[] utf8;

    return result;
}

WordCloud::WordCloud(const sf::Font& font, unsigned int width, unsigned int height)
    : font(font), width(width), height(height) {}

void WordCloud::addWord(const std::string& word) {
    words.push_back(word);
}

bool WordCloud::checkCollision(const sf::Text& newText, const std::vector<sf::Text>& placedWords) {
    sf::FloatRect newBounds = newText.getGlobalBounds();

    for (const auto& placedWord : placedWords) {
        sf::FloatRect placedBounds = placedWord.getGlobalBounds();
        if (newBounds.intersects(placedBounds)) {
            return true; // Есть пересечение
        }
    }
    return false; // Нет пересечения
}

void WordCloud::generate(sf::RenderTexture& renderTexture) {
    bool isMainWordPlaced = false;
    renderTexture.clear(sf::Color(240, 240, 240));

    std::vector<sf::Text> placedWords;

    for (const auto& word : words) {
        int attempts = 0;
        std::string utf8_word = ConvertCP1251ToUTF8(word);
        sf::Text text;
        text.setFont(font);

        text.setString(sf::String::fromUtf8(utf8_word.begin(), utf8_word.end()));

        int size = 50;
        text.setCharacterSize(size);
        text.setFillColor(sf::Color(rand() % 256, rand() % 256, rand() % 256)); // Случайный цвет

        bool collision;
        float x, y;

        do {
            if (attempts < 250) {
                size = 50;
            } else if (attempts < 500) {
                size = 25;
            } else if (attempts < 750) {
                size = 10;
            } else {
                size = 1;
            }
            text.setCharacterSize(size);
            if (!isMainWordPlaced) {
                size = 150;
                text.setCharacterSize(size);
                isMainWordPlaced = true;
            }
            x = rand() % (static_cast<int>(width) - static_cast<int>(text.getLocalBounds().width));
            y = rand() % (static_cast<int>(height) - static_cast<int>(text.getLocalBounds().height));
            text.setPosition(x, y);
            collision = checkCollision(text, placedWords);
            ++attempts;
        } while (collision and attempts < 1000);
        if (attempts >= 1000) {
            break;
        }
        placedWords.push_back(text);
        renderTexture.draw(text);

    }

    renderTexture.display();
}
