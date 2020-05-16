#include <SFML/Graphics.hpp>

#include <time.h>
#include <iostream>
#include <fstream>

#ifndef CUVINTE_H_INCLUDED
#define CUVINTE_H_INCLUDED

///abstract class

class Cuvinte
{
protected:
    ///STL
    std::vector < std::string > words;
public:
    Cuvinte();
    virtual ~Cuvinte()=0;
    std::string GetWord();
};

class Cuvinte3: public Cuvinte
{
public:
    Cuvinte3();
    ~Cuvinte3();
};

class Cuvinte4: public Cuvinte
{
public:
    Cuvinte4();
    ~Cuvinte4();
};

class Cuvinte5: public Cuvinte
{
public:
    Cuvinte5();
    ~Cuvinte5();
};
#endif // CUVINTE_H_INCLUDED
