#ifndef TREEBASIC_H
#define TREEBASIC_H
#include "raz.h"
//#include "vet.h"

template <class T> class treebasic;

template <class T>
ostream& operator<<(ostream&, const treebasic<T>&);

template <class T>
string to_string(const treebasic<T>&);

//per ogni tipo T dev'essere presente la funzione "string to_string(const T&)" esterna alla classe
template <class T>
class treebasic{
     friend ostream& operator<< <T>(ostream&, const treebasic<T>&);
     friend string to_string <T>(const treebasic<T>&);
protected:
    class nodo{
    public:
        nodo* father, *left, *right;
        T info;
        nodo(): father(0), left(0), right(0) {}
        nodo(const T& val, nodo* f=0, nodo* l=0, nodo* r=0): info(val), father(f), left(l), right(r) {}
        static string stampa(nodo*);
    };
    nodo* root;
    //funzioni
    bool parser(string::iterator, string::iterator)const;
    static nodo* somma(nodo*, nodo*, nodo* =0);
    static nodo* differenza(nodo*, nodo*, nodo* =0);
    static nodo* moltiplicazione(nodo*, int&, nodo * =0);
    static nodo* divisione(nodo*, int&, nodo* =0);
    static int n_nodes(nodo*);//conta i nodi dell'albero
    static void nodes(T[], nodo*, int&);//inserisce i vari campi info nell'array
private:
    //funzioni ausiliarie per il costruttore
    nodo* constrRic(const T[], int, string::iterator, int&, nodo* =0);
    int balance_brackets(string::iterator, string::iterator)const;
    //altre funzioni ausialiarie
    nodo* copia(nodo *, nodo* =0)const;
    void distruggi(nodo*);//non si è deciso di implementare il distruttore di nodo per evitare
                            //di distruggere l'intero albero distruggendo un solo nodo
public:
    treebasic(): root(0) {}
    /* la costruzione di un albero sara' formato dalla sua struttura espressa con
     * una stringa controllata da un parser e da un array di elementi da inserire
     * nell'albero. Gli elementi devo essere inseriti secondo l'ordine PREFISSO.
     * la sringa sara' del tipo: (*, Ts, Td) dove "*" indica che sara' il valore
     * del nodo, mentre Ts e Td sono i sottoalberi sinistro e destro rispettivamente.
     * Il nodo foglia è del tipo: (*,_,_), dove "_" indica il nodo vuoto.
     * Es: l'albero (5,(2,_,(1,_,_)),_) sara' (*,(*,_,(*,_,_)),_). Il costruttire vuole
     * per parametri l'array di valori, la sua dimensione e la stringa con la struttura*/
    treebasic(T[], int, string&);//viene costruito almeno un nodo
    treebasic(const treebasic& t): root(copia(t.root)) {}// costruttore di copia profondo
    ~treebasic();// distruttore profondo
    treebasic& operator=(const treebasic&);//assegnazione profonda
    virtual void add(T)=0;//cerca di tenere  l'albero bilanciato
    virtual void remove(string)=0;//rimuove l'oggetto indicato da un percorso
    virtual void remove(T)=0;//rimuove l'oggetto cercandolo
    virtual T search(string)const=0;
    virtual T search (T)const=0;

    static string tree_to_string(nodo*);//stampa la struttura dell'albero
};

//IMPLEMENTAZIONE FUNZIONI TEMPLATE

template <class T>
string treebasic<T>::nodo::stampa(treebasic<T>::nodo* n){
    if(!(n))
        return "_";
    return "('"+to_string(n->info)+"',"+stampa(n->left)+","+stampa(n->right)+")";
}

template <class T>
typename treebasic<T>::nodo* treebasic<T>::copia(nodo * n, nodo* father) const{
    if(!n)
        return 0;
    nodo* x=new nodo(n->info, father, copia(n->left, x), copia(n->right, x));
    return x;
}

template <class T>
void treebasic<T>::distruggi(treebasic<T>::nodo* n){
    if(n){
        distruggi(n->left);
        distruggi(n->right);
    }
}

//PRE={la stringa e' corretta}
template <class T>
int treebasic<T>::balance_brackets(string::iterator i, string::iterator end) const{
    if(*i=='_')
        return 0; 
    int k=1, s=1;
    if(end==i)
        end=i-1;

    for(; k>0 && i+s!=end; s++)
        if(*(i+s)=='(')
            k++;
        else if(*(i+s)==')')
            k--;
    if(k)
        return -1;
    return s-1;
}
//POST={ritorna il numero di passi fino alla posizione della ')' che chiude la parentesi della PRE}

template <class T>
bool treebasic<T>::parser(string::iterator begin, string::iterator end)const{
    if(begin==end)
        return true;
    if(*begin!='(' || *++begin!='*' || *++begin!=',')
        return false;
    if(*(begin+1)=='_' && *(begin+2)==',' && *(begin+3)=='_' && *(begin+4)==')')
        return true;

    begin++;
    bool a=true, b=true;
    string::iterator aux_end;

    if(*(begin)!='_' && *(begin)!='(')
        return false;
    if(*(begin)=='('){
        int l=balance_brackets(begin, end);
        if(l==-1)
            return false;
        aux_end=begin+l+1;
        if(*aux_end!=',')
            return false;
        a=parser(begin, aux_end);
        begin=aux_end+1;
    }
    else
        begin+=2;

    if(*(begin)!='_' && *(begin)!='(')
        return false;
    if(*(begin)=='('){
        int r=balance_brackets(begin, end);
        if(r==-1)
            return false;
        aux_end=begin+r+1;
        if(*aux_end!=')')
            return false;
        b=parser(begin, aux_end);
    }

    return a && b;
}

//PRE=(la stringa s e' corretta e l'albero contiene almeno un nodo, percio' il caso limite sara' "(*, _,_)")
template <class T>
typename treebasic<T>::nodo* treebasic<T>::constrRic(const T A[], int size, string::iterator i, int& k,  nodo* father){
    nodo* x=0;
    if(k<size){
        T val=A[k];
        k++;
        i+=3;
        int left=balance_brackets(i, i);
        int right=balance_brackets(i+left+2, i);
        if(!left && !right)//caso base
            return new nodo(val, father, 0, 0);
        if(!left && right)
            x=new nodo(val, father, 0, constrRic(A, size, i+left+2, k, x));
        else if(left && !right)
            x=new nodo(val, father, constrRic(A, size, i, k, x));
        else
            x=new nodo(val, father, constrRic(A, size, i, k, x), constrRic(A, size, i+left+2, k, x));
    }
    else
        //throw(0);
        cout<<"ERRORE16\n";
    return x;
}

//PRE={size e' la lunghezza corretta di type}
template <class T>
treebasic<T>::treebasic(T type[], int size, string& s){
    if(parser(s.begin(), s.end()) && size>0){
        int k=0;//indice valore da analizzare nell'array
        //constrRic costruisce l'albero prendendo in input l'array di valori,
        //la sua lunghezza, un iteratore iniziale e finale della stringa, l'indice del
        //valore gia' analizzato passasto per riferimento e il valore del noto padre(che inizialmente e' 0)
        root=constrRic(type, size, s.begin(), k);
    }
    else
        //throw(0);
        cout<<"ERRORE10\n";
}

template <class T>
treebasic<T>::~treebasic(){if(root) distruggi(root);}

template <class T>
treebasic<T>& treebasic<T>::operator=(const treebasic<T>& t){
    if(this->root!=t.root){
        delete root;
        root=copia(t.root);
    }
}

template <class T>
typename treebasic<T>::nodo* treebasic<T>::somma(nodo* a, nodo* b, nodo *father){
    nodo* x=0;
    if(!a && b)
        x=new nodo(b->info, father, somma(a, b->left, x), somma(a, b->right, x));
    else if(a && !b)
        x=new nodo(a->info, father, somma(a->left, b, x), somma(a->right, b, x));
    else if(a && b)
        x=new nodo((a->info+b->info), father, somma(a->left, b->left, x), somma(a->right, b->right, x));
    return x;
}

template <class T>
typename treebasic<T>::nodo* treebasic<T>::differenza(nodo* a, nodo* b, nodo *father){
    nodo* x=0;
    if(!a && b)
        x=new nodo(((b->info)*(-1)), father, differenza(a, b->left, x), differenza(a, b->right, x));
    else if(a && !b)
        x=new nodo(((a->info)*(-1)), father, differenza(a->left, b, x), differenza(a->right, b, x));
    else if(a && b)
        x=new nodo((a->info-b->info), father, differenza(a->left, b->left, x), differenza(a->right, b->right, x));
    return x;
}

template <class T>
typename treebasic<T>::nodo* treebasic<T>::moltiplicazione(nodo* a, int& k, nodo* father){
    nodo* x=0;
    if(a)
        x=new nodo((a->info*k), father, moltiplicazione(a->left, k, x), moltiplicazione(a->right, k, x));
    return x;
}

template <class T>
typename treebasic<T>::nodo* treebasic<T>::divisione(nodo* a, int& k, nodo* father){
    nodo* x=0;
    if(a)
        x=new nodo((a->info/k), father, divisione(a->left, k, x), divisione(a->right, k, x));
    return x;
}

template <class T>
int treebasic<T>::n_nodes(nodo* n){
    if(!n)
       return 0;
   return 1+n_nodes(n->left)+n_nodes(n->right);
}

template <class T>
void treebasic<T>::nodes(T A[], nodo* n, int &k){
    if(n){
        A[k]=n->info;
        k++;
        nodes(A, n->left, k);
        nodes(A, n->right, k);
    }
}

template <class T>
string treebasic<T>::tree_to_string(nodo * r){
    if(!r)
        return "_";
    return "(*,"+tree_to_string(r->left)+","+tree_to_string(r->right)+")";
}

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
