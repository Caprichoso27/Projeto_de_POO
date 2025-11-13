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
        void Mostrar();
        void Cont(int &diretorias, int &files);
        string *GetPathDir();
        void ContDiretoria(Diretoria *&maior, Diretoria *&menor);

    protected:

};

#endif // DIRETORIA_H
