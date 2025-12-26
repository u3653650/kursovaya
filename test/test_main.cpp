#include <gtest/gtest.h>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>

#include "ImageSaver.h"
#include "WordCloud.h"
#include "MaskApplier.h"

// Тестирование загрузки шрифта
TEST(LoadFontTest, ValidFontPath) {
    sf::Font font;
    EXPECT_TRUE(font.loadFromFile("opensans.ttf"));
}

TEST(LoadFontTest, InvalidFontPath) {
    sf::Font font;
    EXPECT_FALSE(font.loadFromFile("invalid_font.ttf"));
}

// Тестирование создания RenderTexture
TEST(CreateRenderTextureTest, ValidDimensions) {
    sf::RenderTexture renderTexture;
    EXPECT_TRUE(renderTexture.create(800, 600));
}

TEST(CreateRenderTextureTest, InvalidDimensions) {
    sf::RenderTexture renderTexture;
    EXPECT_FALSE(renderTexture.create(0, 0));  // Невозможные размеры
}

// Тестирование генерации облака слов
TEST(WordCloudTest, GenerateWordCloud) {
    sf::Font font;
    font.loadFromFile("opensans.ttf");

    WordCloud wordCloud(font, 800, 600);
    wordCloud.addWord("test");
    wordCloud.addWord("hello");
    wordCloud.addWord("world");

    sf::RenderTexture renderTexture;
    EXPECT_TRUE(renderTexture.create(800, 600));

    wordCloud.generate(renderTexture);

    // Пример: Проверим, что генерация не вызывает ошибок (например, не получаем пустую картинку)
    sf::Texture generatedTexture = renderTexture.getTexture();
    EXPECT_TRUE(generatedTexture.getSize().x > 0);
    EXPECT_TRUE(generatedTexture.getSize().y > 0);
}

// Тестирование функции applyMask
TEST(ApplyMaskTest, ValidMask) {
    sf::Texture texture;
    texture.loadFromFile("test_image.png");  // Замените на реальное изображение

    // Проверим, что маска применяется корректно
    EXPECT_NO_THROW(applyMask(texture, "tiger.png"));
}

TEST(ApplyMaskTest, InvalidMask) {
    sf::Texture texture;
    texture.loadFromFile("test_image.png");  // Замените на реальное изображение

    // Проверим, что при неправильном пути маски выбрасывается исключение или происходит ошибка
    EXPECT_THROW(applyMask(texture, "invalid_mask.png"), std::runtime_error);
}

// Тестирование ImageSaver
TEST(ImageSaverTest, SaveImageSuccess) {
    sf::RenderTexture renderTexture;
    renderTexture.create(800, 600);  // Создаем render texture для теста
    sf::Texture texture = renderTexture.getTexture();

    // Попробуем сохранить изображение
    EXPECT_TRUE(ImageSaver::saveImage(texture, "output.jpg"));
}

TEST(ImageSaverTest, SaveImageFailure) {
    sf::RenderTexture renderTexture;
    renderTexture.create(800, 600);  // Создаем render texture для теста
    sf::Texture texture = renderTexture.getTexture();

    // Пробуем сохранить в недоступный путь (например, в директорию без прав на запись)
    EXPECT_FALSE(ImageSaver::saveImage(texture, "/invalid/path/output.jpg"));
}

