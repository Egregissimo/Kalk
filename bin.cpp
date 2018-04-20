#include "bin.h"

bin::bin(double d){
    int intero = (int) d;
    double frazionario = d - intero;
    int quoziente = intero;
    bool resto = 0;

    while(quoziente != 0){
        resto = quoziente%2;
        intera.push_back(resto);
        quoziente = quoziente/2;
    }
    std::vector<bool> tmp;
    quoziente = intera.size();
    for(unsigned int it = 0; it<quoziente; it++){
        resto = intera.back();
        intera.pop_back();
        tmp.push_back(resto);
    }

    /* VEDERE SE IL VECTOR tmp CREA GARDBAGE */
    intera = tmp;
    while(frazionario != 0){
        frazionario = frazionario*2;

        if(frazionario >= 1){
            frazionaria.push_back(1);
            frazionario = frazionario-1;
        }
        else
            frazionaria.push_back(0);
    }
}
bin::bin(int d){
    int quoziente = d;
    bool resto = 0;

    while(quoziente != 0){
        resto = quoziente%2;
        intera.push_back(resto);
        quoziente = quoziente/2;
    }
    std::vector<bool> tmp;
    quoziente = intera.size();
    for(unsigned int it = 0; it<quoziente; it++){
        resto = intera.back();
        intera.pop_back();
        tmp.push_back(resto);
    }

    /* VEDERE SE IL VECTOR tmp CREA GARDBAGE */
    intera = tmp;
    frazionaria.push_back(0);
}


void bin::stampa() const{
    for(unsigned int i=0; i<intera.size(); i++)
        std::cout<<intera[i];
    std::cout<<".";
    for(unsigned int i=0; i<frazionaria.size(); i++)
        std::cout<<frazionaria[i];
}
double bin::base10() const{
    int i_out = 0;
    double f_out = 0;
    int i = 0;
    for(std::vector<bool>::const_reverse_iterator it = intera.rbegin(); it != intera.rend(); ++it){
        i_out = i_out + (*it * (pow(2,i)));
        i++;
    }

    for(int i=0; i<frazionaria.size(); i++)
        f_out = f_out + (frazionaria[i] * (pow(2,-(i+1))));

    f_out = i_out + f_out;
    return f_out;
}

bin operator+ (const bin& bin1, const bin& bin2){
    double a = bin1.base10();
    double b = bin2.base10();
    bin out(a+b);
    return out;
}
bin operator -(const bin& bin1, const bin& bin2){
    double a = bin1.base10();
    double b = bin2.base10();
    bin out(a-b);
    return out;
}
bin operator *(const bin& bin1, const bin& bin2){
    double a = bin1.base10();
    double b = bin2.base10();
    bin out(a*b);
    return out;
}
bin operator /(const bin& bin1, const bin& bin2){
    double a = bin1.base10();
    double b = bin2.base10();
    bin out(a/b);
    return out;
}
bool operator< (const bin& bin1, const bin& bin2){
    double a = bin1.base10();
    double b = bin2.base10();

    return a<b;
}
bool operator<= (const bin& bin1, const bin& bin2){
    double a = bin1.base10();
    double b = bin2.base10();

    return a<=b;
}
bool operator> (const bin& bin1, const bin& bin2){
    double a = bin1.base10();
    double b = bin2.base10();

    return a>b;
}
bool operator>= (const bin& bin1, const bin& bin2){
    double a = bin1.base10();
    double b = bin2.base10();

    return a>=b;
}
