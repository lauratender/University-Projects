#include "TextAfisat.h"
#include "MyPictures.h"

#include <SFML/Graphics.hpp>

#include <iostream>
#include <map>
#include <string>

#ifndef RESOURCES_H_INCLUDED
#define RESOURCES_H_INCLUDED
///template
template <typename T> class Resources
{
    private:
    ///STL
     std::map<std::string, T*> mResources;
    public:
        Resources(){};
        void addResource(const std::string name, T* resource)
        {
            mResources.insert(std::pair<std::string, T*>(name, resource));
        }
        T* getResource(std::string name)
        {
            try
            {
                ///init-statement if (c++17)
                if (auto rezultat = mResources.find(name); rezultat != mResources.end())
                        return rezultat->second;
                throw(2);
            }
            catch(int code)
            {
                if (code == 2)
                    std::cout<<"Resource " + name + " not found";
            }
            return nullptr;
        }
        ~Resources()
        {
            for( auto itr = mResources.begin(); itr != mResources.end(); itr++)
            {
               delete itr->second;
               mResources.erase(itr);
            }
        }
};
#endif // RESOURCES_H_INCLUDED
