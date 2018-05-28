#ifndef BINARYTREEBASIC_H
#define BINARYTREEBASIC_H
#include <vector>
#include <typeinfo>
#include "raz.h"
#include "vet.h"
#include "bin.h"
using std::vector;

class binarytreebasic{
     friend ostream& operator<<(ostream&, const binarytreebasic&);
     friend string to_string(const binarytreebasic&);
protected:
    class nodo{
    public:
        tipo* info;                                                 /* campo info polimorfo */
        nodo* father, *left, *right;
        nodo(): info(0), father(0), left(0), right(0) {}
        nodo(tipo* val, nodo* f=0, nodo* l=0, nodo* r=0): info(val), father(f), left(l), right(r) {}
        static string stampa(nodo*);                                /* stampa (il campo info) il nodo corrente e il suo sottoalbero */
    };
    nodo* root;
    /* funzioni */
    static bool parser(string::iterator, string::iterator);             /* constrolla che la stringa in input sia grammaticalmente corretta */
    static int balance_brackets(string::iterator, string::iterator);    /* prende in input un carattere, se questo e' '(' ritorna la sua ')' bilanciata */

    /*  il primo e secondo valore sono rispettivamente il termine a sinistra e destra dei rispettivi operatori. Il terzo si
        riferisce al nodo padre da impostare ad ogni ricorsione */
    static nodo* somma(nodo*, nodo*, nodo* =0);
    static nodo* differenza(nodo*, nodo*, nodo* =0);
    static nodo* moltiplicazione(nodo*, int, nodo * =0);
    static nodo* divisione(nodo*, int, nodo* =0);

    static vector<tipo*> nodes(nodo*);                                  /* ritorna un vettore con i campi info del sottoalbero del nodo letti in ordine PREFISSO */
    static bool controlla_percorso(string &);                           /* constrolla se la stringa per la ricerca di un elemento sia formata esclusivamente da 0 e 1 */
    static bool controlla_input(vector<tipo*>&, string&);               /* constrolla se gli input del costruttore sono corretti */
    static string tree_to_string(nodo*);                                /* stampa la struttura dell'albero prendendo il nodo radice */
private:
    /* funzioni ausialiarie */
    nodo* copia(nodo *, nodo* =0)const;                                 /* effettua una copia profonda dell'albero */
    void distruggi(nodo*);                                              /* si è deciso di non implementare il distruttore di nodo per evitare
                                                                           di distruggere l'intero albero distruggendo un solo nodo */
    /* funzione ricorsica ausiliaria per il costruttore */
    nodo* constrRic(string::iterator, vector<tipo*>::iterator&, nodo* =0);
public:
    binarytreebasic(): root(0) {}
    /* la costruzione di un albero sara' formato dalla sua struttura espressa con
     * una stringa controllata da un parser e da un vector di elementi da inserire
     * nell'albero. Gli elementi devo essere inseriti secondo l'ordine PREFISSO.
     * la stringa sara' del tipo: (*, Ts, Td) dove "*" indica che sara' il valore
     * del nodo, mentre Ts e Td sono i sottoalberi sinistro e destro rispettivamente.
     * Il nodo foglia è del tipo: (*,_,_), dove "_" indica il nodo vuoto.
     * Es: l'albero (5,(2,_,(1,_,_)),_) sara' (*,(*,_,(*,_,_)),_). Il costruttire vuole
     * per parametri l'array di valori, la sua dimensione e la stringa con la struttura */

    binarytreebasic(vector<tipo*>, string &) throw(input_error);        /* costruttore */
    binarytreebasic(const binarytreebasic& t): root(copia(t.root)) {}   /* costruttore di copia profondo */
    virtual ~binarytreebasic();                                         /* distruttore profondo */
    binarytreebasic& operator=(const binarytreebasic&);                /* assegnazione profonda */
    static int n_nodes(nodo*);                                          /* conta i nodi dell'albero */

    tipo* cerca(string)const throw(path_error);                         /* trova l'oggetto indicato dal percorso, se stringa vuota ritorna la radice */

    virtual void add(tipo*)=0;                                          /* aggiungo il nodo tenendo l'albero bilanciato */
    virtual tipo* remove(string)=0;                                     /* rimuove l'oggetto indicato da un percorso */
    virtual tipo* remove(tipo*)=0;                                      /* rimuove l'oggetto cercandolo */
    virtual tipo* search (tipo*)const=0;                                /* trova l'oggetto indicato in input */

    string struttura_tree()const;                                       /* stampa la struttura dell'albero */
    static unsigned int n_nodes_stringa(string::iterator);              /* ritorna il numero di nodi di una stringa */
    Tipo* tipo_tree()const;
};

ostream& operator<<(ostream&, const binarytreebasic&);
string to_string(const binarytreebasic&);

#endif // BINARYTREEBASIC_H
