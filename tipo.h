#ifndef TIPO_H
#define TIPO_H
#include "eccezione.h"
#include <iostream>

using std::ostream;
using std::cout;
using std::endl;
using std::to_string;

//ogni tipo di dato da usare nell'albero deve includere
//ed implementare questa classe
class tipo{
    /* Dichiarazione di amicizia per i metodi dichiarati fuori dalla classe */
    friend std::ostream& operator <<(std::ostream&, const tipo&);
public:
    virtual ~tipo() {}
    virtual tipo* somma(tipo*) =0;                          //somma tra due tipi
    virtual tipo* differenza(tipo*) =0;                     //differenza tra due tipi
    virtual tipo* moltiplicazione(int) =0;                  //moltiplicazione per uno scalare
    virtual tipo* divisione(int) =0;                        //divisione per uno scalare
    virtual bool uguale(tipo*)const =0;                     //operatore di uguaglianza ==
    virtual bool min(tipo*)const =0;                        //operatore <
    virtual string to_stringa()const =0;                    /*  stampa */
};

std::ostream& operator<< (std::ostream&, const tipo&);      /*  posso stampare un oggetto di tipo "tipo", l'overloading di operatore
                                                                richiamarà un metodo virtuale ridefinito nelle classi derivate */

#endif // TIPO_H
