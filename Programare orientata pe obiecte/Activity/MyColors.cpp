#include "MyColors.h"

MyColors* MyColors::instance = 0;
MyColors* MyColors::getInstance(){
    if (instance == 0)
        instance = new MyColors();
    return instance;
}


