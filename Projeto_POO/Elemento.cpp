#include "Elemento.h"

Elemento::Elemento(const string &path) : path(path)
{
    fs::path path_conv = path;
    Nome = path_conv.filename().string();
}

Elemento::~Elemento()
{
    //dtor
}

void Elemento::Mostrar(){//e suposto nao ter nada
}

void Elemento::Cont(int &diretorias, int &files){//e suposto nao ter nada
}

void Elemento::ContDiretoria(Diretoria *&maior, Diretoria *&menor){
}

int Elemento::GetSize(){
}

string *Elemento::GetPath(){
    return &(this->path);
}

void Elemento::Mem_total(size_t &bytes_totais){
}

void Elemento::BigFile(Ficheiro *&file){
}

void Elemento::BigDirectory(Diretoria *&dir){
}
