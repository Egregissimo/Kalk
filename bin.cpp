#include "bin.h"
bin::bin(int d){
    if(d>=0)
        segno = 0;
    else{
        segno = 1;
        d = -1 * d;
    }

    int quoziente = d;
    bool resto = 0;

    if(!d)
        intera.push_back(0);

    while(quoziente != 0){
        resto = quoziente%2;
        intera.push_back(resto);
        quoziente = quoziente/2;
    }
    std::reverse(intera.begin(), intera.end());
}

double bin::base10() const{
    int i_out = 0;
    int i = 0;
    for(std::vector<bool>::const_reverse_iterator it = intera.rbegin(); it != intera.rend(); ++it){
        i_out = i_out + (*it * (pow(2,i)));
        i++;
    }
    if(segno)
        i_out = -1 * i_out;
    return i_out;
}
std::string bin::base16() const{
    int a = (*this).base10();
    std::string out = "";

    int quoziente = a;
    int resto = 0;

    while(quoziente != 0){
        resto = quoziente%16;
        if(resto < 10)
            out = out + std::to_string(resto);
        else{
            switch (resto)
            {
                case 10:
                    out = out + "A";
                break;

                case 11:
                    out = out + "B";
                break;

                case 12:
                    out = out + "C";
                break;

                case 13:
                    out = out + "D";
                break;

                case 14:
                    out = out + "E";
                break;

                case 15:
                    out = out + "F";
                break;
            }
        }
        quoziente = quoziente/16;
    }
    std::reverse(out.begin(), out.end());
    return out;
}

unsigned int bin::getDimIntera() const { return intera.size(); }

bin operator +(const bin& bin1, const bin& bin2){
    double a = bin1.base10();
    double b = bin2.base10();
    bin out(a+b);
    return out;
}
bin operator -(const bin& bin1, const bin& bin2){
    double a = bin1.base10();
    double b = bin2.base10();
    bin out(a-b);
    return out;
}
bin operator *(const bin& bin1, const bin& bin2){
    double a = bin1.base10();
    double b = bin2.base10();
    bin out(a*b);
    return out;
}
bin operator *(int i, const bin& bin2){
    double a = (double)i;
    double b = bin2.base10();
    bin out(a*b);
    return out;
}
bin operator /(const bin& bin1, const bin& bin2){
    double a = bin1.base10();
    double b = bin2.base10();

    if(b<0)
        throw input_error("bin");

    bin out(a/b);
    return out;
}
bin operator/ (int i, const bin& bin2){
    double a = (double)i;
    double b = bin2.base10();


    if(b==0)
        throw input_error("bin");

    bin out(a/b);
    return out;
}
bool operator< (const bin& bin1, const bin& bin2){
    double a = bin1.base10();
    double b = bin2.base10();

    return a<b;
}
bool operator<= (const bin& bin1, const bin& bin2){
    double a = bin1.base10();
    double b = bin2.base10();

    return a<=b;
}
bool operator> (const bin& bin1, const bin& bin2){
    double a = bin1.base10();
    double b = bin2.base10();

    return a>b;
}
bool operator>= (const bin& bin1, const bin& bin2){
    double a = bin1.base10();
    double b = bin2.base10();

    return a>=b;
}
bool operator== (const bin& bin1, const bin& bin2){
    return (bin1.intera == bin2.intera) /*&& (bin1.frazionaria == bin2.frazionaria)*/ && (bin1.segno == bin2.segno);
}
std::ostream& operator<< (std::ostream& os, const bin& bin1){
    if(bin1.segno)
        os<<"-";
    else
        os<<"+";

    for(unsigned int i=0; i<bin1.intera.size(); i++)
        os<<bin1.intera[i];

    return os;
}

string to_string(const bin& bin1){
    std::string out;

    if(bin1.segno)
        out = "-";
    else
        out = "+";

    for(unsigned int i=0; i<bin1.intera.size(); i++)
        out = out + std::to_string(bin1.intera[i]);

    return out;
}

/* Metodi ereditati dalla classe tipo.h */

bin* bin::somma(tipo* b){
    if(!b)
        throw point_error("bin");
    bin* b1 = dynamic_cast<bin*>(b);
    return new bin((*this) + (*b1));
}
bin* bin::differenza(tipo* b){
    if(!b)
        throw point_error("bin");
    bin* b1 = dynamic_cast<bin*>(b);
    return new bin((*this) - (*b1));
}
bin* bin::moltiplicazione(int b){
    return new bin(b * (*this));    /*è da controllare*/
}
bin* bin::divisione(int b){
    return new bin(b / (*this));    /*è da controllare*/
}
bool bin::uguale(tipo* b) const{
    if(!b)
        throw point_error("bin");
    bin* b1 = dynamic_cast<bin*>(b);
    return (*this)==(*b1);
}
bool bin::min(tipo* b) const{
    if(!b)
        throw point_error("bin");
    bin* b1 = dynamic_cast<bin*>(b);
    return (*this)<(*b1);
}
string bin::to_stringa() const{
    return to_string((*this));
}

