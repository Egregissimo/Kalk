#ifndef TREEBASIC_H
#define TREEBASIC_H
#include <iostream>
#include <string>
using std::string;
using std::cout;
using std::ostream;
using std::size_t;

template <class T> class treebasic;

template <class T>
ostream& operator<<(ostream&, const treebasic<T>&);

template <class T>
class treebasic{
     friend ostream& operator<< <T>(ostream&, const treebasic<T>&);
protected:
    class nodo{
    public:
        nodo* father, *right, *left;
        T info;
        nodo(): father(0), left(0), right(0) {}
        //ATTENZIONE: nel costruttore c'e' prima r per right e poi l per left
        nodo(const T& val, nodo* f=0, nodo* r=0, nodo* l=0): info(val), father(f), left(l), right(r) {}
        static string stampa(nodo*);
    };
    nodo* root;
private:
    //funzioni costruttore
    nodo* constrRic(T*, int, nodo*, string::iterator, string::iterator, int&);
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
     * Es: l'albero (5,(2,_,(1,_,_)),_) sara' (*,(*,_,(*,_,_)),_)*/
    treebasic(T[], int, string);//viene costruito almeno un nodo
    treebasic(const treebasic& t): root(copia(t.root)) {}// costruttore di copia profondo
    ~treebasic();// distruttore profondo
    /*virtual treebasic* somma(treebasic<T>* b)const=0;
    virtual treebasic* differenza(treebasic<T>* b)const=0;
    virtual treebasic* moltiplicazione(int)const=0;
    virtual treebasic* divisione(int)const=0;
    virtual void add(T)=0;//cerca di tenere  l'albero bilanciato
    virtual void remove(string)=0;//rimuove l'oggetto indicato da un percorso
    virtual void remove(T)=0;//rimuove l'oggetto cercandolo
    virtual T search(string)const=0;
    virtual T search (T)const=0;*/
};

//IMPLEMENTAZIONE FUNZIONI TEMPLATE

template <class T>
string treebasic<T>::nodo::stampa(treebasic<T>::nodo* n){
    if(!(n))
        return "_";
    string s="(";
    s+=n->info;
    s+=",";
    s+=stampa(n->left);
    s+=",";
    s+=stampa(n->right);
    s+=")";
    return s;
}

template <class T>
typename treebasic<T>::nodo* treebasic<T>::copia(treebasic<T>::nodo * n, treebasic<T>::nodo* father){
    if(!n)
        return n;
    nodo* x=new nodo(n->info, father, copia(n->right, x), copia(n->left, x));
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
typename treebasic<T>::nodo* treebasic<T>::constrRic(T*  A, int size, treebasic<T>::nodo* father, string::iterator i, string::iterator end, int& k){
    A=A+k;
    nodo* x=0;
    if(k<size){//se sto creando piu' nodi di quelli presenti nell'array
        T val=*A;
    cout<<val;
        k++;
        if(*i!='(' || *(++i)!='*' || *(++i)!=',')
            cout<<"ERRORE9\n";
        if(*(i+1)=='_' && *(i+2)==',' && *(i+3)=='_' && *(i+4)==')')
            return new nodo(val, father);
        else if(*(i+1)=='_' && *(i+2)==',' && *(i+3)=='('){//solo Td
            i=i+3;// i punta su un '('
            int r=balance(i, end);
            if(r==-1)
                cout<<"ERRORE10\n";
            x=new nodo(val, father, constrRic(A, size, x, i, end, k), 0);
            i=i+r+1;
            if(*i!=')')
                cout<<"ERRORE11\n";
        }
        else if(*(i+1)=='('){// o solo con Ts o con Ts e Td
            int l=balance(++i, end);//i punta si '('
            if(l!=-1 && *(i+l+1)==','){
                if(*(i+l+2)=='_' && *(i+l+3)==')')//solo Ts
                    x=new nodo(val, father, 0, constrRic(A, size, x, i, end, k));
                else if(*(i+l+2)=='('){
                    int r=balance(i+l+2, end);
                    if(r!=-1 && *(i+l+2+r+1)==')')
                        x=new nodo(val, father, constrRic(A, size, x, i+l+2, end, k), constrRic(A, size, x, i, end, k));
                    else
                        cout<<"ERRORE12\n";
                }
                else
                    cout<<"ERRORE13\n";
            }
            else
                cout<<"ERRORE14\n";
        }
        else
            cout<<"ERRORE15\n";
    }
    else
        cout<<"ERRORE16\n";
    return x;
}

template <class T>
treebasic<T>::treebasic(T type[], int size, string s){
    string::iterator i=s.begin();
    string::iterator end=s.end();
    T* A=type;
    int k=1;
    T val=*A;
    
    if(size>0){
        if(*i!='(' || *(++i)!='*' || *(++i)!=','){
            root=0;
            cout<<"ERRORE1\n";
        }
        if(*(i+1)=='_' && *(i+2)==',' && *(i+3)=='_' && *(i+4)==')')
            root=new nodo(val);
        else if(*(i+1)=='_' && *(i+2)==',' && *(i+3)=='('){//solo Td
            i=i+3;// i punta su un '('
            int r=balance(i, end);
            if(r==-1){
                root=0;
                cout<<"ERRORE2\n";
            }
            root=new nodo(val, 0, constrRic(A, size, root, i, end, k), 0);
            /*qui si vede il motivo per cui nel costruttore del nodo è' presente prima r
             * e poi l: nel momento in cui una funzione ha per parametri altre funzioni,
             * queste vengono risolte a partire da destra, e dato che noi vogliamo che
             * per primo venca costruito Ts rispetto a Td, per inserire nell'albero i
             * valori dell'array nell'ordine corretto, Ts viene messo a destra e Td
             * a sinistra*/
            i=i+r+1;
            if(*i!=')'){
                root=0;
                cout<<"ERRORE3\n";
            }
        }
        else if(*(i+1)=='('){// o solo con Ts o con Ts e Td
            int l=balance(++i, end);//i punta si '('
            if(l!=-1 && *(i+l+1)==','){
                if(*(i+l+2)=='_' && *(i+l+3)==')')//solo Ts
                    root=new nodo(val, 0, 0, constrRic(A, size, root, i, end, k));
                else if(*(i+l+2)=='('){
                    int r=balance(i+l+2, end);
                    if(r!=-1 && *(i+l+2+r+1)==')')
                        root=new nodo(val, 0, constrRic(A, size, root, i+l+2, end, k), constrRic(A, size, root, i, end, k));
                    else{
                        root=0;
                        cout<<"ERRORE4\n";
                    }
                }
                else{
                    root=0;
                    cout<<"ERRORE5\n";
                }
            }
            else{
                root=0;
                cout<<"ERRORE6\n";
            }
        }
        else{
            root=0;
            cout<<"ERRORE7\n";
        }
    }
    else{
        root=0;
        cout<<"ERRORE8\n";
    }
    nodo::stampa(root);
}

template <class T>
treebasic<T>::~treebasic(){distruggi(root);}

template <class T>
ostream& operator <<(ostream& os, const treebasic<T>& t){
    if(t.root)
        os<<"("<<t.root->info<<","<<treebasic<T>::nodo::stampa(t.root->left)<<","<<treebasic<T>::nodo::stampa(t.root->right)<<")";
    return os;
}

#endif // TREEBASIC_H




