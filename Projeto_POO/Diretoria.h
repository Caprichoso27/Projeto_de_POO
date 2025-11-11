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
        Diretoria(const fs::path &path);
        virtual ~Diretoria();

        void AddList(Elemento *el);
        void Mostrar();
        void Cont(int &diretorias, int &files);
    protected:

    private:
};

#endif // DIRETORIA_H
