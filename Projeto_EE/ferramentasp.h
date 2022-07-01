#ifndef FERRAMENTASP_H
#define FERRAMENTASP_H

#include "ferramentas.h"
#include "paciente.h"

class FerramentasP : public Ferramentas
{

private:

public:
    FerramentasP();
    std::map<int,Paciente> listaPacientes;
    std::set<QString> sintomasP;
    void carregarListaCSVPacientes();
    void carregarListaSintomasPaciente(int id);
};

#endif // FERRAMENTASP_H
