#ifndef BINARYTREE_H
#define BINARYTREE_H
#include "binarytreebasic.h"


class binarytree: public binarytreebasic{
    friend ostream& operator<<(ostream&, const binarytree&);
    friend string to_string(const binarytree&);
    friend binarytree& operator +(const binarytree&, const binarytree&);
    friend binarytree& operator -(const binarytree&, const binarytree&);
private:
    static string min_path(nodo*);
    tipo* removeIt(nodo*);
    static nodo* searchIt(nodo*, tipo*);
public:
    binarytree(): binarytreebasic() {}
    binarytree(vector<tipo*> type, string& s): binarytreebasic(type, s) {}
    virtual void add(tipo*) throw(point_error);
    virtual tipo* remove(string) throw(path_error);                     //rimuove l'oggetto indicato da un percorso
    virtual tipo* remove(tipo*) throw(point_error);                     //rimuove l'oggetto cercandolo
    virtual tipo* search (tipo*)const throw(point_error);               //trova l'oggetto indicato

    binarytree& operator *(int);
    binarytree& operator /(int);
};

ostream& operator<< (ostream&, const binarytree&);
string to_string(const binarytree&);
binarytree& operator +(const binarytree&, const binarytree&);
binarytree& operator -(const binarytree&, const binarytree&);

#endif // BINARYTREE_H
