#ifndef COMPILADOR_SINTACTICO_H
#define COMPILADOR_SINTACTICO_H


#include <iostream>
#include "lexico.h"
#include "codigo.h"

using namespace std;

class sintactico {
private:
    lexico lexico;
    codigo generaCodigo;
    char c = 0;

public:
    sintactico();
    ~sintactico();
    void bloque();
    void sentencia();
    void nueSentencia();
    void asignacion();
    bool lectura();
    bool escritura();
    bool variable();
    void expresion();
    bool termino();
    void nueTerminos();
    bool parentesis();
    void nueFactores();
    bool constante();
};

/*
 * Soy Khea Bro.
 */


#endif //COMPILADOR_SINTACTICO_H
