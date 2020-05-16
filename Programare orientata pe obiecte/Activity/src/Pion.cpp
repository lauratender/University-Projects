#include "../headers/Pion.h"

sf::Texture Pion::pawnTxt;
sf::Color Pion::culoriPioni[4]{sf::Color::Red, sf::Color::Yellow, sf::Color::Green, sf::Color::Blue};
sf::Vector2 <float> Pion::offSet[4]{{-23, -25}, {-23, 10}, {23, -25}, {23, 10}};

Pion::Pion(int cnt): nr(cnt)
{
    Tabla::pozitiiPioni[nr-1] = nr - 1;
    pawnSprite.setTexture(pawnTxt);
    pawnSprite.setPosition(Tabla::getPoz(nr-1));
    pawnSprite.setColor(culoriPioni[nr - 1]);
}
void Pion::changePosition (sf::Vector2 <float> &newpoz)
{
    pawnSprite.setPosition(newpoz + offSet[nr-1]);
}
void Pion::draw_pion(sf::RenderWindow& window)
{
    window.draw(pawnSprite);
}
void Pion::LoadTexture()
{
   try
   {
        if(!pawnTxt.loadFromFile("resources/pawn.png"))
            throw (4);
   }
   catch(int code)
   {
       if (code == 4)
        std::cout<<"could not load from file pawn.png\n";
   }
}

