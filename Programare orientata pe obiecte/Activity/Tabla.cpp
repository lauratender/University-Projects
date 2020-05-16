#include "Tabla.h"

//sf::Vector2 <float> startAlbastru(590, 35), startRosu(615, 60), startVerde(565, 60), startGalben(590, 85);

Casute Tabla::casute[54] = {{{615, 60}, 0}, {{590, 85}, 0}, {{565, 60}, 0}, {{590, 35}, 0}, {{395, 60}, 1}, {{285, 60}, 2}, {{180, 60}, 3}, {{75, 60}, 1},
{{75, 130}, 1}, {{180, 130}, 3}, {{285, 130}, 1}, {{395, 130}, 2}, {{395, 200}, 3}, {{285, 200}, 1}, {{180, 200}, 2}, {{75, 200}, 1}, {{75, 270}, 2},
{{180, 270}, 3}, {{285, 270}, 3}, {{395, 270}, 2}, {{395, 340}, 1}, {{285, 340}, 3}, {{180, 340}, 3}, {{75, 340}, 3}, {{75, 410}, 2}, {{180, 410}, 2}, {{285, 410}, 2},
{{395, 410}, 3}, {{395, 480}, 2}, {{285, 480}, 1}, {{180, 480}, 3}, {{75, 480}, 1}, {{75, 550}, 3}, {{180, 550}, 1}, {{285, 550}, 2}, {{395, 550}, 2},
{{395, 620}, 2}, {{285, 620}, 3}, {{180, 620}, 3}, {{75, 620}, 1}, {{75, 690}, 3}, {{180, 690}, 2}, {{285, 690}, 2}, {{395, 690}, 3}, {{395, 760}, 2},
{{285, 760}, 1}, {{180, 760}, 1}, {{75, 760}, 3}, {{75, 830}, 1}, {{180, 830}, 2}, {{285, 830}, 3}, {{395, 830}, 3}, {{505, 830}, 1}, {{580, 830}, 4}};

int Tabla::pozitiiPioni[4] = {-1, -1, -1, -1};

void Tabla::ChangePosition(int pionCurent, int dificultate)
{
    if (casute[pozitiiPioni[pionCurent]].type == 0)
        pozitiiPioni[pionCurent] = dificultate + 1;
    else
    {
        ///lambda expression
        auto poz = [](auto x)
        {
            if ( x >= 53 )
                return 53;
            return x;
        };
        pozitiiPioni[pionCurent] = poz(pozitiiPioni[pionCurent] + dificultate);
    }
}

 sf::Vector2 <float> Tabla::getPoz(int index){
     if (index >=0 && index <= 53)
        return casute[index].poz;
    return casute[0].poz;
 }

 int Tabla::getTypeCasuta(int nr){
     return casute[pozitiiPioni[nr - 1]].type;
 }
