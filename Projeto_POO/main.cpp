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
}
