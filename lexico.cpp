#include "lexico.h"
//#include <ctype.h>
#include <fstream>


lexico::lexico()
{
    ifstream archivo("archivoFuente.txt", ios::in);

    if (archivo.is_open())
    {
        do
        {
            m_caracteres.push_back(archivo.get());
        } while (!archivo.eof());

        verifToken();
        archivo.close();
    }

    else
        cerr << "Imposible de abrir el archivo" << endl;
}

lexico::~lexico()
{

}

int lexico::get_Traza()
{
    traza = (traza) ? 1 : 0;
    return traza;
}

char lexico::devuelveToken(int c)
{
    if (c >= m_caracteres.size())
        return '\0';

    return m_caracteres[c];
}

void lexico::verifToken() {
    int i;

    cout << "*** Compilador ***\n";
    cout << "\n";
    cout << "Selecciona una de las opciones siguientes :\n";
    cout << "0 - Sin traza\n1 - Con traza\n";
    cin >> traza;
    cout << "\n";

    if (get_Traza()) {
        for (i = 0; i < m_caracteres.size() - 1; ++i) {
            switch (m_caracteres[i]) {

                case 'M':
                    cout << "M : Palabra reservada, punto de entrada del programa" << endl;
                    break;
                case 'R':
                    cout << "R : Palabra reservada R" << endl;
                    break;
                case 'W':
                    cout << "W : Palabra reservada W" << endl;
                    break;
                case '{':
                    cout << "{ : Inicio de un bloque" << endl;
                    break;
                case '}':
                    cout << "} : Fin de un bloque" << endl;
                    break;

                case '(':
                    cout << "Parentesis abierto (" << endl;
                    break;

                case ')':
                    cout << "Parentesis de cierre )" << endl;
                    break;

                case '+':
                    cout << "Operador aritmetico +" << endl;
                    break;

                case '-':
                    cout << "Operador aritmetico -" << endl;
                    break;

                case '*':
                    cout << "Operador aritmetico *" << endl;
                    break;

                case '/':
                    cout << "Operador aritmetico /" << endl;
                    break;

                case '%':
                    cout << "Operador aritmetico %" << endl;
                    break;

                case '=':
                    cout << "Simbolo de asignacion =" << endl;
                    break;

                case ';':
                    cout << "Separador de sentencia ;" << endl;
                    break;

                default:
                    if (isdigit(m_caracteres[i]))
                        cout << "Constante : " << m_caracteres[i] << endl;

                    else if (islower(m_caracteres[i]))
                        cout << "Variable : " << m_caracteres[i] << endl;

                    else if (m_caracteres[i] == ' ' || m_caracteres[i] == '\n')
                        cout << "Espacio" << endl;

                    else {
                        cout << "Este caracter no es admitido. " << m_caracteres[i] << endl;
                        return;
                    }

                    break;
            }
        }
    }

    for (i = 0; i < m_caracteres.size(); ++i)
        cout << " " << m_caracteres[i];
}