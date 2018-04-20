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
    friend bool operator> (const bin&, const bin&);
    friend bool operator>= (const bin&, const bin&);
private:
    std::vector<bool> intera;
    std::vector<bool> frazionaria;
public:
    //bin();
    bin(int = 1);                                 /* costruttore che dato in input un valore base 10 lo trasforma in base 2 */
    bin(double = 1);                              /*
                                                     5.375 base 10 = 101.011 base 2
                                                     0.375 × 2 = 0.750          parte intera 0
                                                     0.750 × 2 = 1.5            perte intera 1
                                                     0.5 × 2 = 1.0              parte intera 1
                                                  */

    /* metodi ausiliari */
    void stampa() const;
    double base10() const;
};

bin operator+ (const bin&, const bin&);
bin operator- (const bin&, const bin&);
bin operator* (const bin&, const bin&);
bin operator/ (const bin&, const bin&);


bool operator< (const bin&, const bin&);
bool operator<= (const bin&, const bin&);
bool operator> (const bin&, const bin&);
bool operator>= (const bin&, const bin&);
#endif // BIN_H
