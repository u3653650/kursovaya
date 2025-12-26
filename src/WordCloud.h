#ifndef WORDCLOUD_H
#define WORDCLOUD_H

#include <SFML/Graphics.hpp>
#include <vector>
#include <string>

class WordCloud {
public:
    WordCloud(const sf::Font &font, unsigned int width, unsigned int height);

    void addWord(const std::string &word);

    bool checkCollision(const sf::Text &newText, const std::vector<sf::Text> &placedWords);

    void generate(sf::RenderTexture &renderTexture);

private:
    std::vector<std::string> words;
    const sf::Font &font;
    unsigned int width, height;
};

#endif // WORDCLOUD_H
