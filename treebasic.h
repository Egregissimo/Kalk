#ifndef TREEBASIC_H
#define TREEBASIC_H


class treebasic
{
public:
    virtual KalkBase* somma(KalkBase* a, KalkBase* b)=0;
    virtual KalkBase* differenza(KalkBase* a, KalkBase* b)=0;
    virtual KalkBase* moltiplicazione(KalkBase* a, KalkBase* b)=0;
    virtual KalkBase* divisione(KalkBase* a, KalkBase* b)=0;
};

#endif // TREEBASIC_H
