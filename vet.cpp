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

vet::vet(const vet& v){
    r=v.r; c=v.c;
    v_m = new int[r*c];

    for(int i=0; i<v.r; i++)
        for(int j=0; j<v.c; j++)
            *(v_m+(j+(i*c))) = v[i][j];

}
vet::~vet(){ delete[] v_m; }

int vet::getRow() const { return r; }
int vet::getColumn() const { return c; }

bool vet::isMoltiplication(vet tmp) const{ return c == tmp.r; }
bool vet::isQuadrata() const { return r==c; }
bool vet::sameSize(vet tmp) const{
    if((r == tmp.r) && (c == tmp.c))
        return true;
    else
        return false;
}
void vet::transposed() throw(input_error){
    int* tmp = new int[r*c];
    int index = 0;
    for(int j=0; j<c; j++){
        for(int i=0; i<r; i++){
            *(tmp+index) = *(v_m+(j+(i*c)));
            index++;
        }
    }

    if(index > r*c)
        throw input_error("vet");      //se index supera la dimensione dell'array solleva un eccezione per non fare casini con la matrice/vettore

    delete[] v_m;
    v_m = tmp;
    int ttmp = c;
    c = r; r = ttmp;
}
int vet::norma() const{
    int max=0;
    for(int i=0; i<c; i++){
        int count=0;
        for(int j=0; j<r; j++)
            count+=abs(*(v_m+(i+(j*c))));

        if(count>max)
            max=count;
    }

    return max;
}

/* ------------------------------------------------------ */

int* vet::operator [](size_t i) const { return (v_m + (c*i)); }
vet operator +(const vet& vet1, const vet& vet2) throw(domain_error){
    if(vet1.sameSize(vet2)){
        vet out(vet1.r,vet1.c);
        for(int i=0; i<vet1.r; i++)
            for(int j=0; j<vet1.c; j++)
                out[i][j] = vet1[i][j] + vet2[i][j];

        return out;
    }
    else
        throw domain_error("vet");

}
vet operator -(const vet& vet1, const vet& vet2) throw(domain_error){
    if(vet1.sameSize(vet2)){
        vet out(vet1.r,vet1.c);
        for(int i=0; i<vet1.r; i++)
            for(int j=0; j<vet1.c; j++)
                out[i][j] = vet1[i][j] - vet2[i][j];

        return out;
    }
    else
        throw domain_error("vet");
}
vet vet::operator *(const vet& vet2) throw(domain_error){
    if(this->isMoltiplication(vet2)){
        vet out(this->r,vet2.c);
        int valore=0;

        for(int i=0; i<this->r; i++){
            for(int jj=0; jj<vet2.c; jj++){

                for(int j=0; j<this->c; j++)
                    valore = valore + ((*this)[i][j] * vet2[j][jj]);

                out[i][jj] = valore;
                valore = 0;
            }
        }
        return out;
    }
    else
        throw domain_error("vet");
}
vet operator* (int k, const vet& vet1){
    vet out(vet1.r,vet1.c);
    for(int i=0; i<vet1.r; i++)
        for(int j=0; j<vet1.c; j++)
            out[i][j] = k * vet1[i][j];
    return out;
}
vet operator/ (int k, const vet& vet1){
    vet out(vet1.r,vet1.c);
    for(int i=0; i<vet1.r; i++)
        for(int j=0; j<vet1.c; j++)
            out[i][j] = vet1[i][j] / k;

    return out;
}
vet& vet::operator= (const vet& vet1){
    if(this != &vet1){
        delete[] v_m;

        /* riassegnazione delle dimensioni e riallocazione */
        this->r=vet1.r; this->c=vet1.c;
        this->v_m = new int[r*c];

        for(int i=0; i<vet1.r; i++)
            for(int j=0; j<vet1.c; j++)
                (*this)[i][j] = vet1[i][j];
    }
    return *this;
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
bool operator<= (const vet& vet1, const vet& vet2){ return vet1.norma()<=vet2.norma(); }
bool operator< (const vet& vet1, const vet& vet2){ return vet1.norma()<vet2.norma(); }

std::ostream& operator <<(std::ostream& os, const vet& vet1){
    for(int i=0; i<vet1.r; i++){
        for(int j=0; j<vet1.c; j++)
            os<<vet1[i][j]<<" ";
        os<<std::endl;
    }
    return os;
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



/* Metodi ereditati dalla classe tipo.h */

vet* vet::somma(tipo* b)throw(point_error){
    if(!b)
        throw point_error();
    vet* b1 = dynamic_cast<vet*>(b);
    return new vet((*this) + (*b1));
}
vet* vet::differenza(tipo* b)throw(point_error){
    if(!b)
        throw point_error();
    vet* b1 = dynamic_cast<vet*>(b);
    return new vet((*this) - (*b1));
}
vet* vet::moltiplicazione(int b){
    return new vet(b * (*this));    /*è da controllare*/
}
vet* vet::divisione(int b){
    return new vet(b / (*this));    /*è da controllare*/
}
bool vet::uguale(tipo* b) const throw(point_error){
    if(!b)
        throw point_error();
    vet* b1 = dynamic_cast<vet*>(b);
    return (*this)==(*b1);
}
bool vet::min(tipo* b) const throw(point_error){
    if(!b)
        throw point_error();
    vet* b1 = dynamic_cast<vet*>(b);
    return (*this)<(*b1);
}
string vet::to_stringa() const{
    return to_string((*this));
}
