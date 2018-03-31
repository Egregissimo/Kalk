#include "raz.h"

raz::raz(int n, int d): num(n) {
    if(d==0)
        throw(0);
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
        throw(0);
    if(n==0){
        num=0;
        den=1;
    }
    else{
       double x=n/d;
       int i=0;
       while(!(x*pow(10, i)-floor(x*pow(10, i))))
           i++;
       num=static_cast<int>(x*pow(10, i));//non sono presenti cifre decimali in questo double
       den=static_cast<int>(pow(10, i));
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
    raz t(r.num, r.den);
    return t;
}

raz::operator double() {return num/den;}

raz::operator int() {return static_cast<int>(floor(num/den));}

raz& raz::operator++(){
    (*this)=(*this)+1;
    return *this;
}

raz raz::operator++(int){
    raz aux=*this;
    *this=*this+1;
    return aux;
}

raz raz::pow(const raz& r, int n){
    raz x(pow(r.num, n), pow(r.num, n));
    x.riduzione();
    return r;
}

raz raz::sqrt(const raz & r){
    return raz(static_cast<int>(floor(sqrt(r.num))),
               static_cast<int>(floor(sqrt(r.den))));
}

raz raz::cbrt(const raz & r){
    return raz(static_cast<int>(floor(cbrt(r.num))),
               static_cast<int>(floor(cbrt(r.den))));
}

//PRE={den!=0 && se num==0 => den==1}
void raz::riduzione(){
    if(num==den)
            num=den=1;
    else if(num!=0){
        int aux=(num<den)?num:den;
        for(int i=2; i<=aux; i++)
            if(num%i==0 && den%i==0){
                num=num/i;
                den=den/i;
                aux=(num<den)?num:den;
                i--;
            }
    }
}

raz operator+(const raz& r1, const raz& r2){
    if(r1.num==0)
        return r2;
    if(r2.num==0)
        return r1;

    n=r1.num*r2.den+r2.num*r1.den;
    d=r1.den*r2.den;
    raz ris(n, d);
    ris.riduzione();
    return ris;
}

raz operator-(const raz& r1, const raz& r2){
    if(r1.den==0)
        return raz(-r2.num, -r2.num);
    if(r2.den==0)
        return r1;

    n=r1.num*r2.den-r2.num*r1.den;
    d=r1.den*r2.den;
    raz ris(n, d);
    ris.riduzione();
    return ris;
}

raz operator*(const raz& r1, const raz& r2){
    raz t(r1.num*r2.num, r1.den*r2.den);
    t.riduzione();
    return t;
}

raz operator/(const raz& r1, const raz& r2){
    if(r2.num==0)
        throw(0);
    raz t(r1.num*r2.den, r1.den*r2.num);
    t.riduzione();
    return t;
}

raz operator==(const raz& r1, const raz& r2){
    raz r3(r1.riduzione()), r4(r2.riduzione());
    return r3.num==r4.num && r3.den==r4.den;
}

raz operator!=(const raz&, const raz&){
    raz r3(r1.riduzione()), r4(r2.riduzione());
    return r3.num!=r4.num || r3.den!=r4.den;
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
