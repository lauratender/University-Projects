#include "ResourceContainer.h"
#include "Echipa.h"
#include "Cuvinte.h"
#include "Tabla.h"

#include <chrono>
#include <memory>
#ifndef GAME_H_INCLUDED
#define GAME_H_INCLUDED
enum state
{
    TEAM_NUMBER,
    TEAM_NAMES,
    CONFIRM,
    ALES_DIFICULTATE,
    GET_DIFICULTATE,
    CUVANT,
    TIMER,
    CHECK,
    END
};
///facade
class Game{
private:
    int currentTeamNumber;
    int dificultateCurenta;
    state *gameState;
    std::string strNume;

    Cuvinte3 cuv3;
    Cuvinte4 cuv4;
    Cuvinte5 cuv5;
    ///Heap Memory Allocation
    ///smart pointers
    std::vector<std::shared_ptr<Echipa>> echipe;
    ResourceContainer *resourceContainer;
    sf::RenderWindow& window;

    void PassTime(float);
    void DrawTextDificultate();
    void DisplayTabla();

public:
    Game(state&, sf::RenderWindow&);
    void Intro();
    void ChooseNumberOfTeams();
    void GetNumberOfTeams(int);
    void GetTeamNames(int);
    void ConfirmGameStart(int);
    void AlegeDificultatea();
    void GetDificultate(int);
    void GiveWord();
    void Timer();
    void CheckAnswer(bool);
    void End();
    ~Game();
};

#endif // GAME_H_INCLUDED
