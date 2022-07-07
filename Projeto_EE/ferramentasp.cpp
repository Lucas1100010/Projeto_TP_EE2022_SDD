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
    //std::set<QString> sintomas;//guardando copias?

    std::ifstream dadosPacientesCsv("dados\\Pacientes\\Pacientes.csv");
    if(dadosPacientesCsv.is_open()){

//        std::cout << "OK \n";
        while(std::getline(dadosPacientesCsv,temp,',')){
            idPaciente = std::stoi(temp);
//            std::cout << temp << ", ";
//            std::getchar();

            std::getline(dadosPacientesCsv,temp,',');
            nomePaciente = QString::fromStdString(temp);
//            std::cout << temp << ", ";
//            std::getchar();

            std::getline(dadosPacientesCsv,temp,',');
            idade = std::stoi(temp);
//            std::cout << temp << ", ";
//            std::getchar();

            std::getline(dadosPacientesCsv,temp,',');
            sexo = QString::fromStdString(temp);
//            std::cout << temp << ", ";
//            std::getchar();

            std::getline(dadosPacientesCsv,temp,',');
            peso = std::stof(temp);
//            std::cout << temp << ", ";
//            std::getchar();

            std::getline(dadosPacientesCsv,temp);
            tipoS = QString::fromStdString(temp);
//            std::cout << temp << std::endl;


//            std::cout << " carregando lista de sintomas \n";
            //carregar lista de sintomas para o paciente
            this->carregarListaSintomasPaciente(idPaciente);

//            std::cout << " gerando objeto paciente \n";
            //criar objeto paciente
            Paciente p(idPaciente,nomePaciente,idade,sexo,peso,tipoS,this->sintomasP);
            //adicionar seu endereço ao map
            this->listaPacientes[idPaciente] = p;
            this->sintomasP.clear();


        }
        dadosPacientesCsv.close();
    }


}
void FerramentasP::carregarListaSintomasPaciente(int id){
//    std::cout << " sintomas \n";
    std::string sintoma;
    std::ifstream dadosPacientesSintomasCsv("dados\\Pacientes\\Sintomas\\"+std::to_string(id)+".csv");
    if(dadosPacientesSintomasCsv.is_open() ){
        while (std::getline(dadosPacientesSintomasCsv,sintoma) ) {
            this->sintomasP.insert(QString::fromStdString(sintoma));
        }
        dadosPacientesSintomasCsv.close();
    }

}
