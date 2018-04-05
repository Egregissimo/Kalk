/*#include "treebasic.h"

template <class T>
typename treebasic<T>::nodo* treebasic<T>::copia(treebasic<T>::nodo * n, treebasic<T>::nodo* father){
    if(!n)
        return n;
    nodo* x=new nodo(n->info, father, copia(n->right, x), copia(n->left, x));
    return x;
}

template <class T>
void treebasic<T>::distruggi(nodo* n){
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
        return s;
    return -1;
}
/*POST={ritorna -1 se le parentesi non sono ben bilanciate, altrimenti ritorna il numero
 * di passi fino alla posizione della ')' che chiude la parentesi della PRE}*/

/*template <class T>
typename treebasic<T>::nodo* treebasic<T>::constrRic(T* &A, int size, treebasic<T>::nodo* father, string::iterator i, string::iterator end, int k){
    A=A+1;
    nodo* x=0;
    if(k<size){//se sto creando piu' nodi di quelli presenti nell'array
        if(*i=!'(' && *(++i)=!'*' && *(++i)=!',')
            throw(0);
        if(*(i+1)=='_' && *(i+2)==',' && *(i+3)=='_' && *(i+4)==')')
            return new nodo(*A, father);
        else if(*(i+1)=='_' && *(i+2)==',' && *(i+3)=='('){//solo Td
            i=i+3;// i punta su un '('
            int r=balance(i, end);
            if(r==-1)
                throw(0);
            x=new nodo(*A, father, constrRic(A, size, x, i, end, k+1), 0);
            i=i+r+1;
            if(*i=!')')
                throw(0);
        }
        else if(*(i+1)=='('){// o solo con Ts o con Ts e Td
            int l=balance(++i, end);//i punta si '('
            if(l=!-1 && *(i+l+1)==','){
                if(*(i+l+2)=='_' && *(i+l+3)==')')//solo Ts
                    x=new nodo(*A, father, 0, constrRic(A, size, x, i, end, k+1));
                else if(*(i+l+2)=='('){
                    int r=balance(i+l+2, end);
                    if(r=!-1 && *(i+l+2+r+1)==')')
                        x=new nodo(*A, father, constrRic(A, size, x, i+l+2, end), constrRic(A, size, x, i, end));
                    else
                        throw(0);
                }
                else
                    throw(0);
            }
            else
                throw(0);
        }
        else
            throw(0);
    }
    else
        throw(0);
    return x;
}

template <class T>
treebasic<T>::treebasic(T* type, int size, string s){
    string::iterator i=s.begin();
    string::iterator end=s.end();
    T* A=type;
    if(size>0){
        if(*i=!'(' && *(++i)=!'*' && *(++i)=!',')
            throw(0);
        if(*(i+1)=='_' && *(i+2)==',' && *(i+3)=='_' && *(i+4)==')')
            root=new nodo(*A);
        else if(*(i+1)=='_' && *(i+2)==',' && *(i+3)=='('){//solo Td
            i=i+3;// i punta su un '('
            int r=balance(i, end);
            if(r==-1)
                throw(0);
            root=new nodo(*A, 0, constrRic(A, size, root, i, end), 0);
            /*qui si vede il motivo per cui nel costruttore del nodo è' presente prima r
             * e poi l: nel momento in cui una funzione ha per parametri altre funzioni,
             * queste vengono risolte a partire da destra, e dato che noi vogliamo che
             * per primo venca costruito Ts rispetto a Td, per inserire nell'albero i
             * valori dell'array nell'ordine corretto, Ts viene messo a destra e Td
             * a sinistra*/
            /*i=i+r+1;
            if(*i=!')')
                throw(0);
        }
        else if(*(i+1)=='('){// o solo con Ts o con Ts e Td
            int l=balance(++i, end);//i punta si '('
            if(l=!-1 && *(i+l+1)==','){
                if(*(i+l+2)=='_' && *(i+l+3)==')')//solo Ts
                    root=new nodo(*A, 0, 0, constrRic(A, size, root, i, end));
                else if(*(i+l+2)=='('){
                    int r=balance(i+l+2, end);
                    if(r=!-1 && *(i+l+2+r+1)==')')
                        root=new nodo(*A, 0, constrRic(A, size, root, i+l+2, end), constrRic(A, size, root, i, end));
                    else
                        throw(0);
                }
                else
                    throw(0);
            }
            else
                throw(0);
        }
        else
            throw(0);
    }
    else
        throw(0);
}

template <class T>
treebasic<T>::~treebasic(){distruggi(root);}

template <class T>
ostream& operator <<(ostream& os, const treebasic<T>& t){
    if(t.root)
        os<<"("<<t.root->info<<","<<t.root->left<<","<<t.root->right<<")";
    return os;
}

template <class T>
ostream& operator <<(ostream& os, const typename treebasic<T>::nodo* n){
    if(!n)
        os<<"_";
    os<<"("<<n->info<<","<<n->left<<","<<n->right<<")";
    return os;
}*/
