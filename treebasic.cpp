#include "treebasic.h"

string treebasic::nodo::stampa(treebasic::nodo* n){
    if(!(n))
        return "_";
    return "('"+n->info->to_stringa()+"',"+stampa(n->left)+","+stampa(n->right)+")";
}

bool treebasic::parser(string::iterator begin, string::iterator end){
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

//PRE={la stringa e' corretta}
int treebasic::balance_brackets(string::iterator i, string::iterator end){
    if(*i=='_')
        return 0;
    int k=1, s=1;
    if(end==i)//entra se la stringa è corretta e non dev'essere controllata
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

//PRE={la stringa e' corretta e begin punta a '('}
unsigned int treebasic::n_nodes_stringa(string::iterator begin){
    int count=0, id=1;
    if(*begin=='_')
        return count;
    for(int i=1; id; i++){
        if(*(begin+i)=='*')
            count++;
        else if(*(begin+i)=='(')
            id++;
        else if(*(begin+i)==')')
            id--;
    }
    //dato che la stringa è corretta in for finira'
    return count;
}

treebasic::nodo* treebasic::somma(nodo* a, nodo* b, nodo *father){
    nodo* x=0;
    if(!a && b){
        x=new nodo(b->info, father);
        x->left=somma(a, b->left, x);
        x->right=somma(a, b->right, x);
    }
    else if(a && !b){
        x=new nodo(a->info, father);
        x->left=somma(a->left, b, x);
        x->right=somma(a->right, b, x);
    }
    else if(a && b && !a->left && a->right && !b->left && !b->right && ((a->info->divisione(-1))==b->info))
        return x;
    else if(a && b){
        x=new nodo(((a->info)->somma(b->info)), father);
        x->left=somma(a->left, b->left, x);
        x->right=somma(a->right, b->right, x);
    }
    return x;
}

treebasic::nodo* treebasic::differenza(nodo* a, nodo* b, nodo *father){
    nodo* x=0;
    if(!a && b){
        x=new nodo(((b->info)->moltiplicazione(-1)), father);
        x->left=differenza(a, b->left, x);
        x->right=differenza(a, b->right, x);
    }
    else if(a && !b){
        x=new nodo(a->info, father);
        x->left=differenza(a->left, b, x);
        x->right=differenza(a->right, b, x);
    }
    else if(a && b && !a->left && a->right && !b->left && !b->right && (a->info==b->info))
        return x;
    else if(a && b){
        x=new nodo(((a->info)->differenza(b->info)), father);
        x->left=differenza(a->left, b->left, x);
        x->right=differenza(a->right, b->right, x);
    }
    return x;
}

treebasic::nodo* treebasic::moltiplicazione(nodo* a, int k, nodo* father){
    nodo* x=0;
    if(a){
        x=new nodo(((a->info)->moltiplicazione(k)), father);
        x->left=moltiplicazione(a->left, k, x);
        x->right=moltiplicazione(a->right, k, x);
    }
    return x;
}

treebasic::nodo* treebasic::divisione(nodo* a, int k, nodo* father){
    nodo* x=0;
    if(a){
        x=new nodo(((a->info)->divisione(k)), father);
        x->left=divisione(a->left, k, x);
        x->right=divisione(a->right, k, x);
    }
    return x;
}

int treebasic::n_nodes(nodo* n){
    if(!n)
       return 0;
   return 1+n_nodes(n->left)+n_nodes(n->right);
}

vector<tipo*> treebasic::nodes(nodo* n){
    vector<tipo*> a, b;
    if(!n)
        return a;
    if(!n->left && !n->right){
        a.push_back(n->info);
        return a;
    }
    vector<tipo*> c;
    c.push_back(n->info);
    a=nodes(n->left);
    b=nodes(n->right);
    a.insert(a.end(), b.begin(), b.end());
    c.insert(c.end(), a.begin(), a.end());
    return c;
}

bool treebasic::controlla_percorso(string &s){
    string::iterator begin=s.begin(), end=s.end();
    for(; begin!=end; begin++)
        if(*begin!='0' && *begin!='1')
            return false;
    return true;
}

bool treebasic::controlla_input(vector<tipo*>& v, string &s){
    vector<tipo*>::iterator begin=v.begin(), end=v.end();
    int size=s.size();
    for(; begin!=end; begin++)
        if(typeid(**v.begin())!=typeid(**begin))
            return false;
    return parser(s.begin(), s.end()) && (v.size()==n_nodes_stringa(s.begin())) && (size==0 || size==5 || size%6==1);
}

string treebasic::tree_to_string(nodo * r){
    if(!r)
        return "_";
    return "(*,"+tree_to_string(r->left)+","+tree_to_string(r->right)+")";
}


treebasic::nodo* treebasic::copia(nodo * n, nodo* father) const{
    if(!n)
        return 0;
    nodo* x=new nodo(n->info, father);
    x->left=copia(n->left, x);
    x->right=copia(n->right, x);
    return x;
}

void treebasic::distruggi(treebasic::nodo* n){
    if(n){
        distruggi(n->left);
        distruggi(n->right);
        delete n;
    }
}

//PRE=(la stringa s e' corretta e l'albero contiene almeno un nodo, percio' il caso limite sara' "(*, _,_)")
treebasic::nodo* treebasic::constrRic(string::iterator i, vector<tipo*>::iterator& A, nodo* father){
    tipo* val=*A;
    A++;
    i+=3;
    nodo* x=new nodo(val, father);
    int left=balance_brackets(i, i);
    int right=balance_brackets(i+left+2, i+left+2);
    if(!left && !right)//caso base
        return x;
    if(!left && right)
        x->right=constrRic(i+left+2, A, x);
    else if(left && !right)
        x->left=constrRic(i, A, x);
    else{
        x->left=constrRic(i, A, x);
        x->right=constrRic(i+left+2, A, x);
    }
    return x;
}

treebasic::treebasic(vector<tipo*> type, string& s) throw(input_error){
    if(controlla_input(type, s)){
        //int k=0;//indice valore da analizzare nell'array
        //constrRic costruisce l'albero prendendo in input l'array di valori,
        //la sua lunghezza, un iteratore iniziale e finale della stringa, l'indice del
        //valore gia' analizzato passasto per riferimento e il valore del noto padre(che inizialmente e' 0)
        vector<tipo*>::iterator it=type.begin();
        root=constrRic(s.begin(), it);
    }
    else
        throw input_error();
}

treebasic::~treebasic(){if(root) distruggi(root);}

treebasic& treebasic::operator=(const treebasic& t){
    if(this->root!=t.root){
        delete root;
        root=copia(t.root);
    }
    return *this;
}

tipo* treebasic::cerca(string s)const throw(path_error){
    nodo* x=this->root;
    if(!controlla_percorso(s) || !x)
        throw path_error();
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

string treebasic::struttura_tree()const{
    return tree_to_string(this->root);
}

ostream& operator <<(ostream& os, const treebasic& t){
    if(t.root)
        os<<treebasic::nodo::stampa(t.root);
    return os;
}

string to_string(const treebasic &t){
    if(t.root)
        return  treebasic::nodo::stampa(t.root);
    return "";
}

//throw(0) i dati inseriti in input non sono corretti
//throw(1) il percorso inserito non e' corretto
