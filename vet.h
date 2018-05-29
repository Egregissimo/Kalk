#ifndef VET_H
#define VET_H

#include "tipo.h"
#include <math.h>                                   /* pow - sqrt - abs */

class vet: public tipo{
    /* Dichiarazione di amicizia per i metodi dichiarati fuori dalla classe */
    friend vet operator+(const vet&, const vet&) throw(domain_error);           /* friend */
    friend vet operator-(const vet&, const vet&) throw(domain_error);           /* friend */
    friend vet operator*(int, const vet&);                                      /* friend */
    friend vet operator/(int, const vet&);                                      /* friend */

    friend bool operator== (const vet&, const vet&);                            /* friend */
    friend bool operator< (const vet&, const vet&);                             /* friend */
    friend bool operator<= (const vet&, const vet&);                            /* friend */

    friend std::ostream& operator<< (std::ostream&, const vet&);                /* friend */
    friend string to_string(const vet&);                                        /* friend */ /* per ogni tipo T la funzione "string to_string(const T&)" converte in stringa la classe per stampare poi sul albero */

private:
    int r, c;
    int* v_m;

protected:
    /* Metodi ausiliari per i metodi di calcolo */
    bool isMoltiplication(vet tmp) const;
    bool isQuadrata() const;
    bool sameSize(vet tmp) const;

public:
    vet(int =0, int =1);
    vet(int*, int =0, int =1);                  /* costruttore con array di interi per popolaro nel momento della creazione */
    vet(const vet&);                            /* costruttore di copia profondo */
    ~vet();

    /* Metodi ausiliari */
    int getRow() const;                         /* metodo che titorna il numero di righe di una matrice/vettore */
    int getColumn() const;                      /* mertodo che tirno il nuemro di colonne di una matrice/vettore */

    /* Metodi ausiliari per metodi di calcolo */
    void transposed() throw(input_error);
    int norma() const;

    /* OVELOADING degli operatori */
    int* operator[](size_t) const;
    vet operator*(const vet&) throw(domain_error);                  /* due matrici si possno moltiplicare con A[m,n] e B[n,p], ho C[m,p] */
    vet& operator=(const vet&);

    /* Metodi virtuali ereditati dalla classe tipo e implementati della classe vet */
    vet* somma(tipo*)throw(point_error, domain_error);
    vet* differenza(tipo*)throw(point_error, domain_error);
    vet* moltiplicazione(int);
    vet* divisione(int);
    bool uguale(tipo*)const throw(point_error);
    bool min(tipo*)const throw(point_error);
    string to_stringa()const;
};
/* OVELOADING degli operatori come metodi fuori dalla classe bin, dichiarazione di amicizia per poter accedere ai campi e poter operare */
vet operator+ (const vet&, const vet&) throw(domain_error);         /* due matrici sono sommabili se hanno la stessa dimensione r=r1 & c=c1 */
vet operator- (const vet&, const vet&) throw(domain_error);         /* due matrici sono sottrabili se hanno la stessa dimensione r=r1 & c=c1 */
vet operator* (int, const vet&);                                    /* moltiplicazione di uno scalare per una matrice */
vet operator/ (int, const vet&);                                    /* divisione di uno scalare per una matrica     [A]*[B]-1 o [B]-1 * [A]. */
bool operator== (const vet&, const vet&);                           /* ritorna true sse dim1 == dim2 e se vet1[i][j] == vet2[i][j] */
bool operator<= (const vet&, const vet&);                           /* basata sulla norma, vero sse norma1 <= norma2 */
bool operator< (const vet&, const vet&);                            /* basata sulla norma, vero sse norma1 < norma2 */

std::ostream& operator<< (std::ostream&, const vet&);               /* oveloading di stampa */
string to_string(const vet&);                   /* per ogni tipo T la funzione "string to_string(const T&)" converte in stringa la classe in questo modo:
                                                   1,2,3 ; 4,5,6 dove le ',' separano le celle delle colonne e il ';' le righe */
#endif // VET_H
