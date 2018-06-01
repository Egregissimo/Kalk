#include "binarytree.h"

string binarytree::min_path(nodo* x){
    if(!x)
        return "";
    string a=min_path(x->left), b=min_path(x->right), c;
    if(a.size()<=b.size())
        c=a;
    else
        c=b;
    if(x->father){
        if(x->father->left==x)
            c='0'+c;
        else
            c='1'+c;
    }
    return c;
}

tipo* binarytree::removeIt(nodo* y){
    nodo* x=0, *z=0;
    if(y->left && y->right) //se z ha 0 o 1 figli
        z=y->right;
    if(y->left)             //se ho due figli o un figlio sinistro
        x=y->left;
    else                    //se ho 0 o un figlio destro
        x=y->right;

    if(x)
        x->father=y->father;

    if(!y->father)                  //nel caso l'albero contenga l'unico nodo da rimuovere
        root=x;
    else if(y==y->father->left)     //nel caso z non abbia figli cancella il collegamento
        y->father->left=x;
    else                            //in alternativa collega i vari nodi senza z
        y->father->right=x;

    if(z){
        nodo* t=root;
        string path=min_path(t);
        string::iterator begin=path.begin(), end=path.end();
        for(; begin!=end; begin++){
            if(*begin=='0')
                t=t->left;
            else
                t=t->right;
        }
        if(!t->left)
            t->left=z;
        else
            t->right=z;
    }

    tipo* a=y->info;
    return a;
}

//PRE={x non e' un puntatore nullo}     /* PRE={ l'albero è un albero binario corretto } */
binarytreebasic::nodo* binarytree::searchIt(nodo * x, tipo* a){
    if(!x)                              // se l'albero è vuoto e se non trovo il nodo return 0
        return 0;
    if(x->info->uguale(a))              // se lo trovo ritorno quel puntatore
        return x;

    nodo* z = searchIt(x->left, a);     // cerco prima a sinistra
    if(!z)                              // se non lo trovo cerco a destra
        z = searchIt(x->right, a);
    return z;                           // se lo trovo ritorno quel puntatore altrimenti ritorna 0 dalle chiamate ricorsive
}

void binarytree::add(tipo * a){
    if(!a)
        throw point_error("binarytree");
    nodo* x=root;
    string path=min_path(x);
    string::iterator begin=path.begin(), end=path.end();
    for(; begin!=end; begin++){
        if(*begin=='0')
            x=x->left;
        else
            x=x->right;
    }
    if(!x)
        x=new nodo(a, x);
    else if(!x->left)
        x->left=new nodo(a, x);
    else
        x->right=new nodo(a, x);
}

tipo* binarytree::remove(string s){
    if(!controlla_percorso(s))
        throw path_error("binarytree");
    nodo* x=root;
    string::iterator begin=s.begin(), end=s.end();
    for(; begin!=end; begin++){
        if(*begin=='0')
            x=x->left;
        else
            x=x->right;
    }
    if(x){
        return removeIt(x);
        delete x;
    }
    cout<<"Elemento non trovato\n";
    return 0;
}

tipo* binarytree::remove(tipo* a){
    if(!a)
        throw point_error("binarytree");
    nodo* x=root;
    if(x)
        x=searchIt(x, a);
    if(x){
        return removeIt(x);
        delete x;
    }
    cout<<"Elemento non trovato\n";
    return 0;
}

tipo* binarytree::search(tipo* a)const{
    if(!a)
        throw point_error("binarytree");
    nodo* x=root;
    if(x)
        x=searchIt(x, a);
    if(x)
        return x->info;
    cout<<"Elemento non trovato\n";
    return 0;
}

binarytree& binarytree::operator *(int p){
    binarytreebasic::nodo* x=moltiplicazione(this->root, p);
    string s=binarytreebasic::tree_to_string(x);
    vector<tipo*> A=nodes(x);
    binarytree* c=new binarytree(A, s);
    return *c;
}

binarytree& binarytree::operator /(int p){
    binarytreebasic::nodo* x=divisione(this->root, p);
    string s=binarytreebasic::tree_to_string(x);
    vector<tipo*> A=nodes(x);
    binarytree* c=new binarytree(A, s);
    return *c;
}

ostream& operator<<(ostream& os, const binarytree& t){
    if(t.root)
        os<<binarytreebasic::nodo::stampa(t.root);
    return os;
}

string to_string(const binarytree& t){
    if(t.root)
        return  binarytreebasic::nodo::stampa(t.root);
    return "";
}

binarytree& operator+(const binarytree& a, const binarytree& b){
    binarytreebasic::nodo* x=binarytreebasic::somma(a.root, b.root);
    string s=binarytreebasic::tree_to_string(x);
    vector<tipo*> A=binarytreebasic::nodes(x);
    binarytree* c=new binarytree(A, s);
    return *c;
}

binarytree& operator -(const binarytree& a, const binarytree &b){
    binarytreebasic::nodo* x=binarytreebasic::differenza(a.root, b.root);
    string s=binarytreebasic::tree_to_string(x);
    vector<tipo*> A=binarytreebasic::nodes(x);
    binarytree* c=new binarytree(A, s);
    return *c;
}
