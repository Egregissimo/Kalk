#ifndef BIN_H
#define BIN_H

#include "eccezione.h"
#include <iostream>
#include <string>

class bin{
    friend bin operator+ (const bin&, const bin&);
    friend bin operator- (const bin&, const bin&);
    friend bin operator* (const bin&, const bin&);
    friend bin operator/ (const bin&, const bin&);

private:
    unsigned int dim;
    bool* array;
public:
    bin(unsigned int=1);

    /* metodi ausiliari */
    unsigned int getDim() const;
    bool max(const bin&) const;
    void stampa() const;
    void insert(unsigned int, bool);

    bool operator[](unsigned int) const;
};

bin operator+ (const bin&, const bin&);
bin operator- (const bin&, const bin&);
bin operator* (const bin&, const bin&);
bin operator/ (const bin&, const bin&);

#endif // BIN_H
