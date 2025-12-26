#include <codecvt>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <windows.h>

#include "ImageSaver.h"
#include "WordCloud.h"
#include "MaskApplier.h"


int main(int argc, char *argv[]) {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    system("chcp 1251");
    srand(static_cast<unsigned int>(time(0)));

    if (argc <= 1) {
        std::cerr << "Нет слов" << std::endl;
        return -1;
    }

    const unsigned int width = 800;
    const unsigned int height = 600;

    sf::Font font;
    if (!font.loadFromFile("opensans.ttf")) {
        std::cerr << "Ошибка загрузки шрифта!" << std::endl;
        std::cerr << "Поместите файл opensans.ttf в папку с программой." << std::endl;
        return -1;
    }

    WordCloud wordCloud(font, width, height);

    for (int j = 1; j < 100; ++j) {
        for (int i = 1; i < argc; ++i) {
            std::string word = argv[i];
            wordCloud.addWord(word);
        }
    }

    sf::RenderTexture renderTexture;
    if (!renderTexture.create(width, height)) {
        std::cerr << "Ошибка создания RenderTexture!" << std::endl;
        return -1;
    }

    wordCloud.generate(renderTexture);

    sf::Texture sourceTexture = renderTexture.getTexture();

    applyMask(sourceTexture, "tiger.png");

    const std::string filename = "output.jpg";
    if (ImageSaver::saveImage(sourceTexture, filename)) {
        std::cout << "Изображение успешно сохранено в файл: " << filename << std::endl;
        std::cout << "Размер: " << width << "x" << height << " пикселей" << std::endl;
    } else {
        std::cerr << "Ошибка сохранения файла!" << std::endl;
        return -1;
    }

    return 0;
}
