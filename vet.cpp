#include "vet.h";

vet::vet(int dim1, int dim2){
    r=dim1; c=dim2;
    vet = new int*[r];
    for(int i=0; i<r; i++)
        vet[i] = new int[c];
}

int getRow() const { return r; }
int getColumn() const { return c; }

bool vet::sameSize(vet tmp) const{
    if((r == tmp.r) && (c == tmp.c))
        return true;
    else
        return false;
}

int vet::determinant() const{
    int det=0;
    for(int i=0; i<r; i++){
        for(int j=0; j<c; j++){

        }
    }
    return det;
}


vet operator *(const vet& vet1, const vet& vet2) const{
    if(vet1.sameSize((vet2))){

    }
}
