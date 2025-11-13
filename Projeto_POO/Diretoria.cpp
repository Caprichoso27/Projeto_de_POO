#include "Diretoria.h"

Diretoria::Diretoria(const string &path)  :Elemento(path)
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
    cout << path << endl;
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

string *Diretoria::GetPathDir(){
    return &(this->path);
}

void Diretoria::ContDiretoria(Diretoria *&maior, Diretoria *&menor){
    if(!maior || !menor){
        maior = this;
        menor = this;
    }
    else{
        int tamanho = this->LF.size();
        if(tamanho > maior->LF.size()){
            maior = this;
        }
        if(tamanho < menor->LF.size()){
            menor = this;
        }
    }

    for(Elemento *E : LF){
        E->ContDiretoria(maior, menor);
    }
}
