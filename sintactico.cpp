#include "sintactico.h"

/*
 * El constructor verifica que este el simbolo de incio de programa para poder seguir.
 */
sintactico::sintactico() {
    if (lexico.devuelveToken(c) == 'M')
    {
        c++;
        cout << "M, entrada del programa"<<endl;
        while (lexico.devuelveToken(c) == ' ')
            c++;

        if (lexico.devuelveToken(c) == '{')
        {
            generaCodigo.code();
            cout << "Inicio del bloque"<<endl;
            c++;
            bloque();
        }

        if (lexico.devuelveToken(c) == '}')
        {
            cout << "Exito."<<endl;
            generaCodigo.end();
            return;
        }
    }

    else
    {
        cout << "No hay 'M'. "<<endl;
        return;
    }
}

sintactico::~sintactico() {}


/*
 * Se explica solo esto. Bai
 */
void sintactico::bloque()
{
    while (lexico.devuelveToken(c) == ' ' || lexico.devuelveToken(c) == '\n')
        c++;

    sentencia();
    cout << "Nueva sentencia " << lexico.devuelveToken(c) << endl;
    nueSentencia();
}

/*
 *
 */

void sintactico::sentencia() {

    if (lexico.devuelveToken(c) == 'R') {
        cout << "Lectura encontrada : " << lexico.devuelveToken(c) << endl;
        lectura();
    }

    else if (lexico.devuelveToken(c) == 'W') {
        cout << "Sentencia encontrada : " << lexico.devuelveToken(c) << endl;
        escritura();
    }

    else if (variable()) {
        c++;
        asignacion();
    }
}

void sintactico::nueSentencia() {

    while (lexico.devuelveToken(c) == ' ' || lexico.devuelveToken(c) == '\n')
        c++;

    if (lexico.devuelveToken(c) == ';') {
        cout << "Separador de sentencia ;\n";
        c++;

        if (lexico.devuelveToken(c) == ' ' || lexico.devuelveToken(c) == '\n') {
            while (lexico.devuelveToken(c) == ' ' || lexico.devuelveToken(c) == '\n')
                c++;
        }

        if (lexico.devuelveToken(c) == '}') {
            cout << "Fin de bloque ok. Sintaxis correcta."<<endl;
            generaCodigo.end();
            c++;
            return;
        }

        else if (lexico.devuelveToken(c) == ' ' || lexico.devuelveToken(c) == '\n') {
            while (lexico.devuelveToken(c) == ' ' || lexico.devuelveToken(c) == '\n')
                c++;
        }

        if (lexico.devuelveToken(c) != ' ' || lexico.devuelveToken(c) == '\n') {
            sentencia();
            nueSentencia();
        }
    }

    else {
        cout << "Falta el separador de sentencia."<<endl;
        return;
    }
}

void sintactico::expresion() {
    if (termino())
        nueTerminos();
}

void sintactico::asignacion() {
    char variable = lexico.devuelveToken(c - 1);

    while (lexico.devuelveToken(c) == ' ' || lexico.devuelveToken(c) == '\n') {

        c++;
    }


    if (lexico.devuelveToken(c) != '=') {
        cout << "Falta el '='."<<endl;
        return;
    }

    else {
        cout << "Asignacion nueva"<<endl;
        generaCodigo.pusha(variable);
        c++;

        while (lexico.devuelveToken(c) == ' ' || lexico.devuelveToken(c) == '\n')
            c++;

        expresion();
        generaCodigo.store();
    }
}

bool sintactico::lectura() {
    bool esPermitido = false;
    c++;

    if (lexico.devuelveToken(c) != ' ') {
        cout << "No hay 'espacio'"<<endl;
        return esPermitido;
    }

    else
        c++;

    if (variable()) {
        esPermitido = true;
        generaCodigo.input(lexico.devuelveToken(c));
        c++;
        return esPermitido;
    }

    else {
        cout << "No hay variable.\n";
        return esPermitido;
    }
}

bool sintactico::escritura()
{
    bool esPermitido = false;

    c++;
    if (lexico.devuelveToken(c) != ' ') {
        cout << "No hay 'espacio'"<<endl;
        return esPermitido;
    }

    else
        c++;

    if (variable()) {
        esPermitido = true;
        generaCodigo.output(lexico.devuelveToken(c));
        c++;
        return esPermitido;
    }

    else {
        cout << "No variable."<<endl;
        return esPermitido;
    }
}

bool sintactico::variable()
{
    bool esVariable = false;

    if (lexico.devuelveToken(c) >= 'a' && lexico.devuelveToken(c) <= 'z')
    {
        cout << "Variable aceptada : " << lexico.devuelveToken(c) << endl;
        esVariable = true;
        return esVariable;
    }

    return esVariable;

}

bool sintactico::termino()
{
    if (factor()) {
        nueFactores();
        return true;
    }

    return false;
}

void sintactico::nueTerminos()
{
    bool opeNegativa = true;

    while (lexico.devuelveToken(c) == ' ' || lexico.devuelveToken(c) == '\n')
        c++;

    if (lexico.devuelveToken(c) == '+' || lexico.devuelveToken(c) == '-') {
        if (lexico.devuelveToken(c) == '+')
            opeNegativa = false;

        cout << "Hay termino" << lexico.devuelveToken(c) << endl;

        c++;
        if (termino()) {
            if (opeNegativa)
                generaCodigo.neg();

            generaCodigo.add();

            nueTerminos();
        }
    }
}

bool sintactico::factor() {
    while (lexico.devuelveToken(c) == ' ' || lexico.devuelveToken(c) == '\n')
        c++;

    if (lexico.devuelveToken(c) == '(') {
        c++;
        expresion();
        if (lexico.devuelveToken(c) == ')')
            c++;
        else
        {
            cout << "Falta un ')' "<<endl;
            return false;
        }

        return true;
    }

    else if (variable()) {
        generaCodigo.pusha(lexico.devuelveToken(c));
        generaCodigo.load();
        c++;
        return true;
    }

    else if (constante()) {
        generaCodigo.pushc(lexico.devuelveToken(c));
        cout << "Habemus constante " << lexico.devuelveToken(c) << endl;
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
    while (lexico.devuelveToken(c) == ' ' || lexico.devuelveToken(c) == '\n')
        c++;

    switch (lexico.devuelveToken(c)) {

        case '*':
            generaCodigo.mul();
            c++;
            break;

        case '/':
            generaCodigo.div();
            c++;
            break;

        case '%':
            generaCodigo.mod();
            c++;
            break;

        default:
            break;
    }
}

bool sintactico::constante() {
    bool esPermitido = false;

    if (isdigit(lexico.devuelveToken(c))) {
        esPermitido = true;
        return esPermitido;
    }

    return esPermitido;
}

/*
 * Soy Khea Bro.
 */
