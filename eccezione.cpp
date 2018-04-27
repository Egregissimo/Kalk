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
