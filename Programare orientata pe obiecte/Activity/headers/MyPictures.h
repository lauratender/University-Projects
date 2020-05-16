#include <SFML/Graphics.hpp>
#include <iostream>

#ifndef MYPICTURES_H_INCLUDED
#define MYPICTURES_H_INCLUDED

class MyPictures{
private:
    sf::Sprite sprite;
    sf::Texture pozaFundal;
public:
    MyPictures(std::string numeFisier);
    void draw_picture(sf::RenderWindow& window);
    void display_picture(sf::RenderWindow& window);
};



#endif // MYPICTURES_H_INCLUDED
