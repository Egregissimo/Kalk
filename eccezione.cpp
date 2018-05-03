#include "eccezione.h"

eccezione::eccezione(int num){
    id = num;

    int cl = (int)(num/10);
    switch (cl) {
        case 1: classe = "raz.h"; break;
        case 2: classe = "vet.h"; break;
        case 3: classe = "bin.h"; break;
        default: classe = "Non definita"; break;
    }

    int tipoError = num - cl*10;

    switch (tipoError) {
    case 0:
        significato = "Errore di indice/i. I/il valori/e assegnati/o sono/è fuori dal range";
        break;
    case 1:
        significato = "Operazione di somma o sottrazione non consentita. Le dimensioni delle due matrici non sono uguali";
        break;
    case 2:
        significato = "Operazione di motiplicazione non consentita. Due matrici si possno moltiplicare se A[m,n] e B[n,p]. Ottengo C[m,p]";
        break;
    default:
        break;
    }
}

errore_vet::errore_vet(string mex, string std_mex){ messaggio = mex; standard_mex = std_mex; }
std::ostream& operator<<(std::ostream& os, const errore_vet& er){
    os<<er.messaggio<<std::endl;
    return os;
}
errore_somma::errore_somma(string mex): errore_vet(mex,"meessaggio standar") {}
void errore_somma::stampa_errore() const { std::cout<<messaggio<<std::endl; }

errore_sottrazione::errore_sottrazione(string mex): errore_vet(mex,"messaggio standar") {}
void errore_sottrazione::stampa_errore() const { std::cout<<messaggio<<std::endl; }

errore_prodotto::errore_prodotto(string mex): errore_vet(mex,"messaggio standar") {}
void errore_prodotto::stampa_errore() const { std::cout<<messaggio<<std::endl; }

errore_divisione::errore_divisione(string mex): errore_vet(mex,"messaggio standar") {}
void errore_divisione::stampa_errore() const { std::cout<<messaggio<<std::endl; }
