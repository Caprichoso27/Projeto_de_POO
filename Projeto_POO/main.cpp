#include<filesystem>
#include <fstream>
#include<iostream>
#include<string>

#include "SistemaFicheiros.h"
#include "menu.h"

using namespace std;

int main(){

	SistemaFicheiros *SF = new SistemaFicheiros();
	char op;
	string *pesquisa; //teste para search
	string input;
	string input2;
	string input3;
	list<string> LS;
	bool retorno;

    op = menu_carregamento();
    switch(op){
        case '1': //introduzir path
            do{
                cout << "Introduza o caminho da diretoria: ";
                cin >> input;
                retorno = SF->Load(input);
                system("cls");
            }while(retorno == false);
            cout << "Dados carregados com sucesso" << endl;
            system("pause");
            break;
        case '2': //carregar XML
            do{
                cout << "Introduza o nome do ficheiro a carregar: ";
                cin >> input;
                retorno = SF->Ler_XML(input);
                system("cls");
            }while(retorno == false);
            cout << "Dados carregados com sucesso" << endl;
            system("pause");
            break;
        default:
            break;
    }

    do{
        op = menu_principal();
        switch(op){
            case '1': //Mostrar Diretoria
                system("cls");
                SF->Tree();
                system("pause");
                break;
            case '2': //Pesquisas
                op = menu_pesquisas();
                switch(op){
                    case '1': //pesquisar diretorias
                        input = introduzir_dir();
                        pesquisa = SF->Search(input, 1);
                        if(pesquisa == NULL){
                            cout << "nao encontrado" << endl;
                        }
                        else{
                            cout << "Pesquisa: " << *(pesquisa) << endl;
                        }
                        system("pause");
                        break;
                    case '2': //Pesquisar ficheiros
                        input = introduzir_file();
                        pesquisa = SF->Search(input, 0);
                        if(pesquisa == NULL){
                            cout << "nao encontrado" << endl;
                        }
                        else{
                            cout << "Pesquisa: " << *(pesquisa) << endl;
                        }
                        SF->DataFicheiro(input);
                        system("pause");
                        break;
                    default:
                        break;
                }
                break;
            case '3': //Estatisticas
                system("cls");
                cout << "Total de Ficheiros: " << SF->ContarFicheiros() << endl;
                cout << "Total de diretorias: " << SF->ContarDirectorias() << endl;
                cout << "Diretoria com mais ficheiros: " << *(SF->DirectoriaMaisElementos()) << endl;
                cout << "Diretoria com menos ficheiros: " << *(SF->DirectoriaMenosElementos()) << endl;
                cout << "Memoria total ocupada: " << SF->Memoria() << "bytes" << endl;
                cout << "Ficheiro que mais ocupa memoria: " << *(SF->FicheiroMaior()) << endl;
                cout << "Diretoria que mais ocupa memoria: " << *(SF->DirectoriaMaisEspaco()) << endl;
                system("pause");
                break;
            case '4': //Remover
                op = menu_remocao();
                switch(op){
                    case '1': //Remover Diretoria
                        input = introduzir_dir();
                        retorno = SF->RemoverAll(input,"DIR");
                        if(retorno == true){
                            cout << "Diretoria(s) removida(s) com sucesso" << endl;
                        }
                        else{
                            cout << "Erro na remocao" << endl;
                        }
                        system("pause");
                        break;
                    case '2': //Remover ficheiros
                        input = introduzir_dir();
                        retorno = SF->RemoverAll(input,"");
                        if(retorno == true){
                            cout << "Ficheiro(s) removido(s) com sucesso" << endl;
                        }
                        else{
                            cout << "Erro na remocao" << endl;
                        }
                        system("pause");
                        break;
                    default:
                        break;

                }
                break;
            case '5'://Mover
                op = menu_movimentacao();
                switch(op){
                    case '1': //Mover diretoria
                        input = introduzir_dir();
                        cout << "Destino: " << endl;
                        input2 = introduzir_dir();
                        SF->MoverDirectoria(input, input2);
                        if(retorno == true){
                            cout << "Diretoria movida com sucesso" << endl;
                        }
                        else{
                            cout << "Erro na mudanca" << endl;
                        }
                        system("pause");
                        break;
                    case '2': //Mover ficheiro
                        input = introduzir_file();
                        cout << "Destino: " << endl;
                        input2 = introduzir_dir();
                        SF->MoveFicheiro(input, input2);
                        if(retorno == true){
                            cout << "Ficheiro movido com sucesso" << endl;
                        }
                        else{
                            cout << "Erro na mudança" << endl;
                        }
                        system("pause");
                        break;
                    default:
                        break;
                }
                break;
            case '6': //Verificar duplicados
                retorno = SF->FicheiroDuplicados();
                if(retorno == true){
                    cout << "ha ficheiros repetidos" << endl;
                }
                else{
                    cout << "nao ha ficheiros repetidos" << endl;
                }
                system("pause");
                break;
            case '7': //Renomear ficheiros
                cout << "Nome original: " << endl;
                input = introduzir_file();
                cout << "Novo nome: " << endl;
                input2 = introduzir_file();
                SF->RenomearFicheiros(input, input2);
                cout <<  "Ficheiro(s) renomeados com sucesso" << endl;
                system("pause");
                break;
            case '8': //Pesquisar repitidos
                op = menu_pesquisas_all();
                switch(op){
                    case '1':{ //Pesquisar diretorias repetidas
                        input = introduzir_dir();
                        SF->PesquisarAllDirectorias(LS, input);
                        for(string input : LS){
                            cout << input << endl;
                        }
                        system("pause");
                        break;
                    case '2': //Pesquisar ficheiros repitidos
                        input = introduzir_file();
                        SF->PesquisarAllFicheiros(LS, input);
                        for(string input : LS){
                            cout << input << endl;
                        }
                        system("pause");
                        break;}
                    default: //sair
                        break;
                }
                break;
            case '9': //Copiar Ficheiros
                cout << "Diretoria de Origem:" << endl;
                input = introduzir_dir();
                cout << "Diretoria de Destino:" << endl;
                input2 = introduzir_dir();
                cout << "Introduza nome/parte do nome do ficheiro: ";
                cin >> input3;
                retorno = SF->CopyBatch(input3, input, input2);
                if(retorno == true){
                    cout << "Ficheiros copiados com sucesso" << endl;
                }
                else{
                    cout << "Erro na copia" << endl;
                }
                system("pause");
                break;
            case '0': //Exportar dados
                op = menu_exportacao();
                cout << "Nome: ";
                cin >> input;
                system("cls");
                switch(op){
                    case '1': //Exportar xml
                        input = input + ".xml";
                        SF->Escrever_XML(input);
                        cout << "Dados exportados com sucesso";
                        system("pause");
                        break;
                    case '2': //Exportar txt
                        input = input + ".txt";
                        SF->Tree(&input);
                        cout << "Dados exportados com sucesso";
                        system("pause");
                        break;
                }
                break;
            default:
                delete(SF);
                break;
        }
    }while (op >= '0' && op <= '9');
    return 0;


    //SF.RemoverAll("pasta3",""); //10
    /*cout << SF.ContarFicheiros() << endl;
    cout << SF.ContarDirectorias() << endl;
    cout << *(SF.DirectoriaMaisElementos()) << endl;
    cout << *(SF.DirectoriaMenosElementos()) << endl;
    cout << "bytes: " << SF.Memoria() << endl;
    cout << "Ficheiro: " << *(SF.FicheiroMaior()) << endl;
    cout << "Diretoria: " << *(SF.DirectoriaMaisEspaco()) << endl;*/
    /*teste = SF.Search("pasta4", 0);//9
    if(teste == NULL){
        cout << "nao encontrado" << endl;
    }
    else{
        cout << "Pesquisa: " << *(teste) << endl;//se colocar mos alguma coisa q n exista da erro, teremos de colocar validacao quando for pra printar
    }*/
    //SF.Escrever_XML("tree.xml");
    //SF.MoveFicheiro("texto3.txt", "pasta2");//13
    //SF.MoverDirectoria("pasta2", "pasta3");//14
    //SF.DataFicheiro("texto3.txt");//15
    //SF.Tree(); //16
    /*list<string> LS;
    SF.PesquisarAllDirectorias(LS, "pasta2");
    SF.PesquisarAllFicheiros(LS, "texto1.txt");
    //SF.RenomearFicheiros("texto1.txt", "mudou.txt");*/
    /*bool res = SF.FicheiroDuplicados();
    if(res == true){
        cout << "ha repeticao" << endl;
    }
    else{
        cout << "NAO ha repeticao" << endl;
    }*/
    //SF.CopyBatch("TEXT", "pasta3", "pasta2");
}

