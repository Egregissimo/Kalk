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

template <class T>
treesearch<T>& operator *(const treesearch<T>&, int);

template <class T>
treesearch<T>& operator /(const treesearch<T>&, int);

/*ricordarsi che per invocare un campo dati bisogna fare this->"campo dati"
Non serve ridefinire costruttore di coppia, distruttore o assegnazione dato
che questi alberi derivati non hanno campi dati. Ogni tipo T che usera' questa
classe dovra' implementare l'operatore '<='*/
template <class T>
class treesearch: public treebasic<T>{
    friend ostream& operator<< <T>(ostream&, const treesearch<T>&);
    friend string to_string<T>(const treesearch&);
    friend treesearch& operator + <T>(const treesearch&, const treesearch&);
    friend treesearch& operator - <T>(const treesearch&, const treesearch&);
    friend treesearch<T>& operator * <T>(const treesearch&, int);
    friend treesearch<T>& operator / <T>(const treesearch&, int);
private:
    int num_t(string::iterator, int&)const;
    void merge(T[], int, int, int)const;
    void merge_sort(T[], int, int)const;
    void ordinaRic(T[], T[], int, string::iterator, int&)const;
    T* ordina(T[], int, string &)const;
    string crea_stringa(int) const;

    typename treebasic<T>::nodo* sommaRic(typename treebasic<T>::nodo*, typename treebasic<T>::nodo*, typename treebasic<T>::nodo* =0);
public:
    treesearch(): treebasic<T>() {}
    treesearch(T type[], int size, string& s): treebasic<T>(ordina(type, size, s), size, s) {}
    void add(T);//cerca di tenere  l'albero bilanciato
    void remove(string);//rimuove l'oggetto indicato da un percorso
    void remove(T);//rimuove l'oggetto cercandolo
    T search(string)const;
    T search (T)const;

    treesearch& balance() const;
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

//PRE=(entrambi gli alberi non sono vuoti)
template <class T>
typename treebasic<T>::nodo* sommaRic(typename treebasic<T>::nodo* a, typename treebasic<T>::nodo* b, typename treebasic<T>::nodo* father){
    typename treebasic<T>::nodo* x=0;
    if(!a && b)
         typename treebasic<T>::nodo x=new typename treebasic<T>::nodo(b->info, father, sommaRic(a, b->left, x), sommaRic(a, b->right, x));
    else if(a && !b)
        typename treebasic<T>::nodo x=new typename treebasic<T>::nodo(a->info, father, sommaRic(a->left, b, x), sommaRic(a->right, b, x));
    else if(!a && !b)
        return 0;
    else
        typename treebasic<T>::nodo x=new typename treebasic<T>::nodo((a->info+b->info), father, sommaRic(a->left, b->left, x), sommaRic(a->right, b->right, x));
    return x;
}

template <class T>
void treesearch<T>::add(T a){}

template <class T>
void treesearch<T>::remove(string s){}

template <class T>
void treesearch<T>::remove(T a){}

template <class T>
T treesearch<T>::search(string s)const{}

template <class T>
T treesearch<T>::search(T a)const{}

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
treesearch<T>& operator *(const treesearch<T>& t, int p){
    typename treebasic<T>::nodo* x=treebasic<T>::moltiplicazione(t.root, p);
    string s=treebasic<T>::tree_to_string(x);
    int n=treebasic<T>::n_nodes(x);
    T A[n];
    int k=0;
    treebasic<T>::nodes(A, x, k);
    treesearch<T>* c=new treesearch<T>(A, n, s);
    return *c;
}

template <class T>
treesearch<T>& operator /(const treesearch<T>& t, int p){
    typename treebasic<T>::nodo* x=treebasic<T>::divisione(t.root, p);
    string s=treebasic<T>::tree_to_string(x);
    int n=treebasic<T>::n_nodes(x);
    T A[n];
    int k=0;
    treebasic<T>::nodes(A, x, k);
    treesearch<T>* c=new treesearch<T>(A, n, s);
    return *c;
}

#endif // TREESEARCH_H
