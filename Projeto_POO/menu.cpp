#include<iostream>
#include<string>
#include <limits>
#include "menu.h"

using namespace std;

char menu_carregamento(){
    char op;
    do{
        system("cls");
        cout << "Como quer carregar os dados:" << endl;
        cout << "Indicar caminho para diretoria (1)" << endl;
        cout << "Carregar ficheiro XML (2)" << endl;
        cout << "Opcao escolhida: ";
        cin >> op;
    }while(op <= '0' || op >= '3');
    return op;
}

char menu_principal(){
    char op;
        system("cls");
        cout << "Bem-Vindo!" << endl;
        cout << "Mostrar Diretoria     (1)" << endl;
        cout << "Pesquisar...          (2)" << endl;
        cout << "Estatisticas          (3)" << endl;
        cout << "Remover...            (4)" << endl;
        cout << "Mover...              (5)" << endl;
        cout << "Verificar repeticoes  (6)" << endl;
        cout << "Renomear Ficheiros    (7)" << endl;
        cout << "Pesquisar repetidos   (8)" << endl;
        cout << "Copiar ficheiros      (9)" << endl;
        cout << "Exportar Dados        (0)" << endl;
        cout << "sair              (outro)" << endl;
        cout << "Opcao escolhida: ";
        cin >> op;
    return op;
}

char menu_exportacao(){
    char op;
    do{
        system("cls");
        cout << "Que formato quer os seus dados" << endl;
        cout << "xml ---------------------- (1)" << endl;
        cout << "txt ---------------------- (2)" << endl;
        cout << "sair --------------------- (0)" << endl;
        cout << "Opcao escolhida: ";
        cin >> op;
    }while(op < '0' || op >= '3');
    return op;
}

char menu_pesquisas(){
    char op;
    do{
        system("cls");
        cout << "O que quer pesquisar?" << endl;
        cout << "Diretoria ------- (1)" << endl;
        cout << "Ficheiro -------- (2)" << endl;
        cout << "sair ------------ (0)" << endl;
        cout << "Opcao escolhida: ";
        cin >> op;
    }while(op < '0' || op >= '3');
    return op;
}

char menu_remocao(){
    char op;
    do{
        system("cls");
        cout << "O que quer remover?" << endl;
        cout << "Diretoria ----- (1)" << endl;
        cout << "Ficheiro ------ (2)" << endl;
        cout << "sair ---------- (0)" << endl;
        cout << "Opcao escolhida: ";
        cin >> op;
    }while(op < '0' || op >= '3');
    return op;
}

char menu_movimentacao(){
    char op;
    do{
        system("cls");
        cout << "O que quer mover?" << endl;
        cout << "Diretoria --- (1)" << endl;
        cout << "Ficheiro ---- (2)" << endl;
        cout << "sair -------- (0)" << endl;
        cout << "Opcao escolhida: ";
        cin >> op;
    }while(op < '0' || op >= '3');
    return op;
}

char menu_pesquisas_all(){
    char op;
    do{
        system("cls");
        cout << "Onde quer pesquisar?" << endl;
        cout << "Diretoria ------ (1)" << endl;
        cout << "Ficheiro ------- (2)" << endl;
        cout << "sair ----------- (0)" << endl;
        cout << "Opcao escolhida: ";
        cin >> op;
    }while(op < '0' || op >= '3');
    return op;
}

string introduzir_dir(){
    string input;

    cout << "Introduza o nome da diretoria: ";
    cin >> input;

    return input;
}

string introduzir_file(){
    string input;

    cout << "Introduza o nome do ficheiro: ";
    cin >> input;

    return input;
}
