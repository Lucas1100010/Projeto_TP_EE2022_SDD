#ifndef FERRAMENTASD_H
#define FERRAMENTASD_H

#include <map>
#include <QString>
#include "doenca.h"

class FerramentasD
{
public:
    FerramentasD();
    std::map<int,Doenca> listaDoencas;
    std::set<QString> sintomasD;//é utilizada temporariamente
    std::set<QString> sintomasD_compartilhavel;
    void carregarListaCSVDoencas();
    void carregarListaSintomasDoenca(int id);
};

#endif // FERRAMENTASD_H
