#ifndef binarytreesearch_H
#define binarytreesearch_H
#include "binarytreebasic.h"

/*  Ricordarsi che per invocare un campo dati bisogna fare this->"campo dati"
    Non serve ridefinire costruttore di copia, distruttore o assegnazione dato
    che questi alberi derivati non hanno campi dati. */
class binarytreesearch: public binarytreebasic{
    friend ostream& operator<<(ostream&, const binarytreesearch&);
    friend string to_string(const binarytreesearch&);
    friend binarytreesearch& operator +(const binarytreesearch&, const binarytreesearch&);
    friend binarytreesearch& operator -(const binarytreesearch&, const binarytreesearch&);
private:
    //funzioni per effettuare il merge-sort in O(nlogn)
    static void merge(vector<tipo *> &, vector<tipo *> &, vector<tipo *> &);    //supporta la funzione merge_sort
    static void merge_sort(vector<tipo *> &);                                   //ordina in modo crescente i valori del vettore dato come parametro
    //funzione ricorsiva per creare l'albero di ricerca. Prende in input il primo array per inserirne
    //i valori ordinati nel secondo array da usare nel costruttore
    static void ordinaRic(vector<tipo*>&, string::iterator, vector<tipo*>::iterator&);  //supporta la funzione ordina
    //invoca ordinaRic per ritornare l'array ordinato per inserire i nodi nell'ordine corretto nell'albero di ricerca
    static vector<tipo*> ordina(vector<tipo*>, string &);
    //crea una stringa per un albero bilanciato di ricerca di n nodi
    static string crea_stringa(int);
    static nodo* minimum(nodo*);                                //trova il minimo dell'albero
    static nodo* successor(nodo*);                              //trova il successore del nodo dato in input
    tipo* removeIt(nodo*);                                      //rimuove in modo iterativo il nodo indicato mantenedo le proprieta' del'albero di ricerca
public:
    binarytreesearch(): binarytreebasic() {}
    binarytreesearch(vector<tipo*> type, string& s): binarytreebasic(ordina(type, s), s) {}
    virtual void add(tipo*);                 //cerca di tenere  l'albero bilanciato
    virtual tipo* remove(string);             /* rimuove l'oggetto indicato da un percorso, se stringa vuota elimina la radice */
    virtual tipo* remove(tipo*);             //rimuove l'oggetto cercandolo
    virtual tipo* search (tipo*)const;       //trova l'oggetto indicato

    binarytreesearch balance() const;                           //restituisce un albero di ricerca bilanciato
    binarytreesearch& operator *(int);
    binarytreesearch& operator /(int);
};

ostream& operator<< (ostream&, const binarytreesearch&);
string to_string(const binarytreesearch&);
binarytreesearch& operator +(const binarytreesearch&, const binarytreesearch&);
binarytreesearch& operator -(const binarytreesearch&, const binarytreesearch&);

#endif // binarytreesearch_H
