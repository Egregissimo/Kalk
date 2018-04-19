#ifndef BIN_H
#define BIN_H

#include "eccezione.h"
#include <iostream>
#include <string>
#include <vector>
#include <math.h>                               /* pow */

class bin{
    friend bin operator+ (const bin&, const bin&);
    friend bin operator- (const bin&, const bin&);
    friend bin operator* (const bin&, const bin&);
    friend bin operator/ (const bin&, const bin&);

    friend bool operator< (const bin&, const bin&);
    friend bool operator<= (const bin&, const bin&);
private:
    std::vector<bool> array;
public:
    //bin();
    bin(int = 1);                                 /* costruttore che dato in input un valore base 10 lo trasforma in base 2 */


    /* metodi ausiliari */
    void stampa() const;
    int base10() const;
};

bin operator+ (const bin&, const bin&);
bin operator- (const bin&, const bin&);
bin operator* (const bin&, const bin&);
bin operator/ (const bin&, const bin&);


bool operator< (const bin&, const bin&);
bool operator<= (const bin&, const bin&);
#endif // BIN_H
