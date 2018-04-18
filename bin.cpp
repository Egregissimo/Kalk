#include "bin.h"

bin::bin(unsigned int d){
    for(unsigned int i=0; i<d-1; i++)
        array[i] = 0;
    array[d-1] = 1;
}
unsigned int bin::getDim() const { return array.size(); }
bool bin::max(const bin& bin2) const {
    if(array.size() >= bin2.getDim())
        return true;
    else
        return false;
}
void bin::stampa() const{
    for(unsigned int i=0; i<array.size(); i++)
        std::cout<<array[i];
    std::cout<<std::endl;
}
void bin::insert(unsigned int i, bool val){
    array[i] = val;
}

//bool& bin::operator [](unsigned int i) const { return array[i]; }
/*
bin operator+ (const bin& bin1, const bin& bin2){
    unsigned int tmp_dim;
    unsigned int dim_min;

    unsigned int t = 0;
    bool resto = 0;

    if(bin1.max(bin2))
        tmp_dim = bin1.getDim();
    else
        tmp_dim = bin2.getDim();

    bin out(tmp_dim);

    for(int i=dim_min-1; i=0; i--){
        t = bin1[i] + bin2[i] + resto;
        t = t%2;
        resto = t/2;

       // out[i] = t;
    }

    if(resto == 1){

    }

    return out;
}
*/
