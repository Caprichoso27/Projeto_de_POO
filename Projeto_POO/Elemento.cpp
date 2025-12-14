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

void Elemento::Escrever_file(int ultimo, string espaco, int repeticao, ofstream &file_tree){//e suposto nao ter nada
}

void Elemento::Escrever_ecra(int ultimo, string espaco, int repeticao){
}

void Elemento::Cont(int &diretorias, int &files){//e suposto nao ter nada
}

void Elemento::ContDiretoria(Diretoria *&maior, Diretoria *&menor){
}

int Elemento::GetSize(){
}

void *Elemento::Get(const string &campo){
}

void Elemento::Mem_total(int &bytes_totais){
}

void Elemento::BigFile(Ficheiro *&file){
}

void Elemento::BigDirectory(Diretoria *&dir){
}

Elemento *Elemento::Pesquisar(const string &s, int Tipo){
}

bool Elemento::RemoverAll3(const string &tipo){
}

bool Elemento::MoveFile(const string &Fich, const string &DirNova){
}

bool Elemento::MoveDir(const string &DirOld, const string &DirNew){
}

void Elemento::PesqDir(list<string> &lres, const string &dir){
}

void Elemento::PesqFile(list<string> &lres, const string &file){
}

void Elemento::PesqFile_Ponteiro(list<Elemento *> &lres, const string &file){
}

void Elemento::ChangeName(const string &name){
    this->Nome = name;
}

void Elemento::Dupe(list<list<Elemento *>> &LS){
}

bool Elemento::Find_padrao(const string &padrao, list<Elemento *> &LS){
}

bool Elemento::Colocar_list(list<Elemento *> LS){
}

bool Elemento::Mudar_nome(int &num){
    fs::path path_nome = this->path;

    string nome_wout_ext = path_nome.stem().string();
    string ext = path_nome.extension().string();
    num++;
    string numero = to_string(num);
    if(num >= 100){
        this->Nome = nome_wout_ext + numero + ext;
    }
    else{
        if(num < 10){
            this->Nome = nome_wout_ext + "00" + numero + ext;
        }
        else{
            this->Nome = nome_wout_ext + "0" + numero + ext;
        }
    }
    return true;
}

void Elemento::Escrever_XML(fstream &xml_file, int nivel){
}
