#ifndef TREEBASIC_H
#define TREEBASIC_H
#include "raz.h"
#include "vet.h"

template <class T> class treebasic;

template <class T>
ostream& operator<<(ostream&, const treebasic<T>&);

template <class T>
string to_string(const treebasic<T>&);

//per ogni tipo T dev'essere presente la funzione "string to_string(T)" esterna alla classe
template <class T>
class treebasic{
     friend ostream& operator<< <T>(ostream&, const treebasic<T>&);
     friend string to_string <T>(const treebasic<T>&);
protected:
    class nodo{
    public:
        nodo* father, *right, *left;
        T info;
        nodo(const T& val, nodo* f=0, nodo* l=0, nodo* r=0): info(val), father(f), left(l), right(r) {}
        static string stampa(nodo*);
    };
    nodo* root;
private:
    //funzioni ausiliarie per il costruttore
    nodo* constrRic(T[], int, string::iterator, string::iterator, int&, nodo* =0);
    size_t balance(string::iterator, string::iterator);
    //altre funzioni ausialiarie
    nodo* copia(nodo *, nodo* =0);
    void distruggi(nodo*);
public:
    treebasic(): root(0) {}
    /* la costruzione di un albero sara' formato dalla sua struttura espressa con
     * una stringa controllata da un parser e da un array di elementi da inserire
     * nell'albero. Gli elementi devo essere inseriti secondo l'ordine prefisso.
     * la sringa sara' del tipo: (*, Ts, Td) dove "*" indica che sara' il valore
     * del nodo, mentre Ts e Td sono i sottoalberi sinistro e destro rispettivamente.
     * Il nodo foglia è del tipo: (*,_,_), dove "_" indica il nodo vuoto.
     * Es: l'albero (5,(2,_,(1,_,_)),_) sara' (*,(*,_,(*,_,_)),_). Il costruttire vuole
     * per parametri l'array di valori, la sua dimensione e la stringa con la struttura*/
    treebasic(T[], int, string);//viene costruito almeno un nodo
    treebasic(const treebasic& t): root(new nodo(t.root->info, 0, copia(t.root->left, root), copia(t.root->right, root))) {}// costruttore di copia profondo
    ~treebasic();// distruttore profondo
    virtual treebasic* somma(treebasic<T>* b)const=0;
    virtual treebasic* differenza(treebasic<T>* b)const=0;
    virtual treebasic* moltiplicazione(int)const=0;
    virtual treebasic* divisione(int)const=0;
    virtual void add(T)=0;//cerca di tenere  l'albero bilanciato
    virtual void remove(string)=0;//rimuove l'oggetto indicato da un percorso
    virtual void remove(T)=0;//rimuove l'oggetto cercandolo
    virtual T search(string)const=0;
    virtual T search (T)const=0;
};

//IMPLEMENTAZIONE FUNZIONI TEMPLATE

template <class T>
string treebasic<T>::nodo::stampa(treebasic<T>::nodo* n){
    if(!(n))
        return "_";
    return "('"+to_string(n->info)+"',"+stampa(n->left)+","+stampa(n->right)+")";
}

template <class T>
typename treebasic<T>::nodo* treebasic<T>::copia(nodo * n, nodo* father){
    if(!n)
        return n;
    nodo* x=new nodo(n->info, father, copia(n->left, x), copia(n->right, x));
    return x;
}

template <class T>
void treebasic<T>::distruggi(treebasic<T>::nodo* n){
    if(n){
        distruggi(n->left);
        distruggi(n->right);
        delete n;
    }
}

//PRE={l'iteratore e' in un carattere '('}
template <class T>
size_t treebasic<T>::balance(string::iterator i, string::iterator end){
    int k=1, s=1;
    for(; k>0 && i!=end; s++)
        if(*(i+s)=='(')
            k++;
        else if(*(i+s)==')')
            k--;
    if(!k)
        return s-1;
    return -1;
}
/*POST={ritorna -1 se le parentesi non sono ben bilanciate, altrimenti ritorna il numero
 * di passi fino alla posizione della ')' che chiude la parentesi della PRE}*/

template <class T>
typename treebasic<T>::nodo* treebasic<T>::constrRic(T A[], int size, string::iterator i, string::iterator end, int& k,  nodo* father){
    nodo* x=0;
    k++;
    if(k<size){//se sto creando piu' nodi di quelli presenti nell'array
        T val=A[k];
        if(*i!='(' || *(++i)!='*' || *(++i)!=',')
            //throw(0);
            cout<<"ERRORE9\n";
        if(*(i+1)=='_' && *(i+2)==',' && *(i+3)=='_' && *(i+4)==')')
            return new nodo(val, father, 0, 0);
        else if(*(i+1)=='_' && *(i+2)==',' && *(i+3)=='('){//solo Td
            i=i+3;// i punta su un '('
            int r=balance(i, end);
            if(r==-1)
                //throw(0);
                cout<<"ERRORE10\n";
            x=new nodo(val, father, 0, constrRic(A, size, i, end, k, x));
            i=i+r+1;
            if(*i!=')')
                //throw(0);
                cout<<"ERRORE11\n";
        }
        else if(*(i+1)=='('){// o solo con Ts o con Ts e Td
            int l=balance(++i, end);//i punta si '('
            if(l!=-1 && *(i+l+1)==','){
                if(*(i+l+2)=='_' && *(i+l+3)==')')//solo Ts
                    x=new nodo(val, father, constrRic(A, size, i, end, k, x));
                else if(*(i+l+2)=='('){
                    int r=balance(i+l+2, end);
                    if(r!=-1 && *(i+l+2+r+1)==')')
                        x=new nodo(val, father, constrRic(A, size, i, end, k, x), constrRic(A, size, i+l+2, end, k, x));
                    else
                        //throw(0);
                        cout<<"ERRORE12\n";
                }
                else
                    //throw(0);
                    cout<<"ERRORE13\n";
            }
            else
                //throw(0);
                cout<<"ERRORE14\n";
        }
        else
            //throw(0);
            cout<<"ERRORE15\n";
    }
    else
        //throw(0);
        cout<<"ERRORE16\n";
    return x;
}

template <class T>
treebasic<T>::treebasic(T type[], int size, string s){
    string::iterator i=s.begin();
    string::iterator end=s.end();
    int k=-1;//indice valore gia' analizzato nell'array
    //constrRic costruisce l'albero prendendo in input l'array di valori,
    //la sua lunghezza, un iteratore iniziale e finale della stringa, l'indice del
    //valore gia' analizzato passasto per riferimento e il valore del noto padre(che inizialmente e' 0)
    root=constrRic(type, size, i, end, k);
}

template <class T>
treebasic<T>::~treebasic(){distruggi(root);}

template <class T>
ostream& operator <<(ostream& os, const treebasic<T>& t){
    if(t.root)
        os<<treebasic<T>::nodo::stampa(t.root);
    return os;
}

template <class T>
string to_string(const treebasic<T> &t){
    if(t.root)
        return  treebasic<T>::nodo::stampa(t.root);
    return "";
}

//throw(0) c'e' quando la sintassi della stringa non e' corretta

#endif // TREEBASIC_H
