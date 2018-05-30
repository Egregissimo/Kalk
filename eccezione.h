#ifndef eccezione_H
#define eccezione_H
#include <string>
#include <stdexcept>

using std::string;
using std::runtime_error;


class eccezione{
private:
    string cl;
    string significato;

protected:
    eccezione(string c, string s): cl(c), significato(s) {}

public:
    string stampa_errore() const;
   // virtual void ghost_method() const =0;
};

class dominio_error: public eccezione{
public:
    dominio_error(string c="N/A", string s="il denominatore e' nullo"): eccezione(c,s) {}
};

class input_error: public eccezione{
public:
    input_error(string c="N/A", string s="gli input inseriti non sono corretti"): eccezione(c,s) {}
};

class path_error: public eccezione{
public:
    path_error(string c="N/A", string s="il percorso inserito non e' sintatticamente corretto"): eccezione(c,s) {}
};

class point_error: public eccezione{
public:
    point_error(string c="N/A", string s="il puntatore dato in input e' nullo"): eccezione(c,s) {}
};

#endif // eccezione_H
