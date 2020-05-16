#include "../headers/ResourceContainer.h"
#include "../headers/MyException.h"

ResourceContainer* ResourceContainer::instance = 0;
ResourceContainer::ResourceContainer(){
    LoadFont();
    AddColors();
    AddTexts();
    AddPictures();
}
ResourceContainer* ResourceContainer::getInstance(){
    if (instance == 0)
        instance = new ResourceContainer();
    return instance;
}
void ResourceContainer::LoadFont(){
    Fonts.addResource("fontTusj", new sf::Font ());
    try
    {
        if(!Fonts.getResource("fontTusj")->loadFromFile("resources/FFF_Tusj.ttf"))
            throw MyException();
    }
    catch ( std::exception &e)
    {
        std::cout<< e.what() << '\n';
    }

}
void ResourceContainer::AddColors(){
    Colors.addResource("myGreen", new sf::Color(0, 130, 51));
    Colors.addResource("myYellow", new sf::Color(255, 200, 0));
    Colors.addResource("myOrange", new sf::Color(255, 132, 39));
    Colors.addResource("myMandarin", new sf::Color(255, 107, 53));
    Colors.addResource("myWhite", new sf::Color({248, 255, 229}));
}
void ResourceContainer::AddTexts(){
    try{
    Texts.addResource ("mesajEchipe", new Text_de_afisat("Alege numarul de\nechipe! Introdu un\nnumar de la 2 la 4.",
                                    *Fonts.getResource("fontTusj"), *Colors.getResource("myYellow"), 60, 50, 50));
    Texts.addResource ("nrGresitEchipe", new Text_de_afisat("Numarul de echipe poate\nfi doar de la 2 la 4.",
                                        *Fonts.getResource("fontTusj"), *Colors.getResource("myYellow"), 48, 50, 500));
    Texts.addResource ("numarEchipe", new Text_de_afisat("", *Fonts.getResource("fontTusj"),
                                        *Colors.getResource("myOrange"), 78, 315, 300));
    Texts.addResource ("reintroducereNrEchipe", new Text_de_afisat("Daca ai introdus\ngresit numarul de echipe\ndoar apasa numarul dorit!",
                        *Fonts.getResource("fontTusj"), *Colors.getResource("myOrange"), 48, 50, 700));
    Texts.addResource ("apasaEnter", new Text_de_afisat("Apasa Enter pentru a\ncontinua.",
                        *Fonts.getResource("fontTusj"), *Colors.getResource("myOrange"), 48, 50, 500));
    Texts.addResource ("startText", new Text_de_afisat("Daca sunteti\npregatiti sa inceapa\njocul apasati Enter!",
                        *Fonts.getResource("fontTusj"), *Colors.getResource("myYellow"), 60, 75, 200));
    Texts.addResource ("inputNume", new Text_de_afisat("Introdu numele\nechipelor!",
                        *Fonts.getResource("fontTusj"), *Colors.getResource("myYellow"), 60, 100, 50));
    Texts.addResource ("numeEchipa", new Text_de_afisat("",
                        *Fonts.getResource("fontTusj"),*Colors.getResource("myOrange"), 55, 275, 300));
    Texts.addResource ("randEchipa", new Text_de_afisat("Randul echipei:",
                        *Fonts.getResource("fontTusj"), *Colors.getResource("myYellow"), 60, 100, 50));
    Texts.addResource ("alegeDificultate", new Text_de_afisat("Alege dificultatea!",
                        *Fonts.getResource("fontTusj"), *Colors.getResource("myYellow"), 60, 100, 250));
    Texts.addResource ("limiteDificultate", new Text_de_afisat("Dificultatea poate avea\nvalorea 3, 4 sau 5.",
                        *Fonts.getResource("fontTusj"), *Colors.getResource("myYellow"), 48, 100, 700));
    Texts.addResource ("dificultateCurenta", new Text_de_afisat("", *Fonts.getResource("fontTusj"),
                                        *Colors.getResource("myMandarin"), 78, 315, 350));
    Texts.addResource ("caseStart", new Text_de_afisat("Cuvantul este:",
                        *Fonts.getResource("fontTusj"), *Colors.getResource("myYellow"), 60, 150, 100));
    Texts.addResource ("caseVorbit", new Text_de_afisat("Vorbiti despre\ncuvantul:",
                        *Fonts.getResource("fontTusj"), *Colors.getResource("myYellow"), 60, 100, 100));
    Texts.addResource ("caseDesenat", new Text_de_afisat("Desenati cuvantul:",
                        *Fonts.getResource("fontTusj"), *Colors.getResource("myYellow"), 60, 100, 100));
    Texts.addResource ("caseMima", new Text_de_afisat("Mimati cuvantul:",
                        *Fonts.getResource("fontTusj"), *Colors.getResource("myYellow"), 60, 100, 100));
    Texts.addResource ("cuvant", new Text_de_afisat("",
                        *Fonts.getResource("fontTusj"), *Colors.getResource("myOrange"), 60, 50, 250));
    Texts.addResource ("startProvocare", new Text_de_afisat("Apasa Enter pentru\na incepe tura!",
                        *Fonts.getResource("fontTusj"), *Colors.getResource("myOrange"), 55, 50, 600));
    Texts.addResource ("timpRamas", new Text_de_afisat("Secunde ramase:",
                        *Fonts.getResource("fontTusj"), *Colors.getResource("myYellow"), 60, 100, 50));
    Texts.addResource ("secundeRamase", new Text_de_afisat("", *Fonts.getResource("fontTusj"),
                                        *Colors.getResource("myOrange"), 78, 315, 300));
    Texts.addResource ("timpExpirat", new Text_de_afisat("Timpul a expirat!\n\nAti reusit sa ghiciti?\n\nDaca da, apasati Y,\naltfel apasati N",
                        *Fonts.getResource("fontTusj"), *Colors.getResource("myYellow"), 60, 75, 200));
    Texts.addResource ("castigat", new Text_de_afisat("Jocul este castigat\nde echipa:", *Fonts.getResource("fontTusj"),
                                        *Colors.getResource("myYellow"), 60, 50, 15));
    Texts.addResource ("felicitari", new Text_de_afisat("Felicitari!", *Fonts.getResource("fontTusj"),
                                        *Colors.getResource("myYellow"), 60, 200, 500));
    }
    catch (std::exception& e)
    {
        std::cout << "Standard exception: " << e.what() <<"\n";
    }
}
void ResourceContainer::AddPictures(){
    try
    {
        Pictures.addResource("pozaStart", new MyPictures("resources/Start.png"));
        Pictures.addResource("tabla", new MyPictures("resources/tabla.jpg"));
    }
    catch (std::exception& e)
    {
        std::cout << "Standard exception: " << e.what() <<"\n";
    }
}
