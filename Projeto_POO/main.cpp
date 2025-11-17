#include<filesystem>
#include <fstream>
#include <sstream>
#include<iostream> //uintmax_t
#include<string>

#include "SistemaFicheiros.h"

using namespace std;

int main(){

	SistemaFicheiros SF;

    cout << "Ola bem-vindo" << endl;

    SF.Load("C:/Users/tiago/Desktop/POO_final/teste"); //path completo da diretoria
    //SF.MostrarMem();//teste de memoria
    cout << SF.ContarFicheiros() << endl;
    cout << SF.ContarDirectorias() << endl;
    cout << *(SF.DirectoriaMaisElementos()) << endl;
    cout << *(SF.DirectoriaMenosElementos()) << endl;
    cout << "bytes: " << SF.Memoria() << endl;
    cout << "Ficheiro: " << *(SF.FicheiroMaior()) << endl;
    cout << "Diretoria: " << *(SF.DirectoriaMaisEspaco()) << endl;
}
