#ifndef DIRETORIA_H
#define DIRETORIA_H

#include <fstream>
#include <sstream>
#include<iostream>
#include<string>
#include<list>
#include<filesystem>

#include"Elemento.h"
#include"Ficheiro.h"

using namespace std;

/**
@class Diretoria
@brief Classe concreta que representa uma diretoria
*/
class Diretoria : public Elemento
{
    list<Elemento *> LF;

    public:
        /**
        @brief Construtor da classe Diretoria
        @param[in] const string &path - Caminho da diretoria
        */
        Diretoria(const string &path);

        /**
        @brief Destrutor. Responsável por limpar a memória de todos os elementos filhos(lista LF)
        */
        virtual ~Diretoria();

        /**
        @brief Adiciona um elemento (filho) à lista da diretoria
        @param[in] Elemento *el - Ponteiro para o elemento a adicionar
        */
        void AddList(Elemento *el);

        /**
        @brief Retorno um dos campos do objeto em questão(Ficheiro)
        @param[in] const string &campo - Nome do campo do qual se quer o valor
        @return Ponteiro genérico, do qual se terá de fazer cast na receção
        */
        void *Get(const string &campo);

        /**
        @brief Remove filhos da diretoria com base no tipo especificado
        @param[in] int Tipo - variável para indicar o tipo de elemento a pesquisar("DIR" para diretoria, qualquer outra string para ficheiro)
        @return True se a operação foi concluída
        */
        bool RemoverAll_Dir(const string &tipo);

    protected:
        /**
        @brief Escreve o nome do ficheiro no formato de tree
        @see Elemento::Escrever_file
        */
        void Escrever_file(int ultimo, string espaco, int repeticao, ofstream &file_tree);

        /**
        @brief Escreve o nome da diretoria em questão na consola, chama a funcao para que o processo continue
        @see Elemento::Escrever_ecra
        */
        void Escrever_ecra(int ultimo, string espaco, int repeticao);

        /**
        @brief Percorre os filhos contando diretorias e ficheiros
        @see Elemento::Cont
        */
        void Cont(int &diretorias, int &files);

        /**
        @brief Calcula o tamanho da diretoria em memória
        @see Elemento::GetSize
        */
        int GetSize();

        /**
        @brief Soma o tamanho total da diretoria e dos seus filhos recursivamente
        @see Elemento::Mem_total
        */
        void Mem_total(int &bytes_totais);

        /**
        @brief Compara esta diretoria com a maior/menor atual e percorre os filhos
        @see Elemento::ContDiretoria
        */
        void ContDiretoria(Diretoria *&maior, Diretoria *&menor);

        /**
        @brief Percorre os filhos à procura do maior ficheiro
        @see Elemento::BigFile
        */
        void BigFile(Ficheiro *&file);

        /**
        @brief Compara esta diretoria com a maior em memória e percorre os filhos
        @see Elemento::BigDirectory
        */
        void BigDirectory(Diretoria *&dir);

        /**
        @brief Pesquisa nesta diretoria ou recursivamente nos filhos
        @see Elemento::Pesquisar
        */
        Elemento *Pesquisar(const string &s, int Tipo);

        /**
        @brief Verifica se a diretoria deve ser removida
        @see Elemento::RemoverAll3
        */
        bool RemoverAll3(const string &tipo);

        /**
        @brief Move um ficheiro dentro desta estrutura de diretorias
        @see Elemento::MoveFile
        */
        bool MoveFile(const string &Fich, const string &DirNova);

        /**
        @brief Move uma diretoria dentro desta estrutura
        @see Elemento::MoveDir
        */
        bool MoveDir(const string &DirOld, const string &DirNew);

        /**
        @brief Pesquisa diretorias recursivamente
        @see Elemento::PesqDir
        */
        void PesqDir(list<string> &lres, const string &dir);

        /**
        @brief Pesquisa ficheiros recursivamente
        @see Elemento::PesqFile
        */
        void PesqFile(list<string> &lres, const string &file);

        /**
        @brief Pesquisa ficheiros recursivamente, retorna ponteiros
        @see Elemento::PesqFile_Ponteiro
        */
        void PesqFile_Ponteiro(list<Elemento *> &lres, const string &file);

        /**
        @brief Percorre a diretoria agrupando elementos duplicados
        @see Elemento::Dupe
        */
        void Dupe(list<list<Elemento *>> &LS);

        /**
        @brief Procura padrão nos filhos e cria cópias dos encontrados para a lista
        @see Elemento::Find_padrao
        */
        bool Find_padrao(const string &padrao, list<Elemento *> &LS);

        /**
        @brief Adiciona uma lista de elementos à lista LF desta diretoria
        @see Elemento::Colocar_list
        */
        bool Colocar_list(list<Elemento *> LS);

        /**
        @brief Escreve a estrutura da diretoria em XML
        @see Elemento::Escrever_XML
        */
        void Escrever_XML(fstream &xml_file, int nivel);
};

#endif // DIRETORIA_H
