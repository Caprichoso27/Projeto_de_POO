#ifndef ELEMENTO_H
#define ELEMENTO_H

#include<filesystem>
#include <fstream>
#include <sstream>
#include<iostream> //uintmax_t
#include<string>

using namespace std;
namespace fs = std::filesystem;

class Elemento
{
    protected:
    string Nome;
    fs::path path;

    public:
        Elemento(const fs::path &path);
        virtual ~Elemento();

        virtual void Mostrar(); //virtual para que seja dependente dos filhos, se os filhos tiverem uma funcao com o mesmo nome sera executada a funcao dos filhos, fazendo assim a diferenciacao entre files e diretorios
        virtual void Cont(int &diretorias, int &files);
};

#endif // ELEMENTO_H
