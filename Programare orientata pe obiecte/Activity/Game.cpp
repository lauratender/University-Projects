#include "Game.h"

Game::Game(state &state, sf::RenderWindow& mainwindow): gameState(&state), window(mainwindow)
{
    resourceContainer = ResourceContainer::getInstance();
    Pion::LoadTexture();
    currentTeamNumber = 0;
    dificultateCurenta = 0;
    strNume = "";
}
void Game::PassTime(float seconds)
{
    auto start = std::chrono::high_resolution_clock::now();
    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);

    while (duration.count() < seconds * 1000000)
    {
        stop = std::chrono::high_resolution_clock::now();
        duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
    }
}
void Game::Intro()
{
    resourceContainer->Pictures.getResource("pozaStart")->display_picture(window);
    PassTime(2);
}
void Game::ChooseNumberOfTeams()
{
    window.clear(*resourceContainer->Colors.getResource("myGreen"));
    window.draw(resourceContainer->Texts.getResource("mesajEchipe")->text);
    window.draw(resourceContainer->Texts.getResource("reintroducereNrEchipe")->text);
    window.display();
}
void Game::GetNumberOfTeams(int character_code)
{
    window.clear(*resourceContainer->Colors.getResource("myGreen"));
    window.draw(resourceContainer->Texts.getResource("mesajEchipe")->text);
    window.draw(resourceContainer->Texts.getResource("reintroducereNrEchipe")->text);
    switch(character_code)
    {
    case 8: ///backspace
    {
        resourceContainer->Texts.getResource("numarEchipe")->Clear_info();
        break;
    }
    case 13: ///enter
    {
        if (currentTeamNumber)
        {
            *gameState = TEAM_NAMES;
            window.clear(*resourceContainer->Colors.getResource("myGreen"));
            window.draw(resourceContainer->Texts.getResource("inputNume")->text);
            window.display();
            return;
        }
        break;
    }
    default:
    {
        resourceContainer->Texts.getResource("numarEchipe")->Change_info(static_cast<char>(character_code));
        window.draw(resourceContainer->Texts.getResource("numarEchipe")->text);
        currentTeamNumber = character_code - '0';
        if (currentTeamNumber >= 2 && currentTeamNumber <= 4)
        {
            window.draw(resourceContainer->Texts.getResource("apasaEnter")->text);
        }
        else
        {
            window.draw(resourceContainer->Texts.getResource("nrGresitEchipe")->text);
            currentTeamNumber = 0;
        }
    }
    }
    window.display();
}
void Game::GetTeamNames(int character_code)
{
    window.clear(*resourceContainer->Colors.getResource("myGreen"));
    window.draw(resourceContainer->Texts.getResource("inputNume")->text);
    if(character_code == 13)
    {
        if(Echipa::getNumberOfTeams() < currentTeamNumber && strNume != "")
        {
            try
            {
                auto ech = std::make_shared<Echipa>(Echipa::getNumberOfTeams() + 1, strNume, window);
                echipe.push_back(ech);
                resourceContainer->Texts.addResource ("numeEchipa" + std::to_string(Echipa::getNumberOfTeams()), new Text_de_afisat(strNume,
                        *resourceContainer->Fonts.getResource("fontTusj"), *resourceContainer->Colors.getResource("myOrange"), 60, 275, 150));
            }
            catch (std::exception& e)
            {
                std::cout << "Standard exception: " << e.what() <<"\n";
            }
            *resourceContainer->Texts.getResource("numeEchipa")+='\n';
            strNume = "";
        }
        if(Echipa::getNumberOfTeams() == currentTeamNumber)
        {
            *gameState = CONFIRM;
            window.clear(*resourceContainer->Colors.getResource("myGreen"));
            window.draw(resourceContainer->Texts.getResource("startText")->text);
            window.display();
            return;
        }
    }
    else
    {
        if(character_code == 8 && strNume != "")
        {
            strNume.pop_back();
            --*resourceContainer->Texts.getResource("numeEchipa");
        }
        else if (character_code <= 128 && character_code != 8)
        {
            strNume += static_cast<char>(character_code);
            *resourceContainer->Texts.getResource("numeEchipa")+=(static_cast<char>(character_code));
        }
        window.clear(*resourceContainer->Colors.getResource("myGreen"));
        window.draw(resourceContainer->Texts.getResource("inputNume")->text);
        window.draw(resourceContainer->Texts.getResource("numeEchipa")->text);
        window.display();
    }
}
void Game::DisplayTabla()
{
    resourceContainer->Pictures.getResource("tabla")->draw_picture(window);
    for (auto ech : echipe)
        std::cout<<*ech;
    window.display();
    PassTime(2);
}
void Game::ConfirmGameStart(int character_code)
{
    if(character_code == 13)
    {
        *gameState = ALES_DIFICULTATE;
        currentTeamNumber = 1;
        DisplayTabla();
    }
}
void Game::DrawTextDificultate()
{
    window.clear(*resourceContainer->Colors.getResource("myGreen"));
    window.draw(resourceContainer->Texts.getResource("randEchipa")->text);
    window.draw(resourceContainer->Texts.getResource("numeEchipa" + std::to_string(currentTeamNumber))->text);///numele echipei
    window.draw(resourceContainer->Texts.getResource("alegeDificultate")->text);
    window.draw(resourceContainer->Texts.getResource("limiteDificultate")->text);
}
void Game::AlegeDificultatea()
{
    DrawTextDificultate();
    window.display();
    *gameState = GET_DIFICULTATE;
}
void Game::GetDificultate(int character_code)
{
    DrawTextDificultate();
    switch(character_code)
    {
    case 8: ///backspace
    {
        resourceContainer->Texts.getResource("dificultateCurenta")->Clear_info();
        break;
    }
    case 13: ///enter
    {
        if (dificultateCurenta)
        {
            *gameState = CUVANT;
            return;
        }
        break;
    }
    default:
    {
        resourceContainer->Texts.getResource("dificultateCurenta")->Change_info(static_cast<char>(character_code));
        window.draw(resourceContainer->Texts.getResource("dificultateCurenta")->text);
        dificultateCurenta = character_code - '0';
        if (dificultateCurenta >= 3 && dificultateCurenta <= 5)
        {
            window.draw(resourceContainer->Texts.getResource("apasaEnter")->text);
        }
        else
        {
            dificultateCurenta = 0;
        }
    }
    }
    window.display();
}
void Game::GiveWord()
{
    window.clear(*resourceContainer->Colors.getResource("myGreen"));

    switch(Tabla::getTypeCasuta(currentTeamNumber))
    {
    case 0:
        {
            window.draw(resourceContainer->Texts.getResource("caseStart")->text);
            break;
        }
    case 1:
        {
            window.draw(resourceContainer->Texts.getResource("caseVorbit")->text);
            break;
        }
    case 2:
        {
            window.draw(resourceContainer->Texts.getResource("caseDesenat")->text);
            break;
        }
    case 3:
        {
            window.draw(resourceContainer->Texts.getResource("caseMima")->text);
            break;
        }
    }
    switch(dificultateCurenta)
    {
        case 3:
            {
                resourceContainer->Texts.getResource("cuvant")->Change_info(cuv3.GetWord());
                break;
            }
        case 4:
            {
                resourceContainer->Texts.getResource("cuvant")->Change_info(cuv4.GetWord());
                break;
            }
        case 5:
            {
                resourceContainer->Texts.getResource("cuvant")->Change_info(cuv5.GetWord());
                break;
            }
    }
    window.draw(resourceContainer->Texts.getResource("cuvant")->text);
    window.draw(resourceContainer->Texts.getResource("startProvocare")->text);
    window.display();
    *gameState = TIMER;
}
void Game::Timer()
{
    int i = 60;
    while (i > 0)
    {
        resourceContainer->Texts.getResource("secundeRamase")->Change_info(std::to_string(i));
        window.clear(*resourceContainer->Colors.getResource("myGreen"));
        window.draw(resourceContainer->Texts.getResource("timpRamas")->text);
        window.draw(resourceContainer->Texts.getResource("secundeRamase")->text);
        window.display();
        i--;
        PassTime(1);
    }
    window.clear(*resourceContainer->Colors.getResource("myGreen"));
    window.draw(resourceContainer->Texts.getResource("timpExpirat")->text);
    window.display();
    *gameState = CHECK;
}
 void Game::CheckAnswer(bool raspuns)
 {

     if (raspuns) /// succes
     {
        *echipe[currentTeamNumber-1]+= dificultateCurenta;
     }

    if (Tabla::getTypeCasuta(currentTeamNumber) == 4)
        {
            *gameState = END;
            return;
        }
    DisplayTabla();
    if (currentTeamNumber < Echipa::getNumberOfTeams())
        currentTeamNumber++;
    else
        currentTeamNumber = 1;
     *gameState = ALES_DIFICULTATE;

 }
 void Game::End()
 {
      window.clear(*resourceContainer->Colors.getResource("myGreen"));
      window.draw(resourceContainer->Texts.getResource("castigat")->text);
      window.draw(resourceContainer->Texts.getResource("numeEchipa" + std::to_string(currentTeamNumber))->text);///numele echipei
      window.draw(resourceContainer->Texts.getResource("felicitari")->text);
      window.display();
 }
Game:: ~Game()
{
    delete gameState;
    delete resourceContainer;
}
