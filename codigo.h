#ifndef COMPILADOR_CODIGO_H
#define COMPILADOR_CODIGO_H

#include <iostream>
#include <fstream>

using namespace std;

class codigo {
private:
    ofstream m_salida;

public:
    codigo();
    ~codigo();

    void code();
    void pushc(char constante);
    void pusha(char direccion);
    void load();
    void store();
    void neg();
    void add();
    void mul();
    void div();
    void mod();
    void input(char direccion);
    void output(char direccion);
    void end();
};


#endif //COMPILADOR_CODIGO_H
