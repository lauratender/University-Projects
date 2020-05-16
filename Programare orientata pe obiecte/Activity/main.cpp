#include "headers/Game.h"
///interfata grafica SFML
#include <SFML/Graphics.hpp>

int main()
{

    sf::RenderWindow window(sf::VideoMode(712, 949), "Activity game");
    sf::Event event;
    state gameState = TEAM_NUMBER;

    Game game(gameState, window);

    game.Intro();
    game.ChooseNumberOfTeams();

    while (window.isOpen())
    {

        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            else
            {
                switch(gameState)
                {
                    case TEAM_NUMBER:
                        {
                            if(event.type == sf::Event::TextEntered)
                                game.GetNumberOfTeams(event.text.unicode);
                            break;
                        }
                    case TEAM_NAMES:
                        {
                            if(event.type == sf::Event::TextEntered)
                                game.GetTeamNames(event.text.unicode);
                            break;
                        }
                    case CONFIRM:
                        {
                            game.ConfirmGameStart(event.text.unicode);
                            break;
                        }
                    case ALES_DIFICULTATE:
                    {
                        game.AlegeDificultatea();
                        break;
                    }
                    case GET_DIFICULTATE:
                        {
                            if(event.type == sf::Event::TextEntered)
                                game.GetDificultate(event.text.unicode);
                            break;
                        }
                    case CUVANT:
                        {
                            game.GiveWord();
                            break;
                        }
                    case TIMER:
                        {
                            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Enter)
                                {
                                    game.Timer();
                                    while (window.pollEvent(event)){}
                                }
                            break;
                        }
                    case CHECK:
                        {
                            if (event.type == sf::Event::KeyPressed)
                            {
                                if (event.key.code == sf::Keyboard::N)///esec
                                    game.CheckAnswer(0);
                                if (event.key.code == sf::Keyboard::Y)///succes
                                    game.CheckAnswer (1);
                            }
                            break;
                        }
                    case END:
                        {
                            game.End();
                            break;
                        }

                }
            }
        }
    }
}
