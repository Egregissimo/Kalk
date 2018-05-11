#include <QCoreApplication>
#include "binarytreesearch.h"
#include "binarytree.h"

int main(int argc, char *argv[])
{
    /*QCoreApplication a(argc, argv);

    return a.exec();*/
    try{

        string s="(*,(*,_,(*,_,_)),(*,(*,_,_),(*,_,_)))";
        string s1="(*,(*,_,(*,(*,_,_),_)),(*,(*,_,_),_))";

        raz R[]={raz(5,5), raz(3.14), raz(1.5, 0.7), raz(5, 10), raz(5, 70), raz(0.0, 1.5)};
        bin B[]={bin(10), bin(-20), bin(3), bin(4), bin(2.5), bin(9)};

        int str[6] = {-9,3,-3,3,3,-1}; int str2[6] = {4,0,-2,2,2,3}; int str3[6] = {1,0,-2,3}; int str4[6] = {2,3,1,-1};
        vet V[]={vet(str,2,3), vet(str,3,2), vet(str2,2,3), vet(str2,3,2), vet(str3,2,2), vet(str4,2,2)};

        vector<tipo*> v;
        vector<tipo*> v_b;
        vector<tipo*> v_v;
        for(int i=0; i<6; i++){
            v.push_back(&R[i]);
            v_b.push_back(&B[i]);
            v_v.push_back(&V[i]);
        }

        cout<<"Vettore R[]: ";
        for(int i=0; i<6; i++)
            cout<<v[i]->to_stringa()<<" ";
        cout<<endl;

        cout<<"Vettore B[]: ";
        for(int i=0; i<6; i++)
            cout<<v_b[i]->to_stringa()<<" ";
        cout<<endl;

        cout<<"Vettore V[]: ";
        for(int i=0; i<6; i++)
            cout<<v_v[i]->to_stringa()<<" ";
        cout<<endl<<"********************************************************************************************"<<endl;

        cout<<"BTS raz:"<<endl;
        binarytreesearch a(v, s1);
        cout<<a<<endl;
        cout<<a.balance()<<endl;

        cout<<"BTS bin:"<<endl;
        binarytreesearch bts_b(v_b, s1);
        cout<<bts_b<<endl;
        cout<<bts_b.balance()<<endl;

        cout<<"BTS vet:"<<endl;
        binarytreesearch bts_v(v_v, s1);
        cout<<bts_v<<endl;
        cout<<bts_v.balance()<<endl;
        cout<<endl<<"********************************************************************************************"<<endl;
    /*
     * TEST DI ADD, PRODOTTO E DIVISIONE CON SCALARE
        bin x(2.5);
        bts_b.add(&x);
        cout<<endl<<"Funzione di add:"<<endl<<bts_b<<endl;

        cout<<endl<<"Prodotto e divisione:"<<endl;
        cout<<bts_b*2<<endl;
        cout<<bts_b/2<<endl;
    */

    /*
     * TEST DEL METODO remove(string s) e remove(tipo* t)
        cout<<endl<<"BTS raz:"<<endl<<a<<endl;
        raz x(5,10);
        a.remove("");
        cout<<endl<<"Funzione di remove(""):"<<endl<<a<<endl;
        a.remove(&x);
        cout<<endl<<"Funzione di remove(&x):"<<endl<<a<<endl;


        cout<<endl<<"BTS bin:"<<endl<<a<<endl;
        bin x(2.5);
        bts_b.remove("");
        cout<<endl<<"Funzione di remove(""):"<<endl<<bts_b<<endl;
        bts_b.remove(&x);
        cout<<endl<<"Funzione di remove(&x):"<<endl<<bts_b<<endl;
    */

    /*
     * TEST DI RICERCA
       tipo* ris = a.search(&R[4]);
       cout<<"QUI -->"<<*ris<<endl;
       cout<<a.cerca("")->to_stringa()<<endl;

       tipo* ris = bts_b.search(&B[4]);
       cout<<"QUI -->"<<*ris<<endl;
       cout<<bts_b.cerca("")->to_stringa()<<endl;
    */

        cout<<"BT raz:"<<endl;
        binarytree b(v, s);
        cout<<b<<endl;

        cout<<"BT bin:"<<endl;
        binarytree bt_b(v_b, s);
        cout<<bt_b<<endl;

        cout<<"BT vet:"<<endl;
        binarytree bt_v(v_v, s);
        cout<<bt_v<<endl;

        bin x(2.5);
        bt_b.add(&x);
        cout<<bt_b<<endl;
        bt_b.remove("");
        cout<<endl<<"Funzione di remove(""):"<<endl<<bt_b<<endl;
        bt_b.remove(&x);
        cout<<endl<<"Funzione di remove(&x):"<<endl<<bt_b<<endl;
    /*
        cout<<b.search(&R[0])<<endl;
        cout<<b.cerca("")->to_stringa()<<endl;
        cout<<b*2<<endl<<b/2<<endl;
    */
    }
    //catch(eccezione ex){throw runtime_error(ex.stampa_errore());}
    catch(input_error ex){ cout<<ex.stampa_errore()<<endl; }
    return 0;
}
