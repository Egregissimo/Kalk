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

        bin x(2.5);
        bts_b.add(&x);
        cout<<endl<<"prodotto:"<<endl<<bts_b<<endl;
        cout<<bts_b*2<<endl;
        cout<<bts_b/2<<endl;



        /*
        a.remove("");
        cout<<a<<endl;
        a.remove(&x);
        cout<<a<<endl;
        cout<<a.search(&R[0])<<endl;
        cout<<a.cerca("")->to_stringa()<<endl;
        cout<<a*2<<endl<<a/2<<endl;
        */

        cout<<"BTS vet:"<<endl;
        binarytreesearch bts_v(v_v, s1);
        cout<<bts_v<<endl;
        cout<<bts_v.balance()<<endl;
        cout<<endl<<"********************************************************************************************"<<endl;







/*

        cout<<"albero normale"<<endl;
        binarytree b(v, s);
        cout<<b<<endl;
        b.add(&x);
        cout<<b<<endl;
        b.remove("");
        cout<<b<<endl;
        b.remove(&x);
        cout<<b<<endl;
        cout<<b.search(&R[0])<<endl;
        cout<<b.cerca("")->to_stringa()<<endl;
        cout<<b*2<<endl<<b/2<<endl;
        */
    }
    //catch(eccezione ex){throw runtime_error(ex.stampa_errore());}
    catch(input_error ex){ cout<<ex.stampa_errore()<<endl; }
    return 0;
}
