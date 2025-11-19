#include "Diretoria.h"

Diretoria::Diretoria(const string &path)  :Elemento(path)
{
}

Diretoria::~Diretoria()
{
    for(Elemento *E : LF){
        delete E;
    }
    LF.clear();
}

void Diretoria::AddList(Elemento *el){
    LF.push_front(el);
}

void Diretoria::Mostrar(int nivel, string linha, int &ult){ //ESTA MERDA TA TD FDD CAGA NISTO-----------------------

    int index = 0;
    int ult_filho = 0;
    string linha_filho = linha;

        cout << linha << Nome << endl;
        for(Elemento *E : this->LF){
            index++;
            if(index == LF.size()){
                ult_filho = 1;
            }
        }

    nivel++;

}

/*  for(Elemento *E : this->LF){ //recursivo para que entre na diretoria e repita o processo
        index++;
        if(index == LF.size()){
            ult_filho = 1;
        }
        E->Mostrar(nivel, linha, ult_filho);
    }*/

//ATE AQUI TA TD MAL-------------------------------------------------------------------------------------------------
void Diretoria::Cont(int &diretorias, int &files){ //percorrer
    diretorias++;
    for(Elemento *E : LF){
        E->Cont(diretorias, files);
    }
}

string *Diretoria::GetPathDir(){
    return &(this->path);
}

void Diretoria::ContDiretoria(Diretoria *&maior, Diretoria *&menor){ //mecanismo de percorrer no fundo
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

int Diretoria::GetSize(){
    int tamanho = sizeof(*this);

    tamanho += Nome.capacity() * sizeof(char);
    tamanho += path.capacity() * sizeof(char);
    tamanho += sizeof(LF) + (LF.size() * sizeof(void *) * 3); //estamos a calcular 3 pointers pq cada no da lista tem pointer para a frente e para tras, bem como para o elemento em questao, uma vez que a nossa lista e de ponteiros

    return tamanho;
}

void Diretoria::Mem_total(size_t &bytes_totais){ //percorrer
    bytes_totais += this->GetSize();
    for(Elemento *E : LF){
        E->Mem_total(bytes_totais);
    }
}

void Diretoria::BigFile(Ficheiro *&file){
    for(Elemento *E : LF){
        E->BigFile(file);
    }
}

void Diretoria::BigDirectory(Diretoria *&dir){
    if(!dir){
        dir = this;
    }
    if(this->GetSize() > dir->GetSize()){
        dir = this;
    }
    for(Elemento *E : LF){
        E->BigDirectory(dir);
    }
}

string *Diretoria::Pesquisar(const string &s, int Tipo){
    if(Tipo == 1){
        int comp = s.compare(this->Nome);
        if(comp == 0){
            return &this->path;
        }
    }
    for(Elemento *E : LF){
        string *pesq = E->Pesquisar(s, Tipo);
        if(pesq != NULL){
            return pesq;
        }
    }
    return NULL;
}
