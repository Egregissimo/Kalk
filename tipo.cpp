#include "tipo.h"

std::ostream& operator<< (std::ostream& os, const tipo& tp){
    string tmp = tp.to_stringa();
    os<<tmp;
    return os;
}
