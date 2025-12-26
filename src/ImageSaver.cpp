#include "ImageSaver.h"
#include <SFML/Graphics.hpp>

bool ImageSaver::saveImage(const sf::Texture& texture, const std::string& filename) {
    return texture.copyToImage().saveToFile(filename);
}
