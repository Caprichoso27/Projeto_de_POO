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

        void Mostrar(int nivel);
        void Cont(int &diretorias, int &files);
        int GetSize();
        void Mem_total(size_t &bytes_totais);
        void BigFile(Ficheiro *&file);
        Elemento *Pesquisar(const string &s, int Tipo);
        bool RemoverAll3(const string &tipo);
        void *Get(const string &campo);
    protected:

    private:
};

#endif // FICHEIRO_H
