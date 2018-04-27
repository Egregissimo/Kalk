#ifndef EXCEPTION_H
#define EXCEPTION_H
#include <iostream>
#include <string>

using std::string;

class eccezione{
private:
    int id;
    string classe;
    string significato;
public:
    eccezione(int =0);
};

#endif // EXCEPTION_H
