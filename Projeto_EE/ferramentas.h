#ifndef FERRAMENTAS_H
#define FERRAMENTAS_H
#include <iostream>
#include <map>
#include "paciente.h"
#include "ferramentasp.h"
#include "doenca.h"
#include "ferramentasd.h"
#include <set>
#include <QString>

class Ferramentas
{

    //a classe ferramentas gerencia os dados que entram e saem, alem de gerar dados informativos
private:
    //essa lista precisa ser repassada para mainwindow, pois
    //ela so existira enquanto o objeto Ferramentas existir

    //std::map<int,Doencas> listaDoencas;
public:
    Ferramentas();
    FerramentasP *ferramentas_p = new FerramentasP();
    FerramentasD *ferramentas_d = new FerramentasD();
    std::map<QString, std::map<QString, float> > pacienteXdoencas;
    std::set<QString> nomesD;
    bool salvarCSV(bool m);
    void correlacionar(int id);
    std::map<QString , QString> listaParaResumoGeral;
};

#endif // FERRAMENTAS_H
