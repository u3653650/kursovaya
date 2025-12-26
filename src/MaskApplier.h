#ifndef CMAKESFMLPROJECT_MASKAPPLIER_H
#define CMAKESFMLPROJECT_MASKAPPLIER_H
#include <string>

#include "SFML/Graphics.hpp"


bool applyMask(sf::Texture& targetTexture, const std::string& maskFileName);


#endif //CMAKESFMLPROJECT_MASKAPPLIER_H