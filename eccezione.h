#ifndef EXCEPTION_H
#define EXCEPTION_H
#include <iostream>
#include <string>

using std::string;

class eccezione{
private:
    int id;
    string classe;
    string significato;
public:
    eccezione(int =0);
};


class errore_vet{
    friend std::ostream& operator<<(std::ostream&, const errore_vet&);
public:
    string messaggio;
    string standard_mex;
    errore_vet(string = "N/A", string = "N/A");
    virtual void stampa_errore() const =0;
};
std::ostream& operator<<(std::ostream&, const errore_vet&);

class errore_index:public errore_vet{
public:
    errore_index(string = "N/A");
    void stampa_errore() const;
};
class errore_somma:public errore_vet{
public:
    errore_somma(string = "N/A");
    void stampa_errore() const;
};
class errore_sottrazione:public errore_vet{
public:
    errore_sottrazione(string = "N/A");
    void stampa_errore() const;
};
class errore_prodotto:public errore_vet{
public:
    errore_prodotto(string = "N/A");
    void stampa_errore() const;
};
class errore_divisione:public errore_vet{
public:
    errore_divisione(string = "N/A");
    void stampa_errore() const;
};

#endif // EXCEPTION_H
