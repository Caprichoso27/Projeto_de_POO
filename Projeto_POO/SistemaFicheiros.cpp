#include<filesystem>
#include <fstream>
#include<iostream>
#include<list>
#include "SistemaFicheiros.h"

using namespace std;
namespace fs = std::filesystem;

SistemaFicheiros::SistemaFicheiros(){
    Dir_principal = NULL;
}

SistemaFicheiros::~SistemaFicheiros(){
    if (Dir_principal != NULL) {
        delete Dir_principal;
        Dir_principal = NULL;
    }
}

bool SistemaFicheiros::Load(const string &path){

	string linha;
	Diretoria *dir_atual;

	if(path.empty()){
		cout << "path não introduzido";
		return false;
	}

	if(fs::exists(path)){
        dir_atual = new Diretoria(path);
        Dir_principal = dir_atual;
        CarregarDiretoria(path, dir_atual);
    }
    else{
        cout << "Diretoria não encontrada" << endl;
        return false;
    }
	return true;
}

void SistemaFicheiros::CarregarDiretoria(const string &path, Diretoria *dir_atual){ //falta metodo para adicionar subdiretorias dentro da diretoria
    //entry-variavel automatica de cada iteracao do directory_iterator
    for (auto const& elemento : fs::directory_iterator{path}){ //vai percurrer o path todo e atribuir um a um a entry
        if(elemento.is_directory()){
            auto *new_dir_atual = new Diretoria(elemento.path().string()); //se construtor n aceitar entry -> entry.path().string()
            dir_atual->AddList(new_dir_atual);
            CarregarDiretoria(elemento.path().string(), new_dir_atual); //trocar diretoria para que se saiba onde estamos
        }
        else{
            auto *F = new Ficheiro(elemento.path().string()); //se construtor n aceitar entry -> entry.path().string()
            dir_atual->AddList(F);
        }
    }
}

int SistemaFicheiros::ContarFicheiros(){
    int diretorias = 0;
    int files = 0;
    this->Dir_principal->Cont(diretorias, files);

    return files;
}

int SistemaFicheiros::ContarDirectorias(){
    int diretorias = 0;
    int files = 0;
    this->Dir_principal->Cont(diretorias, files);

    return diretorias - 1; //Para retirar a diretoria dada pelo utilizador
}

int SistemaFicheiros::Memoria(){
    int bytes_totais = 0;
    this->Dir_principal->Mem_total(bytes_totais);

    return bytes_totais;
}

string *SistemaFicheiros::DirectoriaMaisElementos(){
    Diretoria *maior = NULL;
    Diretoria *menor = NULL;
    this->Dir_principal->ContDiretoria(maior, menor);

    return (string *)maior->Get("path");
}

string *SistemaFicheiros::DirectoriaMenosElementos(){
    Diretoria *maior = NULL;
    Diretoria *menor = NULL;
    this->Dir_principal->ContDiretoria(maior, menor);

    return (string *)menor->Get("path");
}

string *SistemaFicheiros::FicheiroMaior(){
    Ficheiro *file = NULL;
    this->Dir_principal->BigFile(file);

    return (string *)file->Get("path");
}

string *SistemaFicheiros::DirectoriaMaisEspaco(){
    Diretoria *dir = NULL;
    this->Dir_principal->BigDirectory(dir);

    return (string *)dir->Get("path");
}

string *SistemaFicheiros::Search(const string &s, int Tipo){

    Elemento *pesq = this->Dir_principal->Pesquisar(s, Tipo);
    if(pesq == NULL){ //para que o GetPath nao de erro
        return NULL;
    }
    return (string *)pesq->Get("path");
}

bool SistemaFicheiros::RemoverAll(const string &s, const string &tipo){ //validar output
    if(s.empty()){
        return false;
    }

    Diretoria *dir_destroy = (Diretoria *)this->Dir_principal->Pesquisar(s, 1);

    if(dir_destroy == NULL){
        return false;
    }

    dir_destroy->RemoverAll_Dir(tipo);

    return true;
}

void SistemaFicheiros::Escrever_XML(const string &s){
    if(s.empty()){
        return;
    }

    int nivel = -1;

    fstream xml_file;
    xml_file.open(s, std::ios::out);
    if(xml_file.is_open()){
        string path = *(string *)this->Dir_principal->Get("path");
        xml_file << "<path>" << path << "</path>" << endl;
        this->Dir_principal->Escrever_XML(xml_file, nivel);
        xml_file.close();
    }
    else{
        cout << "Erro ao abrir ficheiro" << endl;
    }
}

bool SistemaFicheiros::Ler_XML(const string &s){
    if(s.empty()){
        return false;
    }

    fstream xml_file;
    xml_file.open(s, std::ios::in);
    if(xml_file.is_open()){
        string linha;
        string tipo;
        getline(xml_file, linha);
        int inicio = linha.find(">");
        int fim = linha.rfind("<");
        string path = linha.substr(inicio + 1, fim - (inicio + 1));
        Diretoria *dir = new Diretoria(path);
        CarregarDiretoria_XML(path, dir, xml_file);
        this->Dir_principal = dir;
        return true;
    }
    return false;
}

void SistemaFicheiros::CarregarDiretoria_XML(string path, Diretoria *dir, fstream &xml_file){
    string linha;
    string tipo;
    string valor;
    int inicio;
    int fim;
    string path_original = path;

    while(getline(xml_file, linha)){
        Headers_XML(tipo, valor, linha);
        if(tipo == "ficheiro"){
            path = path + "/" + valor;
            auto *F = new Ficheiro(path); //se construtor n aceitar entry -> entry.path().string()
            dir->AddList(F);
        }
        else if(tipo == "diretoria"){
            path = path + "/" + valor;
            auto *new_dir = new Diretoria(path); //se construtor n aceitar entry -> entry.path().string()
            dir->AddList(new_dir);
            CarregarDiretoria_XML(path, new_dir, xml_file); //trocar diretoria para que se saiba onde estamos
        }
        else if(tipo == "/diretoria"){
            return;
        }
        path = path_original;
    }
}

void SistemaFicheiros::Headers_XML(string &tipo, string &valor, const string &linha){
    int inicio_tipo = linha.find("<");
    if(linha[inicio_tipo + 1] == 'f'){
        int inicio = linha.find(">") + 1;
        int fim = linha.rfind("<");
        valor = linha.substr(inicio, fim - inicio);
        tipo = "ficheiro";
        return;
    }
    if(linha[inicio_tipo + 1] == 'd'){
        int inicio = linha.find("=") + 1;
        int fim = linha.rfind(">");
        valor = linha.substr(inicio, fim - inicio);
        tipo = "diretoria";
        return;
    }
    tipo = "/diretoria";
}

bool SistemaFicheiros::MoveFicheiro(const string &Fich, const string &DirNova){
    if(Fich.empty() || DirNova.empty()){
        return false;
    }

    bool retorno = this->Dir_principal->MoveFile(Fich, DirNova);
    return retorno;
}

bool SistemaFicheiros::MoverDirectoria(const string &DirOld, const string &DirNew){
    if(DirOld.empty() || DirNew.empty()){
        return false;
    }

    bool retorno = this->Dir_principal->MoveDir(DirOld, DirNew);
    return retorno;
}

string *SistemaFicheiros::DataFicheiro(const string &ficheiro){
    Ficheiro *file = (Ficheiro *)this->Dir_principal->Pesquisar(ficheiro, 0);
    if(file == NULL){
        return NULL;
    }
    fs::path path_file = *(string *)file->Get("path"); //visto em https://stackoverflow.com/questions/61030383/how-to-convert-stdfilesystemfile-time-type-to-time-t
    fs::file_time_type file_time = fs::last_write_time(path_file);
    const auto systemTime = std::chrono::file_clock::to_sys(file_time);
    time_t time_file = std::chrono::system_clock::to_time_t(systemTime);

    string resultado = ctime(&time_file);

    return &resultado;
}

void SistemaFicheiros::Tree(const string *fich){
    int ultimo = 0;
    string espaco = "";
    int repeticao = 0;

    if(fich == NULL){
        this->Dir_principal->Escrever_ecra(ultimo, espaco, repeticao);
    }
    else{
        ofstream file_tree;
        file_tree.open(*fich, std::ios_base::out);
        this->Dir_principal->Escrever_file(ultimo, espaco, repeticao, file_tree);
        file_tree.close();
    }
}

void SistemaFicheiros::PesquisarAllDirectorias(list<string> &lres, const string &dir){
    if(dir.empty()){
        return;
    }
    this->Dir_principal->PesqDir(lres, dir);
}

void SistemaFicheiros::PesquisarAllFicheiros(list<string> &lres, const string &file){
    if(file.empty()){
        return;
    }
    this->Dir_principal->PesqFile(lres, file);
}

void SistemaFicheiros::PesquisarAllFicheiros_Ponteiro(list<Elemento *> &lres, const string &file){
    if(file.empty()){
        return;
    }

    this->Dir_principal->PesqFile_Ponteiro(lres, file);
}

void SistemaFicheiros::RenomearFicheiros(const string &fich_old, const string &fich_new){
    list<Elemento *> LS;
    PesquisarAllFicheiros_Ponteiro(LS, fich_old);

    for(Elemento *E : LS){
        E->ChangeName(fich_new);
    }
}

bool SistemaFicheiros::FicheiroDuplicados(){
    list<list<Elemento *>> LS;
    this->Dir_principal->Dupe(LS);

    for(list<Elemento *> lista_interna: LS){
        if(lista_interna.size() > 1){
            return true;
        }
    }
    return false;
}

bool SistemaFicheiros::CopyBatch(const string &padrao, const string &DirOrigem, const string &DirDestino){
    if(!&padrao || !&DirOrigem || !&DirDestino){
        return false;
    }
    list<Elemento *> List_Retirar;

    Elemento *Dir_Origem = this->Dir_principal->Pesquisar(DirOrigem, 1);
    Elemento *Dir_Dest = this->Dir_principal->Pesquisar(DirDestino, 1);
    Dir_Origem->Find_padrao(padrao, List_Retirar);
    Dir_Dest->Colocar_list(List_Retirar);
    list<list<Elemento *>> LS;
    Dir_Dest->Dupe(LS);
    for(list<Elemento *> lista_interna: LS){
        if(lista_interna.size() > 1){
            int num = 0;
            for(Elemento *E : lista_interna){
                cout << "muda nome" << endl;
                E->Mudar_nome(num);
            }
        }
    }
    return true;
}
