#include "bin.h"

bin::bin(int d){
    int quoziente = d;
    bool resto = 0;

    while(quoziente != 0){
        resto = quoziente%2;
        array.push_back(resto);
        quoziente = quoziente/2;
    }
    std::vector<bool> tmp;
    quoziente = array.size();
    for(unsigned int it = 0; it<quoziente; it++){
        resto = array.back();
        array.pop_back();
        tmp.push_back(resto);
    }

    /* VEDERE SE IL VECTOR tmp CREA GARDBAGE */
    array = tmp;
}


void bin::stampa() const{
    for(unsigned int i=0; i<array.size(); i++)
        std::cout<<array[i];
    //std::cout<<std::endl;
}
int bin::base10() const{
    int out = 0;
    int i = 0;
    for(std::vector<bool>::const_reverse_iterator it = array.rbegin(); it != array.rend(); ++it){
        out = out + (*it * (pow(2,i)));
        i++;
    }
    return out;
}

bin operator+ (const bin& bin1, const bin& bin2){
    int a = bin1.base10();
    int b = bin2.base10();
    bin out(a+b);
    return out;
}
bin operator -(const bin& bin1, const bin& bin2){
    int a = bin1.base10();
    int b = bin2.base10();
    bin out(a-b);
    return out;
}
bin operator *(const bin& bin1, const bin& bin2){
    int a = bin1.base10();
    int b = bin2.base10();
    bin out(a*b);
    return out;
}
bin operator /(const bin& bin1, const bin& bin2){
    int a = bin1.base10();
    int b = bin2.base10();
    bin out(a/b);
    return out;
}
bool operator< (const bin& bin1, const bin& bin2){
    int a = bin1.base10();
    int b = bin2.base10();

    return a<b;
}
bool operator<= (const bin& bin1, const bin& bin2){
    int a = bin1.base10();
    int b = bin2.base10();

    return a<=b;
}
