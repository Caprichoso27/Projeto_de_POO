#include<filesystem>
#include <fstream>
#include <sstream>
#include<iostream>
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
    this->Dir_principal->Mostrar();
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

    return maior->GetPath();
}

string *SistemaFicheiros::DirectoriaMenosElementos(){
    Diretoria *maior = NULL;
    Diretoria *menor = NULL;
    this->Dir_principal->ContDiretoria(maior, menor);

    return menor->GetPath();
}

string *SistemaFicheiros::FicheiroMaior(){
    Ficheiro *file = NULL;
    this->Dir_principal->BigFile(file);

    return file->GetPath();
}

string *SistemaFicheiros::DirectoriaMaisEspaco(){
    Diretoria *dir = NULL;
    this->Dir_principal->BigDirectory(dir);

    return dir->GetPath();
}

/*string *SistemaFicheiros::Search(const string &s, int Tipo){


}*/

