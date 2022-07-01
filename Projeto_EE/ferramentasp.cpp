#include "ferramentasp.h"
#include <QString>
#include <set>
#include <fstream>
#include "paciente.h"
#include <QDir>
#include <iostream>



FerramentasP::FerramentasP()
{

}
void FerramentasP::carregarListaCSVPacientes(){
    int idPaciente;
    std::string temp;
    QString nomePaciente;
    int idade;
    QString sexo;
    float peso;
    QString tipoS;
    std::set<QString> sintomas;//guardando copias?

    std::ifstream dadosPacientesCsv(QDir::currentPath().toStdString()+"dados/Pacientes/Pacientes.csv");
    if(dadosPacientesCsv.is_open()){
        while(dadosPacientesCsv >> idPaciente){
            std::getline(dadosPacientesCsv,temp,',');
            nomePaciente = QString::fromStdString(temp);
            dadosPacientesCsv >> idade;
            std::getline(dadosPacientesCsv,temp,',');
            sexo = QString::fromStdString(temp);
            dadosPacientesCsv >> peso;
            dadosPacientesCsv >> temp;
            tipoS = QString::fromStdString(temp);

            //carregar lista de sintomas para o paciente
            this->carregarListaSintomasPaciente(idPaciente);

            //criar objeto paciente
            Paciente p(idPaciente,nomePaciente,idade,sexo,peso,tipoS,this->sintomasP);
            //adicionar seu endereço ao map
            this->listaPacientes[idPaciente] = p;
            this->sintomasP.clear();


        }
    }
}
void FerramentasP::carregarListaSintomasPaciente(int id){
    std::string sintoma;
    std::ifstream dadosPacientesSintomasCsv(QDir::currentPath().toStdString()+"dados/Pacientes/Sintomas/"+std::to_string(id));
    if(dadosPacientesSintomasCsv.is_open() ){
        while (std::getline(dadosPacientesSintomasCsv,sintoma) ) {
            this->sintomasP.insert(QString::fromStdString(sintoma));
        }
    }
}
