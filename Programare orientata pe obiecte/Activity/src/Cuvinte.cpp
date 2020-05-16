#include "../headers/Cuvinte.h"

Cuvinte::Cuvinte()
{
    srand(time(NULL));
}

Cuvinte::~Cuvinte() {}

std::string Cuvinte::GetWord()
{
    if (words.size()!=0)
    {
        int index = rand() % words.size();
        std::string x = words[index];
        std::swap(words[index], words[words.size()-1]);
        words.pop_back();
        return x;
    }
    else
    {
        int wordType = 0;

        ///RTTI

        if ( dynamic_cast <Cuvinte3*> (this) != nullptr )
            wordType = 3;
        if ( dynamic_cast <Cuvinte4*> (this) != nullptr )
            wordType = 4;
        if ( dynamic_cast <Cuvinte5*> (this) != nullptr )
            wordType = 5;

        std::cout<<"nu mai exista cuvinte ";
        if (wordType)
            std::cout<<"de dificultate "<<wordType;
        return "";
    }
}

Cuvinte3::Cuvinte3(): Cuvinte()
{
    std:: string line;
    std:: ifstream myfile;
    myfile.open("resources/cuvinte3.txt");
    if ( myfile.is_open())
    {
        while (getline(myfile, line))
        {
            words.push_back(line);
        }
        myfile.close();
    }
}

Cuvinte3::~Cuvinte3() {}

Cuvinte4::Cuvinte4(): Cuvinte()
{
    std:: string line;
    std:: ifstream myfile;
    myfile.open("resources/cuvinte4.txt");
    if ( myfile.is_open())
    {
        while (getline(myfile, line))
        {
            words.push_back(line);
        }
        myfile.close();
    }
}

Cuvinte4::~Cuvinte4() {}

Cuvinte5::Cuvinte5(): Cuvinte()
{
    std:: string line;
    std:: ifstream myfile;
    myfile.open("resources/cuvinte5.txt");
    if ( myfile.is_open())
    {
        while (getline(myfile, line))
        {
            words.push_back(line);
        }
        myfile.close();
    }
}

Cuvinte5::~Cuvinte5() {}
