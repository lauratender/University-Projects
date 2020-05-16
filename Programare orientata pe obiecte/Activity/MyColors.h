#include <SFML/Graphics.hpp>

#ifndef MYCOLORS_H_INCLUDED
#define MYCOLORS_H_INCLUDED

class MyColors  ///singleton
{
private:
    static MyColors *instance;
    MyColors(){}
public:
    //sf::Color myWhite{248, 255, 229};
    sf::Color myGreen{0, 130, 51};
    sf::Color myYellow{255, 200, 0};
    sf::Color myOrange{255, 132, 39};
    sf::Color myMandarin{255, 107, 53};
    static MyColors* getInstance();
};

#endif // MYCOLORS_H_INCLUDED
