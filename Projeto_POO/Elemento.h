#ifndef ELEMENTO_H
#define ELEMENTO_H

#include<filesystem>
#include <fstream>
#include <sstream>
#include<iostream> //uintmax_t
#include<string>
#include<list>

using namespace std;
namespace fs = std::filesystem;

class Diretoria;
class Ficheiro;

/**
@class Elemento
@brief Classe que reperesenta um componente de uma diretoria genérico(pasta ou ficheiro)
*/
class Elemento
{
    protected:
    string Nome;
    string path;

    public:
        /**
        @brief Construtor da classe Elemento.
        @param[in] const string &path - O caminho do elemento para inicializar o objeto
        */
        Elemento(const string &path);

        /**
        @brief Destrutor virtual da classe Elemento
        */
        virtual ~Elemento();

        /**
        @brief Escreve a estrutura da diretoria "mãe" num ficheiro de texto(para exportação).
        @param[in] int ultimo - Variável para indicar se determinado file é o último na lista de uma determinada diretoria
        @param[in] string espaco - String de espacos anteriores, para que haja diferença de níveis
        @param[in] int repeticao - Contador auxiliar para controlo de recursividade
        @param[in,out] ofstream &file_tree - Ponteiro do ficheiro para onde a Tree está a ser escrita
        */
        virtual void Escrever_file(int ultimo, string espaco, int repeticao, ofstream &file_tree);

        /**
        @brief Mostra a estrutura da diretoria "mãe"
        @param[in] int ultimo - Variável para indicar se determinado file é o último na lista de uma determinada diretoria
        @param[in] string espaco - String de espacos anteriores, para que haja diferença de níveis
        @param[in] int repeticao - Contador auxiliar para controlo de recursividade
        */
        virtual void Escrever_ecra(int ultimo, string espaco, int repeticao);

        /**
        @brief Contabiliza o número de diretorias e ficheiros na diretoria "mãe"
        @param[in,out] int &diretorias - Contador de diretorias
        @param[in,out] int &files - Contador de ficheiros
        */
        virtual void Cont(int &diretorias, int &files);

        /**
        @brief Encontra a diretoria com mais e menos elementos
        @param[in,out] Diretoria *&maior - Ponteiro para a diretoria com mais elementos encontrada(variando ao longo da execução)
        @param[in,out] Diretoria *&menor - Ponteiro para a diretoria com menos elementos encontrada(variando ao longo da execução)
        */
        virtual void ContDiretoria(Diretoria *&maior, Diretoria *&menor);

        /**
        @brief Calcula o tamanho do objeto em memória
        @return int - O tamanho em bytes do objeto ao qual esta adjacente
        */
        virtual int GetSize();

        /**
        @brief Retorno um dos campos do objeto em questão(Diretoria, Ficheiro)
        @param[in] const string &campo - Nome do campo do qual se quer o valor
        @return Ponteiro genérico, do qual se terá de fazer cast na receção
        */
        virtual void *Get(const string &campo);

        /**
        @brief Calcula o total de memória ocupada por toda a diretoria, de forma recursiva
        @param[in,out] int &bytes_totais - Acumulador de bytes
        */
        virtual void Mem_total(int &bytes_totais);

        /**
        @brief Encontra o ficheiro que ocupa mais memória
        @param[in,out] Ficheiro *&file - Ponteiro para o maior ficheiro encontrado(variando ao longo da execução)
        */
        virtual void BigFile(Ficheiro *&file);

        /**
        @brief Encontra a sub-diretoria que ocupa mais memória
        @param[in,out] Diretoria *&dir - Ponteiro para a maior diretoria encontrada(variando ao longo da execução)
        */
        virtual void BigDirectory(Diretoria *&dir);

        /**
        @brief Pesquisa um elemento pelo nome na diretoria "mãe"
        @param[in] const string &s - O nome a pesquisar
        @param[in] int Tipo - O tipo de elemento (1 para Diretoria, 0 para Ficheiro)
        @return Ponteiro para o elemento encontrado ou NULL
        */
        virtual Elemento *Pesquisar(const string &s, int Tipo);

        /**
        @brief Verifica se o elemento deve ser removido com base no tipo
        @param[in] const string &tipo - String que define o critério ("DIR" para diretorias, qualquer outra string para ficheiros)
        @return True se for para remover, False caso contrário
        */
        virtual bool RemoverAll3(const string &tipo);

        /**
        @brief Move um ficheiro para uma nova diretoria
        @param[in] const string &Fich - Nome do ficheiro a mover
        @param[in] const string &DirNova - Nome da diretoria de destino
        @return True se movido com sucesso, False caso contrário
        */
        virtual bool MoveFile(const string &Fich, const string &DirNova);

        /**
        @brief Move uma diretoria para outra diretoria
        @param[in] const string &DirOld - Nome da diretoria a mover
        @param[in] const string &DirNew - Nome da diretoria de destino
        @return True se movido com sucesso, False caso contrário
         */
        virtual bool MoveDir(const string &DirOld, const string &DirNew);

        /**
        @brief Pesquisa todas as diretorias existentes com um determinado nome
        @param[in,out] list<string> &lres - Lista de strings onde os path de cada diretoria encontrada correspondente a pesquisa
        @param[in] const string &dir - Nome da diretoria a pesquisar
        */
        virtual void PesqDir(list<string> &lres, const string &dir);

        /**
        @brief Pesquisa todas os ficheiros existentes com um determinado nome
        @param[in,out] list<string> &lres - Lista de strings onde os path de cada ficheiro encontrado correspondente a pesquisa
        @param[in] const string &file - Nome do ficheiro a pesquisar.
         */
        virtual void PesqFile(list<string> &lres, const string &file);

        /**
        @brief Pesquisa todas os ficheiros existentes com um determinado nome(retorna ponteiros)
        @param[in,out] list<Elemento *> &lres - Lista de ponteiros para Elemento onde os resultados serão adicionados
        @param[in] const string &file - Nome do ficheiro a pesquisar
        */
        virtual void PesqFile_Ponteiro(list<Elemento *> &lres, const string &file);

        /**
        @brief Altera o nome do elemento
        @param[in] const string &name - O novo nome a atribuir
        */
        void ChangeName(const string &name);

        /**
        @brief Verifica duplicados agrupando-os por nome
        @param[in,out] list<list<Elemento *>> &LS - Hashing onde cada sub-lista contém elementos com o mesmo nome
        */
        virtual void Dupe(list<list<Elemento *>> &LS);

        /**
        @brief Procura ficheiros que contenham um padrão no nome e adiciona-os a uma lista
        @param[in] const string &padrao - Padrão de texto a procurar
        @param[in,out] list<Elemento *> &LS - Lista onde os elementos encontrados serão adicionados
        @return True se encontrou, False caso contrário
        */
        virtual bool Find_padrao(const string &padrao, list<Elemento *> &LS);

        /**
        @brief Adiciona à lista da diretoria adjacente, todos os elementos presentes na lista LS, passada por parâmetro
        @param[in] list<Elemento *> LS - Lista de elementos a adicionar
        @return True se adicionado com sucesso
        */
        virtual bool Colocar_list(list<Elemento *> LS);

        /**
        @brief Renomeia o ficheiro adicionando um número sequencial para diferenciar possíveis duplicados
        @param[in,out] int &num - Contador para gerar o número sequencial
        @return True se renomeado com sucesso
        */
        bool Mudar_nome(int &num);

        /**
        @brief Exporta a estrutura da diretoria no formato XML
        @param[in,out] fstream &xml_file - Ponteiro para ficheiro XML onde será escrita a diretoria em XML
        @param[in] int nivel - Contador para que se saiba quando "\t" o elemento terá de ter atrás
        */
        virtual void Escrever_XML(fstream &xml_file, int nivel);
};

#endif // ELEMENTO_H
