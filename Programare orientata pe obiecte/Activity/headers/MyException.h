#include <iostream>
#include <exception>
#ifndef MYEXCEPTION_H_INCLUDED
#define MYEXCEPTION_H_INCLUDED

class MyException: public std::exception
{
  virtual const char* what() const throw()
  {
    return "could not load font";
  }
};

#endif // MYEXCEPTION_H_INCLUDED
