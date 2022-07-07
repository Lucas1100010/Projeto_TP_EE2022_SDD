#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <limits>
#include <QString>
#include <QDate>
#include <iostream>
#include <QMessageBox>
#include <QBrush>
#include <vector>
#include "paciente.h"
#include "doenca.h"
#include <fstream>
#include <QDir>
#include <map>
#include <set>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    std::ifstream inicializarConfig("config_inicializar.txt");
    if( inicializarConfig.is_open() ){
        std::string temp;
        bool inicializarP = 0;
        bool inicializarD = 0;
        std::getline(inicializarConfig,temp,' ');
        inicializarConfig >> inicializarP;
        std::getline(inicializarConfig,temp,' ');
        inicializarConfig >> inicializarD;
        std::cout << inicializarP << " " << inicializarD << std::endl;
        ui->checkBox_carregarPacientesIniciar->setChecked(inicializarP);
        ui->checkBox_carregarDoencasIniciar->setChecked(inicializarD);
        inicializarConfig.close();
    }else{
        QMessageBox::warning(this,"Inicializar","Não foi possivel encontrar o arquivo\nde inicialização");
    }
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

    if(ui->checkBox_carregarDoencasIniciar->isChecked()){
        this->ferramentas->ferramentas_d->carregarListaCSVDoencas();
        for( QString s : this->ferramentas->ferramentas_d->sintomasD_compartilhavel ){
            std::cout << s.toStdString() << std::endl;
            ui->listWidget_sintomasPossiveis->addItem(s);

        }
    }




    //verificar presença de um arquivo CSV contendo a lista de pacientes, se existir, carregar a lista map com os objetos
    //pasta pacientes que contera a lista de pacientes, dentro da pasta, outra pasta com nome sintomas, contera arquivos CSV
    //nomeadas com o nome do paciente, e contera os sintomas relacionados
    //QString nome, int idade, char sexo, float peso, QString tipoSanguineo, std::vector<QString> sintomas

    //########
    if(ui->checkBox_carregarPacientesIniciar->isChecked()){
        this->ferramentas->ferramentas_p->carregarListaCSVPacientes();

//        std::cout << "OK \n";
    }
    //########





}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_cadastrarPaciente_clicked()
{
    //GERAR ID
    //verificar se ja existe algo na lista de pacientes na memoria
    //pegar o tamanho da lista +1 e definir como id do objeto
    int id = this->ferramentas->ferramentas_p->listaPacientes.size() +1 ;

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
            int idade = ui->comboBox_idadePaciente->itemText( ui->comboBox_idadePaciente->currentIndex() ).toInt();
            QString sex = ui->comboBox_Sexo->itemText( ui->comboBox_Sexo->currentIndex() );
            float peso = ui->doubleSpinBox_pesoPaciente->value();
            QString sangue = ui->comboBox_tipoSanguineo->itemText( ui->comboBox_tipoSanguineo->currentIndex() );
            std::set<QString> sintomas;//puxar dados do listwidget

            for(int val = 0; val < ui->listWidget_sintomasPaciente->count() ; val ++ ){
                sintomas.insert(ui->listWidget_sintomasPaciente->item(val)->text());
            }


            //Paciente(QString nome, int idade, char sexo, float peso, QString tipoSanguineo, std::vector<QString> sintomas);
            Paciente p(id,n,idade,sex,peso,sangue,sintomas);

            std::cout << id << " ";
            std::cout << n.toStdString() << " ";
            std::cout << idade << " ";
            std::cout << sex.toStdString() << " ";
            std::cout << peso << " ";
            std::cout << sangue.toStdString() << std::endl;

            this->ferramentas->ferramentas_p->listaPacientes.insert(std::pair<int,Paciente>(id,p));
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
        if( this->ferramentas->ferramentas_p->listaPacientes.size() > 0){

            //antes de adicionar pacientes, verificar se ele ja esta na lista
            for( std::pair<int,Paciente> p: this->ferramentas->ferramentas_p->listaPacientes ){//o que tem dentro da listaPacientes sao objetos Pacientes
                if( this->nomesP_2.insert( p.second.getNome()).second ){
                    ui->comboBox_listaPacientes->addItem(p.second.getNome());//recebe QString como argumento

                    std::cout << p.first << std::endl;
                }


            }

        }
    }
    else if( index == 2){

        int i = 0;
        ui->tableWidget_ResumoGeral->clearContents();
        for( const auto &[id, p] : this->ferramentas->ferramentas_p->listaPacientes   ){

            this->ferramentas->correlacionar(id);

            if( i >= ui->tableWidget_ResumoGeral->rowCount() ){
                ui->tableWidget_ResumoGeral->insertRow(i);
            }
            // nome idade sexo peso doenca
            ui->tableWidget_ResumoGeral->setItem(i,0, new QTableWidgetItem(p.getNome() ) );
            ui->tableWidget_ResumoGeral->setItem(i,1, new QTableWidgetItem( QString::number( p.getIdade() ) ) );
            ui->tableWidget_ResumoGeral->setItem(i,2, new QTableWidgetItem(p.getSexo()) );
            ui->tableWidget_ResumoGeral->setItem(i,3, new QTableWidgetItem( QString::number( p.getPeso() )) );
            ui->tableWidget_ResumoGeral->setItem(i,4, new QTableWidgetItem(this->ferramentas->listaParaResumoGeral[p.getNome()] ));
            i++;
        }


    }
}

Ferramentas *MainWindow::getFerramentas() const
{
    return ferramentas;
}


void MainWindow::on_comboBox_listaPacientes_activated(int index)
{
    ui->lineEdit_idadePaciente->setText( QString::number(this->ferramentas->ferramentas_p->listaPacientes[index+1].getIdade()) );
    ui->lineEdit_sexoPaciente->setText( this->ferramentas->ferramentas_p->listaPacientes[index+1].getSexo() );
    ui->lineEdit_peso->setText( QString::number(this->ferramentas->ferramentas_p->listaPacientes[index+1].getPeso()) );
    ui->lineEdit_tipoS->setText( this->ferramentas->ferramentas_p->listaPacientes[index+1].getTipoSanguineo() );

}


void MainWindow::on_pushButton_adicionarSintomaAList_clicked()
{
    QString sintoma = ui->lineEdit_sintomaInsert_C->text();

    if( ui->listWidget_sintomaCadastro->findItems( sintoma , Qt::MatchFlag::MatchExactly ).size() < 1 && sintoma.size() > 2){
        std::cout << " ok " << std::endl;
        ui->listWidget_sintomaCadastro->addItem( sintoma );
    }else{
        QMessageBox::warning(this,"Cadastro Doença","O sintoma tem menos de 3 caracteres/nou o sintoma já esta cadastrado.");
    }

}


void MainWindow::on_listWidget_sintomaCadastro_itemDoubleClicked(QListWidgetItem *item)
{
    ui->listWidget_sintomaCadastro->takeItem( ui->listWidget_sintomaCadastro->currentRow() );
}


void MainWindow::on_pushButton_salvarDadosDoenca_clicked()
{

    //atualizar lista de sintomas cadastrados

    int id;
    QString nome_doenca = ui->lineEdit_nomeDoenca_C->text();
    QString causador = ui->comboBox_causadorDoenca_C->currentText();
    std::set<QString> lista_Doencas;

    id = this->ferramentas->ferramentas_d->listaDoencas.size() + 1;
    std::cout << nome_doenca.toStdString() << " " << nome_doenca.size() << std::endl;
    if( this->ferramentas->nomesD.insert( nome_doenca ).second and nome_doenca.size() > 1){

        for( int u = 0 ; u < ui->listWidget_sintomaCadastro->count() ; u ++){
           //sintomas.insert(ui->listWidget_sintomasPaciente->item(val)->text());
            lista_Doencas.insert( ui->listWidget_sintomaCadastro->item(u)->text() );
            if( this->ferramentas->ferramentas_d->sintomasD_compartilhavel.insert( ui->listWidget_sintomaCadastro->item(u)->text() ).second ){
                ui->listWidget_sintomasPossiveis->addItem( ui->listWidget_sintomaCadastro->item(u)->text() );
            }else{
                QMessageBox::warning(this,"Cadastro Doenças","Sintoma já cadastrado.");
            }

        }

        Doenca d(id,nome_doenca, causador, lista_Doencas);

        this->ferramentas->ferramentas_d->listaDoencas[id] = d;
        QMessageBox::warning(this,"Cadastro Doenças","Cadastro concluido.");
    }else{
        QMessageBox::warning(this,"Cadastro Doenças","Nome tem menos de 2 caracteres\n ou doença já está cadastrada.");
    }

}


void MainWindow::on_pushButton_SalvarPacientesCSV_clicked()
{
    if( this->ferramentas->salvarCSV(1) ){
        QMessageBox::warning(this,"Salvar dados", "Dados salvos com sucesso.");
    }else{
        QMessageBox::warning(this,"Salvar dados", "Ocorreu algum erro.");
    }

}


void MainWindow::on_pushButton_SalvarDoencasCSV_clicked()
{
    if( this->ferramentas->salvarCSV(0) ){
        QMessageBox::warning(this,"Salvar dados", "Dados salvos com sucesso.");
    }else{
        QMessageBox::warning(this,"Salvar dados", "Ocorreu algum erro.");
    }
}


void MainWindow::on_pushButton_CarregarPacientesCSV_clicked()
{
    this->ferramentas->ferramentas_p->carregarListaCSVPacientes();
    QMessageBox::warning(this,"Carregar dados", "Ok.");
}


void MainWindow::on_pushButton_CarregarDoencasCSV_clicked()
{
    this->ferramentas->ferramentas_d->carregarListaCSVDoencas();
    QMessageBox::warning(this,"Carregar dados", "Ok.");
}


void MainWindow::on_pushButton_carregar_tab_paciente_clicked()
{
//    std::cout << "Para correlacionar\n";
    int index = ui->comboBox_listaPacientes->currentIndex();
    this->ferramentas->correlacionar(index+1);
    QString nome = this->ferramentas->ferramentas_p->listaPacientes[index+1].getNome();
    std::cout << nome.toStdString() << std::endl;
    int i = 0;

    ui->tableWidget_pacienteXdoenca->clearContents();

    std::map<QString,float> doencas = this->ferramentas->pacienteXdoencas[ nome ];

    std::cout <<"\n objeto criado ";

    for( const auto &d : doencas){

        if(i >= ui->tableWidget_pacienteXdoenca->rowCount() ){
            ui->tableWidget_pacienteXdoenca->insertRow( i );
        }
       std::cout << d.first.toStdString() << " " << d.second << "\n";
       ui->tableWidget_pacienteXdoenca->setItem(i, 0, new QTableWidgetItem(d.first) );
       ui->tableWidget_pacienteXdoenca->setItem(i, 1, new QTableWidgetItem(QString::number(d.second) + "%" ) );
       i++;
    }
}


void MainWindow::on_pushButton_entrar_clicked()
{
    QString usuario = ui->lineEdit_login->text();
    QString senha =ui->lineEdit_senha->text();
    std::string tempU;
    std::string tempS;
    std::ifstream dadosLogin("dados/login/login.csv");

    bool ok = 0;

    if(dadosLogin.is_open()){
        while(std::getline(dadosLogin,tempU,',')){
            std::getline(dadosLogin,tempS);
            if(usuario == QString::fromStdString(tempU) and senha == QString::fromStdString(tempS)){
                ok = 1;
            }
        }

        if(ok){
            ui->tabPaciente->setEnabled(1);
            ui->tabCadastroPaciente->setEnabled(1);
            ui->tabCadastroDoenca->setEnabled(1);
            ui->tabCarregarSalvar->setEnabled(1);
            ui->tabResultados->setEnabled(1);
        }else{
            QMessageBox::warning(this,"Login","Usuário ou senha inválido");
        }

    }else{
        QMessageBox::warning(this, "Login","Arquivo de login inexistente.");

    }


}


void MainWindow::on_checkBox_carregarPacientesIniciar_stateChanged(int arg1)
{
    std::ofstream inicializarConfig("config_inicializar.txt");
    if(inicializarConfig.is_open()){
//        CARREGAR_PACIENTES_AO_INICIAR 1
//        CARREGAR_DOENCAS_AO_INICIAR 1
        std::string dados1 = "CARREGAR_PACIENTES_AO_INICIAR 1\nCARREGAR_DOENCAS_AO_INICIAR 1";
        std::string dados2 = "CARREGAR_PACIENTES_AO_INICIAR 1\nCARREGAR_DOENCAS_AO_INICIAR 0";
        std::string dados3 = "CARREGAR_PACIENTES_AO_INICIAR 0\nCARREGAR_DOENCAS_AO_INICIAR 0";
        if(arg1 == 2 and ui->checkBox_carregarDoencasIniciar->isCheckable()){
            inicializarConfig << dados1;
        }else if(arg1 == 2 and not ui->checkBox_carregarDoencasIniciar->isCheckable()){
            inicializarConfig << dados2;
        }else{
            inicializarConfig << dados3;
        }
        inicializarConfig.close();
    }
//    std::cout << arg1 << std::endl;

}

