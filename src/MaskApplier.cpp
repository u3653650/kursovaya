#include "MaskApplier.h"

#include <iostream>

bool applyMask(sf::Texture& targetTexture, const std::string& maskFileName) {
    std::string maskPath = "masks/" + maskFileName;
    sf::Image targetImage = targetTexture.copyToImage();
    sf::Texture maskTex;
    if (!maskTex.loadFromFile(maskPath)) {
        std::cerr << "Cannot load mask: " << maskPath << std::endl;
        return false;
    }
    sf::Image maskImage = maskTex.copyToImage();
    for (unsigned int x = 0; x < targetImage.getSize().x; ++x) {
        for (unsigned int y = 0; y < targetImage.getSize().y; ++y) {
            sf::Color targetColor = targetImage.getPixel(x, y);
            sf::Color maskColor = maskImage.getPixel(x, y);
            if (maskColor.r == 255) {
                targetColor.r = 240;
                targetColor.g = 240;
                targetColor.b = 240;
            }
            targetImage.setPixel(x, y, targetColor);
        }
    }
    if (!targetTexture.loadFromImage(targetImage)) {
        std::cerr << "Failed to update texture from image!" << std::endl;
        return false;
    }
    return true;
}
