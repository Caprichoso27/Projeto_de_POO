#ifndef SISTEMAFICHEIROS_H
#define SISTEMAFICHEIROS_H
#include<string>

#include"Diretoria.h"
#include"Ficheiro.h"

using namespace std;

class SistemaFicheiros
{
    Diretoria *Dir_principal;

    void CarregarDiretoria(const string &path, Diretoria *dir_atual);

	public:
		bool Load(const string &path);
		void MostrarMem(); //teste de memoria, pode tornar se tree
		int ContarFicheiros();
		int ContarDirectorias(); //feito ate aqui
		int Memoria();
		string *DirectoriaMaisElementos ();
		string *DirectoriaMenosElementos ();
		string *FicheiroMaior();
		string *DirectoriaMaisEspaco();
		string *Search(const string &s, int Tipo);//tipo = 0 ->file; tipo = 1->dir
		bool RemoverAll(const string &s, const string &tipo); //true->destruiu o que era suposto
		bool MoveFicheiro(const string &Fich, const string &DirNova);
	protected:
};

#endif
