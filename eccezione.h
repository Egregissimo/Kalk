#ifndef EXCEPTION_H
#define EXCEPTION_H
#include <iostream>
#include <string>

using std::string;

class eccezione{
private:
    string classe;
    int id;
public:
    eccezione(string cl="NA", int num=0);
};

#endif // EXCEPTION_H
