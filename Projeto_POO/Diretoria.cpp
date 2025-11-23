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

void Diretoria::Mostrar(int nivel){ //ESTA MERDA TA TD FDD CAGA NISTO-----------------------------------
    nivel++;

    cout << Nome << endl;
    for(Elemento *E : this->LF){
        for(int i=1 ; i<=nivel ; i++){
            cout << "   ";
        }
        E->Mostrar(nivel);
    }
}

/*  for(Elemento *E : this->LF){ //recursivo para que entre na diretoria e repita o processo
        index++;
        if(index == LF.size()){
            ult_filho = 1;
        }
        E->Mostrar(nivel, linha, ult_filho);
    }*/

//ATE AQUI TA TD MAL--------------------------------------------------------------------------------------------------------------
void Diretoria::Cont(int &diretorias, int &files){ //percorrer
    diretorias++;
    for(Elemento *E : LF){
        E->Cont(diretorias, files);
    }
}

void *Diretoria::Get(const string &campo){
    if(campo == "path"){
        return &(this->path);
    }
    if(campo =="Nome"){
        return &(this->Nome);
    }
    return NULL;
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

Elemento *Diretoria::Pesquisar(const string &s, int Tipo){
    if(Tipo == 1){
        int comp = s.compare(this->Nome);
        if(comp == 0){
            return this;
        }
    }
    for(Elemento *E : LF){
        Elemento *pesq = E->Pesquisar(s, Tipo);
        if(pesq != NULL){
            return pesq;
        }
    }
    return NULL;
}

bool Diretoria::RemoverAll2(const string &tipo){
    auto E = LF.begin(); //auto porque nao sabemos o return de LF.begin
    while(E != LF.end()){
        Elemento *E2 = *E; //para que tenhamos outro ponteiro, para apagar esta instancia se necessario
        bool remover = E2->RemoverAll3(tipo);
        if(remover == true){
            E = LF.erase(E);
            delete E2;
        }
        else{
            E++;
        }
    }
    return true;
}

bool Diretoria::RemoverAll3(const string &tipo){ //saber se e ou nao para apagar
    if(tipo == "DIR"){
        return true;
    }
    else{
        return false;
    }
}


/*Diretoria *Diretoria::Pesquisa_Dir_Ant(const string &s, int tipo){
    for(Elemento *E : LF){
        Elemento *pesq = E->Pesquisar(s, tipo);
        if(pesq != NULL){
            return this;
        }
    }
    for (Elemento *E : LF) {
        Diretoria *subDir = dynamic_cast<Diretoria*>(E);
        if (subDir != NULL) {
            Diretoria *resultado = subDir->Pesquisa_Dir_Ant(s, tipo);
            if (resultado != NULL) {
                return resultado; // Elemento encontrado em subdiretoria
            }
        }
    }
    return NULL;
}*/

bool Diretoria::MoveFile(const string &Fich, const string &DirNova){
    Elemento *elemento = this->Pesquisar(Fich, 0);
    if(elemento == NULL){
        return false;
    }

    std::filesystem::path path_elemento = *((string *)elemento->Get("path"));
    std::filesystem::path dir_mae = path_elemento.parent_path();
    string dir_antiga = dir_mae.filename().string();//temos o path apenas queremos o nome para a funcao pesquisar nao dar erro

    Diretoria *dir = (Diretoria *)this->Pesquisar(DirNova, 1);
    if(dir == NULL){
        return false;
    }
    Diretoria *dir_ant = (Diretoria *)this->Pesquisar(dir_antiga, 1);

    /*string string_dir = dir->path + "/" + *((string *)file->Get("Nome"));

    std::filesystem::path path_file = *((string *)file->Get("path"));
    std::filesystem::path path_dir = string_dir;

    std::filesystem::rename(path_file, path_dir);*/

    dir->LF.push_front(elemento);
    dir_ant->LF.remove(elemento);

    return true;
}
