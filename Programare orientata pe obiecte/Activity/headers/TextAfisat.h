#include <SFML/Graphics.hpp>

#include <string>

#ifndef TEXTAFISAT_H_INCLUDED
#define TEXTAFISAT_H_INCLUDED

class Text_de_afisat
{
private:
    std::string info;
    sf::Font font;
    sf::Color color;
    int dim;
    float pozx, pozy;

public:
    sf::Text text;
    Text_de_afisat(std::string inf,sf::Font &ft, sf:: Color clr, int sz, float x, float y);
    void Change_info(char);
    void Change_info(std::string);
    void Clear_info();
    Text_de_afisat& operator+=(char);
    Text_de_afisat& operator--();
};
#endif // TEXTAFISAT_H_INCLUDED
