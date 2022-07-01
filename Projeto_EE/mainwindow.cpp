#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <limits>
#include <QString>
#include <QDate>
#include <iostream>
#include <QMessageBox>
#include <QBrush>
#include <vector>
#include <paciente.h>
#include <fstream>
#include <QDir>
#include <map>
#include <iostream>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //Este FOR adiciona valores ao comboBox que guarda as idades aceitaveis
    for(int i = 1; i <= 100; i++){
        ui->comboBox_idadePaciente->addItem(QString::number(i));//a função addItem aceita apenas QChar ou QString como argumento
                                                                //entao "QString::number(i)" converte o inteiro em objeto QString
                                                                //nome da funcao é number, namespace QString
    }

    //automaticamente define data de cadastro para a data atual
    ui->dateEdit_dataCadastro->minimumDate() = QDate::currentDate();
    ui->dateEdit_dataCadastro->setDate(QDate::currentDate());
    //carregar lista de sintomas cadastrados

    //verificar presença de um arquivo CSV contendo a lista de pacientes, se existir, carregar a lista map com os objetos
    //pasta pacientes que contera a lista de pacientes, dentro da pasta, outra pasta com nome sintomas, contera arquivos CSV
    //nomeadas com o nome do paciente, e contera os sintomas relacionados
    //QString nome, int idade, char sexo, float peso, QString tipoSanguineo, std::vector<QString> sintomas

    //########
    if(ui->checkBox_carregarPacientesIniciar->isChecked()){
        this->ferramentas_p->carregarListaCSVPacientes();
    }
    //########





}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_listWidget_Ajuda_itemClicked(QListWidgetItem *item)
{
    QString nomeItem = item->text();
    if(nomeItem == "Login"){

    }
}


void MainWindow::on_pushButton_cadastrarPaciente_clicked()
{
    //GERAR ID
    //verificar se ja existe algo na lista de pacientes na memoria
    //pegar o tamanho da lista +1 e definir como id do objeto
    int id = this->ferramentas_p->listaPacientes.size() +1 ;

    //validar dados do form
    bool nome_c = 1;
    bool nSintomas_p = 1;
    if ( ui->lineEdit_nomeCompleto->text().size() < 8 ) nome_c = 0;
    if ( ui->listWidget_sintomasPaciente->count() < 1 ) nSintomas_p = 0;

    if(!nome_c && !nSintomas_p) QMessageBox::warning(this,"Cadastro de paciente","Nome e sintoma inválido, insira no minimo 8 caracteres\nno nome e no minimo um sintoma.");
    else if(!nome_c) QMessageBox::warning(this,"Cadastro de paciente","Nome inválido, insira no minimo 8 caracteres.");
    else if(!nSintomas_p) QMessageBox::warning(this,"Cadastro de paciente","Sintoma inválido, insira no minimo um sintoma.");


    else if(nome_c and nSintomas_p){


        QString n = ui->lineEdit_nomeCompleto->text();

        if(this->nomesP.count(n) == 0){
            this->nomesP.insert(n);
            int idade = ui->comboBox_idadePaciente->itemData( ui->comboBox_idadePaciente->currentIndex() ).toInt();
            QString sex = ui->comboBox_Sexo->itemData( ui->comboBox_Sexo->currentIndex() ).toString();
            float peso = ui->doubleSpinBox_pesoPaciente->decimals();
            QString sangue = ui->comboBox_tipoSanguineo->itemData( ui->comboBox_tipoSanguineo->currentIndex() ).toString();
            std::set<QString> sintomas;//puxar dados do listwidget

            for(int val = 0; val < ui->listWidget_sintomasPaciente->count() ; val ++ ){
                sintomas.insert(ui->listWidget_sintomasPaciente->item(val)->text());
            }


            //Paciente(QString nome, int idade, char sexo, float peso, QString tipoSanguineo, std::vector<QString> sintomas);
            Paciente p(id,n,idade,sex,peso,sangue,sintomas);

            this->getFerramentas_p()->listaPacientes.insert(std::pair<int,Paciente>(id,p));
            QMessageBox::information(this,"Cadastro de paciente","Paciente cadastrado. id: "+QString::fromStdString(std::to_string(id)));
        }
        else{
            QMessageBox::warning(this,"Cadastro de paciente","Esse nome já existe.");
        }

    }

}


void MainWindow::on_listWidget_sintomasPossiveis_itemDoubleClicked(QListWidgetItem *item)
{
    if ( ui->listWidget_sintomasPaciente->findItems( item->text(), Qt::MatchFlag::MatchExactly ).size() < 1){
        ui->listWidget_sintomasPaciente->addItem(item->text());
    }
    //ui->listWidget_sintomasPaciente->findItems( item->text(), Qt::MatchFlag::MatchExactly ).size()
    //findItems retorna um QList<QListWidgetItem *> por esse motivo utilizo .size(), caso o item procurado esteja na lista entao ela tera 1 item
    //Qt::MatchFlag::MatchExactly  flag especifica para a funcao findItems, so adiciona o item procurado a QList retornada por findItems caso o Match seja identico

}


void MainWindow::on_listWidget_sintomasPaciente_itemDoubleClicked(QListWidgetItem *item)
{
    ui->listWidget_sintomasPaciente->takeItem( ui->listWidget_sintomasPaciente->currentRow() );
}


void MainWindow::on_tabGeral_tabBarClicked(int index)
{
    if(index == 1){
        //tabPaciente
        //chamar funcao atualizar lista da tab paciente

        //verificar se o vector q contem os pacientes tem um tamanho maior que 0
        if( this->ferramentas_p->listaPacientes.size() > 0){

            //antes de adicionar pacientes, verificar se ele ja esta na lista
            for(std::pair<int,Paciente> p: this->ferramentas_p->listaPacientes){//o que tem dentro da listaPacientes sao objetos Pacientes
                ui->comboBox_listaPacientes->addItem(p.second.getNome());//recebe QString como argumento
            }

        }
    }
}

FerramentasP *MainWindow::getFerramentas_p() const
{
    return ferramentas_p;
}


