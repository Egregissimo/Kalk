#ifndef VET_H
#define VET_H

#include <iostream>

class vet{
    friend raz operator+(const vet&, const vet&) const;
    friend raz operator-(const vet&, const vet&) const;
    friend raz operator*(const vet&, const vet&);
    friend raz operator/(const vet&, const vet&);

private:
    int r, c;
    int **vet;
public:
    vet(int dim1=0, int dim2=0);

    int getRow() const;
    int getColumn() const;

    void inverse();
    int determinant() const;
    bool sameSize(vet tmp) const;
};

vet operator+ (const vet&, const vet&) const; /* due matrici sono sommabili se hanno la stessa dimensione r=r1 & c=c1 */
vet operator- (const vet&, const vet&) const; /* due matrici sono sottrabili se hanno la stessa dimensione r=r1 & c=c1 */
vet operator* (const vet&, const vet&); /* due matrici si possno moltiplicare con A[m,n] e B[n,p], ho C[n,p] */
vet operator/ (const vet&, const vet&); /* [A]*[B]-1 o [B]-1 * [A]. */

#endif // VET_H
