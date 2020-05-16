#include "Resources.h"

#include <SFML/Graphics.hpp>

#ifndef RESOURCECONTAINER_H_INCLUDED
#define RESOURCECONTAINER_H_INCLUDED

class ResourceContainer  ///singleton
{
private:
    static ResourceContainer *instance;
    ResourceContainer();

    Resources <MyPictures> Pictures;
    Resources <Text_de_afisat> Texts;
    Resources <sf::Color> Colors;
    Resources <sf::Font> Fonts;
    void LoadFont();

    void AddColors();
    void AddTexts();
    void AddPictures();

    static ResourceContainer* getInstance();
    friend class Game;
};



#endif // RESOURCECONTAINER_H_INCLUDED
