#include "eccezione.h"

string eccezione::stampa_errore()const{
    return "From class: "+cl+", the message is: "+significato;
}
