#ifndef RAZ_H
#define RAZ_H
#include <cmath>
#include "tipo.h"

using std::sqrt;
using std::floor;
using std::pow;
using std::cbrt;

class raz: public tipo{
    friend raz operator+(const raz&, const raz&);
    friend raz operator-(const raz&, const raz&);
    friend raz operator*(const raz&, const raz&);
    friend raz operator/(const raz&, const raz&);
    friend bool operator==(const raz&, const raz&);
    friend bool operator!=(const raz&, const raz&);
    friend bool operator<=(const raz&, const raz&);
    friend bool operator<(const raz&, const raz&);
    friend ostream& operator<<(ostream&, const raz&);
    friend string to_string(const raz&);
private:
    int num, den;
    int degree(double);//ritorna il numero di cifre dopo la virgola in un double
public:
    raz(int n=0, int d=1);
    raz(double n, double d=1);
    int getNum()const;
    int getDen()const;
    static raz inverso(const raz&);//ritorna il reciproco del numero razionale dato per parametro
    explicit operator double();//da raz a double, dev'essere invocato "static_cast<double>(raz r)"
    explicit operator int();
    raz& operator++();//prefisso
    raz operator++(int);//postfisso
    static raz pow(const raz&, int);//elevamento a potenza
    static raz sqrt(const raz&);//radice quadrata
    static raz cbrt(const raz&);//radice cubica
    raz riduzione() const;//restituisce un razionale ridotto ai minimi termini

    //implementazione metodi virtuali
    raz* somma(tipo*);
    raz* differenza(tipo*);
    raz* moltiplicazione(int);
    raz* divisione(int);
    bool uguale(tipo*)const;
    bool min(tipo*)const;
    string to_stringa()const;
};

raz operator+(const raz&, const raz&);
raz operator-(const raz&, const raz&);
raz operator*(const raz&, const raz&);
raz operator/(const raz&, const raz&);
bool operator==(const raz&, const raz&);
bool operator!=(const raz&, const raz&);
bool operator<=(const raz&, const raz&);
bool operator<(const raz&, const raz&);
ostream& operator<<(ostream&, const raz&);
string to_string(const raz&);

#endif // RAZ_H
