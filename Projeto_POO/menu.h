#include<iostream>
#include<string>

/**
@brief Menu inicial de carregamento de dados
@return O caracter com a opção escolhida
*/
char menu_carregamento();

/**
@brief Menu principal com todas as funcionalidades do sistema
@return O caracter com a opção escolhida
*/
char menu_principal();

/**
@brief Menu para escolher o formato de exportação
@return O caracter com a opção escolhida
*/
char menu_exportacao();

/**
@brief Menu de seleção de tipo para pesquisa.
@return O caracter com a opção escolhida
*/
char menu_pesquisas();

/**
@brief Menu de seleção de tipo para remoção
@return O caracter com a opção escolhida
*/
char menu_remocao();

/**
@brief Menu de seleção de tipo para movimentação
@return O caracter com a opção escolhida
*/
char menu_movimentacao();

/**
@brief Menu de pesquisa global (repetidos).
@return O caracter com a opção escolhida
*/
char menu_pesquisas_all();

/**
@brief Solicita ao utilizador o nome de uma diretoria
@return A string introduzida pelo utilizador
*/
std::string introduzir_dir();

/**
@brief Solicita ao utilizador o nome de um ficheiro
@return A string introduzida pelo utilizador
*/
std::string introduzir_file();
