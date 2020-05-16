#include "Pion.h"

#include <SFML/Graphics.hpp>

#include <string>

#ifndef ECHIPA_H_INCLUDED
#define ECHIPA_H_INCLUDED

class Echipa{
    private:
        const int nr;
        const std:: string name;
        static int numberOfTeams;
        Pion pion;
        sf::RenderWindow& window;
    public:
        static int getNumberOfTeams();
        Echipa(int cnt, std::string nume, sf::RenderWindow& mainwindow);
        friend std::ostream& operator << (std::ostream &out, Echipa &ech);
        Echipa& operator+=(int);
};

#endif // ECHIPA_H_INCLUDED
