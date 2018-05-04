#ifndef TREEBASIC_H
#define TREEBASIC_H
#include <vector>
#include <typeinfo>
#include "raz.h"
//#include "vet.h"
using std::vector;

class treebasic{
     friend ostream& operator<<(ostream&, const treebasic&);
     friend string to_string(const treebasic&);
protected:
    class nodo{
    public:
        tipo* info;//campo info polimorfo
        nodo* father, *left, *right;
        nodo(): father(0), left(0), right(0) {}
        nodo(tipo* val, nodo* f=0, nodo* l=0, nodo* r=0): info(val), father(f), left(l), right(r) {}
        static string stampa(nodo*);//stampa il nodo corrente e il suo sottoalbero
    };
    nodo* root;
    //funzioni
    static bool parser(string::iterator, string::iterator);//constrolla che la stringa in input sia grammaticalmente corretta
    //prende in input un carattere, se questo e' '(' ritorna la sua ')' bilanciata
    static int balance_brackets(string::iterator, string::iterator);
    static unsigned int n_nodes_stringa(string::iterator);//ritorna il numero di nodi di una stringa
    //il primo e secondo valore sono rispettivamente il termine a sinistra e destra dei rispettivi operatori. Il terzo si
    //riferisce al nodo padre da impostare ad ogni ricorsione
    static nodo* somma(nodo*, nodo*, nodo* =0);
    static nodo* differenza(nodo*, nodo*, nodo* =0);
    static nodo* moltiplicazione(nodo*, int, nodo * =0);
    static nodo* divisione(nodo*, int, nodo* =0);
    static int n_nodes(nodo*);//conta i nodi dell'albero
    static vector<tipo*> nodes(nodo*);//ritorna un vettore con i campi info del sottoalbero del nodo letti in modo infisso
    static bool controlla_percorso(string &);//constrolla se la stringa per la ricerca di un elemento sia formata esclusivamente da 0 e 1
    static bool controlla_input(vector<tipo*>&, string&);//constrolla se gli input del costruttore sono corretti
    static string tree_to_string(nodo*);//stampa la struttura dell'albero prendendo il nodo radice
private:
    //altre funzioni ausialiarie
    nodo* copia(nodo *, nodo* =0)const;//effettua una copia profonda dell'albero
    void distruggi(nodo*);//non si è deciso di implementare il distruttore di nodo per evitare
                            //di distruggere l'intero albero distruggendo un solo nodo
    //funzioni ausiliarie per il costruttore
    nodo* constrRic(string::iterator, vector<tipo*>::iterator&, nodo* =0);//funzione ricorsica del costruttore

public:
    treebasic(): root(0) {}
    /* la costruzione di un albero sara' formato dalla sua struttura espressa con
     * una stringa controllata da un parser e da un array di elementi da inserire
     * nell'albero. Gli elementi devo essere inseriti secondo l'ordine PREFISSO.
     * la stringa sara' del tipo: (*, Ts, Td) dove "*" indica che sara' il valore
     * del nodo, mentre Ts e Td sono i sottoalberi sinistro e destro rispettivamente.
     * Il nodo foglia è del tipo: (*,_,_), dove "_" indica il nodo vuoto.
     * Es: l'albero (5,(2,_,(1,_,_)),_) sara' (*,(*,_,(*,_,_)),_). Il costruttire vuole
     * per parametri l'array di valori, la sua dimensione e la stringa con la struttura*/
    treebasic(vector<tipo*>, string &);//viene costruito almeno un nodo
    treebasic(const treebasic& t): root(copia(t.root)) {}// costruttore di copia profondo
    ~treebasic();// distruttore profondo
    treebasic& operator=(const treebasic&);//assegnazione profonda

    virtual void add(tipo*)=0;//cerca di tenere  l'albero bilanciato
    virtual tipo* remove(string)=0;//rimuove l'oggetto indicato da un percorso
    virtual tipo* remove(tipo*)=0;//rimuove l'oggetto cercandolo
    virtual tipo* search(string)const=0;//trova l'oggetto indicato dal percorso
    virtual tipo* search (tipo*)const=0;//trova l'oggetto indicato in input

    string struttura_tree()const;//stampa la struttura dell'albero
};

ostream& operator<<(ostream&, const treebasic&);
string to_string(const treebasic&);

#endif // TREEBASIC_H
