#ifndef TREESEARCH_H
#define TREESEARCH_H
#include "treebasic.h"

template <class T> class treesearch;

template <class T>
ostream& operator<< (ostream&, const treesearch<T>&);

template <class T>
string to_string(const treesearch<T>&);

template <class T>
treesearch<T>& operator +(const treesearch<T>&, const treesearch<T>&);

template <class T>
treesearch<T>& operator -(const treesearch<T>&, const treesearch<T>&);

/*ricordarsi che per invocare un campo dati bisogna fare this->"campo dati"
Non serve ridefinire costruttore di coppia, distruttore o assegnazione dato
che questi alberi derivati non hanno campi dati. Ogni tipo T che usera' questa
classe dovra' implementare l'operatore '<=' e '<'*/
template <class T>
class treesearch: public treebasic<T>{
    friend ostream& operator<< <T>(ostream&, const treesearch<T>&);
    friend string to_string<T>(const treesearch&);
    friend treesearch& operator + <T>(const treesearch&, const treesearch&);
    friend treesearch& operator - <T>(const treesearch&, const treesearch&);
private:
    //stessa funzione di balance_brackets, ma in piu' conta i nodi all'interno della stringa
    int num_t(string::iterator, int&)const;
    //funzioni per effettuare il merge-sort in O(nlogn)
    void merge(T[], int, int, int)const;
    void merge_sort(T[], int, int)const;
    //funzione ricorsiva per creare l'albero di ricerca. Prende in input il primo array per inserirne
    //i valori ordinati nel secondo array da usare nel costruttore
    void ordinaRic(T[], T[], int, string::iterator, int&)const;
    //invoca ordinaRic per ritornare l'array ordinato per l'albero di ricerca
    T* ordina(T[], int, string &)const;
    //crea una stringa per un albero bilanciato di ricerca di n nodi
    string crea_stringa(int) const;
    typename treebasic<T>::nodo* minimum(typename treebasic<T>::nodo*)const;//trova il minimo dell'albero
    typename treebasic<T>::nodo* successor(typename treebasic<T>::nodo*)const;//trova il successore del nodo dato in input
    T removeIt(typename treebasic<T>::nodo*);//rimuove in modo iterativo il nodo indicato mantenedo leproprieta' del'albero di ricerca
public:
    treesearch(): treebasic<T>() {}
    treesearch(T type[], int size, string& s): treebasic<T>(ordina(type, size, s), size, s) {}
    virtual void add(const T);//cerca di tenere  l'albero bilanciato
    virtual T remove(string);//rimuove l'oggetto indicato da un percorso
    virtual T remove(const T);//rimuove l'oggetto cercandolo
    virtual T search(string)const;//trova l'oggetto indicato da un percorso
    virtual T search (const T)const;//trova l'oggetto indicato

    treesearch& balance() const;//restituisce un albero di ricerca bilanciato
    treesearch<T>& operator *(int);
    treesearch<T>& operator /(int);
};

//PRE={la stringa è corretta}
template <class T>
int treesearch<T>::num_t(string::iterator i, int& count) const{
    int k=1, s=1;
    size_t X[2];
    if(*i=='_'){
        return 0;
    }
    else{
        for(; k>0; s++)
            if(*(i+s)=='(')
                k++;
            else if(*(i+s)==')')
                k--;
            else if(*(i+s)=='*')
                count++;

        return s-1;
    }
}
//POST={X[0]=posizione di ')' che bilancia la '(' in i; X[1]= num nodi del sottoalbero}

template <class T>
void treesearch<T>::merge(T A[], int l, int q, int r) const{
    int i, j, k;
    int n1=q-l+1;
    int n2=r-q;
     T L[n1], R[n2];

    for (i=0; i<n1; i++)
        L[i]=A[l+i];
    for (j=0; j<n2; j++)
        R[j]=A[q+1+j];
    i=0;
    j=0;
    k=l;
    while(i<n1 && j<n2){
        if(L[i]<=R[j]){
            A[k]=L[i];
            i++;
        }
        else{
            A[k]=R[j];
            j++;
        }
        k++;
    } 
    while(i<n1){
        A[k]=L[i];
        i++;
        k++;
    }
    while(j<n2){
        A[k]=R[j];
        j++;
        k++;
    }
}

template <class T>
void treesearch<T>::merge_sort(T A[], int l, int r)const{
    if (l<r){
        int q=l+(r-l)/2;
 
        merge_sort(A, l, q);
        merge_sort(A, q+1, r);
 
        merge(A, l, q, r);
    }
}

template <class T>
void treesearch<T>::ordinaRic(T A[], T B[], int size, string::iterator begin, int& k)const{
    if(size>1){
        begin+=3;
        int q=0;
        int l=num_t(begin, q);
        B[k]=A[q];
        T LEFT[q];
        for(int i=0; i<q; i++)
            LEFT[i]=A[i];
        T RIGHT[size-q-1];
        for(int i=0; i<size-q-1; i++)
            RIGHT[i]=A[q+1+i];
        k++;
        ordinaRic(LEFT, B, q, begin, k);
        ordinaRic(RIGHT, B, size-q-1, begin+l+2, k);
    }
    else if(size==1){
        B[k]=A[0];
        k++;
    }
}

template <class T>
T* treesearch<T>::ordina(T t[], int size, string& s) const{
    if(treebasic<T>::parser(s.begin(), s.end())){
        T A[size];
        T* B=new T[size];
        for(int i=0; i<size; i++)
            A[i]=t[i];
        merge_sort(A, 0, size-1);
        int k=0;
        ordinaRic(A, B, size, s.begin(), k);
        return B;
    }
    else
        //throw(0);
        cout<<"ERRORE8\n";
}

template <class T>
string treesearch<T>::crea_stringa(int n) const{
    if(!n)
        return "_";
    int q=(n+1)/2;
    return "(*,"+crea_stringa(q-1)+","+crea_stringa(n-q)+")";
}

template <class T>
typename treebasic<T>::nodo* treesearch<T>::minimum(typename treebasic<T>::nodo* r) const{
    if(!r)
        return 0;
    while(r->left)
        r=r->left;
    return r;
}

template <class T>
typename treebasic<T>::nodo* treesearch<T>::successor(typename treebasic<T>::nodo* r) const{
    if(!r)
        return 0;
    if(r->right)
        return minimum(r->right);
    //altrimenti e' il primo padre sinistro
    typename treebasic<T>::nodo* y=r->father;
    while(y && r==y->right){
        r=y;
        y=y->father;
    }
    return y;
}

//PRE=(x e t non sono nulli)
template <class T>
T treesearch<T>::removeIt(typename treebasic<T>::nodo* z){
    typename treebasic<T>::nodo* x=0, *y=0;
    if(!z->left || !z->right)//se z ha 0 o 1 figli
        y=z;
    else//z ha 2 figli
        y=successor(z);
    if(y->left)//se ho due figli o un figlio sinistro
        x=y->left;
    else//se ho 0 o un figlio destro
        x=y->right;
    if(x)
        x->father=y->father;
    if(!y->father)//nel caso l'albero contenga l'unico nodo da rimuovere
        this->root=x;
    else if(y==y->father->left)//nel caso z non abbia figli cancella il collegamento
        y->father->left=x;
    else//in alternativa collega i vari nodi senza z
        y->father->right=x;
    if(x!=z)
        z->info=y->info;
    T a=z->info;
    return a;
}

template <class T>
void treesearch<T>::add(const T a){
    //addRic(this->root, a);
    typename treebasic<T>::nodo *y=0, *x=this->root;
    while(x){
        y=x;
        if(a<x->info)
            x=x->left;
        else
            x=x->right;
    }
    if(!y)
        this->root=new typename treebasic<T>::nodo(a);
    else if(a<y->info)
        y->left=new typename treebasic<T>::nodo(a, y);
    else
        y->right=new typename treebasic<T>::nodo(a, y);
}

template <class T>
T treesearch<T>::remove(string s){
    typename treebasic<T>::nodo* x=this->root;
    if(!treebasic<T>::controlla_percorso(s))
        cout<<"ERRORE20\n";
        //trow(0);
    string::iterator begin=s.begin(), end=s.end();
    for(; x && begin!=end; begin++){
        if(*begin=='0')
            x=x->left;
        else
            x=x->right;
    }
    if(x)
        return removeIt(x);
    cout<<"Elemento non trovato\n";
    return 0;
}

template <class T>
T treesearch<T>::remove(const T a){
    typename treebasic<T>::nodo* x=this->root;
    while(x && x->info!=a)
        if(a<x->info)
            x=x->left;
        else
            x=x->right;
    if(x)
        return removeIt(x);
    cout<<"Elemento non trovato";
    return 0;
}

template <class T>
T treesearch<T>::search(string s)const{
    typename treebasic<T>::nodo* x=this->root;
    if(!treebasic<T>::controlla_percorso(s) || !x)
        cout<<"ERRORE20\n";
        //trow(0);
    string::iterator begin=s.begin(), end=s.end();
    for(; x && begin!=end; begin++)
        if(*begin=='0')
            x=x->left;
        else
            x=x->right;
    if(x)
        return x->info;
    cout<<"Elemento non trovato\n";
    return 0;
}

template <class T>
T treesearch<T>::search(const T a)const{
    typename treebasic<T>::nodo* x=this->root;
    if(!x)
        cout<<"ERRORE21\n";
        //throw(0);
    while(x && x->info!=a)
        if(a<x->info)
            x=x->left;
        else
            x=x->right;
    if(x)
        return x->info;
    cout<<"Elemento non trovato\n";
    return 0;
}

template <class T>
treesearch<T>& treesearch<T>::balance() const{
    int n=treebasic<T>::n_nodes(this->root);
    T A[n];
    int k=0;
    treebasic<T>::nodes(A, this->root, k);
    string s=crea_stringa(n);
    treesearch<T>* a=new treesearch<T>(A, n, s);
    return *a;
}

template <class T>
ostream& operator<<(ostream& os, const treesearch<T>& t){
    if(t.root)
        os<<treebasic<T>::nodo::stampa(t.root);
    return os;
}

template <class T>
string to_string(const treesearch<T>& t){
    if(t.root)
        return  treebasic<T>::nodo::stampa(t.root);
    return "";
}

template <class T>
treesearch<T>& operator+(const treesearch<T>& a, const treesearch<T>& b){
    typename treebasic<T>::nodo* x=treebasic<T>::somma(a.root, b.root);
    string s=treebasic<T>::tree_to_string(x);
    int n=treebasic<T>::n_nodes(x);
    T A[n];
    int k=0;
    treebasic<T>::nodes(A, x, k);
    treesearch<T>* c=new treesearch<T>(A, n, s);
    return *c;
}

template <class T>
treesearch<T> &operator -(const treesearch<T> &a, const treesearch<T> &b){
    typename treebasic<T>::nodo* x=treebasic<T>::differenza(a.root, b.root);
    string s=treebasic<T>::tree_to_string(x);
    int n=treebasic<T>::n_nodes(x);
    T A[n];
    int k=0;
    treebasic<T>::nodes(A, x, k);
    treesearch<T>* c=new treesearch<T>(A, n, s);
    return *c;
}

template <class T>
treesearch<T>& treesearch<T>::operator *(int p){
    typename treebasic<T>::nodo* x=treebasic<T>::moltiplicazione(this->root, p);
    string s=treebasic<T>::tree_to_string(x);
    int n=treebasic<T>::n_nodes(x);
    T A[n];
    int k=0;
    treebasic<T>::nodes(A, x, k);
    treesearch<T>* c=new treesearch<T>(A, n, s);
    return *c;
}

template <class T>
treesearch<T>& treesearch<T>::operator /(int p){
    typename treebasic<T>::nodo* x=treebasic<T>::divisione(this->root, p);
    string s=treebasic<T>::tree_to_string(x);
    int n=treebasic<T>::n_nodes(x);
    T A[n];
    int k=0;
    treebasic<T>::nodes(A, x, k);
    treesearch<T>* c=new treesearch<T>(A, n, s);
    return *c;
}

#endif // TREESEARCH_H
