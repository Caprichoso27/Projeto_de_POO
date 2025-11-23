#ifndef DIRETORIA_H
#define DIRETORIA_H

#include <fstream>
#include <sstream>
#include<iostream> //uintmax_t
#include<string>
#include<list>
#include<filesystem>
#include<algorithm>

#include"Elemento.h"

using namespace std;

class Diretoria : public Elemento
{
    list<Elemento *> LF;

    public:
        Diretoria(const string &path);
        virtual ~Diretoria();

        void AddList(Elemento *el);
        void Mostrar(int nivel);
        void Cont(int &diretorias, int &files);
        //string *GetPathDir();
        void *Get(const string &campo);
        void ContDiretoria(Diretoria *&maior, Diretoria *&menor);
        int GetSize();
        void Mem_total(size_t &bytes_totais);
        void BigFile(Ficheiro *&file);
        void BigDirectory(Diretoria *&dir);
        Elemento *Pesquisar(const string &s, int Tipo);
        bool RemoverAll2(const string &tipo);
        bool RemoverAll3(const string &tipo);
        bool MoveFile(const string &Fich, const string &DirNova);
        bool MoveDir(const string &DirOld, const string &DirNew);
    protected:
        //Diretoria *Pesquisa_Dir_Ant(const string &s, int tipo);

};

#endif // DIRETORIA_H
