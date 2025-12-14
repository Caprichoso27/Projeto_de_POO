#include "Ficheiro.h"

Ficheiro::Ficheiro(const string &path) : Elemento(path)
{
}

Ficheiro::~Ficheiro()
{
    //dtor
}

void Ficheiro::Escrever_file(int ultimo, string espaco, int repeticao, ofstream &file_tree){
    if(ultimo == 0){
        espaco = espaco + "   |";
    }
    else{
        espaco = espaco + "   ";
    }
    file_tree << espaco << "--" << Nome << endl;
}

void Ficheiro::Escrever_ecra(int ultimo, string espaco, int repeticao){
    if(ultimo == 0){
        espaco = espaco + "   |";
    }
    else{
        espaco = espaco + "   ";
    }
    cout << espaco << "--" << Nome << endl;
}

void Ficheiro::Cont(int &diretorias, int &files){
    files++;
}

int Ficheiro::GetSize(){
    int tamanho = sizeof(*this);

    tamanho += Nome.capacity() * sizeof(char);
    tamanho += path.capacity() * sizeof(char);

    return tamanho;
}

void Ficheiro::Mem_total(int &bytes_totais){
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
    if(campo =="nome"){
        return &(this->Nome);
    }
    return NULL;
}

void Ficheiro::PesqFile(list<string> &lres, const string &file){
    if(file.compare(this->Nome) == 0){
        lres.push_front(this->path);
    }
}

void Ficheiro::PesqFile_Ponteiro(list<Elemento *> &lres, const string &file){
    if(file.compare(this->Nome) == 0){
        lres.push_front(this);
    }
}

void Ficheiro::Dupe(list<list<Elemento *>> &LS){
    string name = *(string *)this->Get("nome");
    for(list<Elemento *> &L_interna : LS){
        if(!L_interna.empty()){
            string name_list = *(string *)L_interna.front()->Get("nome");
            if(name.compare(name_list) == 0){
                L_interna.push_front(this);
                return;
            }
        }
    }
    list<Elemento *> nova_lista;
    nova_lista.push_front(this);
    LS.push_back(nova_lista);
}

/*bool Ficheiro::Find_padrao(const string &padrao, list<Elemento *> &LS){
    string file_name = this->Nome;
    string padrao_certo = padrao;
    for(int i=0 ; i<padrao_certo.length() ; i++){
        padrao_certo[i] = tolower(padrao_certo[i]);
    }
    for(int i=0 ; i<file_name.length() ; i++){
        file_name[i] = tolower(file_name[i]);
    }

    if(file_name.find(padrao_certo) != string::npos){
        LS.push_front(this);
        return true;
    }
    return false;
}*/

bool Ficheiro::Find_padrao(const string &padrao, list<Elemento *> &LS){
    string file_name = this->Nome;
    string padrao_certo = padrao;
    for(int i=0 ; i<padrao_certo.length() ; i++){
        padrao_certo[i] = tolower(padrao_certo[i]);
    }
    for(int i=0 ; i<file_name.length() ; i++){
        file_name[i] = tolower(file_name[i]);
    }

    if(file_name.find(padrao_certo) != string::npos){
        return true;
    }
    return false;
}

void Ficheiro::Escrever_XML(fstream &xml_file, int nivel){
    nivel++;
    int i = 0;
    string espaco = "";
    while(i < nivel){
        espaco = espaco + "     ";
        i++;
    }
    xml_file << espaco << "<ficheiro>" << Nome << "</ficheiro>"<< endl;
}
