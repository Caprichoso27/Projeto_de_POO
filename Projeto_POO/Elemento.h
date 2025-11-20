#ifndef ELEMENTO_H
#define ELEMENTO_H

#include<filesystem>
#include <fstream>
#include <sstream>
#include<iostream> //uintmax_t
#include<string>

using namespace std;
namespace fs = std::filesystem;

class Diretoria;
class Ficheiro;

class Elemento
{

    protected:
    string Nome;
    string path;

    public:
        Elemento(const string &path);
        virtual ~Elemento();

        virtual void Mostrar(int nivel); //virtual para que seja dependente dos filhos, se os filhos tiverem uma funcao com o mesmo nome sera executada a funcao dos filhos, fazendo assim a diferenciacao entre files e diretorios
        virtual void Cont(int &diretorias, int &files);
        virtual void ContDiretoria(Diretoria *&maior, Diretoria *&menor);
        virtual int GetSize();
        virtual void *Get(const string &campo);
        string *GetPath();
        virtual void Mem_total(size_t &bytes_totais);
        virtual void BigFile(Ficheiro *&file);
        virtual void BigDirectory(Diretoria *&dir);
        virtual Elemento *Pesquisar(const string &s, int Tipo);
        virtual bool RemoverAll3(const string &tipo);

};

#endif // ELEMENTO_H
