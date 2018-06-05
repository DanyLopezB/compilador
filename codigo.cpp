#include "codigo.h"

codigo::codigo() {
    m_salida.open("salida.txt");
}

void codigo::code() {
    m_salida << ".CODE"<<endl;
}
void codigo::pushc(char constante) {
    m_salida << "PUSHC " << constante << endl;
}
void codigo::pusha(char direccion) {
    m_salida << "PUSHA " << direccion << endl;
}
void codigo::load() {
    m_salida << "LOAD"<< endl;
}
void codigo::store() {
    m_salida << "STORE" << endl;
}
void codigo::neg() {
    m_salida << "NEG"<<endl;
}
void codigo::add() {
    m_salida << "ADD" <<endl;
}
void codigo::mul() {
    m_salida << "MUL"<<endl;
}
void codigo::div() {
    m_salida << "DIV"<<endl;
}
void codigo::mod() {
    m_salida << "MOD"<<endl;
}
void codigo::input(char direccion) {
    m_salida << "INPUT "<< direccion <<endl;
}
void codigo::output(char direccion) {
    m_salida << "OUTPUT "<< direccion << endl;
}
void codigo::end() {
    m_salida << "END"<<endl;
}

codigo::~codigo() {
    m_salida.close();
}