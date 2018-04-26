#include "vet.h"

vet::vet(int dim1, int dim2){
    r=dim1; c=dim2;
    v_m = new int[r*c];
}
vet::vet(int* st, int dim1, int dim2){
    r=dim1; c=dim2;
    v_m = new int[r*c];

    for(int i=0; i<r; i++)
        for(int j=0; j<c; j++)
            *(v_m+(j+(i*c))) = *(st+(j+(i*c)));
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
int vet::norma() const{
    int out = 0;
    if((r == 1) || (c == 1)){
        /* NORMA VETTORE */
        for(int i=0; i<r*c; i++)
             out = pow(*(v_m+i), 2) + out;
        out = sqrt(out);
    }
    else{
        /* NORMA VETTORE */
        int max;
        for(int j=0; j<1; j++)
            for(int i=0; i<r; i++)
                out = abs(*(v_m+(j+(i*c)))) + out;

        for(int j=1; j<c; j++){
            max = 0;
            for(int i=0; i<r; i++){
                max = abs(*(v_m+(j+(i*c)))) + max;
            }
            if(max >= out)
                out = max;
        }
    }
    return out;
}

/* ------------------------------------------------------ */

int* vet::operator [](size_t i) const { return (v_m + (c*i)); }
vet operator +(const vet& vet1, const vet& vet2){
    if(vet1.sameSize(vet2)){
        vet out(vet1.r,vet1.c);
        for(int i=0; i<vet1.r; i++)
            for(int j=0; j<vet1.c; j++)
                out[i][j] = vet1[i][j] + vet2[i][j];

        return out;
    }
    else
        throw eccezione();
}
vet operator -(const vet& vet1, const vet& vet2){
    if(vet1.sameSize(vet2)){
        vet out(vet1.r,vet1.c);
        for(int i=0; i<vet1.r; i++)
            for(int j=0; j<vet1.c; j++)
                out[i][j] = vet1[i][j] - vet2[i][j];

        return out;
    }
    else
        throw eccezione();
}
vet vet::operator *(const vet& vet2){
    if(this->isMoltiplication(vet2)){
        vet out(this->r,vet2.c);
        int valore=0;

        for(int i=0; i<this->r; i++){
            for(int jj=0; jj<vet2.c; jj++){

                for(int j=0; j<this->c; j++)
                    valore = valore + ((*this)[i][j] * vet2[j][jj]);

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
    vet out(vet1.r,vet1.c);
    for(int i=0; i<vet1.r; i++)
        for(int j=0; j<vet1.c; j++)
            out[i][j] = k * vet1[i][j];
    return out;
}

string to_string(const vet& vet1){
    string out;
    for(int i=0; i<vet1.r; i++){
        for(int j=0; j<vet1.c-1; j++){
            out = out + std::to_string(vet1[i][j]) + ",";
        }
        out = out + std::to_string(vet1[i][vet1.c-1]);
        out = out + ";";
    }
    return out;
}

bool operator== (const vet& vet1, const vet& vet2){
    bool out = true;

    if( vet1.sameSize(vet2)){
        /* stessa dimensione */
        for(int i=0; i<vet1.getRow() && out; i++)
            for(int j=0; j<vet1.getColumn() && out; j++)
                if(vet1[i][j] != vet2[i][j])
                    out = false;

        return out;
    }
    return false;
}
bool operator< (const vet& vet1, const vet& vet2){ return vet1.norma()<vet2.norma(); }
bool operator<= (const vet& vet1, const vet& vet2){ return vet1.norma()<=vet2.norma(); }
