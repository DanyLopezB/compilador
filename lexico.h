#ifndef COMPILADOR_LEXICO_H
#define COMPILADOR_LEXICO_H

#include <iostream>
#include <vector>

using namespace std;

class lexico {
private:
    vector<char> m_caracteres;

public:
    lexico();
    ~lexico();
    char devuelveToken(int c);
    void verifToken();
};



#endif //COMPILADOR_LEXICO_H
