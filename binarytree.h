#ifndef BINARYTREE_H
#define BINARYTREE_H
#include "binarytreebasic.h"


class binarytree: public binarytreebasic{
    friend ostream& operator<<(ostream&, const binarytree&);
    friend string to_string(const binarytree&);
    friend binarytree& operator +(const binarytree&, const binarytree&);
    friend binarytree& operator -(const binarytree&, const binarytree&);
private:
    static string min_path(nodo*);                  //trova il percorso più corto che presenta un nodo con 0 o 1 figlio attraverso una stringa di 0 e 1
    tipo* removeIt(nodo*);                          //funzione iterativa per rimuovere il nodo
    static nodo* searchIt(nodo*, tipo*);            //funzione iterativa per trovare il nodo
public:
    binarytree(): binarytreebasic() {}
    binarytree(vector<tipo*> type, string& s): binarytreebasic(type, s) {}
    virtual void add(tipo*);                            //aggiunge nel percorso più corto il nodo dato come parametro
    virtual tipo* remove(string);                     //rimuove l'oggetto indicato da un percorso
    virtual tipo* remove(tipo*);                     //rimuove l'oggetto cercandolo
    virtual tipo* search (tipo*)const;               //trova l'oggetto indicato

    binarytree& operator *(int);
    binarytree& operator /(int);
};

ostream& operator<< (ostream&, const binarytree&);
string to_string(const binarytree&);
binarytree& operator +(const binarytree&, const binarytree&);
binarytree& operator -(const binarytree&, const binarytree&);

#endif // BINARYTREE_H
