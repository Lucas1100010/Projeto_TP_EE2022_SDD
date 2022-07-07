#ifndef FERRAMENTASP_H
#define FERRAMENTASP_H

#include <map>
#include "paciente.h"

class FerramentasP
{

private:

public:
    FerramentasP();
    std::map<int,Paciente> listaPacientes;
    std::set<QString> sintomasP;//é utilizada temporariamente
    void carregarListaCSVPacientes();
    void carregarListaSintomasPaciente(int id);
};

#endif // FERRAMENTASP_H
