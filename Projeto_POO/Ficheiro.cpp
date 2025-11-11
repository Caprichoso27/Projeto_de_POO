#include "Ficheiro.h"

Ficheiro::Ficheiro(const fs::path &path) : Elemento(path) //inicializa campos aqui, e mais rapido
{
    //ctor
}

Ficheiro::~Ficheiro()
{
    //dtor
}

void Ficheiro::Mostrar(){
    cout << path.string() << endl;
}

void Ficheiro::Cont(int &diretorias, int &files){
    files++;
}
