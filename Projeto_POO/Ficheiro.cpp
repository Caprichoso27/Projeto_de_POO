#include "Ficheiro.h"

Ficheiro::Ficheiro(const string &path) : Elemento(path) //inicializa campos aqui, e mais rapido
{
    //ctor
}

Ficheiro::~Ficheiro()
{
    //dtor
}

void Ficheiro::Mostrar(){
    cout << path << endl;
}

void Ficheiro::Cont(int &diretorias, int &files){
    files++;
}
