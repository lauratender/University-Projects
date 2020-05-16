#include "Echipa.h"

int Echipa:: numberOfTeams = 0;

Echipa:: Echipa(int cnt, std::string nume, sf::RenderWindow& mainwindow): nr(cnt), name(nume), pion(cnt), window(mainwindow)
{
    numberOfTeams++;
}
std::ostream& operator<< (std::ostream &out, Echipa &ech)
{
    ech.pion.draw_pion(ech.window);
    return out;
}
Echipa& Echipa::operator += (int dificultate)
 {
    Tabla::ChangePosition(nr-1, dificultate);
    pion.changePosition(Tabla::casute[Tabla::pozitiiPioni[nr - 1]].poz);
    return *this;
 }

 int Echipa::getNumberOfTeams(){
     return numberOfTeams;
 }
