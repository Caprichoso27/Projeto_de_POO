#include<filesystem>
#include <fstream>
#include <sstream>
#include<iostream>
#include<list>
#include "SistemaFicheiros.h"

using namespace std;
namespace fs = std::filesystem;

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
        SistemaFicheiros::CarregarDiretoria(path, dir_atual);
    }
    else{
        cout << "Diretoria não encontrada" << endl;
    }
	return true;
}

void SistemaFicheiros::CarregarDiretoria(const string &path, Diretoria *dir_atual){ //falta metodo para adicionar subdiretorias dentro da diretoria
    //entry-variavel automatica de cada iteracao do directory_iterator
    for (auto const& elemento : fs::directory_iterator{path}){ //vai percurrer o path todo e atribuir um a um a entry
        if(elemento.is_directory()){
            auto *new_dir_atual = new Diretoria(elemento.path().string()); //se construtor n aceitar entry -> entry.path().string()
            dir_atual->AddList(new_dir_atual);
            SistemaFicheiros::CarregarDiretoria(elemento.path().string(), new_dir_atual); //trocar diretoria para que se saiba onde estamos
        }
        else{
            auto *F = new Ficheiro(elemento.path().string()); //se construtor n aceitar entry -> entry.path().string()
            dir_atual->AddList(F);
        }
    }
}

void SistemaFicheiros::MostrarMem(){ //podera tornar-se tree, falta ajustes nos \t
    int nivel = 0;
    this->Dir_principal->Mostrar(nivel);
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
    size_t bytes_totais;
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

    dir_destroy->RemoverAll2(tipo);

    return true;
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
    fs::path path_file = *(string *)file->Get("path");
    fs::file_time_type file_time = fs::last_write_time(path_file);

    //RETIRADO DO MANO CHAT
    auto stp = chrono::time_point_cast<chrono::system_clock::duration>(file_time - fs::file_time_type::clock::now()+ chrono::system_clock::now());

    // Converter para time_t (para formatar/imprimir)
    time_t cftime = chrono::system_clock::to_time_t(stp);

    // Converter para string
    string* resultado = new string(std::ctime(&cftime));

    cout << *resultado << endl;
    system("pause");

    return resultado;
}
