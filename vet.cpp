#include "vet.h"

vet::vet(int dim1, int dim2){
    r=dim1; c=dim2;
    v_m = new int[r*c];
}
void vet::insert(int val, int i, int j){
    if((i>=0) && (i<r) && (j>=0) && (j<c))
        *(v_m+(j+(i*c))) = val;
    else
        throw eccezione();
    /* gestire un eccesione nel caso in cui gli indici da visitare
       non siano dentro le dimensioni della matrice/vettore */
}
int vet::getRow() const { return r; }
int vet::getColumn() const { return c; }
int vet::getVal(int i, int j) const {
    if((i>=0) && (i<r) && (j>=0) && (j<c))
        return *(v_m+(j+(i*c)));
    else
        throw eccezione();
    /* gestire un eccesione nel caso in cui gli indici da visitare
       non siano dentro le dimensioni della matrice/vettore */
}
void vet::stampa() const{
    for(int i=0; i<r; i++){
        for(int j=0; j<c; j++)
            std::cout<<*(v_m+(j+(i*c)))<<" ";
        std::cout<<std::endl;
    }
}

/* ------------------------------------------------------ */
int vet::determinant() const{
    int det=0;
    for(int i=0; i<r; i++){
        for(int j=0; j<c; j++){

        }
    }
    return det;
}
void vet::inverse(){

}

/* ------------------------------------------------------ */

bool vet::isMoltiplication(vet tmp) const{ return c == tmp.r; }
bool vet::sameSize(vet tmp) const{
    if((r == tmp.r) && (c == tmp.c))
        return true;
    else
        return false;
}
void vet::transposed(){
    int* tmp = new int[r*c];
    int index = 0;
    for(int j=0; j<c; j++){
        for(int i=0; i<r; i++){
            *(tmp+index) = *(v_m+(j+(i*c)));
            index++;
        }
    }

    if(index > r*c)
        throw eccezione();      //se index supera la dimensione dell'array solleva un eccezione per non fare casini con la matrice/vettore

    delete[] v_m;
    v_m = tmp;
    int ttmp = c;
    c = r; r = ttmp;
}

/* ------------------------------------------------------ */

int* vet::operator [](size_t i) const { return (v_m + (c*i)); }
vet operator +(const vet& vet1, const vet& vet2){
    if(vet1.sameSize(vet2)){
        vet out(vet1.getRow(),vet1.getColumn());
        for(int i=0; i<vet1.getRow(); i++)
            for(int j=0; j<vet1.getColumn(); j++)
               //out.insert((vet1.getVal(i,j) + vet2.getVal(i,j)), i, j);
               out[i][j] = vet1.getVal(i,j) + vet2.getVal(i,j);

        return out;
    }
}
vet operator -(const vet& vet1, const vet& vet2){
    if(vet1.sameSize(vet2)){
        vet out(vet1.getRow(),vet1.getColumn());
        for(int i=0; i<vet1.getRow(); i++)
            for(int j=0; j<vet1.getColumn(); j++)
               //out.insert((vet1.getVal(i,j) - vet2.getVal(i,j)), i, j);
                out[i][j] = vet1.getVal(i,j) - vet2.getVal(i,j);
        return out;
    }
    else
        throw eccezione();
}
vet vet::operator *(const vet& vet2){
    if(this->isMoltiplication(vet2)){
        vet out(this->getRow(),vet2.getColumn());
        int valore=0;

        for(int i=0; i<this->getRow(); i++){
            for(int jj=0; jj<vet2.getColumn(); jj++){

                for(int j=0; j<this->getColumn(); j++)
                    valore = valore + (this->getVal(i,j) * vet2.getVal(j,jj));

                //out.insert(valore, i, jj);
                out[i][jj] = valore;
                valore = 0;
            }
        }
        return out;
    }
    else
        throw eccezione();
}
vet operator* (int k, const vet& vet1){
    vet out(vet1.getRow(),vet1.getColumn());
    for(int i=0; i<vet1.getRow(); i++)
        for(int j=0; j<vet1.getColumn(); j++)
            out[i][j] = k * vet1[i][j];
    return out;
}
