#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QListWidget>
#include <QMainWindow>
#include <paciente.h>
#include <vector>
#include "ferramentas.h"
#include <set>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    Ferramentas *getFerramentas() const;

private slots:

    void on_pushButton_cadastrarPaciente_clicked();

    void on_listWidget_sintomasPossiveis_itemDoubleClicked(QListWidgetItem *item);

    void on_listWidget_sintomasPaciente_itemDoubleClicked(QListWidgetItem *item);

    void on_tabGeral_tabBarClicked(int index);

    void on_comboBox_listaPacientes_activated(int index);

    void on_pushButton_adicionarSintomaAList_clicked();

    void on_listWidget_sintomaCadastro_itemDoubleClicked(QListWidgetItem *item);

    void on_pushButton_salvarDadosDoenca_clicked();

    void on_pushButton_SalvarPacientesCSV_clicked();

    void on_pushButton_SalvarDoencasCSV_clicked();

    void on_pushButton_CarregarPacientesCSV_clicked();

    void on_pushButton_CarregarDoencasCSV_clicked();

    void on_pushButton_carregar_tab_paciente_clicked();

    void on_pushButton_entrar_clicked();

    void on_checkBox_carregarPacientesIniciar_stateChanged(int arg1);

private:
    Ui::MainWindow *ui;
    Ferramentas *ferramentas = new Ferramentas();
    std::set<QString> nomesP;//para controlar nomes repetidos no form cadastro
    std::set<QString> nomesP_2;
    std::set<QString> sintomas;
    std::map<QString,int> pacientesControle;//vai relacionar paciente com id para a aba paciente
    //std::vector<Paciente> listaPacientes;
    //std::map<int,Paciente> lista_Pacientes;
};
#endif // MAINWINDOW_H
