#include<filesystem>
#include <fstream>
#include <sstream>
#include<iostream> //uintmax_t
#include<string>

#include "SistemaFicheiros.h"

using namespace std;

int main(){

	SistemaFicheiros SF;
	string *teste; //teste para search

    cout << "Ola bem-vindo" << endl;

    SF.Load("C:/Users/tiago/Desktop/POO_final/teste");//1 //path completo da diretoria
    //SF.RemoverAll("pasta3",""); //10
    SF.MostrarMem();//teste de memoria
    cout << SF.ContarFicheiros() << endl;
    cout << SF.ContarDirectorias() << endl;
    cout << *(SF.DirectoriaMaisElementos()) << endl;
    cout << *(SF.DirectoriaMenosElementos()) << endl;
    cout << "bytes: " << SF.Memoria() << endl;
    cout << "Ficheiro: " << *(SF.FicheiroMaior()) << endl;
    cout << "Diretoria: " << *(SF.DirectoriaMaisEspaco()) << endl;
    teste = SF.Search("pasta4", 0);//9
    if(teste == NULL){
        cout << "nao encontrado" << endl;
    }
    else{
        cout << "Pesquisa: " << *(teste) << endl;//se colocar mos alguma coisa q n exista da erro, teremos de colocar validacao quando for pra printar
    }
    SF.MoveFicheiro("texto3.txt", "pasta2");//13
    SF.MoverDirectoria("pasta2", "pasta3");//14
    SF.MostrarMem();
}
