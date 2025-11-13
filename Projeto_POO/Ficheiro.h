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

class Ficheiro : public Elemento
{
    string extensao;

    public:
        Ficheiro(const string &path);
        virtual ~Ficheiro();

        void Mostrar();
        void Cont(int &diretorias, int &files);
    protected:

    private:
};

#endif // FICHEIRO_H
