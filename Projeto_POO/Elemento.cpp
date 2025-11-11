#include "Elemento.h"

Elemento::Elemento(const fs::path &path) : path(path)
{
    Nome = path.filename().string();
}

Elemento::~Elemento()
{
    //dtor
}

void Elemento::Mostrar(){//e suposto nao ter nada
}

void Elemento::Cont(int &diretorias, int &files){//e suposto nao ter nada
}
