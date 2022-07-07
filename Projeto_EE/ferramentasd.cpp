#include "ferramentasd.h"
#include <set>
#include <QString>
#include <fstream>
#include <iostream>
#include "doenca.h"


FerramentasD::FerramentasD()
{

}
void FerramentasD::carregarListaCSVDoencas(){

    int id;
    QString nomeDoenca;
    QString causador;
    //std::set<QString> sintomas;
    std::string temp;

    std::ifstream dadosDoencasCsv("dados\\Doencas\\Doencas.csv");
    if(dadosDoencasCsv.is_open()){
        while ( std::getline(dadosDoencasCsv, temp, ',') ) {
            id = stoi(temp);

            std::getline(dadosDoencasCsv, temp, ',');
            nomeDoenca = QString::fromStdString(temp);

            std::getline(dadosDoencasCsv, temp);
            causador = QString::fromStdString(temp);

            //gerar lista de sintomas
            this->carregarListaSintomasDoenca(id);

            //gerar objeto
            Doenca d(id,nomeDoenca,causador,this->sintomasD);

            this->listaDoencas[id] = d;
            this->sintomasD.clear();



        }
        dadosDoencasCsv.close();
    }

}
void FerramentasD::carregarListaSintomasDoenca(int id){
//    std::cout << " sintomas \n";
    std::string sintoma;
    std::ifstream dadosDoencasSintomasCsv("dados\\Doencas\\Sintomas\\"+std::to_string(id)+".csv");
    if(dadosDoencasSintomasCsv.is_open() ){
        while (std::getline(dadosDoencasSintomasCsv,sintoma) ) {
            this->sintomasD.insert(QString::fromStdString(sintoma));
            this->sintomasD_compartilhavel.insert(QString::fromStdString(sintoma));
        }
        dadosDoencasSintomasCsv.close();
    }
}
