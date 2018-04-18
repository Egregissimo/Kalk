#include "bin.h"

bin::bin(unsigned int d){
    dim = d;
    array = new bool[d];
}
unsigned int bin::getDim() const { return dim; }
bool bin::max(const bin& vet2) const {
    if(dim>=vet2.dim)
        return true;
    else
        return false;
}
void bin::stampa() const{
    for(unsigned int i=0; i<dim; i++)
        std::cout<<array[i];
}
void bin::insert(unsigned int i, bool val){
    array[i] = val;
}

bool bin::operator [](unsigned int i) const { return array[i]; }

bin operator+ (const bin& bin1, const bin& bin2){
    unsigned int tmp_dim;
    if(bin1.max(bin2))
        tmp_dim = bin1.getDim();
    else
        tmp_dim = bin2.getDim();
    bin out(tmp_dim);



    return out;
}
