#include <gtest/gtest.h>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>

#include "ImageSaver.h"
#include "WordCloud.h"
#include "MaskApplier.h"

TEST(LoadFontTest, ValidFontPath) {
    sf::Font font;
    EXPECT_TRUE(font.loadFromFile("opensans.ttf"));
}

TEST(LoadFontTest, InvalidFontPath) {
    sf::Font font;
    EXPECT_FALSE(font.loadFromFile("invalid_font.ttf"));
}

TEST(CreateRenderTextureTest, ValidDimensions) {
    sf::RenderTexture renderTexture;
    EXPECT_TRUE(renderTexture.create(800, 600));
}

TEST(CreateRenderTextureTest, InvalidDimensions) {
    sf::RenderTexture renderTexture;
    EXPECT_FALSE(renderTexture.create(0, 0));
}

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

    sf::Texture generatedTexture = renderTexture.getTexture();
    EXPECT_TRUE(generatedTexture.getSize().x > 0);
    EXPECT_TRUE(generatedTexture.getSize().y > 0);
}

TEST(ApplyMaskTest, ValidMask) {
    sf::Texture texture;
    texture.loadFromFile("test_image.png");
    EXPECT_NO_THROW(applyMask(texture, "tiger.png"));
}

TEST(ApplyMaskTest, InvalidMask) {
    sf::Texture texture;
    texture.loadFromFile("test_image.png");
    EXPECT_THROW(applyMask(texture, "invalid_mask.png"), std::runtime_error);
}

TEST(ImageSaverTest, SaveImageSuccess) {
    sf::RenderTexture renderTexture;
    renderTexture.create(800, 600);
    sf::Texture texture = renderTexture.getTexture();
    EXPECT_TRUE(ImageSaver::saveImage(texture, "output.jpg"));
}

TEST(ImageSaverTest, SaveImageFailure) {
    sf::RenderTexture renderTexture;
    renderTexture.create(800, 600);
    sf::Texture texture = renderTexture.getTexture();
    EXPECT_FALSE(ImageSaver::saveImage(texture, "/invalid/path/output.jpg"));
}
