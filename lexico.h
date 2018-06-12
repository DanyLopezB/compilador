#ifndef COMPILADOR_LEXICO_H
#define COMPILADOR_LEXICO_H

#include <iostream>
#include <vector>
#include <fstream>

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

/*
 * Soy Khea Bro.
 */



#endif //COMPILADOR_LEXICO_H
