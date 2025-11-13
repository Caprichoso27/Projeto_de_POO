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

class Elemento
{

    protected:
    string Nome;
    string path;

    public:
        Elemento(const string &path);
        virtual ~Elemento();

        virtual void Mostrar(); //virtual para que seja dependente dos filhos, se os filhos tiverem uma funcao com o mesmo nome sera executada a funcao dos filhos, fazendo assim a diferenciacao entre files e diretorios
        virtual void Cont(int &diretorias, int &files);
        virtual void ContDiretoria(Diretoria *&maior, Diretoria *&menor);

};

#endif // ELEMENTO_H
