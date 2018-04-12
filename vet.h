#ifndef VET_H
#define VET_H

#include "eccezione.h"
#include <iostream>

class vet{
    friend vet operator+(const vet&, const vet&);
    friend vet operator-(const vet&, const vet&);
    friend vet operator/(const vet&, const vet&);
    friend vet operator*(size_t, const vet&);

private:
    int r, c;
    int* v_m;
public:
    vet(int dim1=1, int dim2=1);

    /* Metodi ausiliari                        -------------------------- */
    void insert(int val=0, int i=0, int j=0);   /* metodo per inserire un valore val in posizione (i,j) */
    int getRow() const;                         /* metodo che titorna il numero di righe di una matrice/vettore */
    int getColumn() const;                      /* mertodo che tirno il nuemro di colonne di una matrice/vettore */
    int getVal(int i, int j) const;             /* metodo che ritorna il valore in posizione (i,j) */
    void stampa() const;


    /* Metodi di calcolo                       -------------------------- */
    int determinant() const;
    void inverse();

    /* Metodi ausiliari per metodi di calcolo  -------------------------- */
    bool isMoltiplication(vet tmp) const;
    bool sameSize(vet tmp) const;
    void transposed();

    /* overloading di operatore */
    int* operator[](size_t) const;
    vet operator*(const vet&);              /* due matrici si possno moltiplicare con A[m,n] e B[n,p], ho C[m,p] */
};

vet operator+ (const vet&, const vet&);   /* due matrici sono sommabili se hanno la stessa dimensione r=r1 & c=c1 */
vet operator- (const vet&, const vet&);   /* due matrici sono sottrabili se hanno la stessa dimensione r=r1 & c=c1 */
vet operator* (int, const vet&);       /* moltiplicazione di uno scalare per una matrice */
vet operator/ (const vet&, const vet&);   /* [A]*[B]-1 o [B]-1 * [A]. */

#endif // VET_H
