#ifndef DIRETORIA_H
#define DIRETORIA_H

#include <fstream>
#include <sstream>
#include<iostream> //uintmax_t
#include<string>
#include<list>

#include"Elemento.h"

using namespace std;

class Diretoria : public Elemento
{
    list<Elemento *> LF;

    public:
        Diretoria(const string &path);
        virtual ~Diretoria();

        void AddList(Elemento *el);
        void Mostrar(int nivel, string linha, int &ult);
        void Cont(int &diretorias, int &files);
        string *GetPathDir();
        void ContDiretoria(Diretoria *&maior, Diretoria *&menor);
        int GetSize();
        void Mem_total(size_t &bytes_totais);
        void BigFile(Ficheiro *&file);
        void BigDirectory(Diretoria *&dir);
        string *Pesquisar(const string &s, int Tipo);
    protected:

};

#endif // DIRETORIA_H
