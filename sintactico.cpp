#include "sintactico.h"

/*
 * El constructor verifica que este el simbolo de incio de programa para poder seguir.
 * Verifica los tokens de apertura y cierre del programa
 */
sintactico::sintactico() {
    if (lex.devuelveToken(c) == 'M') {
        c++;
        cout << "M, entrada del programa"<<endl;
        while (lex.devuelveToken(c) == ' ' || lex.devuelveToken(c) == '\n')
            c++;

        if (lex.devuelveToken(c) == '{') {
            generaCodigo.code();
            cout << "Inicio del bloque"<<endl;
            c++;
            bloque();
        }

        if (lex.devuelveToken(c) == '}') {
            cout << "Exito."<<endl;
            generaCodigo.end();
            return;
        }
    }

    else {
        cout << "No hay 'M'. "<<endl;
        return;
    }
}

sintactico::~sintactico() {}


/*
 * Iniciamos verificando si hay nueva sentecia y continua.
 */
void sintactico::bloque() {

    while (lex.devuelveToken(c) == ' ' || lex.devuelveToken(c) == '\n')
        c++;

    sentencia();
    cout << "Nueva sentencia " << lex.devuelveToken(c) << endl;
    nueSentencia();
}

/*
 *
 */

void sintactico::sentencia() {

    if (lex.devuelveToken(c) == 'R') {
        cout << "Lectura encontrada : " << lex.devuelveToken(c) << endl;
        lectura();
    }

    else if (lex.devuelveToken(c) == 'W') {
        cout << "Sentencia encontrada : " << lex.devuelveToken(c) << endl;
        escritura();
    }

    else if (variable()) {
        c++;
        asignacion();
    }
}

bool sintactico::escritura()  {
    bool esPermitido = false;

    c++;
    if (lex.devuelveToken(c) != ' ') {
        cout << "No hay 'espacio'"<<endl;
        return esPermitido;
    }

    else
        c++;

    if (variable()) {
        esPermitido = true;
        generaCodigo.output(lex.devuelveToken(c));
        c++;
        return esPermitido;
    }

    else {
        cout << "No variable."<<endl;
        return esPermitido;
    }
}

/*
 *
 */

void sintactico::nueSentencia() {

    while (lex.devuelveToken(c) == ' ' || lex.devuelveToken(c) == '\n')
        c++;

    if (lex.devuelveToken(c) == ';') {
        cout << "Separador de sentencia ;" << endl;
        c++;

        if (lex.devuelveToken(c) == ' ' || lex.devuelveToken(c) == '\n') {
            while (lex.devuelveToken(c) == ' ' || lex.devuelveToken(c) == '\n')
                c++;
        }

        if (lex.devuelveToken(c) == '}') {
            cout << "Fin de bloque ok. Sintaxis correcta."<<endl;
            generaCodigo.end();
            c++;
            return;
        }

        else if (lex.devuelveToken(c) == ' ' || lex.devuelveToken(c) == '\n') {
            while (lex.devuelveToken(c) == ' ' || lex.devuelveToken(c) == '\n')
                c++;
        }

        if (lex.devuelveToken(c) != ' ' || lex.devuelveToken(c) != '\n') {
            sentencia();
            nueSentencia();

        }
    }

    else {
        cout << "Falta el separador de sentencia"<<endl;
        return;
    }
}

void sintactico::expresion() {
    if (termino())
        nueTerminos();
}

void sintactico::asignacion() {
    char variable = lex.devuelveToken(c - 1);

    while (lex.devuelveToken(c) == ' ' || lex.devuelveToken(c) == '\n')
        c++;


    if (lex.devuelveToken(c) != '=') {
        cout << "Falta el '=' "<<endl;
        return;
    }

    else {
        cout << "Asignacion nueva"<<endl;
        generaCodigo.pusha(variable);
        c++;

        while (lex.devuelveToken(c) == ' ' || lex.devuelveToken(c) == '\n')
            c++;

        expresion();
        generaCodigo.store();
    }
}

bool sintactico::lectura() {

    bool esPermitido = false;
    c++;

    if (lex.devuelveToken(c) != ' ') {
        cout << "No hay 'espacio'"<<endl;
        return esPermitido;
    }

    else
        c++;

    if (variable()) {
        esPermitido = true;
        generaCodigo.input(lex.devuelveToken(c));
        c++;
        return esPermitido;
    }

    else {
        cout << "No hay variable."<<endl;
        return esPermitido;
    }
}



bool sintactico::variable() {

    bool esVariable = false;

    if (lex.devuelveToken(c) >= 'a' && lex.devuelveToken(c) <= 'z') {
        cout << "Variable aceptada : " << lex.devuelveToken(c) << endl;
        esVariable = true;
        return esVariable;
    }

    return esVariable;

}

bool sintactico::termino() {

    if (parentesis()) {
        nueFactores();
        return true;
    }

    return false;
}

void sintactico::nueTerminos() {

   // bool neg = true;

    while (lex.devuelveToken(c) == ' ' || lex.devuelveToken(c) == '\n'){
        c++;
    }

    switch (lex.devuelveToken(c)) {

        case '*':
            cout << "Hay termino " << lex.devuelveToken(c) << endl;
            c++;
            if (termino()) {
                generaCodigo.mul();
            }
            break;
        case '+':
            cout << "Hay termino " << lex.devuelveToken(c) << endl;
            c++;
            if (termino()) {
                generaCodigo.add();
            }
            break;

        case '/':
            cout << "Hay termino " << lex.devuelveToken(c) << endl;
            c++;
            if (termino()) {
                generaCodigo.div();
            }
            break;
        case '-':
            cout << "Hay termino " << lex.devuelveToken(c) << endl;
            c++;
            if (termino()) {
                generaCodigo.neg();
            }
            break;
        case '%':
            cout << "Hay termino " << lex.devuelveToken(c) << endl;
            c++;
            if (termino()) {
                generaCodigo.mod();
            }
            break;

        default:
            break;
    }

   /* if (lex.devuelveToken(c) == '+' || lex.devuelveToken(c) == '-' || lex.devuelveToken(c) == '*'|| lex.devuelveToken(c) == '/') {
        if (lex.devuelveToken(c) == '+')
            neg = false;

        cout << "Hay termino " << lex.devuelveToken(c) << endl;

        c++;

        if (termino()) {
            if (neg)
                generaCodigo.neg();

            generaCodigo.add();

        }
    }*/

}


bool sintactico::parentesis() {
    while (lex.devuelveToken(c) == ' ' || lex.devuelveToken(c) == '\n')
        c++;

    if (lex.devuelveToken(c) == '(') {
        c++;
        expresion();

        if (lex.devuelveToken(c) == ')')
            c++;

        else {
            cout << "Falta un ')' "<<endl;
            return false;
        }

        return true;
    }

    else if (variable()) {
        generaCodigo.pusha(lex.devuelveToken(c));
        generaCodigo.load();
        c++;
        return true;
    }

    else if (constante()) {
        generaCodigo.pushc(lex.devuelveToken(c));
        cout << "Habemus constante " << lex.devuelveToken(c) << endl;
        c++;
        return true;
    }

    else {
        cout << "Fallo el factor"<<endl;
        return false;
    }

    return false;
}

void sintactico::nueFactores() {
    while (lex.devuelveToken(c) == ' ' || lex.devuelveToken(c) == '\n')
        c++;
    nueTerminos();
}

bool sintactico::constante() {
    bool esPermitido = false;

    if (isdigit(lex.devuelveToken(c))) {
        esPermitido = true;
        return esPermitido;
    }

    return esPermitido;
}

/*
 * Soy Khea Bro.
 */
