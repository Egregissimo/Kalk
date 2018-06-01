#include <QCoreApplication>
#include "mygui.h"
int main(int argc, char *argv[]){
    QApplication app(argc, argv);
    app.setWindowIcon(QIcon("icon_kalk.ico"));
    mygui widget;
    widget.show();

    return app.exec();

    /*
    try{
        QApplication app(argc, argv);
        string s="(*,(*,(*,_,_),_),(*,_,(*,_,_)))";
        tipo* a=new raz(5,7);
        tipo* b=new raz(-8, 10);
        tipo* c=new raz(2.5);
        tipo* d=new raz(3.1, 5.2);
        tipo* e=new raz(6,12);
        tipo* f=new raz(-18,-20);
        vector<tipo*> v;
        v.push_back(a);
        v.push_back(b);
        v.push_back(c);
        v.push_back(d);
        v.push_back(e);
        binarytreesearch t(v, s);
        binarytree tt(v, s);
        string qs("Albero binario di ricerca t:<br/>"+to_string(t)+"<br/>Bilancio l'albero t:<br/>"+to_string(t.balance())+"<br/>Aggiungo in nodo (9/10):<br/>");
        t.add(f);
        qs+=to_string(t)+"<br/>";
        qs+="Albero t con il nodo aggiunto:<br/>"+to_string(t);
        qs+="<br/>Trova il nodo (5/2):<br/>"+t.search(c)->to_stringa()+"<br/>Trova il nodo nel percorso '0':<br/>"+t.cerca("0")->to_stringa()
                                   +"<br/>Rimuovo il nodo nel percorso '0':<br/>"+t.remove("0")->to_stringa()+"<br/>"+to_string(t)+"<br/>Rimuovo il nodo (5/7):<br/>"+t.remove(a)->to_stringa()
                +"<br/>"+to_string(t);

        qs+="<br/><br/>Albero binario tt:<br/>"+to_string(tt)+"<br/>Aggiungo in nodo (9/10):<br/>";
        tt.add(f);
        qs+=to_string(tt)+"<br/>";
        qs+="Albero tt con il nodo aggiunto:<br/>"+to_string(tt);
        cout<<tt<<endl;
        tt.search(c)->to_stringa();
        qs+="<br/>Trova il nodo (5/2):<br/>"+tt.search(c)->to_stringa()+"<br/>Trova il nodo nel percorso '0':<br/>"+tt.cerca("0")->to_stringa();
        qs+="<br/>Rimuovo il nodo nel percorso '0':<br/>"+tt.remove("0")->to_stringa()+"<br/>"+to_string(tt)+"<br/>Rimuovo il nodo (5/7):<br/>"+tt.remove(a)->to_stringa()
                +"<br/>"+to_string(tt);
        QTextEdit* te=new QTextEdit(QString::fromStdString(qs));
        te->setReadOnly(true);
        te->resize(400, 650);
        te->show();
        return app.exec();
    }
    catch(eccezione e){
        throw runtime_error(e.stampa_errore());
    }
    */
}
