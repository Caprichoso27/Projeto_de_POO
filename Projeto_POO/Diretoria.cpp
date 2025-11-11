#include "Diretoria.h"

Diretoria::Diretoria(const fs::path &path)  :Elemento(path)
{
}

Diretoria::~Diretoria()
{
    //dtor
}

void Diretoria::AddList(Elemento *el){
    LF.push_front(el);
}

void Diretoria::Mostrar(){
    cout << path.string() << endl;
    for(Elemento *E : this->LF){ //recursivo para que entre na diretoria e repita o processo
        E->Mostrar();
    }
}

void Diretoria::Cont(int &diretorias, int &files){
    diretorias++;
    for(Elemento *E : LF){
        E->Cont(diretorias, files);
    }
}
