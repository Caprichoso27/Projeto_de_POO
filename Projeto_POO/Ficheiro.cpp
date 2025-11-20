#include "Ficheiro.h"

Ficheiro::Ficheiro(const string &path) : Elemento(path)
{
}

Ficheiro::~Ficheiro()
{
    //dtor
}

void Ficheiro::Mostrar(int nivel){
    cout << Nome << endl;
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

Elemento *Ficheiro::Pesquisar(const string &s, int Tipo){
    if(Tipo == 0){
        int comp = s.compare(this->Nome);
        if(comp == 0){
            return this;
        }
    }
    return NULL;
}

bool Ficheiro::RemoverAll3(const string &tipo){
    if(tipo != "DIR"){
        return true;
    }
    else{
        return false;
    }
}

void *Ficheiro::Get(const string &campo){
    if(campo == "path"){
        return &(this->path);
    }
    if(campo =="extensao"){
        return &(this->extensao);
    }
    if(campo =="Nome"){
        return &(this->Nome);
    }
    return NULL;
}

