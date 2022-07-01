#ifndef FERRAMENTAS_H
#define FERRAMENTAS_H
#include <iostream>
#include <map>
#include "paciente.h"

class Ferramentas
{

    //a classe ferramentas gerencia os dados que entram e saem, alem de gerar dados informativos
private:
    //essa lista precisa ser repassada para mainwindow, pois
    //ela so existira enquanto o objeto Ferramentas existir

    //std::map<int,Doencas> listaDoencas;
public:
    Ferramentas();
    int gerarID_listaMAPAtual();
    int gerarID_listaSETAtual();
};

#endif // FERRAMENTAS_H
