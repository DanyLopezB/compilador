#ifndef COMPILADOR_LEXICO_H
#define COMPILADOR_LEXICO_H

#include <iostream>
#include <vector>

using namespace std;

class lexico
{

private:
    vector<char> m_caracteres;
    int traza = 0;	// traza = 1 muestra paso a paso

public:
    lexico();
    ~lexico();
    char devuelveToken(int c);
    void verifToken();
    int get_Traza(void);
};



#endif //COMPILADOR_LEXICO_H
