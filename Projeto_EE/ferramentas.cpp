#include "ferramentas.h"
#include <iostream>
#include <QString>
#include <fstream>
#include <QDir>
#include <map>
#include "paciente.h"
#include <set>
#include <fstream>
#include "doenca.h"

Ferramentas::Ferramentas()
{

}

void Ferramentas::correlacionar(int id){
    std::cout << "Correlacionar\n";
    Paciente paciente = this->ferramentas_p->listaPacientes[id];
    float ptemp = 0;

    std::cout << paciente.getNome().toStdString() << " ";
    for( QString doe : paciente.getSintomas() ){
        std::cout << doe.toStdString() << " ";
    }
    std::cout << std::endl;

    for( std::pair<int, Doenca> d : this->ferramentas_d->listaDoencas ){

        Doenca doenca = d.second;
        std::map < QString, float> mapDoenca;
        float total = 0;
        int numero_sintomas = doenca.getSintomas().size();
//        std::cout << "tamanho da lista de sintomas da doenca " << doenca.getNomeDoenca().toStdString() << " é " << numero_sintomas << "\n";
        float percentual;

        for( QString sintoma : paciente.getSintomas() ){
            //std::cout << sintoma.toStdString() << " " << doenca.getSintomas().count( sintoma ) << std::endl;
            if( doenca.getSintomas().count( sintoma ) ){
                  std::cout << "tem " << sintoma.toStdString() << " " << doenca.getNomeDoenca().toStdString() << "\n";
                  total ++;
            }

        }
        percentual = (total/numero_sintomas) * 100.0;
//        std::cout << paciente.getNome().toStdString() << " " << doenca.getNomeDoenca().toStdString() << " " << percentual << std::endl;
//        mapDoenca[doenca.getNomeDoenca()] = percentual;
        this->pacienteXdoencas[paciente.getNome()][doenca.getNomeDoenca()]=percentual;
        if(percentual > ptemp){
            this->listaParaResumoGeral[paciente.getNome()] = doenca.getNomeDoenca();
        }

//        for( std::pair<QString, std::map<QString, float> > pp : this->pacienteXdoencas ){

//            std::cout << "NOME: " << pp.first.toStdString() << " \n ";

//            for( std::pair<QString, float> dd : pp.second){
//                std::cout << "NOME doenca:" <<  dd.first.toStdString() << ",- percentual " << dd.second << " \n";
//            }

//        }

    }

}


bool Ferramentas::salvarCSV(bool m){
    //se m = 1 -> salvar pacientes
    //se m = 0 -> salvar doencas

    //Não pode adicionar pacientes existentes

    if(m){
    //paciente
        QString nome;
        int idade;
        QString sexo;
        float peso;
        QString tipoSanguineo;
        std::set<QString> sintomas;
        int idPaciente;
        int linhas = 0;
        std::string temp;
        std::set<QString> listaTemporaria;
        bool aconteceuAlgo = 0;

        //abrir a lista de pacientes csv
        std::ifstream dadosCarregados("dados\\Pacientes\\Pacientes.csv");

        if( dadosCarregados.is_open() ){

            //contar numero de linhas
            //pegar cada nome e adicionar a um set
            while(std::getline(dadosCarregados,temp,',')) {
                std::getline(dadosCarregados,temp, ',');
                listaTemporaria.insert(QString::fromStdString(temp) );
                linhas ++;
                std::getline(dadosCarregados,temp);

            }
            dadosCarregados.close();
        }


        std::ofstream dadosCSVSalvar("dados\\Pacientes\\Pacientes.csv",std::ios::app);//se o arquivo nao existir, ele vai criar

        if( dadosCSVSalvar.is_open() ){

        //para cada objeto da lista de pacientes na memoria, adicionar ao set, e verificar o .second
        //se falso, nada acontece
        //se verdadeiro, adcione ao arquivo CSV
            if( this->ferramentas_p->listaPacientes.size() > 0 ){


                for( std::pair<int,Paciente> paciente : this->ferramentas_p->listaPacientes  ){

                    nome = paciente.second.getNome();
                    if( listaTemporaria.insert( nome ).second ){
                        aconteceuAlgo = 1;
                        idade = paciente.second.getIdade();
                        sexo = paciente.second.getSexo();
                        peso = paciente.second.getPeso();
                        tipoSanguineo = paciente.second.getTipoSanguineo();
                        sintomas = paciente.second.getSintomas();

                        //idPaciente = paciente.second.getIdPaciente();//substituir por linhas
                        idPaciente = linhas + 1;
                        std::cout << idPaciente << std::endl;

                        dadosCSVSalvar << idPaciente << "," << nome.toStdString() << "," << idade << ",";
                        dadosCSVSalvar << sexo.toStdString() << "," << peso << "," << tipoSanguineo.toStdString() << "\n";

                        //criar lista csv de sintomas relacionado ao id do paciente
                        std::ofstream sintomasCSV("dados\\Pacientes\\Sintomas\\" +std::to_string( idPaciente ) +".csv");
                        if( sintomasCSV.is_open() ){
                            for( QString s: sintomas ){
                                sintomasCSV << s.toStdString() << std::endl;
                            }
                            sintomasCSV.close();
                        }


                    }


                }

                dadosCSVSalvar.close();
                if(aconteceuAlgo == 0 ) return 0;
                return 1;
            }else{
                //exibir warning
                return 0;
            }


        }


    }else{
        //doenca
        int id;
        QString nomeDoenca;
        QString causador;
        std::set<QString> listaTemporaria;
        std::set<QString> sintomas;
        std::string temp;
        int linhas = 0;
        bool aconteceuAlgo = 0;

        //abrir a lista de pacientes csv
        std::ifstream dadosCarregados("dados\\Doencas\\Doencas.csv");

        if( dadosCarregados.is_open() ){

            //contar numero de linhas
            //pegar cada nome e adicionar a um set
            while(std::getline(dadosCarregados,temp,',')) {
                std::getline(dadosCarregados,temp, ',');
                listaTemporaria.insert(QString::fromStdString(temp) );
                linhas ++;
                std::getline(dadosCarregados,temp);

            }
            dadosCarregados.close();
        }

        std::ofstream dadosCSVSalvar("dados\\Doencas\\Doencas.csv",std::ios::app);

        if( dadosCSVSalvar.is_open() ){

            if( this->ferramentas_d->listaDoencas.size() > 0 ){

                for( std::pair<int,Doenca> doenca : this->ferramentas_d->listaDoencas){
                    nomeDoenca = doenca.second.getNomeDoenca();

                    if( listaTemporaria.insert( nomeDoenca ).second ){
                        aconteceuAlgo = 1;
                        id = linhas + 1;
                        causador = doenca.second.getCausador();
                        sintomas = doenca.second.getSintomas();

                        dadosCSVSalvar << id << "," << nomeDoenca.toStdString() << "," << causador.toStdString() << "\n";

                        //criar lista csv de sintomas relacionado ao id do paciente
                        std::ofstream sintomasCSV("dados\\Doencas\\Sintomas\\" +std::to_string( id ) +".csv");
                        if( sintomasCSV.is_open() ){
                            for( QString s: sintomas ){
                                sintomasCSV << s.toStdString() << std::endl;
                            }
                            sintomasCSV.close();
                        }



                    }


                }

            }
            dadosCSVSalvar.close();
            if(aconteceuAlgo == 0 ) return 0;
            return 1;
        }else{
            return 0;
        }



    }
}
