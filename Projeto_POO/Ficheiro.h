#ifndef FICHEIRO_H
#define FICHEIRO_H

#include<filesystem>
#include <fstream>
#include <sstream>
#include<iostream> //uintmax_t
#include<string>
#include<list>

#include"Elemento.h"

using namespace std;
namespace fs = std::filesystem;

/**
@class Ficheiro
@brief Classe que representa um ficheiro, filha de Elemento
*/
class Ficheiro : public Elemento
{

    public:
        /**
        @brief Construtor da classe Ficheiro.
        @param[in] const string &path - Caminho do ficheiro, desde a "root"
        */
        Ficheiro(const string &path);

        /**
        @brief Destrutor da classe Ficheiro.
        */
        virtual ~Ficheiro();

        /**
        @brief Retorno um dos campos do objeto em questão(Ficheiro)
        @param[in] const string &campo - Nome do campo do qual se quer o valor
        @return Ponteiro genérico, do qual se terá de fazer cast na receção
        */
        void *Get(const string &campo);

    protected:
        /**
        @brief Escreve o nome do ficheiro no formato de tree
        @see Elemento::Escrever_file
        */
        void Escrever_file(int ultimo, string espaco, int repeticao, ofstream &file_tree);

        /**
        @brief Escreve o nome do ficheiro em questão na consola
        @see Elemento::Escrever_ecra
        */
        void Escrever_ecra(int ultimo, string espaco, int repeticao);

        /**
        @brief Incrementa o contador de ficheiros
        @see Elemento::Cont
        */
        void Cont(int &diretorias, int &files);

        /**
        @brief Calcula o tamanho ocupado pelo ficheiro em questão
        @return Tamanho em bytes.
        */
        int GetSize();

        /**
        @brief Adiciona o tamanho do ficheiro em questão ao tamanho total
        @see Elemento::Mem_total
        */
        void Mem_total(int &bytes_totais);

        /**
        @brief Compara o tamanho deste ficheiro com o maior atual
        @see Elemento::BigFile
        */
        void BigFile(Ficheiro *&file);

        /**
        @brief Verifica se o nome deste ficheiro corresponde ao nome pesquisado
        @see Elemento::Pesquisar
        */
        Elemento *Pesquisar(const string &s, int Tipo);

        /**
        @brief Verifica se o ficheiro deve ser removido(retorna true se tipo não for igual a "DIR")
        @see Elemento::RemoverAll3
        */
        bool RemoverAll3(const string &tipo);

        /**
        @brief Adiciona o path do ficheiro em questão à lista se o nome corresponder
        @see Elemento::PesqFile
        */
        void PesqFile(list<string> &lres, const string &file);

        /**
        @brief Adiciona o ponteiro à lista se o nome corresponder
        @see Elemento::PesqFile_Ponteiro
        */
        void PesqFile_Ponteiro(list<Elemento *> &lres, const string &file);

        /**
        @brief Verifica se este ficheiro já existe nas listas de duplicados e adiciona o nome ao espaço correspondente
        @see Elemento::Dupe
        */
        void Dupe(list<list<Elemento *>> &LS);

        /**
        @brief Verifica se o nome do ficheiro contém o padrão, dado pelo utilizador
        @see Elemento::Find_padrao
        */
        bool Find_padrao(const string &padrao, list<Elemento *> &LS);

        /**
        @brief Escreve a tag XML, juntamente com o nome do ficheiro em questão
        @see Elemento::Escrever_XML
        */
        void Escrever_XML(fstream &xml_file, int nivel);

    private:
};

#endif // FICHEIRO_H
