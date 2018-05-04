#include "treesearch.h"

void treesearch::merge(vector<tipo*>&left, vector<tipo*>& right, vector<tipo*>& bars){
    int nL=left.size();
    int nR=right.size();
    int i=0, j=0, k=0;

    while(j<nL && k<nR) {
        if(left[j]->min(right[k])){
            bars[i]=left[j];
            j++;
        }
        else{
            bars[i]=right[k];
            k++;
        }
        i++;
    }
    while(j<nL){
        bars[i]=left[j];
        j++; i++;
    }
    while(k<nR){
        bars[i]=right[k];
        k++;
        i++;
    }
}

void treesearch::merge_sort(vector<tipo*>& bar){
    if(bar.size()<=1) return;

    unsigned int mid=bar.size()/ 2;
    vector<tipo*> left;
    vector<tipo*> right;

    for(size_t j=0; j<mid; j++)
        left.push_back(bar[j]);
    for(size_t j=0; j<(bar.size())-mid; j++)
        right.push_back(bar[mid+j]);

    merge_sort(left);
    merge_sort(right);
    merge(left, right, bar);
}

//PRE={gli input sono corretti}
void treesearch::ordinaRic(vector<tipo*>& A, string::iterator begin, vector<tipo*>::iterator& it)const{
    int size=A.size();
    if(size>1){
        begin+=3;
        int q=n_nodes_stringa(begin);
        int l=balance_brackets(begin, begin);
        *it=A[q];
        vector<tipo*> LEFT, RIGHT;
        for(int i=0; i<q; i++)
            LEFT.push_back(A[i]);
        for(int i=0; i<size-q-1; i++)
            RIGHT.push_back(A[q+1+i]);
        it++;
        ordinaRic(LEFT, begin, it);
        ordinaRic(RIGHT, begin+l+2, it);
    }
    else if(size==1){
        *it=A[0];
        it++;
    }
}

vector<tipo*> treesearch::ordina(vector<tipo*> t, string& s) const{
    if(controlla_input(t, s)){
        vector<tipo*> A=t;
        vector<tipo*> B(t.size());
        vector<tipo*>::iterator it=B.begin();
        merge_sort(A);
        ordinaRic(A, s.begin(), it);
        return B;
    }
    else
        //throw(0);
        cout<<"ERRORE8\n";
}

string treesearch::crea_stringa(int n) const{
    if(!n)
        return "_";
    int q=(n+1)/2;
    return "(*,"+crea_stringa(q-1)+","+crea_stringa(n-q)+")";
}

treebasic::nodo* treesearch::minimum(nodo* r) const{
    if(!r)
        return 0;
    while(r->left)
        r=r->left;
    return r;
}

treebasic::nodo* treesearch::successor(nodo* r) const{
    if(!r)
        return 0;
    if(r->right)
        return minimum(r->right);
    //altrimenti e' il primo padre sinistro
    nodo* y=r->father;
    while(y && r==y->right){
        r=y;
        y=y->father;
    }
    return y;
}

//PRE=(x e t non sono nulli)
tipo* treesearch::removeIt(nodo* z){
    nodo* x=0, *y=0;
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
    tipo* a=z->info;
    return a;
}

void treesearch::add(tipo* a){
    //addRic(this->root, a);
    nodo *y=0, *x=this->root;
    while(x){
        y=x;
        if(a->min(x->info))
            x=x->left;
        else
            x=x->right;
    }
    if(!y)
        this->root=new nodo(a);
    else if(a->min(y->info))
        y->left=new nodo(a, y);
    else
        y->right=new nodo(a, y);
}

tipo* treesearch::remove(string s){
    nodo* x=this->root;
    if(!controlla_percorso(s))
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

tipo* treesearch::remove(tipo* a){
    nodo* x=this->root;
    while(x && !(x->info->uguale(a)))
        if(a->min(x->info))
            x=x->left;
        else
            x=x->right;
    if(x)
        return removeIt(x);
    cout<<"Elemento non trovato";
    return 0;
}

tipo* treesearch::search(string s)const{
    nodo* x=this->root;
    if(!controlla_percorso(s) || !x)
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

tipo* treesearch::search(tipo* a)const{
    nodo* x=this->root;
    if(!x)
        cout<<"ERRORE21\n";
        //throw(0);
    while(x && !(x->info->uguale(a)))
        if(a->min(x->info))
            x=x->left;
        else
            x=x->right;
    if(x)
        return x->info;
    cout<<"Elemento non trovato\n";
    return 0;
}

treesearch treesearch::balance() const{
    int n=n_nodes(this->root);
    vector<tipo*> A=nodes(this->root);
    string s=crea_stringa(n);
    treesearch a(A, s);
    return a;
}

ostream& operator<<(ostream& os, const treesearch& t){
    if(t.root)
        os<<treebasic::nodo::stampa(t.root);
    return os;
}

string to_string(const treesearch& t){
    if(t.root)
        return  treebasic::nodo::stampa(t.root);
    return "";
}

treesearch& operator+(const treesearch& a, const treesearch& b){
    treebasic::nodo* x=treebasic::somma(a.root, b.root);
    string s=treebasic::tree_to_string(x);
    vector<tipo*> A=treebasic::nodes(x);
    treesearch* c=new treesearch(A, s);
    return *c;
}

treesearch &operator -(const treesearch &a, const treesearch &b){
    treebasic::nodo* x=treebasic::differenza(a.root, b.root);
    string s=treebasic::tree_to_string(x);
    vector<tipo*> A=treebasic::nodes(x);
    treesearch* c=new treesearch(A, s);
    return *c;
}

treesearch treesearch::operator *(int p){
    treebasic::nodo* x=treebasic::moltiplicazione(this->root, p);
    string s=treebasic::tree_to_string(x);
    vector<tipo*> A=treebasic::nodes(x);
    treesearch c(A, s);
    return c;
}

treesearch treesearch::operator /(int p){
    treebasic::nodo* x=treebasic::divisione(this->root, p);
    string s=treebasic::tree_to_string(x);
    vector<tipo*> A=treebasic::nodes(x);
    treesearch c(A, s);
    return c;
}
