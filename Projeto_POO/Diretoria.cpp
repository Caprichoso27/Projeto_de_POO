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

void Diretoria::Escrever_file(int ultimo, string espaco, int repeticao, ofstream &file_tree){
    if(repeticao != 0){
        if(ultimo == 0){
            espaco = espaco + "   |";
        }
        else{
            espaco = espaco + "   ";
        }
        file_tree << espaco << "--" << Nome << endl;
    }
    else{
        repeticao = 1;
        file_tree << espaco << Nome << endl;
    }


    for(Elemento *E : this->LF){
        auto ult = LF.end();
        ult--;
        if(E == *ult){
            ultimo = 1;
        }
        else{
            ultimo = 0;
        }
        E->Escrever_file(ultimo, espaco, repeticao, file_tree);
    }
}

void Diretoria::Escrever_ecra(int ultimo, string espaco, int repeticao){
    if(repeticao != 0){
        if(ultimo == 0){
            espaco = espaco + "   |";
        }
        else{
            espaco = espaco + "   ";
        }
        cout << espaco << "--" << Nome << endl;
    }
    else{
        repeticao = 1;
        cout << espaco << Nome << endl;
    }


    for(Elemento *E : this->LF){
        auto ult = LF.end();
        ult--;
        if(E == *ult){
            ultimo = 1;
        }
        else{
            ultimo = 0;
        }
        E->Escrever_ecra(ultimo, espaco, repeticao);
    }
}

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

void Diretoria::Mem_total(int &bytes_totais){ //percorrer
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

bool Diretoria::RemoverAll_Dir(const string &tipo){
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

    dir->LF.push_front(elemento);
    dir_ant->LF.remove(elemento);

    return true;
}

bool Diretoria::MoveDir(const string &DirOld, const string &DirNew){
    Elemento *elemento = this->Pesquisar(DirOld, 1);
    if(elemento == NULL){
        return false;
    }

    std::filesystem::path path_elemento = *((string *)elemento->Get("path"));
    std::filesystem::path dir_mae = path_elemento.parent_path();
    string dir_antiga = dir_mae.filename().string();//temos o path apenas queremos o nome para a funcao pesquisar nao dar erro

    Diretoria *dir = (Diretoria *)this->Pesquisar(DirNew, 1);
    if(dir == NULL){
        return false;
    }
    Diretoria *dir_ant = (Diretoria *)this->Pesquisar(dir_antiga, 1);

    dir->LF.push_front(elemento);
    dir_ant->LF.remove(elemento);

    return true;
}

void Diretoria::PesqFile(list<string> &lres, const string &file){
    for(Elemento *E : LF){
        E->PesqFile(lres, file);
    }
}

void Diretoria::PesqDir(list<string> &lres, const string &dir){
    if(dir.compare(this->Nome) == 0){
        lres.push_front(this->path);
    }

    for(Elemento *E : LF){
        E->PesqDir(lres, dir);
    }
}

void Diretoria::PesqFile_Ponteiro(list<Elemento *> &lres, const string &file){

    for(Elemento *E : LF){
        E->PesqFile_Ponteiro(lres, file);
    }
}

void Diretoria::Dupe(list<list<Elemento *>> &LS){
    for(Elemento *E : LF){
        E->Dupe(LS);
    }
}

/*bool Diretoria::Find_padrao(const string &padrao, list<Elemento *> &LS){
    auto ult = LF.begin();
    bool remover;

    while(ult != LF.end()) {
        Elemento *E = *ult;

        remover = E->Find_padrao(padrao, LS);

        if (remover == true){
            ult = LF.erase(ult);
        }
        else{
            ++ult;
        }
    }
    return false;
}*/

bool Diretoria::Find_padrao(const string &padrao, list<Elemento *> &LS){
    auto ult = LF.begin();
    string path;

    bool copiar;

    for(Elemento *E : LF){
        copiar = E->Find_padrao(padrao, LS);
        if(copiar == true){
            path = *(string *)E->Get("path");
            auto *F = new Ficheiro(path); //se construtor n aceitar entry -> entry.path().string()
            LS.push_front(F);
        }
    }
    return false;
}

bool Diretoria::Colocar_list(list<Elemento *> LS){
    for(Elemento *E : LS){
        this->LF.push_front(E);
    }
    return true;
}

void Diretoria::Escrever_XML(fstream &xml_file, int nivel){
    nivel++;
    int i = 0;
    string espaco = "";
    while(i < nivel){
        espaco = espaco + "     ";
        i++;
    }
    if(nivel > 0){
        xml_file << espaco << "<diretoria name=" << this->Nome << ">" << endl;

        for(Elemento *E : this->LF){
            E->Escrever_XML(xml_file, nivel);
        }

        xml_file << espaco << "</diretoria>" << endl;
    }
    else{
        for(Elemento *E : this->LF){
            E->Escrever_XML(xml_file, nivel);
        }
    }
}
