#include <SFML/Graphics.hpp>

#ifndef CASUTE_H_INCLUDED
#define CASUTE_H_INCLUDED


/*enum typeCasuta{
    start,
    vorbit,
    desenat,
    mima,
    finish
};*/

class Casute{
        sf::Vector2 <float> poz;
        const int type;
        friend class Tabla;
        friend class Echipa;
    public:
        Casute(sf::Vector2 <float>, int);
};

#endif // CASUTE_H_INCLUDED
