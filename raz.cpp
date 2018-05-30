#include "raz.h"

int raz::degree(double d){
    int i=0;
    while((d*std::pow(10, i)-floor(d*std::pow(10, i))) && i<=10)
       i++;
    return i;
}

raz::raz(int n, int d): num(n){
    if(d==0)
        throw dominio_error("raz");
    else if(num==0)
        den=1;
    else if(d<0){
        num=-num;
        den=-d;
    }
    else
        den=d;
    riduzione();
}

raz::raz(double n, double d){
    if(d==0)
        throw dominio_error("raz");
    if(n==0){
        num=0;
        den=1;
    }
    else{
        //numeratore
        int degree_num=degree(n);
        int num_num=static_cast<int>(n*std::pow(10, degree_num));//non sono presenti cifre decimali in questo double
        int den_num=static_cast<int>(std::pow(10, degree_num));
        raz x(num_num, den_num);//viene invocato il costruttore raz(int, int)
        //cout<<"degree: "<<degree_num<<" num_num: "<<num_num<<" den_num: "<<den_num<<endl;
        //denominatore
        int degree_den=degree(d);
        int num_den=static_cast<int>(d*std::pow(10, degree_den));//non sono presenti cifre decimali in questo double
        int den_den=static_cast<int>(std::pow(10, degree_den));
        raz y(num_den, den_den);
        //cout<<"degree: "<<degree_den<<" num_num: "<<num_den<<" den_num: "<<den_den<<endl;

        //cout<<x<<" "<<y<<endl;
        raz z=x/y;
        num=z.num;
        den=z.den;
    }
    riduzione();
}

int raz::getNum()const{
    return num;
}

int raz::getDen()const{
    return den;
}

raz raz::inverso(const raz& r){
    raz t(r.den, r.num);
    return t;
}

raz::operator double() {return static_cast<double>(num)/static_cast<double>(den);}

raz::operator int() {return static_cast<int>(floor(num/den));}

raz& raz::operator++(){//prefisso
    *this=*this+1;
    return *this;
}

raz raz::operator++(int){//postfisso
    raz aux(*this);
    *this=*this+1;
    return aux;
}

raz raz::pow(const raz& r, int n){
    return raz(std::pow(r.num, n), std::pow(r.den, n));
    
}

raz raz::sqrt(const raz & r){
    return raz(std::sqrt(r.num), std::sqrt(r.den));
    //avviene già la riduzione
}

raz raz::cbrt(const raz & r){
    return raz(static_cast<int>(floor(std::cbrt(r.num))),
               static_cast<int>(floor(std::cbrt(r.den))));
}

//PRE={den!=0}
raz raz::riduzione()const{
    raz x(*this);
    if(x.num==x.den)
            x.num=x.den=1;
    else if(x.num!=0){
        int aux=(abs(x.num)<abs(x.den))?abs(x.num):abs(x.den);
        for(int i=2; i<=aux; i++)
            if(x.num%i==0 && x.den%i==0){
                x.num=x.num/i;
                x.den=x.den/i;
                aux=(x.num<x.den)?x.num:x.den;
                i--;
            }
    }
    else
        x.den=1;
    return x;
}

raz* raz::somma(tipo* b){
    if(!b)
        throw point_error("raz");
    raz *b1=static_cast<raz*>(b);
    return new raz(((*this)+(*b1)));
}

raz* raz::differenza(tipo* b){
    if(!b)
        throw point_error("raz");
    raz*b1=static_cast<raz*>(b);
    return new raz(((*this)-(*b1)));
}

raz* raz::moltiplicazione(int b){
    return new raz(((*this)*b));
}

raz* raz::divisione(int b){
    return new raz(((*this)/b));
}

bool raz::uguale(tipo* b) const{
    if(!b)
        throw point_error("raz");
    raz* b1=static_cast<raz*>(b);
    return (*this)==(*b1);
}

bool raz::min(tipo* b) const{
    if(!b)
        throw point_error("raz");
    raz*b1=static_cast<raz*>(b);
    return (*this)<(*b1);
}

string raz::to_stringa()const{
    return to_string(*this);
}

raz operator+(const raz& r1, const raz& r2){
    if(!r1.num)
        return r2;
    if(!r2.num)
        return r1;
    int n=r1.num*r2.den+r2.num*r1.den;
    int d=r1.den*r2.den;

    return raz(n, d);
}

raz operator-(const raz& r1, const raz& r2){
    int n=r1.num*r2.den-r2.num*r1.den;
    int d=r1.den*r2.den;

    return raz(n, d);
}

raz operator*(const raz& r1, const raz& r2){
    return raz(r1.num*r2.num, r1.den*r2.den);
}

raz operator/(const raz& r1, const raz& r2){
    if(r2.num==0)
        throw dominio_error("raz");
    return raz(r1.num*r2.den, r1.den*r2.num);
}

bool operator==(const raz& r1, const raz& r2){
    raz r3(r1), r4(r2);
    return r3.num==r4.num && r3.den==r4.den;
}

bool operator!=(const raz& r1, const raz& r2){
    return r1.num!=r2.num || r1.den!=r2.den;
}

bool operator<=(const raz& r1, const raz& r2){
    return (r1.num*r2.den<=r2.num*r1.den);
}

bool operator<(const raz& r1, const raz& r2){
    return (r1.num*r2.den<r2.num*r1.den);
}

ostream& operator<<(ostream& os, const raz& r){
    if(r.num==0)
        os<<0;
    else if(r.den==1)
        os<<r.num;
    else
        os<<r.num<<"/"<<r.den;
    return os;
}

string to_string(const raz &r){
    if(r.num==0)
        return to_string(0);
    else if(r.den==1)
        return to_string(r.num);
    else
        return to_string(r.num)+"/"+to_string(r.den);
}
