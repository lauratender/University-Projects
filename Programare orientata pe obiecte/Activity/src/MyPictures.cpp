#include "../headers/MyPictures.h"

MyPictures::MyPictures(std::string numeFisier)
{
    try
    {
        if(!pozaFundal.loadFromFile(numeFisier))
            throw(3);
    }
    catch(int code)
    {
        if (code == 3)
            std::cout<<"could not load picture "<<numeFisier;
    }
    sprite.setTexture(pozaFundal);
}
void MyPictures::draw_picture(sf::RenderWindow& window)
{
    window.clear();
    window.draw(sprite);
}
void MyPictures::display_picture(sf::RenderWindow& window)
{
    draw_picture(window);
    window.display();
}
