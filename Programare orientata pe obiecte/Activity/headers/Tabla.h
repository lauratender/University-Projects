#include "Casute.h"
#ifndef TABLA_H_INCLUDED
#define TABLA_H_INCLUDED

class Tabla
{
    private:
        static Casute casute[54];
        static int pozitiiPioni[4];
        friend class Echipa;
        friend class Pion;
    public:
        static void ChangePosition(int, int);
        static sf::Vector2 <float> getPoz(int);
        static int getTypeCasuta(int);
};

#endif // TABLA_H_INCLUDED
