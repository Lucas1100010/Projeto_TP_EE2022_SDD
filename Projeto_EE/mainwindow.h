#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QListWidget>
#include <QMainWindow>
#include <paciente.h>
#include <vector>
#include "ferramentasp.h"
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

    FerramentasP *getFerramentas_p() const;

private slots:
    void on_listWidget_Ajuda_itemClicked(QListWidgetItem *item);

    void on_pushButton_cadastrarPaciente_clicked();

    void on_listWidget_sintomasPossiveis_itemDoubleClicked(QListWidgetItem *item);

    void on_listWidget_sintomasPaciente_itemDoubleClicked(QListWidgetItem *item);

    void on_tabGeral_tabBarClicked(int index);

private:
    Ui::MainWindow *ui;
    FerramentasP *ferramentas_p = new FerramentasP();
    std::set<QString> nomesP;//para controlar nomes repetidos
    //std::vector<Paciente> listaPacientes;
    //std::map<int,Paciente> lista_Pacientes;
};
#endif // MAINWINDOW_H
