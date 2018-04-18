#ifndef BIN_H
#define BIN_H

#include "eccezione.h"
#include <iostream>
#include <string>
#include <vector>

class bin{
    friend bin operator+ (const bin&, const bin&);
    friend bin operator- (const bin&, const bin&);
    friend bin operator* (const bin&, const bin&);
    friend bin operator/ (const bin&, const bin&);

private:
    std::vector<bool> array;
public:
    bin(unsigned int=1);

    /* metodi ausiliari */
    unsigned int getDim() const;
    void stampa() const;
    void insert(unsigned int, bool);
    bool max(const bin& vet2) const;

    //bool& operator[](unsigned int) const;
};

bin operator+ (const bin&, const bin&);
bin operator- (const bin&, const bin&);
bin operator* (const bin&, const bin&);
bin operator/ (const bin&, const bin&);

#endif // BIN_H
