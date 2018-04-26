#ifndef VET_H
#define VET_H

#include "eccezione.h"
#include <iostream>
#include <string>
#include <math.h>                               /* pow - sqrt - abs */
class vet{
    friend vet operator+(const vet&, const vet&);
    friend vet operator-(const vet&, const vet&);
    friend vet operator/(const vet&, const vet&);
    friend vet operator*(int, const vet&);
    friend bool operator== (const vet&, const vet&);
    friend bool operator< (const vet&, const vet&);
    friend bool operator<= (const vet&, const vet&);
    friend string to_string(const vet&);         /* per ogni tipo T la funzione "string to_string(const T&)" converte in stringa la classe per stampare poi sul albero */

private:
    int r, c;
    int* v_m;
public:
    vet(int =1, int =1);
    vet(int*, int =1, int =1);                  /* costruttore con array di interi per popolaro nel momento della creazione */

    /* Metodi ausiliari                         -------------------------- */
    void insert(int val=0, int i=0, int j=0);   /* metodo per inserire un valore val in posizione (i,j) */
    int getRow() const;                         /* metodo che titorna il numero di righe di una matrice/vettore */
    int getColumn() const;                      /* mertodo che tirno il nuemro di colonne di una matrice/vettore */
    int getVal(int i, int j) const;             /* metodo che ritorna il valore in posizione (i,j) */
    void stampa() const;

    /* Metodi di calcolo                        -------------------------- */

    /* Metodi ausiliari per metodi di calcolo   -------------------------- */
    bool isMoltiplication(vet tmp) const;
    bool sameSize(vet tmp) const;
    void transposed();
    int norma() const;

    /* overloading di operatore */
    int* operator[](size_t) const;
    vet operator*(const vet&);                  /* due matrici si possno moltiplicare con A[m,n] e B[n,p], ho C[m,p] */
};

vet operator+ (const vet&, const vet&);         /* due matrici sono sommabili se hanno la stessa dimensione r=r1 & c=c1 */
vet operator- (const vet&, const vet&);         /* due matrici sono sottrabili se hanno la stessa dimensione r=r1 & c=c1 */
vet operator* (int, const vet&);                /* moltiplicazione di uno scalare per una matrice */
vet operator/ (const vet&, const vet&);         /* [A]*[B]-1 o [B]-1 * [A]. */
bool operator== (const vet&, const vet&);       /* ritorna true sse dim1 == dim2 e se vet1[i][j] == vet2[i][j] */
bool operator< (const vet&, const vet&);
bool operator<= (const vet&, const vet&);

string to_string(const vet&);                   /* per ogni tipo T la funzione "string to_string(const T&)" converte in stringa la classe in questo modo:
                                                   1,2,3 ; 4,5,6 dove le ',' separano le celle delle colonne e il ';' le righe */
#endif // VET_H
