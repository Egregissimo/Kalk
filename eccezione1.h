#ifndef ECCEZIONE1_H
#define ECCEZIONE1_H
#include <string>
#include <stdexcept>
using std::string;
using std::runtime_error;

//Ogni errore possiede un id: la prima cifra indica la classe a cui
//appartiene l'errore, le altre cifre indicano l'errore vero e proprio.
//Ogni errore possiede un messaggio specifico. Nel momento si crea un nuovo
//tipo che possiede eccezioni gli errrori vengono gestiti nel seguente modo:
//si crea la classe:
//id="i vari tipi sono numerati in ordine crescente"
//class errore_nometipo: public eccezione1{
//public:
//    errore_nometipo(int);
//};
//il suo costruttore prende il codice dell'errore, senza l'identificativo
//della classe, percio' senza la prima cifra del campo "id".
//il costruttore sara' del tipo:
//errore_vet::errore_nometipo(int num){
//    int i=10;
//    while(num/i)
//        i=i*10;
//    id=i*2+num;
//    classe="nometipo.h";
//    switch (num) {
//    default:
//        significato="errore non esistente/non creato";
//        break;
//    }
//}
//in cui all'interno dell switch vengo inseriti i vari errori col
//relativo messaggio d'errore, come nella caso "default".


class eccezione1{
protected:
    string significato;
    eccezione1(string s): significato(s) {}
public:
    string stampa_errore() const;
};

class domain_error: public eccezione1{
public:
    domain_error(string s="il dominio inserito non e' corretto"): eccezione1(s) {}
};

class input_error: public eccezione1{
public:
    input_error(string s="gli input inseriti non sono corretti"): eccezione1(s) {}
};

class path_error: public eccezione1{
public:
    path_error(string s="il percorso inserito non e' sintatticamente corretto"): eccezione1(s) {}
};

class point_error: public eccezione1{
public:
    point_error(string s="il puntatore dato in input e' nullo"): eccezione1(s) {}
};

#endif // ECCEZIONE1_H
