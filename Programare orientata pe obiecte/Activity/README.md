# Activity Game
## Proiect Programare orientata pe obiecte, Anul I, semestrul al II-lea

Jocul reprezinta o varianta digitala a jocului clasic Activity. Jocul se joaca in 2-4 echipe de minim 2 persoane. Echipele isi vor alege cate un nume. La fiecare tura echipele isi vor alege dificultatea cuvantului si vor primi cate un cuvant aleator. Daca membrii echipei au descoperit cuvantul, pionul echipei va avansa un numar de pozitii egal cu dificultatea. Prima echipa care ajunge la finish castiga jocul!

![Game Picture](https://github.com/lauratender/UniversityProjects/blob/master/Programare%20orientata%20pe%20obiecte/Activity/GamePic.PNG?raw=true)

## Cerinte

* Interfața grafica 
   
   Pentru acest proiect am folosit SFML.
   
```cpp
   #include <SFML/Graphics.hpp>
```

* RTTI 

in "Cuvinte.cpp"
```cpp
   if ( dynamic_cast <Cuvinte3*> (this) != nullptr )
            wordType = 3;
   if ( dynamic_cast <Cuvinte4*> (this) != nullptr )
            wordType = 4;
   if ( dynamic_cast <Cuvinte5*> (this) != nullptr )
            wordType = 5;
```

* Abstract Classes 

in "Cuvinte.h"
```cpp
class Cuvinte
{
protected:
    std::vector < std::string > words;
public:
    Cuvinte();
    virtual ~Cuvinte()=0;
    std::string GetWord();
};
```

* Operatori (minim 4 * numărul membrilor echipei)

in "TextAfisat.cpp"
```cpp
Text_de_afisat& Text_de_afisat::operator+=(char c)
 {
    info += c;
    text.setString(info);
    return *this;
 }
 Text_de_afisat& Text_de_afisat::operator--()
 {
     info.pop_back();
     text.setString(info);
     return *this;
 }
 ```
 in "Echipa.cpp"
 ```cpp
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
  ```

* Heap Memory Allocation

in "Game.h"
```cpp
std::vector<std::shared_ptr<Echipa>> echipe;
  ```
 in "Game.cpp"
 ```cpp
echipe.push_back(ech);
  ```
 * Exceptions
 
 in "MyException.h"
 ```cpp
 class MyException: public std::exception
{
  virtual const char* what() const throw()
  {
    return "could not load font";
  }
};
```
in "ResourceContainer.cpp"
 ```cpp
try
    {
        if(!Fonts.getResource("fontTusj")->loadFromFile("FFF_Tusj.ttf"))
            throw MyException();
    }
catch ( std::exception &e)
    {
        std::cout<< e.what() << '\n';
    }
```

* STL

in "Resources.h"
 ```cpp
  std::map<std::string, T*> mResources;
  // ...
  mResources.insert(std::pair<std::string, T*>(name, resource));
  // ...
   for( auto itr = mResources.begin(); itr != mResources.end(); itr++)
 ```
 
 * Lambda expressions
 
 in "Tabla.cpp"
 ```cpp
 auto poz = [](auto x)
        {
            if ( x >= 53 )
                return 53;
            return x;
        };
 pozitiiPioni[pionCurent] = poz(pozitiiPioni[pionCurent] + dificultate);
  ```
  
  * Templates
  
  in  "Resources.h"
  ```cpp
  template <typename T> class Resources
   ```
   
   * Smart pointers 
  in "Game.h"
  ```cpp
  std::vector<std::shared_ptr<Echipa>> echipe;
  ```
  in "Game.cpp"
  ```cpp
  auto ech = std::make_shared<Echipa>(Echipa::getNumberOfTeams() + 1, strNume, window);
  ```
  
  * Design patterns 
  
  Singleton in "ResourceContainer.h", "ResourceContainer.cpp"
  ```cpp
  private:
    static ResourceContainer *instance;
    ResourceContainer();
// ...
    static ResourceContainer* getInstance();
  ```
  ```cpp
  ResourceContainer* ResourceContainer::getInstance(){
    if (instance == 0)
        instance = new ResourceContainer();
    return instance;
  }
  ```
  
  Facade
  class Game in "Game.h"
  
  * Features of C++17/20
  
  init statement for if
  
  in "Resources.h"
  ```cpp
  if (auto rezultat = mResources.find(name); rezultat != mResources.end())
        return rezultat->second;
   ```
