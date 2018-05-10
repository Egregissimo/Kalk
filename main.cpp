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
        vector<tipo*> v;
        for(int i=0; i<6; i++)
            v.push_back(&R[i]);
        for(int i=0; i<6; i++)
            cout<<v[i]->to_stringa()<<" ";
        cout<<endl;
        binarytreesearch a(v, s1);
        cout<<a<<endl;
        cout<<a.balance()<<endl;
        raz x(2,3);
        a.add(&x);
        cout<<a<<endl;
        a.remove("");
        cout<<a<<endl;
        a.remove(&x);
        cout<<a<<endl;
        cout<<a.search(&R[0])<<endl;
        cout<<a.cerca("")->to_stringa()<<endl;
        cout<<a*2<<endl<<a/2<<endl;
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
    }
    catch(eccezione ex){throw runtime_error(ex.stampa_errore());}
    return 0;
}
