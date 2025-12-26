#ifndef IMAGESAVER_H
#define IMAGESAVER_H

#include <SFML/Graphics.hpp>
#include <string>

class ImageSaver {
public:
    static bool saveImage(const sf::Texture &texture, const std::string &filename);
};

#endif // IMAGESAVER_H
