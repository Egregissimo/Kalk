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

    while(quoziente != 0){
        resto = quoziente%2;
        intera.push_back(resto);
        quoziente = quoziente/2;
    }
    std::reverse(intera.begin(), intera.end());
    frazionaria.push_back(0);
}
bin::bin(double d){
    if(d>=0)
        segno = 0;
    else{
        segno = 1;
        d = -1 * d;
    }

    int intero = (int) d;
    double frazionario = d - intero;
    int quoziente = intero;
    bool resto = 0;

    while(quoziente != 0){
        resto = quoziente%2;
        intera.push_back(resto);
        quoziente = quoziente/2;
    }

    std::reverse(intera.begin(), intera.end());

    if(frazionario == 0)
        frazionaria.push_back(0);
    else{
        while(frazionario != 0){
            frazionario = frazionario*2;

            if(frazionario >= 1){
                frazionaria.push_back(1);
                frazionario = frazionario-1;
            }
            else
                frazionaria.push_back(0);
        }
    }
}

double bin::base10() const{
    int i_out = 0;
    double f_out = 0;
    int i = 0;
    for(std::vector<bool>::const_reverse_iterator it = intera.rbegin(); it != intera.rend(); ++it){
        i_out = i_out + (*it * (pow(2,i)));
        i++;
    }

    for(int i=0; i<frazionaria.size(); i++)
        f_out = f_out + (frazionaria[i] * (pow(2,-(i+1))));

    f_out = i_out + f_out;

    if(segno)
        f_out = -1 * f_out;
    return f_out;
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
unsigned int bin::getDimFrazionaria() const { return frazionaria.size(); }
/*
bin& bin::operator =(const bin& bin1){
    if(this != &bin1){
        this->intera.clear();
        this->frazionaria.clear();

        this->segno = bin1.segno;
        for(unsigned int i=0; i<bin1.intera.size(); i++)
            this->intera.push_back(bin1.intera[i]);

        for(unsigned int i=0; i<bin1.frazionaria.size(); i++)
            this->frazionaria.push_back(bin1.frazionaria[i]);
    }
    return *this;
}
*/
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
bin operator /(const bin& bin1, const bin& bin2) throw(input_error){
    double a = bin1.base10();
    double b = bin2.base10();

    if(b<0)
        throw input_error("bin");

    bin out(a/b);
    return out;
}
bin operator/ (int i, const bin& bin2) throw(input_error){
    double a = (double)i;
    double b = bin2.base10();


    if(b<0)
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
    return (bin1.intera == bin2.intera) && (bin1.frazionaria == bin2.frazionaria) && (bin1.segno == bin2.segno);
}
std::ostream& operator<< (std::ostream& os, const bin& bin1){
    if(bin1.segno)
        os<<"-";
    else
        os<<"+";

    for(unsigned int i=0; i<bin1.intera.size(); i++)
        os<<bin1.intera[i];
    os<<".";
    for(unsigned int i=0; i<bin1.frazionaria.size(); i++)
        os<<bin1.frazionaria[i];

    return os;
}

string to_string(const bin& bin1){
    std::string out;

    if(bin1.segno)
        out = "-";
    else
        out = "+";

    for(int i=0; i<bin1.intera.size(); i++)
        out = out + std::to_string(bin1.intera[i]);

    out = out + ".";

    for(int i=0; i<bin1.frazionaria.size(); i++)
        out = out + std::to_string(bin1.frazionaria[i]);

    return out;
}

/* Metodi ereditati dalla classe tipo.h */

bin* bin::somma(tipo* b){
    bin* b1 = dynamic_cast<bin*>(b);
    return new bin((*this) + (*b1));
}
bin* bin::differenza(tipo* b){
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
    bin* b1 = dynamic_cast<bin*>(b);
    return (*this)==(*b1);
}
bool bin::min(tipo* b) const{
    bin* b1 = dynamic_cast<bin*>(b);
    return (*this)<(*b1);
}
string bin::to_stringa() const{
    return to_string((*this));
}

