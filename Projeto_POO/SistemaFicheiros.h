#ifndef SISTEMAFICHEIROS_H
#define SISTEMAFICHEIROS_H
#include<string>

#include"Diretoria.h"
#include"Ficheiro.h"

using namespace std;

class SistemaFicheiros
{
    Elemento *Dir_principal;
    /**
    @brief Carrega a estrutura de dados a partir de um path dado pelo utilizador
    @param const string &path - string onde é guardado o caminho dado pelo utilizador
    @param Diretoria *dir_atual - será o ponteiro que terá acesso à nossa "mãe", no funco a lista que contêm todas as outras
    @return
    */
    void CarregarDiretoria(const string &path, Diretoria *dir_atual);
    /**
    @brief Pesquisa na diretoria completa e coloca numa lista os ficheiros com o mesmo nome, dado pelo utilizador
    @param[in,out] list<Elemento *> &lres - Lista onde serão guardados os ponteiros cujos ficheiros são repetidos
    @param[in] const string &file - string com o nome dado pelo utilizador
    @return
    */
    void PesquisarAllFicheiros_Ponteiro(list<Elemento *> &lres, const string &file);
    /**
    @brief Função auxiliar de Ler_XML(), neste caso esta foca-se no carregamento dados que estarão dentro da diretoria em questão
    @param[in] string path - string que tem o path da diretoria, desde o root, para que possamos carregar o resto dos dados
    @param[in] Diretoria *dir - Ponteiro para a diretoria "mãe", para que a estrutura tenha acesso a todos os ficheiros
    @param[in] fstream &xml_file - Ponteiro para o ficheiro previamente aberto, neste caso um ficheiro XML
    @return
    */
    void CarregarDiretoria_XML(string path, Diretoria *dir, fstream &xml_file);
    /**
    @brief Separa de cada linha as tags de XML, bem como o conteúdo propriamente dito de cada linha
    @param[in] string path - string que tem o path da diretoria, desde o root, para que possamos carregar o resto dos dados
    @param[in] Diretoria *dir - Ponteiro para a diretoria "mãe", para que a estrutura tenha acesso a todos os ficheiros
    @param[in] fstream &xml_file - Ponteiro para o ficheiro previamente aberto, neste caso um ficheiro XML
    @return
    */
    void Headers_XML(string &tipo, string &valor, const string &linha);

	public:
	    /**
        @brief Construtor padrão Inicializa a diretoria "mãe"
        */
	    SistemaFicheiros();

        /**
        @brief Destrutor Limpa toda a memória alocada para a árvore de ficheiros.
        */
	    virtual ~SistemaFicheiros();

        /**
        @brief Carrega a estrutura de ficheiros a partir de um caminho dado pelo utilizador
        @param[in] const string &path - Caminho para a pasta que o utilizador quer gerir
        @return True se o carregamento for bem sucedido, False caso contrário.
        */
		bool Load(const string &path);

        /**
        @brief Conta o número total de ficheiros da diretoria em questão
        @return O número total de ficheiros
        */
		int ContarFicheiros();

        /**
        @brief Conta o número total de sub-diretorias da diretoria em questão
        @return O número total de diretorias
        */
		int ContarDirectorias();

        /**
        @brief Calcula a memória total ocupada por todos os elementos
        @return O total de bytes ocupados pela diretoria
        */
		int Memoria();

        /**
        @brief Identifica a diretoria que contém o maior número de sub-elementos
        @return Ponteiro para string com o path da diretoria encontrada(com mais elementos)
        */
		string *DirectoriaMaisElementos ();

        /**
        @brief Identifica a diretoria que contém o menor número de sub-elementos
        @return Ponteiro para string com o path da diretoria encontrada(com menos elementos)
        */
		string *DirectoriaMenosElementos ();

        /**
        @brief Identifica o ficheiro que ocupa mais espaço em memória
        @return Ponteiro para string com o path do ficheiro encontrado
        */
		string *FicheiroMaior();

        /**
        @brief Identifica a diretoria que ocupa mais espaço total(somatório dos seus elementos)
        @return Ponteiro para string com o path da diretoria
        */
		string *DirectoriaMaisEspaco();

        /**
        @brief Pesquisa um elemento na árvore
        @param[in] const string &s - O nome do elemento a pesquisar
        @param[in] int Tipo - variável para indicar o tipo de elemento a pesquisar(0 para ficheiros, 1 para diretoria)
        @return Ponteiro para string com o path do elemento encontrado ou NULL se não existir
        */
		string *Search(const string &s, int Tipo);

        /**
        @brief Remove elementos do sistema de ficheiros
        @param[in] const string &s - O nome do elemento a remover
        @param[in] int Tipo - variável para indicar o tipo de elemento a pesquisar("DIR" para diretoria, qualquer outra string para ficheiro)
        @return True se a remoção for bem sucedida
        */
		bool RemoverAll(const string &s, const string &tipo);

        /**
        @brief Exporta a diretoria atual para um ficheiro XML
        @param[in] const string &s - Nome do ficheiro onde a diretoria será exportada
        */
		void Escrever_XML(const string &s);

        /**
        @brief Carrega para memoria a diretoria presente num ficheiro XML
        @param[in] const string &s - Nome do ficheiro XML a ler
        @return True se a leitura for bem sucedida
        */
		bool Ler_XML(const string &s);

        /**
        @brief Move um ficheiro de uma diretoria para outra
        @param[in] const string &Fich - Nome do ficheiro a mover
        @param[in] const string &DirNova - Nome da diretoria de destino
        @return True se movido com sucesso
        */
		bool MoveFicheiro(const string &Fich, const string &DirNova);

        /**
        @brief Move uma diretoria completa para dentro de outra diretoria
        @param[in] const string &DirOld - Nome da diretoria a ser movida
        @param[in] const string &DirNew - Nome da diretoria de destino
        @return True se movido com sucesso
        */
		bool MoverDirectoria(const string &DirOld, const string &DirNew);

        /**
        @brief Obtém a data da última modificação de um determinado ficheiro
        @param[in] const string &ficheiro - Nome do ficheiro a consultar
        @return Ponteiro para string com a data de última modificação
        */
		string *DataFicheiro(const string &ficheiro);

        /**
        @brief Apresenta a árvore de ficheiros
        @param[in] const string *fich - Ponteiro para o nome do ficheiro on será escrita a árvore(.txt). Se NULL, imprime no ecrã.
        */
		void Tree(const string *fich = NULL);

        /**
        @brief Pesquisa todas as ocorrências de uma diretoria e guarda os path respetivos numa lista
        @param[in,out] list<string> &lres - Lista de strings onde os path serão armazenados
        @param[in] const string &dir - Nome da diretoria a pesquisar
        */
		void PesquisarAllDirectorias(list<string> &lres, const string &dir);

        /**
        @brief Pesquisa todas as ocorrências de um ficheiro e guarda os path respetivos numa lista
        @param[in,out] list<string> &lres - Lista de strings onde os path serão armazenados
        @param[in] const string &file - Nome do ficheiro a pesquisar
        */
		void PesquisarAllFicheiros(list<string> &lres, const string &file);

        /**
        @brief Renomeia todas as ocorrências de um ficheiro para um novo nome
        @param[in] const string &fich_old - Nome do ficheiro cujo nome queremos mudar
        @param[in] const string &fich_new - Novo nome a atribuir
        */
		void RenomearFicheiros(const string &fich_old, const string &fich_new);

        /**
        @brief Verifica se existem ficheiros com nomes repetidos na diretoria
        @return True se existirem duplicados, False caso contrário
        */
		bool FicheiroDuplicados();

        /**
        @brief Copia ficheiros de uma diretoria para outra com base num padrão introduzido pelo utilizador
        @param[in] const string &padrao - String com padrão a procurar no nome dos ficheiros
        @param[in] const string &DirOrigem - Diretoria onde estão os ficheiros
        @param[in] const string &DirDestino - Diretoria para onde vão os ficheiros
        @return True se a cópia for bem sucedida
        */
		bool CopyBatch(const string &padrao, const string &DirOrigem, const string &DirDestino);
	protected:
};

#endif
