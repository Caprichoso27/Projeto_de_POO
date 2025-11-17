#include "Ficheiro.h"

Ficheiro::Ficheiro(const string &path) : Elemento(path)
{
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

int Ficheiro::GetSize(){
    int tamanho = sizeof(*this);

    tamanho += extensao.capacity() * sizeof(char);
    tamanho += Nome.capacity() * sizeof(char);
    tamanho += path.capacity() * sizeof(char);

    return tamanho;
}

void Ficheiro::Mem_total(size_t &bytes_totais){
    bytes_totais += GetSize();
}

void Ficheiro::BigFile(Ficheiro *&file){
    if(!file){
        file = this;
    }
    if(file->GetSize() < this->GetSize()){
        file = this;
    }
}
