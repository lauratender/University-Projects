#include "Tabla.h"

#include <SFML/Graphics.hpp>

#include <iostream>

#ifndef PION_H_INCLUDED
#define PION_H_INCLUDED

class Pion{
private:
    int nr;
    static sf::Texture pawnTxt;
    sf::Sprite pawnSprite;
    static sf::Color culoriPioni[4];
    static sf::Vector2 <float> offSet[4];
public:
    Pion(int cnt);
    static void LoadTexture();
    void changePosition (sf::Vector2 <float> &newpoz);
    void draw_pion(sf::RenderWindow& window);
};

#endif // PION_H_INCLUDED
