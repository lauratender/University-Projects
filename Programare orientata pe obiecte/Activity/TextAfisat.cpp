#include "TextAfisat.h"

Text_de_afisat::Text_de_afisat(std::string inf,sf::Font &ft, sf:: Color clr = sf::Color:: Black, int sz = 48, float x =0, float y=0): info(inf),
                                                                                                                                      font(ft),
                                                                                                                                      color(clr),
                                                                                                                                      dim(sz),
                                                                                                                                      pozx(x),
                                                                                                                                      pozy(y)
{
    text.setString(info);
    text.setCharacterSize(dim);
    text.setFillColor(color);
    text.setPosition(pozx, pozy);
    text.setFont(font);
}

void Text_de_afisat::Change_info(char c)
{
    info = c;
    text.setString(info);
}
void Text_de_afisat::Change_info(std::string str)
{
    info = str;
    text.setString(info);
}
void Text_de_afisat::Clear_info()
{
    info = "";
    text.setString(info);
}
 Text_de_afisat& Text_de_afisat::operator+=(char c)
 {
    info += c;
    text.setString(info);
    return *this;
 }
 Text_de_afisat& Text_de_afisat::operator--()
 {
     info.pop_back();
     text.setString(info);
     return *this;
 }
